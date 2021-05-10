/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SubtractiveSynthAudioProcessor::SubtractiveSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts (*this, nullptr, "Parameters", createParams()) 
#endif
{
    synth.addSound (new SynthSound());
    synth.addVoice (new SynthVoice());
}

SubtractiveSynthAudioProcessor::~SubtractiveSynthAudioProcessor()
{
    
}

//==============================================================================
const juce::String SubtractiveSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SubtractiveSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SubtractiveSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SubtractiveSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SubtractiveSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SubtractiveSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SubtractiveSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SubtractiveSynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SubtractiveSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void SubtractiveSynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SubtractiveSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate (sampleRate);
    
    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            voice->prepareToPlay (sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }
    
}

void SubtractiveSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SubtractiveSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
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

void SubtractiveSynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    // Update voice
    {
        for (int i = 0; i < synth.getNumVoices(); ++i)
        {
            if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
            {
                // Osc
                auto& oscWaveChoice = *apvts.getRawParameterValue ("OSC1WAVETYPE");
                
                
                // Amp Adsr
                auto& attack = *apvts.getRawParameterValue ("ATTACK");
                auto& decay = *apvts.getRawParameterValue ("DECAY");
                auto& sustain = *apvts.getRawParameterValue ("SUSTAIN");
                auto& release = *apvts.getRawParameterValue ("RELEASE");
                
                auto& freq = *apvts.getRawParameterValue("CUTOFF");
                auto& res = *apvts.getRawParameterValue("RESONANCE");
                
                // Filter Adsr
                auto& fAttack = *apvts.getRawParameterValue ("FILTERATTACK");
                auto& fDecay = *apvts.getRawParameterValue ("FILTERDECAY");
                auto& fSustain = *apvts.getRawParameterValue ("FILTERSUSTAIN");
                auto& fRelease = *apvts.getRawParameterValue ("FILTERRELEASE");
                
                // Filter
                auto& filterType = *apvts.getRawParameterValue ("FILTERTYPE");
                auto& cutoff = *apvts.getRawParameterValue ("FILTERFREQ");
                auto& resonance = *apvts.getRawParameterValue ("FILTERRES");
                           
                // Update voice
                voice->getOscillator().setWaveType (oscWaveChoice);
                voice->getAdsr().update (attack.load(), decay.load(), sustain.load(), release.load());
                voice->updateFilter (filterType, cutoff, resonance);
            }
        }
    }
    
    synth.renderNextBlock (buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool SubtractiveSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SubtractiveSynthAudioProcessor::createEditor()
{
    return new SubtractiveSynthAudioProcessorEditor (*this);
}

//==============================================================================
void SubtractiveSynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SubtractiveSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SubtractiveSynthAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout SubtractiveSynthAudioProcessor::createParams()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    // OSC select
    params.push_back (std::make_unique<juce::AudioParameterChoice>("OSC1WAVETYPE", "Osc 1 Wave Type", juce::StringArray { "Sine", "Saw", "Square" }, 0));
    
    // ADSR
    params.push_back (std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 0.1f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 0.1f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 1.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", juce::NormalisableRange<float> { 0.1f, 3.0f, 0.1f }, 0.4f));
    
    // Filter ADSR
    params.push_back (std::make_unique<juce::AudioParameterFloat>("FILTERATTACK", "Filter Attack", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 0.1f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("FILTERDECAY", "Filter Decay", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 0.1f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("FILTERSUSTAIN", "Filter Sustain", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 1.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("FILTERRELEASE", "Filter Release", juce::NormalisableRange<float> { 0.1f, 3.0f, 0.1f }, 0.4f));
    
    // Filter
    params.push_back (std::make_unique<juce::AudioParameterChoice>("FILTERTYPE", "Filter Type", juce::StringArray { "Low-Pass", "Band-Pass", "High-Pass" }, 0));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("FILTERFREQ", "Filter Freq", juce::NormalisableRange<float> { 20.0f, 20000.0f, 0.1f, 0.6f }, 200.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("FILTERRES", "Filter Resonance", juce::NormalisableRange<float> { 1.0f, 10.0f, 0.1f }, 1.0f));
    
    
    return { params.begin(), params.end() };
}