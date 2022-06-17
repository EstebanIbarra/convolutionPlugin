/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ConvolutionPluginAudioProcessorEditor::ConvolutionPluginAudioProcessorEditor (ConvolutionPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), dragAndDropComponent(p)
{
    addAndMakeVisible(sourceIR);
    sourceIR.addItemList(EnvVars::getSourceOptions(), 1);
    attachmentSourceIR = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "IR_SOURCE", sourceIR);
    
    addAndMakeVisible(dragAndDropComponent);
    
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
    
    setSize (400, 400);
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
}

void ConvolutionPluginAudioProcessorEditor::resized()
{
    const float spacing = 0.04f;
    const float leftMarginOffset = 0.2f;
    const float horizontalElementsHeight = 0.06f;
    const float comboBoxWidth = 0.6f;
    const float dragAndDropWidth = 1.0f - 2.0f * spacing;
    const float dragAndDropHeight = 0.2f;
    const float sliderWidth = 1.0f - (leftMarginOffset);
    float proportionalY = spacing;
    sourceIR.setBoundsRelative(spacing, proportionalY, comboBoxWidth, horizontalElementsHeight);
    proportionalY += horizontalElementsHeight + spacing;
    dragAndDropComponent.setBoundsRelative(spacing, proportionalY, dragAndDropWidth, dragAndDropHeight);
    proportionalY += dragAndDropHeight + spacing;
    internalIR.setBoundsRelative(spacing, proportionalY, comboBoxWidth, horizontalElementsHeight);
    proportionalY += horizontalElementsHeight + spacing;
    limiterIO.setBoundsRelative(leftMarginOffset / 2.7f, proportionalY + spacing / 2, 0.1f, 0.1f);
    limiterThreshold.setBoundsRelative(leftMarginOffset, proportionalY, sliderWidth, horizontalElementsHeight);
    proportionalY += horizontalElementsHeight + spacing;
    limiterRelease.setBoundsRelative(leftMarginOffset, proportionalY, sliderWidth, horizontalElementsHeight);
    proportionalY += horizontalElementsHeight + spacing;
    dryWet.setBoundsRelative(spacing, proportionalY, 0.28f, 0.28f);
    proportionalY += 0.28f + spacing;
    DBG("Total Y = " << proportionalY);
}
