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
    DragAndDropVisualiser(ConvolutionPluginAudioProcessor&);
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
     Draws the audio wave
     @param TBD
     @return void
     */
    void drawAudioWave ();
    
private:
    ConvolutionPluginAudioProcessor &audioProcessor;
    juce::AudioFormatManager formatManager;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DragAndDropVisualiser)
};
