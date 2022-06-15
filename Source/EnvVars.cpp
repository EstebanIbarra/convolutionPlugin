/*
  ==============================================================================

    EnvVars.cpp
    Created: 15 Jun 2022 3:26:54pm
    Author:  eir

  ==============================================================================
*/

#include "EnvVars.h"

juce::StringArray EnvVars::getSourceOptions()
{
    return juce::StringArray("Internal", "External", "Audio Bus");
}

juce::StringArray EnvVars::getinternalIROptions()
{
    return juce::StringArray(
       "Block Inside",
       "Bottle Hall",
       "Cement Blocks 1",
       "Cement Blocks 2",
       "Chateau de Logne Outside",
       "Conic Long Echo Hall",
       "Deep Space",
       "Derlon Sanctuary",
       "Direct Cabinet 1",
       "Direct Cabinet 2",
       "Direct Cabinet 3",
       "Direct Cabinet 4",
       "Five Columns Long",
       "Five Columns",
       "French 18th Century Salon",
       "Going Home",
       "Greek 7 Echo Hall",
       "Highly Damped Large Room",
       "In The Silo Revised",
       "In The Silo",
       "Large Bottle Hall",
       "Large Long Echo Hall",
       "Large Wide Echo Hall",
       "Masonic Lodge",
       "Musikcereinsaal",
       "Narrow Bumpy Space",
       "Nice Drum Room",
       "On a Star",
       "Parking Garage",
       "Rays",
       "Right Glass Triangle",
       "Ruby Room",
       "Scala Milan Opera Hall",
       "Small Drum Room",
       "Small Prehistoric Cave",
       "St Nicolaes Church",
       "Trig Room",
       "Vocal Duo"
       );
}
