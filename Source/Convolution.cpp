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
    prepare();
    
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

void Convolution::prepareExternalIR(juce::AudioProcessorValueTreeState &apvts, const juce::File &applicationDataFolder, const juce::String &fileName, const int &irNumChannels)
{
    appData = applicationDataFolder;
    
    if (fileName != "") {
        juce::String impulsePath = juce::File::addTrailingSeparator(appData.getFullPathName()) + fileName;
        impulseFile = juce::File(impulsePath);
     
        const juce::dsp::Convolution::Stereo isStereo = irNumChannels == 2 ? juce::dsp::Convolution::Stereo::yes : juce::dsp::Convolution::Stereo::no;
        const juce::dsp::Convolution::Trim requiresTrimming = juce::dsp::Convolution::Trim::yes;
        
        prepare();
        
        juceConvolution.loadImpulseResponse(impulseFile.getFullPathName(), isStereo, requiresTrimming, impulseFile.getSize());
    } else {
        prepare();
    }
}

void Convolution::prepareBusIR(juce::AudioBuffer<float> &busBuffer)
{
    prepare();
    const juce::dsp::Convolution::Stereo isStereo = referenceSpec.numChannels == 2 ? juce::dsp::Convolution::Stereo::yes : juce::dsp::Convolution::Stereo::no;
    
    juceConvolution.loadImpulseResponse(std::move(busBuffer), referenceSpec.sampleRate, isStereo, juce::dsp::Convolution::Trim::yes, juce::dsp::Convolution::Normalise::no);
}

void Convolution::prepareManager(juce::dsp::ProcessSpec &spec, juce::AudioProcessorValueTreeState &apvts, const juce::File &applicationDataFolder)
{
    referenceSpec = spec;
    int sourceIndex = apvts.getRawParameterValue("IR_SOURCE")->load();
    switch (sourceIndex) {
        case 0:
            prepareInternalIR(apvts);
            break;
        case 1:
            prepareExternalIR(apvts, applicationDataFolder);
            break;
        default:
            prepare();
            break;
    }
}

void Convolution::process(juce::AudioBuffer<float> &mainBuffer, juce::AudioBuffer<float> &busBuffer, juce::AudioProcessorValueTreeState &apvts)
{
    int sourceIndex = apvts.getRawParameterValue("IR_SOURCE")->load();
    if (sourceIndex == 2)
        prepareBusIR(busBuffer);
    juce::dsp::AudioBlock<float> audioBlock(mainBuffer);
    juce::dsp::ProcessContextReplacing<float> context(audioBlock);
    juceConvolution.process(context);
}

const char* Convolution::getInternalIRData(const int &index)
{
    return binaryIRWav[index];
}

const int Convolution::getInternalIRSize(const int &index)
{
    return binaryIRWavSize[index];
}

juce::File Convolution::getCurrentExternalIR()
{
    return impulseFile;
}
