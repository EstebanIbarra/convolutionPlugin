/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class ConvolutionPluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    ConvolutionPluginAudioProcessorEditor (ConvolutionPluginAudioProcessor&);
    ~ConvolutionPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    ConvolutionPluginAudioProcessor& audioProcessor;
    
    juce::ComboBox sourceIR;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> attachmentSourceIR;
    
    juce::ComboBox busChannel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> attachmentBusChannel;
    
    juce::ComboBox internalIR;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> attachmentInternalIR;
    
    juce::ToggleButton limiterIO;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> attachmentLimiterIO;
    
    juce::Slider limiterThreshold;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachmentLimiterThreshold;
    
    juce::Slider limiterRelease;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachmentLimiterRelease;
    
    juce::Slider dryWet;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachmentDryWet;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConvolutionPluginAudioProcessorEditor)
};
