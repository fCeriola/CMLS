/*
  ==============================================================================
    OscData.h
  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


class OscData : public juce::dsp::Oscillator<float>
{
public:
    void prepareToPlay (juce::dsp::ProcessSpec& spec);
    void setWaveType (const int choice);
    void setWaveFrequency (const int midiNoteNumber);
    void getNextAudioBlock (juce::dsp::AudioBlock<float>& block);
    
private:
    void processFmOsc (juce::dsp::AudioBlock<float>& block);
    
    juce::dsp::Oscillator<float> fmOsc { [](float x) { return std::sin (x); } };
    int lastMidiNote { 0 };
};