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
     @param double inputSampleRate
     @param int inputSamplesPerBlock
     @param int InputChannels
     @return void
     */
    void prepare(double inputSampleRate, int inputSamplesPerBlock, int inputChannels);
    /**
     Preprocess the Audio Buffer
     @param juce::AudioBuffer<float> inputBuffer
     @return void
     */
    void process(juce::AudioBuffer<float> inputBuffer);
private:
    juce::dsp::Convolution juceConvolution;
    juce::File impulseFile;
};
