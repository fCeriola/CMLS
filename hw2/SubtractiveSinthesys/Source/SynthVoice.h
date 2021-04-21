/*
  ==============================================================================

    SynthVoice.h
    Created: 20 Apr 2021 4:24:21pm
    Author:  Gimbo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff);
    void controllerMoved(int controllerNumber, int newControllerValue)override;
    void pitchWheelMoved(int newPitchWheelValue)override;
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock(juce::AudioBuffer< float >& outputBuffer, int startSample, int numSamples) override;
    

private:
    bool isPrepared{ false }; /*double check that prepareToPlay is called before renderNextBlock*/

    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParameters;

    juce::dsp::Oscillator<float> osc { [](float x) { return x < 0.0f ? -1.0f : 1.0f; }};
    juce::dsp::Gain<float> gain;
    
    

    // return std::sin (x); //Sine Wave
    // return x / MathConstants<float>::pi; // Saw Wave
    // return x < 0.0f ? -1.0f : 1.0f;  // Square Wave

};