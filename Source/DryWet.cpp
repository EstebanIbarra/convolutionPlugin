/*
  ==============================================================================

    DryWet.cpp
    Created: 28 May 2022 1:41:28pm
    Author:  eir

  ==============================================================================
*/

#include "DryWet.h"

DryWet::DryWet(){};
DryWet::~DryWet(){};

void DryWet::process(juce::AudioBuffer<float> &inputBufferWet, juce::AudioBuffer<float> &inputBufferDry, juce::AudioProcessorValueTreeState &apvts)
{
    float inputDryWet = apvts.getRawParameterValue("DRY_WET")->load();
    inputDryWet /= 100.0f;
    for(int channel = 0; channel < inputBufferWet.getNumChannels(); channel++) {
        for (int sampleIndex = 0; sampleIndex < inputBufferWet.getNumSamples(); sampleIndex++) {
            float wetSample = inputBufferWet.getSample(channel, sampleIndex);
            float drySample = inputBufferDry.getSample(channel, sampleIndex);
            float outputSample = drySample * (1.0f - inputDryWet) + (wetSample * inputDryWet);
            inputBufferWet.setSample(channel, sampleIndex, outputSample);
        }
    }
}
