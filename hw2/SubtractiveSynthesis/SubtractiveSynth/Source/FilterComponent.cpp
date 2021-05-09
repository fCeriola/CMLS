/*
  ==============================================================================

    FilterComponent.cpp
    Created: 7 May 2021 4:19:19pm
    Author:  DAVID

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComponent.h"

//==============================================================================
FilterComponent::FilterComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    setSize (200, 200);
    
    filterCutoffDial.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    filterCutoffDial.setRange(20.0f, 20000.0f);
    filterCutoffDial.setValue(600.0f);
    filterCutoffDial.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    filterCutoffDial.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&filterCutoffDial);
    
    filterResDial.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    filterResDial.setRange(0.1f, 1.0f);
    filterResDial.setValue(2.0f);
    filterResDial.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    filterResDial.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&filterResDial);
    
    filterCutoffValue = new juce::AudioProcessorValueTreeState::SliderAttachment (audioProcessor.apvts, "cutoff", filterCutoffDial);
    filterResValue = new juce::AudioProcessorValueTreeState::SliderAttachment (audioProcessor.apvts, "resonance", filterResDial);
    filterCutoffDial.setSkewFactorFromMidPoint(1000.0f);

}

FilterComponent::~FilterComponent()
{
}

void FilterComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
 
    juce::Rectangle<int> titleArea (0, 10, getWidth(), 20);
    
    g.fillAll (juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText("Filter", titleArea, juce::Justification::centredTop);
    g.drawText("Cutoff", 46, 70, 50, 25, juce::Justification::centredLeft);
    g.drawText("Resonance", 107, 70, 70, 25, juce::Justification::centredLeft);
    
    juce::Rectangle <float> area (25, 25, 150, 150);
    
    g.setColour(juce::Colours::yellow);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void FilterComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    juce::Rectangle<int> area = getLocalBounds().reduced(40);
    
    filterCutoffDial.setBounds (30, 90, 70, 70);
    filterResDial.setBounds (100, 90, 70, 70);
}
