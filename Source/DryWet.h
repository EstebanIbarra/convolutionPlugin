/*
  ==============================================================================

    DryWet.h
    Created: 28 May 2022 1:41:28pm
    Author:  eir

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class DryWet
{
public:
    
    DryWet();
    ~DryWet();
    
    /**
     Mixes the dry and wet signal with the specified relation
     @param juce::AudioBuffer<float> &inputBufferWet
     @param juce::AudioBuffer<float> &inputBufferDry
     @param juce::AudioProcessorValueTreeState &apvts
     */
    void process(juce::AudioBuffer<float> &inputBufferWet, juce::AudioBuffer<float> &inputBufferDry, juce::AudioProcessorValueTreeState &apvts);
};
