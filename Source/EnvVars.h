/*
  ==============================================================================

    EnvVars.h
    Created: 15 Jun 2022 3:26:54pm
    Author:  eir

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class EnvVars
{
public:
    /**
     Returns an array with the source options for the Convolution Plugin
     @param void
     @return juce::StringArray
     */
    static juce::StringArray getSourceOptions();
    
    /**
     Returns an array with the internal IRs available in the plugin
     @param void
     @return juce::StringArray
     */
    static juce::StringArray getinternalIROptions();
};
