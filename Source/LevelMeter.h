/*
  ==============================================================================

    LevelMeter.h
    Created: 17 Jun 2022 8:23:22pm
    Author:  eir

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class LevelMeter  : public juce::Component
{
public:
    LevelMeter();
    ~LevelMeter() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    /**
     Level setter
     @param float &value
     @return void
     */
    void setLevel(const float &value);

private:
    float level {-60.0f};
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LevelMeter)
};
