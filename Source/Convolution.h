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
     @return void
     */
    void prepare(double inputSampleRate);
    /**
     Preprocess the Audio Buffer
     @param juce::AudioBuffer<float> inputBuffer
     @return void
     */
    void process(juce::AudioBuffer<float> inputBuffer);
    /**
     Process a sample in the Audio Buffer
     @param float sample
     @param u_int8_t channel
     @return float processedSample
     */
    float processSample(float sample, u_int8_t channel);
private:
    double sampleRate {0.0f};
};
