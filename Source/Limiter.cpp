/*
  ==============================================================================

    Limiter.cpp
    Created: 21 May 2022 12:32:17pm
    Author:  eir

  ==============================================================================
*/

#include "Limiter.h"

Limiter::Limiter(){};
Limiter::~Limiter(){};

void Limiter::prepare(juce::dsp::ProcessSpec spec)
{
    juceLimiter.reset();
    juceLimiter.prepare(spec);
}

void Limiter::process(juce::AudioBuffer<float> &inputBuffer, float thresholdInDb, float releaseInMs)
{
    juce::dsp::AudioBlock<float> audioBlock(inputBuffer);
    juce::dsp::ProcessContextReplacing<float> context(audioBlock);
    juceLimiter.setThreshold(thresholdInDb);
    juceLimiter.setRelease(releaseInMs);
    juceLimiter.process(context);
}
