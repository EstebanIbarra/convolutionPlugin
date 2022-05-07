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

void Convolution::prepare(double inputSampleRate)
{
    sampleRate = inputSampleRate;
}

void Convolution::process(juce::AudioBuffer<float> inputBuffer)
{
    for (uint8_t channel = 0; channel < inputBuffer.getNumChannels(); channel++) {
        for (int sampleIndex = 0; sampleIndex < inputBuffer.getNumSamples(); sampleIndex++) {
            float sample = inputBuffer.getSample(channel, sampleIndex);
            float processedSample = processSample(sample, channel);
            inputBuffer.setSample(channel, sampleIndex, processedSample);
        }
    }
}


float Convolution::processSample(float sample, u_int8_t channel)
{
    return 0.0f;
}
