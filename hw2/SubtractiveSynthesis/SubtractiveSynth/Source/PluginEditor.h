/*
  ==============================================================================
    This file contains the basic framework code for a JUCE plugin editor.
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "AdsrComponent.h"
#include "OscComponent.h"
#include "FilterComponent.h"

//==============================================================================
/**
*/
class SubtractiveSynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SubtractiveSynthAudioProcessorEditor (SubtractiveSynthAudioProcessor&);
    ~SubtractiveSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    SubtractiveSynthAudioProcessor& audioProcessor;
    OscComponent osc;
    AdsrComponent adsr;
    FilterComponent filter;
    
    juce::Image background = juce::ImageFileFormat::loadFrom(juce::File("D:/Documenti/Politecnico/CMLS/CMLS_homeworks/CMLS/hw2/SubtractiveSynthesis/SubtractiveSynth/background.png"));
 
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SubtractiveSynthAudioProcessorEditor)
};