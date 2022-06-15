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

void Convolution::prepare()
{
//    Initializes juce Convolution
    juceConvolution.reset();
    juceConvolution.prepare(referenceSpec);
    

}

void Convolution::prepareInternalIR(juce::AudioProcessorValueTreeState &apvts)
{
    this->prepare();
    
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

void Convolution::prepareExternalIR()
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
    
    this->prepare();
    
    //    Loads User defined IR
    juceConvolution.loadImpulseResponse(impulseFile.getFullPathName(), isStereo, requiresTrimming, impulseFile.getSize());
}

void Convolution::prepareBusIR(juce::AudioBuffer<float> &busBuffer)
{
    this->prepare();
    const juce::dsp::Convolution::Stereo isStereo = referenceSpec.numChannels == 2 ? juce::dsp::Convolution::Stereo::yes : juce::dsp::Convolution::Stereo::no;
    
    juceConvolution.loadImpulseResponse(std::move(busBuffer), referenceSpec.sampleRate, isStereo, juce::dsp::Convolution::Trim::yes, juce::dsp::Convolution::Normalise::no);
}

void Convolution::prepareManager(juce::dsp::ProcessSpec &spec, juce::AudioProcessorValueTreeState &apvts)
{
    referenceSpec = spec;
    int sourceIndex = apvts.getRawParameterValue("IR_SOURCE")->load();
    switch (sourceIndex) {
        case 0:
            this->prepareInternalIR(apvts);
            break;
        case 1:
            this->prepareExternalIR();
            break;
        default:
            this->prepare();
            break;
    }
}

void Convolution::process(juce::AudioBuffer<float> &mainBuffer, juce::AudioBuffer<float> &busBuffer, juce::AudioProcessorValueTreeState &apvts)
{
    int sourceIndex = apvts.getRawParameterValue("IR_SOURCE")->load();
    if (sourceIndex == 2)
        this->prepareBusIR(busBuffer);
    juce::dsp::AudioBlock<float> audioBlock(mainBuffer);
    juce::dsp::ProcessContextReplacing<float> context(audioBlock);
    juceConvolution.process(context);
}
