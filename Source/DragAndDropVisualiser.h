/*
  ==============================================================================

    DragAndDropVisualiser.h
    Created: 16 Jun 2022 10:53:26pm
    Author:  eir

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
 */
class DragAndDropVisualiser  : public juce::Component, public juce::FileDragAndDropTarget
{
public:
    DragAndDropVisualiser(ConvolutionPluginAudioProcessor &p);
    ~DragAndDropVisualiser() override;
    
    void paint (juce::Graphics&) override;
    void resized() override;
    
    /**
     Determines if the dragged files are valid audio files
     @param juce::StringArray &files
     @return bool
     */
    bool isInterestedInFileDrag (const juce::StringArray& files) override;
    
    /**
     Determines if the dragged file is a valid audio file
     @param juce::String &file
     @return bool
     */
    bool isInterestedInFileDrag (const juce::String &file);
    
    /**
     Process the file(s) dropped
     @param juce::StringArray &files
     @param int x
     @param int y
     @return void
     */
    void filesDropped (const juce::StringArray &files, int x, int y) override;
    
    /**
     Draws the External IR Component
     @param juce::Graphics &g
     @return void
     */
    void drawExternalIRWaveform(juce::Graphics &g);
    
    /**
     Draws the internal IR Component
     @param juce::Graphics &g
     @return void
     */
    void drawInternalIRCWaveform(juce::Graphics &g);
    
    /**
     Draws a waveform
     @param juce::Graphics &g
     @param bool isStereo, defaults to false
     @return void
     */
    void drawWaveform(juce::Graphics &g, bool isStereo = false);
    
    /**
     Changes the source IR
     @return std::function<void>
     */
    std::function<void()> changeSourceIR;
    
private:
    ConvolutionPluginAudioProcessor &audioProcessor;
    juce::AudioFormatManager formatManager;
    juce::AudioBuffer<float> waveformBuffer;
    std::vector<float> audioSamplesL;
    std::vector<float> audioSamplesR;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DragAndDropVisualiser)
};
