/*
  ==============================================================================

    SynthSound.h
    Created: 20 Apr 2021 4:24:57pm
    Author:  Gimbo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public :
    bool    appliesToNote(int midiNoteNumber) override { return true; }
    bool 	appliesToChannel(int midiChannel) override { return true; }
};
