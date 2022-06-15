/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ConvolutionPluginAudioProcessorEditor::ConvolutionPluginAudioProcessorEditor (ConvolutionPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    addAndMakeVisible(sourceIR);
    sourceIR.addItemList(EnvVars::getSourceOptions(), 1);
    attachmentSourceIR = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "IR_SOURCE", sourceIR);
    
    addAndMakeVisible(internalIR);
    internalIR.addItemList(EnvVars::getinternalIROptions(), 1);
    attachmentInternalIR = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "INTERNAL_IR", internalIR);
    
    addAndMakeVisible(limiterIO);
    attachmentLimiterIO = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.apvts, "LIMITER_BYPASS", limiterIO);
    
    addAndMakeVisible(limiterThreshold);
    limiterThreshold.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    attachmentLimiterThreshold = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "LIMITER_THRESHOLD", limiterThreshold);
    
    addAndMakeVisible(limiterRelease);
    limiterRelease.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    attachmentLimiterRelease = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "LIMITER_RELEASE", limiterRelease);
    
    addAndMakeVisible(dryWet);
    dryWet.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    attachmentDryWet = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DRY_WET", dryWet);
    
    setSize (500, 500);
}

ConvolutionPluginAudioProcessorEditor::~ConvolutionPluginAudioProcessorEditor()
{
}

//==============================================================================
void ConvolutionPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void ConvolutionPluginAudioProcessorEditor::resized()
{
    const float leftMargin = 0.02f;
    const float comboBoxWidth = 0.6f;
    const float comboBoxHeight = 0.05f;
    const float sliderWidth = 0.55f;
    const float sliderHeight = 0.05f;
    sourceIR.setBoundsRelative(leftMargin, 0.02f, comboBoxWidth, comboBoxHeight);
    internalIR.setBoundsRelative(leftMargin, comboBoxHeight + 0.05f, comboBoxWidth, comboBoxHeight);
    limiterIO.setBoundsRelative(leftMargin, 0.6f, 0.1, 0.1);
    limiterThreshold.setBoundsRelative(0.2f, 0.5f, sliderWidth, sliderHeight);
    limiterRelease.setBoundsRelative(0.2f, 0.55f + sliderHeight, sliderWidth, sliderHeight);
    dryWet.setBoundsRelative(leftMargin, 0.7f, 0.3f, 0.3f);
}
