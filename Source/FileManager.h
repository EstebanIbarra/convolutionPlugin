/*
  ==============================================================================

    FileManager.h
    Created: 16 Jun 2022 11:02:11pm
    Author:  eir

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class FileManager
{
public:
    FileManager();
    ~FileManager();
    
    /**
     Copies a file to the Application Data folder
     @param juce::String &absolutePath
     @return void
     */
    void copyFileToApplicationData (const juce::String &absolutePath);
    
    /**
     Sets the full path for the Application Data Folder
     @param juce::String &absolutePath
     @return void
     */
    void setApplicationDataFolder(const juce::String &absolutePath);
    
    /**
     Get the path of the Application Data Folder
     @return juce::File
     */
    juce::File getApplicationDataFolder();
    
private:
    /**
     Creates folder structure
     @return void
     */
    void createFolderStructure();
    
    juce::File applicationDataFolder;
    juce::StringArray dirs {
        JucePlugin_Name,
        "External",
        "IR"
    };
};
