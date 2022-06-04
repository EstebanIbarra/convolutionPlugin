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
     @param juce::AudioProcessorValueTreeState &apvts
     @return void
     */
    void process(juce::AudioBuffer<float> &inputBuffer, juce::AudioProcessorValueTreeState &apvts);
    
private:
    juce::dsp::Limiter<float> juceLimiter;
};
