#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "EnvVars.h"
#include "DragAndDropVisualiser.h"
#include "LevelMeter.h"

class ConvolutionPluginAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Timer
{
public:
    ConvolutionPluginAudioProcessorEditor (ConvolutionPluginAudioProcessor&);
    ~ConvolutionPluginAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void timerCallback() override;

private:
    ConvolutionPluginAudioProcessor& audioProcessor;
    
    juce::ComboBox sourceIR;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> attachmentSourceIR;
    
    DragAndDropVisualiser dragAndDropComponent;
    
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
    
    LevelMeter levelMeterL;
    LevelMeter levelMeterR;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConvolutionPluginAudioProcessorEditor)
};
