/*
  ==============================================================================

    LevelMeter.cpp
    Created: 17 Jun 2022 8:23:22pm
    Author:  eir

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LevelMeter.h"

//==============================================================================
LevelMeter::LevelMeter()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

LevelMeter::~LevelMeter()
{
}

void LevelMeter::paint (juce::Graphics& g)
{
    juce::Rectangle<float> bounds = getLocalBounds().toFloat();
    g.setColour(findColour(juce::Slider::ColourIds::backgroundColourId));
    g.fillRoundedRectangle(bounds, 5.0f);
    
    g.setColour(findColour(juce::Slider::ColourIds::thumbColourId));
    const float scaledX = juce::jmap(level, -60.0f, 6.0f, 0.0f, static_cast<float>(getWidth()));
    g.fillRoundedRectangle(bounds.removeFromLeft(scaledX), 5.0f);
}

void LevelMeter::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void LevelMeter::setLevel(const float &value)
{
    level = value;
}
