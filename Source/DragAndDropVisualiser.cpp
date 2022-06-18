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
    
    g.fillAll (getLookAndFeel().findColour (juce::ComboBox::backgroundColourId));   // clear the background
    
    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    
    g.setColour (juce::Colours::white);
    int sourceIR = audioProcessor.apvts.getRawParameterValue("IR_SOURCE")->load();
    switch (sourceIR) {
        case 0: // Internal IR
            drawInternalIRCWaveform(g);
            break;
        case 1: // External IR
            drawExternalIRWaveform(g);
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
            
            changeSourceIR();
            audioProcessor.convolution.prepareExternalIR(
                 audioProcessor.apvts,
                 audioProcessor.fileManager.getApplicationDataFolder(),
                 ogFile.getFileName(),
                 channelLayout.size()
             );
            repaint();
        }
    }
}

void DragAndDropVisualiser::drawExternalIRWaveform(juce::Graphics &g)
{
    juce::File currentIR = audioProcessor.convolution.getCurrentExternalIR();
    juce::String fileName = currentIR.getFileName();
    juce::Rectangle<float> bounds = getLocalBounds().toFloat();
    if (fileName == "") {
        g.setFont (14.0f);
        g.drawText ("Drop your IR here", bounds, juce::Justification::centred, true);
    } else {
        std::unique_ptr<juce::AudioFormatReader> fileReader(formatManager.createReaderFor(currentIR));
        int sampleLenght = static_cast<int>(fileReader->lengthInSamples);
        int numChannels = fileReader->getChannelLayout().size();
        jassert(numChannels == 1 || numChannels ==2);
        waveformBuffer.clear();
        if (numChannels == 1) {
            waveformBuffer.setSize(numChannels, sampleLenght);
            fileReader->read(&waveformBuffer, 0, sampleLenght, 0, true, false);
            drawWaveform(g);
        } else {
            waveformBuffer.setSize(numChannels, sampleLenght);
            fileReader->read(&waveformBuffer, 0, sampleLenght, 0, true, true);
            drawWaveform(g, true);
        }
        g.setFont(10.0f);
        g.drawText(fileName, bounds, juce::Justification::centredBottom, true);
    }
}

void DragAndDropVisualiser::drawInternalIRCWaveform(juce::Graphics &g)
{
    const int indexIR = audioProcessor.apvts.getRawParameterValue("INTERNAL_IR")->load();
    const char *binaryData = audioProcessor.convolution.getInternalIRData(indexIR);
    const int binaryDataSize = audioProcessor.convolution.getInternalIRSize(indexIR);
    waveformBuffer.clear();
    juce::WavAudioFormat wavFormat;
    juce::MemoryInputStream *inputStream = new juce::MemoryInputStream(binaryData, binaryDataSize, false);
    std::unique_ptr<juce::AudioFormatReader> formatReader(wavFormat.createReaderFor(inputStream, true));
    if (formatReader.get() != nullptr) {
        int sampleLenght = static_cast<int>(formatReader->lengthInSamples);
        waveformBuffer.setSize(formatReader->numChannels, sampleLenght);
        formatReader->read(&waveformBuffer, 0, sampleLenght, 0, true, false);
        drawWaveform(g, true);
    } else {
        juce::Rectangle<float> bounds = getLocalBounds().toFloat();
        g.setFont (14.0f);
        g.drawText ("Oops, something went wrong", bounds, juce::Justification::centred, true);
    }
}

void DragAndDropVisualiser::drawWaveform(juce::Graphics &g, bool isStereo)
{
    audioSamplesL.clear();
    audioSamplesR.clear();
    const int numSamples = waveformBuffer.getNumSamples();
    const int ratio = numSamples / getWidth();
    const float *bufferL(waveformBuffer.getReadPointer(0));
    const float height = static_cast<float>(getHeight());
    const float halfHeight = height / 2.0f;
    juce::Path pathL;
    const juce::PathStrokeType thickness (2.0f);
    if (isStereo) {
        juce::Path pathR;
        const float *bufferR(waveformBuffer.getReadPointer(1));
        for (int sample = 0; sample < numSamples; sample += ratio) {
            audioSamplesL.push_back(bufferL[sample]);
            audioSamplesR.push_back(bufferR[sample]);
        }
        const float quarterHeight = halfHeight / 2.0f;
        pathL.startNewSubPath(0.0f, quarterHeight);
        pathR.startNewSubPath(0.0f, height - quarterHeight);
        for (int sample = 0; sample < audioSamplesL.size(); sample++) {
            float scaledYL = juce::jmap(audioSamplesL[sample], -1.0f, 1.0f, halfHeight, 0.0f);
            pathL.lineTo(sample, scaledYL);
            float scaledYR = juce::jmap(audioSamplesR[sample], -1.0f, 1.0f, height, halfHeight);
            pathR.lineTo(sample, scaledYR);
        }
        g.strokePath(pathR, thickness);
    } else {
        for (int sample = 0; sample < numSamples; sample += ratio) {
            audioSamplesL.push_back(bufferL[sample]);
        }
        pathL.startNewSubPath(0.0f, halfHeight);
        for (int sample = 0; sample < audioSamplesL.size(); sample++) {
            float scaledY = juce::jmap(audioSamplesL[sample], -1.0f, 1.0f, static_cast<float>(getHeight()), 0.0f);
            pathL.lineTo(sample, scaledY);
        }
    }
    g.strokePath(pathL, thickness);
}
