/*
  ==============================================================================

    Limiter.h
    Created: 21 May 2022 12:32:17pm
    Author:  eir

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Limiter
{
public:
    Limiter();
    ~Limiter();
    
    /**
     Prepares the Spec
     @param juce::dsp::ProcessSpec spec
     @return void
     */
    void prepare(juce::dsp::ProcessSpec spec);
    
    /**
     Preprocess the Audio Buffer
     @param juce::AudioBuffer<float> inputBuffer
     @return void
     */
    void process(juce::AudioBuffer<float> &inputBuffer, float thresholdInDb = 0.0f, float releaseInMs = 1000.0f);
    
private:
    juce::dsp::Limiter<float> juceLimiter;
};
