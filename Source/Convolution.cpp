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

void Convolution::prepare(juce::dsp::ProcessSpec spec)
{
//    Gets impulse path for user defined IRs
    juce::String impulsePath = juce::File::getSpecialLocation(juce::File::userDesktopDirectory).getFullPathName() + "/impulse.wav";
    impulseFile = juce::File(impulsePath);
    
    /* TODO: Find a way to get the numChannels from File */
    uint8_t irNumChannels = 1;
    
//    Defines if IR is stereo and if requires trimming
    const auto isStereo = irNumChannels == 2 ? juce::dsp::Convolution::Stereo::yes : juce::dsp::Convolution::Stereo::no;
    const auto requiresTrimming = juce::dsp::Convolution::Trim::yes;
    
//    Initializes juce Convolution
    juceConvolution.reset();
    juceConvolution.prepare(spec);
    
//    Loads User defined IR
    juceConvolution.loadImpulseResponse(impulseFile.getFullPathName(), isStereo, requiresTrimming, impulseFile.getSize());
}

void Convolution::process(juce::AudioBuffer<float> &inputBuffer)
{
    juce::dsp::AudioBlock<float> audioBlock(inputBuffer);
    juce::dsp::ProcessContextReplacing<float> context(audioBlock);
    juceConvolution.process(context);
}
