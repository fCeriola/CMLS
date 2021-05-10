/*
  ==============================================================================

    FIlterData.cpp
    Created: 10 May 2021 2:54:16pm
    Author:  DAVID

  ==============================================================================
*/

#include "FIlterData.h"

void FilterData::update (const float sampleRate, const float cutoff, const float res)
{
    coeffs = *juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, cutoff, res);
    juce::dsp::IIR::Filter<float>::Filter(coeffs);
}   