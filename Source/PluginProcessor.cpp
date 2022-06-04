/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ConvolutionPluginAudioProcessor::ConvolutionPluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr, "parameters", createParameters())
#endif
{
    dryWet = std::make_unique<DryWet>();
}

ConvolutionPluginAudioProcessor::~ConvolutionPluginAudioProcessor()
{
}

//==============================================================================

juce::AudioProcessorValueTreeState::ParameterLayout ConvolutionPluginAudioProcessor::createParameters()
{
    juce::AudioProcessorValueTreeState::ParameterLayout parameters;
    
    parameters.add(std::make_unique<juce::AudioParameterBool>("LIMITER_BYPASS", "Limiter I/O", false));
    parameters.add(std::make_unique<juce::AudioParameterFloat>("LIMITER_THRESHOLD", "Limiter Threshold", -12.0f, 2.0f, 0.0f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>("LIMITER_RELEASE", "Limiter Release", 1.0f, 4000.0f, 1000.0f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>("DRY_WET", "Dry/Wet", 0.0f, 100.0f, 50.0f));
    
    return parameters;
}

const juce::String ConvolutionPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ConvolutionPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ConvolutionPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ConvolutionPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ConvolutionPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ConvolutionPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ConvolutionPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ConvolutionPluginAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ConvolutionPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void ConvolutionPluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void ConvolutionPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
//    Prepares Dry Buffer
    dryBuffer.setSize(getTotalNumInputChannels(), samplesPerBlock);
    dryBuffer.clear();
    
//    Initializes specs
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumInputChannels();
    
//    Prepares Audio Classes
    convolution.prepare(spec);
    limiter.prepare(spec);
}

void ConvolutionPluginAudioProcessor::releaseResources()
{
    convolution.~Convolution();
    limiter.~Limiter();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ConvolutionPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void ConvolutionPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    dryBuffer.makeCopyOf(buffer);
    convolution.process(buffer, apvts);
    if (apvts.getRawParameterValue("LIMITER_BYPASS")->load())
        limiter.process(buffer, apvts);
    dryWet->process(buffer, dryBuffer, apvts);
}

//==============================================================================
bool ConvolutionPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ConvolutionPluginAudioProcessor::createEditor()
{
    return new ConvolutionPluginAudioProcessorEditor (*this);
}

//==============================================================================
void ConvolutionPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ConvolutionPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ConvolutionPluginAudioProcessor();
}
