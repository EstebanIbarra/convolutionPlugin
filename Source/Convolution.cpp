/*
  ==============================================================================

    Convolution.cpp
    Created: 7 May 2022 1:57:38pm
    Author:  eir

  ==============================================================================
*/

#include "Convolution.h"

Convolution::Convolution(){}
Convolution::~Convolution(){}

void Convolution::prepare(juce::dsp::ProcessSpec &spec)
{
//    Initializes juce Convolution
    juceConvolution.reset();
    juceConvolution.prepare(spec);

}

void Convolution::prepareInternalIR(juce::dsp::ProcessSpec &spec, juce::AudioProcessorValueTreeState &apvts)
{
    this->prepare(spec);
    
    int internalIRIndex = apvts.getRawParameterValue("INTERNAL_IR")->load();
    juceConvolution.loadImpulseResponse(
        binaryIRWav[internalIRIndex],
        binaryIRWavSize[internalIRIndex],
        juce::dsp::Convolution::Stereo::yes,
        juce::dsp::Convolution::Trim::yes,
        0,
        juce::dsp::Convolution::Normalise::yes
    );
}

void Convolution::prepareExternalIR(juce::dsp::ProcessSpec &spec)
{
    /* TODO: Copy file from drag and drop into TBD folder */
    
    //    Gets impulse path for user defined IRs
    juce::String impulsePath = juce::File::getSpecialLocation(juce::File::userApplicationDataDirectory).getFullPathName() + "/impulse.wav";
    impulseFile = juce::File(impulsePath);
    
    /* TODO: Find a way to get the numChannels from File */
    uint8_t irNumChannels = 1;
    
    //    Defines if IR is stereo and if requires trimming
    const juce::dsp::Convolution::Stereo isStereo = irNumChannels == 2 ? juce::dsp::Convolution::Stereo::yes : juce::dsp::Convolution::Stereo::no;
    const juce::dsp::Convolution::Trim requiresTrimming = juce::dsp::Convolution::Trim::yes;
    
    this->prepare(spec);
    
    //    Loads User defined IR
    juceConvolution.loadImpulseResponse(impulseFile.getFullPathName(), isStereo, requiresTrimming, impulseFile.getSize());
}

void Convolution::prepareBusIR(juce::dsp::ProcessSpec &spec)
{
    this->prepare(spec);
}

void Convolution::prepareManager(juce::dsp::ProcessSpec &spec, juce::AudioProcessorValueTreeState &apvts)
{
    int sourceIndex = apvts.getRawParameterValue("IR_SOURCE")->load();
    switch (sourceIndex) {
        case 0:
            this->prepareInternalIR(spec, apvts);
            break;
        case 1:
            this->prepareExternalIR(spec);
            break;
        case 2:
            this->prepareBusIR(spec);
        default:
            this->prepare(spec);
            break;
    }
}

void Convolution::process(juce::AudioBuffer<float> &inputBuffer, juce::AudioProcessorValueTreeState &apvts)
{
    juce::dsp::AudioBlock<float> audioBlock(inputBuffer);
    juce::dsp::ProcessContextReplacing<float> context(audioBlock);
    juceConvolution.process(context);
}
