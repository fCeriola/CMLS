/*
  ==============================================================================

    FIlterData.h
    Created: 10 May 2021 2:54:16pm
    Author:  DAVID

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class FilterData : public juce::dsp::IIR::Filter<float>
{
public: 
    void update (const float sampleRate, const float cutoff, const float res);

private:
    juce::dsp::IIR::Coefficients<float> coeffs;
    //juce::dsp::ProcessorDuplicator <juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients <float>> lowPassFilter;
    //lowPassFilter(juce::dsp::IIR::Coefficients<float>::makeLowPass(44100, 20000.0f, 0.1));
};