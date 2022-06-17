/*
  ==============================================================================

    DragAndDropVisualiser.cpp
    Created: 16 Jun 2022 10:53:26pm
    Author:  eir

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DragAndDropVisualiser.h"

//==============================================================================
DragAndDropVisualiser::DragAndDropVisualiser(ConvolutionPluginAudioProcessor &p) : audioProcessor(p)
{
}

DragAndDropVisualiser::~DragAndDropVisualiser()
{
}

void DragAndDropVisualiser::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
     draws some placeholder text to get you started.
     
     You should replace everything in this method with your own
     drawing code..
     */
    
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
    
    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    
    g.setColour (juce::Colours::white);
    int sourceIR = audioProcessor.apvts.getRawParameterValue("IR_SOURCE")->load();
    switch (sourceIR) {
        case 0: // Internal IR
            /* TODO: Get float values of internal IR */
            drawAudioWave();
            g.setFont (14.0f);
            g.drawText ("Internal IR Wave Placeholder", getLocalBounds(), juce::Justification::centred, true);
            break;
        case 1: // External IR
            g.setFont (14.0f);
            g.drawText ("Drop your IR here", getLocalBounds(), juce::Justification::centred, true);
            break;
        default:
            break;
    }
}

void DragAndDropVisualiser::resized()
{
    formatManager.registerBasicFormats();
}

bool DragAndDropVisualiser::isInterestedInFileDrag(const juce::StringArray& files)
{
    for (juce::String file : files) {
        if (file.contains(".wav") || file.contains(".mp3") || file.contains(".aiff")) return true;
    }
    return false;
}

bool DragAndDropVisualiser::isInterestedInFileDrag(const juce::String &file)
{
    return (file.contains(".wav") || file.contains(".mp3") || file.contains(".aiff")) ? true : false;
}

void DragAndDropVisualiser::filesDropped(const juce::StringArray &files, int x, int y)
{
    for (juce::String file : files) {
        if (isInterestedInFileDrag(file)) {
            juce::File ogFile = file;
            audioProcessor.fileManager.copyFileToApplicationData(ogFile.getFullPathName());
            
            auto fileReader = formatManager.createReaderFor(ogFile);
            auto channelLayout = fileReader->getChannelLayout();
            
            
            audioProcessor.convolution.prepareExternalIR(
                 audioProcessor.apvts,
                 audioProcessor.fileManager.getApplicationDataFolder(),
                 ogFile.getFileName(),
                 channelLayout.size()
             );
        }
    }
}

void DragAndDropVisualiser::drawAudioWave()
{
    
}
