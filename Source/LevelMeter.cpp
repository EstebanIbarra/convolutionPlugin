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
    g.setColour(findColour(juce::ComboBox::backgroundColourId));
    g.fillRoundedRectangle(bounds, 5.0f);
    
    g.setColour(juce::Colours::grey);
    g.drawRoundedRectangle(bounds, 5.0f, 1.0f);
    
    g.setGradientFill(gradient);
    const float scaledX = juce::jmap(level, -60.0f, 6.0f, 0.0f, static_cast<float>(getWidth()));
    g.fillRoundedRectangle(bounds.removeFromLeft(scaledX), 5.0f);
}

void LevelMeter::resized()
{
    juce::Rectangle<float> bounds = getLocalBounds().toFloat();
    gradient = juce::ColourGradient {
        juce::Colours::green,
        bounds.getRelativePoint(0.0f, 0.5f),
        juce::Colours::red,
        bounds.getRelativePoint(1.0f, 0.5f),
        false
    };
    gradient.addColour(0.5f, juce::Colours::yellow);
}

void LevelMeter::setLevel(const float &value)
{
    level = value;
}
