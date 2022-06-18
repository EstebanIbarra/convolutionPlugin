/*
  ==============================================================================

    FileManager.cpp
    Created: 16 Jun 2022 11:02:11pm
    Author:  eir

  ==============================================================================
*/

#include "FileManager.h"

FileManager::FileManager()
{
    createFolderStructure();
}

FileManager::~FileManager()
{
    applicationDataFolder = "";
}

void FileManager::createFolderStructure()
{
    setApplicationDataFolder(juce::File::getSpecialLocation(juce::File::userApplicationDataDirectory).getFullPathName());
    for (juce::String dir : dirs) {
        setApplicationDataFolder(juce::File::addTrailingSeparator(applicationDataFolder.getFullPathName()) + dir);
    }
    if (!applicationDataFolder.isDirectory()) applicationDataFolder.createDirectory();
}

void FileManager::copyFileToApplicationData (const juce::String &absolutePath)
{
    juce::File file = absolutePath;
    file.copyFileTo(juce::File::addTrailingSeparator(applicationDataFolder.getFullPathName()) + file.getFileName());
}

void FileManager::setApplicationDataFolder(const juce::String &absolutePath)
{
    applicationDataFolder = absolutePath;
}

juce::File FileManager::getApplicationDataFolder()
{
    return applicationDataFolder;
}
