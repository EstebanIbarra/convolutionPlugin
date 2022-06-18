/*
  ==============================================================================

    Convolution.h
    Created: 7 May 2022 1:57:38pm
    Author:  eir

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Convolution
{
public:
    Convolution();
    ~Convolution();
    
    /**
     Initializes Juce Convolution
     @return void
     */
    void prepare();
    
    /**
     Prepares the Class for using any internal IR
     @param juce::AudioProcessorValueTreeState &apvts
     @return void
     */
    void prepareInternalIR(juce::AudioProcessorValueTreeState &apvts);
    
    /**
     Prepares the Class for using any external IR
     @param juce::AudioProcessorValueTreeState &apvts
     @param juce::File &applicationDataFolder
     @param juce::String &fileName
     @return void
     */
    void prepareExternalIR(juce::AudioProcessorValueTreeState &apvts, const juce::File &applicationDataFolder, const juce::String &fileName = "", const int &irNumChannels = 1);
    
    /**
     Prepares the Class for using any bus IR
     @param juce::AudioBuffer<float> &busBuffer
     @return void
     */
    void prepareBusIR(juce::AudioBuffer<float> &busBuffer);
    
    /**
     Prepares the Class for using any bus IR
     @param juce::dsp::ProcessSpec &spec
     @param juce::AudioProcessorValueTreeState &apvts
     @return void
     */
    void prepareManager(juce::dsp::ProcessSpec &spec, juce::AudioProcessorValueTreeState &apvts, const juce::File &applicationDataFolder);
    
    /**
     Preprocess the Audio Buffer
     @param juce::AudioBuffer<float> &mainBuffer
     @param juce::AudioBuffer<float> &busBuffer
     @param juce::AudioProcessorValueTreeState &apvts
     @return void
     */
    void process(juce::AudioBuffer<float> &mainBuffer, juce::AudioBuffer<float> &busBuffer, juce::AudioProcessorValueTreeState &apvts);
    
    /**
     Gets the internal IR data
     @param int &index
     @return const char*
     */
    const char* getInternalIRData(const int &index);
    
    /**
     Gets the internal IR size
     @param juce::AudioProcessorValueTreeState &apvts
     @return int char*
     */
    const int getInternalIRSize(const int &index);
    
    /**
     Gets the current external IR File
     @return juce::File
     */
    juce::File getCurrentExternalIR();
    
private:
    juce::dsp::Convolution juceConvolution;
    juce::File appData;
    juce::File impulseFile;
    juce::dsp::ProcessSpec referenceSpec;
    const char *binaryIRWav[38] {
        BinaryData::Block_Inside_wav,
        BinaryData::Bottle_Hall_wav,
        BinaryData::Cement_Blocks_1_wav,
        BinaryData::Cement_Blocks_2_wav,
        BinaryData::Chateau_de_Logne_Outside_wav,
        BinaryData::Conic_Long_Echo_Hall_wav,
        BinaryData::Deep_Space_wav,
        BinaryData::Derlon_Sanctuary_wav,
        BinaryData::Direct_Cabinet_N1_wav,
        BinaryData::Direct_Cabinet_N2_wav,
        BinaryData::Direct_Cabinet_N3_wav,
        BinaryData::Direct_Cabinet_N4_wav,
        BinaryData::Five_Columns_Long_wav,
        BinaryData::Five_Columns_wav,
        BinaryData::French_18th_Century_Salon_wav,
        BinaryData::Going_Home_wav,
        BinaryData::Greek_7_Echo_Hall_wav,
        BinaryData::Highly_Damped_Large_Room_wav,
        BinaryData::In_The_Silo_Revised_wav,
        BinaryData::In_The_Silo_wav,
        BinaryData::Large_Bottle_Hall_wav,
        BinaryData::Large_Long_Echo_Hall_wav,
        BinaryData::Large_Wide_Echo_Hall_wav,
        BinaryData::Masonic_Lodge_wav,
        BinaryData::Musikvereinsaal_wav,
        BinaryData::Narrow_Bumpy_Space_wav,
        BinaryData::Nice_Drum_Room_wav,
        BinaryData::On_a_Star_wav,
        BinaryData::Parking_Garage_wav,
        BinaryData::Rays_wav,
        BinaryData::Right_Glass_Triangle_wav,
        BinaryData::Ruby_Room_wav,
        BinaryData::Scala_Milan_Opera_Hall_wav,
        BinaryData::Small_Drum_Room_wav,
        BinaryData::Small_Prehistoric_Cave_wav,
        BinaryData::St_Nicolaes_Church_wav,
        BinaryData::Trig_Room_wav,
        BinaryData::Vocal_Duo_wav
    };
    const int binaryIRWavSize[38] {
        BinaryData::Block_Inside_wavSize,
        BinaryData::Bottle_Hall_wavSize,
        BinaryData::Cement_Blocks_1_wavSize,
        BinaryData::Cement_Blocks_2_wavSize,
        BinaryData::Chateau_de_Logne_Outside_wavSize,
        BinaryData::Conic_Long_Echo_Hall_wavSize,
        BinaryData::Deep_Space_wavSize,
        BinaryData::Derlon_Sanctuary_wavSize,
        BinaryData::Direct_Cabinet_N1_wavSize,
        BinaryData::Direct_Cabinet_N2_wavSize,
        BinaryData::Direct_Cabinet_N3_wavSize,
        BinaryData::Direct_Cabinet_N4_wavSize,
        BinaryData::Five_Columns_Long_wavSize,
        BinaryData::Five_Columns_wavSize,
        BinaryData::French_18th_Century_Salon_wavSize,
        BinaryData::Going_Home_wavSize,
        BinaryData::Greek_7_Echo_Hall_wavSize,
        BinaryData::Highly_Damped_Large_Room_wavSize,
        BinaryData::In_The_Silo_Revised_wavSize,
        BinaryData::In_The_Silo_wavSize,
        BinaryData::Large_Bottle_Hall_wavSize,
        BinaryData::Large_Long_Echo_Hall_wavSize,
        BinaryData::Large_Wide_Echo_Hall_wavSize,
        BinaryData::Masonic_Lodge_wavSize,
        BinaryData::Musikvereinsaal_wavSize,
        BinaryData::Narrow_Bumpy_Space_wavSize,
        BinaryData::Nice_Drum_Room_wavSize,
        BinaryData::On_a_Star_wavSize,
        BinaryData::Parking_Garage_wavSize,
        BinaryData::Rays_wavSize,
        BinaryData::Right_Glass_Triangle_wavSize,
        BinaryData::Ruby_Room_wavSize,
        BinaryData::Scala_Milan_Opera_Hall_wavSize,
        BinaryData::Small_Drum_Room_wavSize,
        BinaryData::Small_Prehistoric_Cave_wavSize,
        BinaryData::St_Nicolaes_Church_wavSize,
        BinaryData::Trig_Room_wavSize,
        BinaryData::Vocal_Duo_wavSize
    };
};
