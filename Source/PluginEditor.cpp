#include "PluginProcessor.h"
#include "PluginEditor.h"

ConvolutionPluginAudioProcessorEditor::ConvolutionPluginAudioProcessorEditor (ConvolutionPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), dragAndDropComponent(p)
{
    addAndMakeVisible(sourceIR);
    sourceIR.addItemList(EnvVars::getSourceOptions(), 1);
    sourceIR.onChange = [this] () {
        const int sourceState = audioProcessor.apvts.getRawParameterValue("IR_SOURCE")->load();
        dragAndDropComponent.repaint();
        sourceState ==  0 ?  internalIR.setEnabled(true) : internalIR.setEnabled(false);
    };
    attachmentSourceIR = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "IR_SOURCE", sourceIR);
    
    addAndMakeVisible(dragAndDropComponent);
    dragAndDropComponent.changeSourceIR = [this] () {
        sourceIR.setSelectedItemIndex(1);
    };
    
    addAndMakeVisible(internalIR);
    internalIR.addItemList(EnvVars::getinternalIROptions(), 1);
    internalIR.onChange = [this] () {
        dragAndDropComponent.repaint();
    };
    attachmentInternalIR = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "INTERNAL_IR", internalIR);
    
    addAndMakeVisible(limiterIO);
    limiterIO.onClick = [this] () {
        if (limiterIO.getToggleState()) {
            limiterThreshold.setEnabled(true);
            limiterRelease.setEnabled(true);
        } else {
            limiterThreshold.setEnabled(false);
            limiterRelease.setEnabled(false);
        }
    };
    attachmentLimiterIO = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.apvts, "LIMITER_BYPASS", limiterIO);
    
    addAndMakeVisible(limiterThreshold);
    limiterThreshold.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    limiterThreshold.setSkewFactor(1.7f);
    attachmentLimiterThreshold = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "LIMITER_THRESHOLD", limiterThreshold);
    
    addAndMakeVisible(limiterRelease);
    limiterRelease.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    limiterRelease.setSkewFactor(0.3f);
    attachmentLimiterRelease = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "LIMITER_RELEASE", limiterRelease);
    
    addAndMakeVisible(dryWet);
    dryWet.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    dryWet.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    attachmentDryWet = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DRY_WET", dryWet);
    
    addAndMakeVisible(levelMeterL);
    addAndMakeVisible(levelMeterR);
    
    setSize (400, 400);
    
    startTimerHz(30);
}

ConvolutionPluginAudioProcessorEditor::~ConvolutionPluginAudioProcessorEditor()
{
}

void ConvolutionPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
}

void ConvolutionPluginAudioProcessorEditor::resized()
{
    const float spacing = 0.04f;
    const float leftMarginOffset = 0.2f + spacing / 2;
    const float slidersWidth = 1.0f - (leftMarginOffset + spacing / 2.0f);
    const float levelMeterWidth = 1.0f - (leftMarginOffset + spacing);
    const float horizontalElementsHeight = 0.06f;
    const float comboBoxWidth = 0.6f;
    const float dragAndDropWidth = 1.0f - 2.0f * spacing;
    const float dragAndDropHeight = 0.34f;
    float proportionalY = spacing;
    
    sourceIR.setBoundsRelative(spacing, proportionalY, comboBoxWidth, horizontalElementsHeight);
    proportionalY += horizontalElementsHeight + spacing;
    
    dragAndDropComponent.setBoundsRelative(spacing, proportionalY, dragAndDropWidth, dragAndDropHeight);
    proportionalY += dragAndDropHeight + spacing;
    
    internalIR.setBoundsRelative(spacing, proportionalY, comboBoxWidth, horizontalElementsHeight);
    proportionalY += horizontalElementsHeight + spacing;
    
    limiterIO.setBoundsRelative(leftMarginOffset / 2.7f, proportionalY + spacing / 2, 0.1f, 0.1f);
    limiterThreshold.setBoundsRelative(leftMarginOffset, proportionalY, slidersWidth, horizontalElementsHeight);
    proportionalY += horizontalElementsHeight + spacing;
    
    limiterRelease.setBoundsRelative(leftMarginOffset, proportionalY, slidersWidth, horizontalElementsHeight);
    proportionalY += horizontalElementsHeight + spacing;

    dryWet.setBoundsRelative(spacing / 2.0f, proportionalY - spacing / 2.0f, 0.2f, 0.2f);
    levelMeterL.setBoundsRelative(leftMarginOffset, proportionalY, levelMeterWidth, horizontalElementsHeight);
    proportionalY += horizontalElementsHeight + spacing / 2.0f;
    levelMeterR.setBoundsRelative(leftMarginOffset, proportionalY, levelMeterWidth, horizontalElementsHeight);
    proportionalY += horizontalElementsHeight + spacing;
}

void ConvolutionPluginAudioProcessorEditor::timerCallback()
{
    levelMeterL.setLevel(audioProcessor.getRMSValue(0));
    levelMeterR.setLevel(audioProcessor.getRMSValue(1));
    levelMeterL.repaint();
    levelMeterR.repaint();
    const int sourceState = audioProcessor.apvts.getRawParameterValue("IR_SOURCE")->load();
    juce::AudioBuffer<float> buffer = audioProcessor.getConvolutionBusBuffer();
    if (sourceState == 2 && buffer.getNumChannels() > 0 && buffer.getNumChannels() < 3) {
        dragAndDropComponent.setBusBuffer(buffer);
        dragAndDropComponent.repaint();
    }
}
