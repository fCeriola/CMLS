/*
  ==============================================================================
    This file contains the basic framework code for a JUCE plugin editor.
  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SubtractiveSynthAudioProcessorEditor::SubtractiveSynthAudioProcessorEditor (SubtractiveSynthAudioProcessor& p)
: AudioProcessorEditor (&p)
, audioProcessor (p)
, osc (audioProcessor.apvts, "OSC1WAVETYPE")
, adsr ("Amp Envelope", audioProcessor.apvts, "ATTACK", "DECAY", "SUSTAIN", "RELEASE") 
, filt ("Filter Control", audioProcessor.apvts, "CUTOFF", "RESONANCE")
//, gain("Gain", audioProcessor.apvts, "GAIN")
{
    setSize (620, 500);
    addAndMakeVisible (osc);
    addAndMakeVisible (adsr);
    addAndMakeVisible (filt);
   // addAndMakeVisible (gain);
}

SubtractiveSynthAudioProcessorEditor::~SubtractiveSynthAudioProcessorEditor()
{
}

//==============================================================================
void SubtractiveSynthAudioProcessorEditor::paint (juce::Graphics& g)
{

    juce::Image background = juce::ImageFileFormat::loadFrom(juce::File("D:/Documenti/Politecnico/CMLS/CMLS_homeworks/CMLS/hw2/SubtractiveSynthesis/SubtractiveSynth/background.png"));
    g.drawImageAt(background, 0, 0, false);
  
}

void SubtractiveSynthAudioProcessorEditor::resized()
{
    const auto paddingX = 5;
    const auto paddingY = 35;
    const auto paddingY2 = 235;
    
    osc.setBounds (paddingX, paddingY, 300, 200);
    adsr.setBounds (osc.getRight(), paddingY, 300, 200);
    filt.setBounds (paddingX, paddingY2, 300, 200);
    //gain.setBounds(paddingX, paddingY, 100, 200);
}