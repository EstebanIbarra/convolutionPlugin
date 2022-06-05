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
     @param juce::dsp::ProcessSpec &spec
     @return void
     */
    void prepare(juce::dsp::ProcessSpec &spec);
    
    /**
     Prepares the Class for using any internal IR
     @param juce::dsp::ProcessSpec &spec
     @param juce::AudioProcessorValueTreeState &apvts
     @return void
     */
    void prepareInternalIR(juce::dsp::ProcessSpec &spec, juce::AudioProcessorValueTreeState &apvts);
    
    /**
     Prepares the Class for using any external IR
     @param juce::dsp::ProcessSpec &spec
     @return void
     */
    void prepareExternalIR(juce::dsp::ProcessSpec &spec);
    
    /**
     Prepares the Class for using any bus IR
     @param juce::dsp::ProcessSpec &spec
     @return void
     */
    void prepareBusIR(juce::dsp::ProcessSpec &spec);
    
    /**
     Prepares the Class for using any bus IR
     @param juce::dsp::ProcessSpec &spec
     @param juce::AudioProcessorValueTreeState &apvts
     @return void
     */
    void prepareManager(juce::dsp::ProcessSpec &spec, juce::AudioProcessorValueTreeState &apvts);
    
    /**
     Preprocess the Audio Buffer
     @param juce::AudioBuffer<float> &inputBuffer
     @param juce::AudioProcessorValueTreeState &apvts
     @return void
     */
    void process(juce::AudioBuffer<float> &inputBuffer, juce::AudioProcessorValueTreeState &apvts);
    
private:
    juce::dsp::Convolution juceConvolution;
    juce::File impulseFile;
    const char * binaryIRWav[38] {
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
