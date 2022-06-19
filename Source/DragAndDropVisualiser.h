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
     Draws the External IR waveform
     @param juce::Graphics &g
     @return void
     */
    void drawExternalIRWaveform(juce::Graphics &g);
    
    /**
     Draws the internal IR waveform
     @param juce::Graphics &g
     @return void
     */
    void drawInternalIRWaveform(juce::Graphics &g);
    
    /**
     Draws the Bus Buffer waveform
     @param juce::Graphics &g
     @return void
     */
    void drawBusBufferWaveform(juce::Graphics &g);
    
    /**
     Draws the waveform contained in an AudioBuffer
     @param juce::Graphics &g
     @param juce::AudioBuffer<float> &buffer
     @param bool isStereo, defaults to false
     @return void
     */
    void drawWaveform(juce::Graphics &g, juce::AudioBuffer<float> &buffer, bool isStereo = false);
    
    /**
     Draws error message
     @param juce::Graphics &g
     @return void
     */
    void drawErrorMessage(juce::Graphics &g);
    
    /**
     Changes the source IR
     @return std::function<void>
     */
    std::function<void()> changeSourceIR;
    
    void setBusBuffer(juce::AudioBuffer<float> &buffer);
    
private:
    ConvolutionPluginAudioProcessor &audioProcessor;
    juce::AudioFormatManager formatManager;
    juce::AudioBuffer<float> waveformBuffer;
    juce::AudioBuffer<float> busBuffer;
    std::vector<float> audioSamplesL;
    std::vector<float> audioSamplesR;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DragAndDropVisualiser)
};
