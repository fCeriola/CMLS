/*
  ==============================================================================

    FIlterData.h
    Created: 10 May 2021 2:54:16pm
    Author:  DAVID

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class FilterData
{
public:
    void prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels);
    void process(juce::AudioBuffer<float>& buffer);
    void updateParameters(const int filterType, const float frequency, const float resonance);
    void reset();

private:
    juce::dsp::StateVariableTPTFilter<float> filter;
    bool isPrepared{ false };
};