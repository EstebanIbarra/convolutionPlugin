/*
  ==============================================================================

    Convolution.h
    Created: 7 May 2022 1:57:38pm
    Author:  eir

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Convolution
{
public:
    Convolution();
    ~Convolution();
    
    /**
     Prepares the Sample Rate
     @param juce::dsp::ProcessSpec spec
     @return void
     */
    void prepare(juce::dsp::ProcessSpec spec);
    
    /**
     Preprocess the Audio Buffer
     @param juce::AudioBuffer<float> &inputBuffer
     @param juce::AudioProcessorValueTreeState &apvts
     @return void
     */
    void process(juce::AudioBuffer<float> &inputBuffer, juce::AudioProcessorValueTreeState &apvts);
    
private:
    juce::dsp::Convolution juceConvolution;
    juce::File impulseFile;
};
