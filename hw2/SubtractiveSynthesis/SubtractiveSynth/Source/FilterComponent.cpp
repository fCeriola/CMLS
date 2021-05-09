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
FilterComponent::FilterComponent (juce::String name, juce::AudioProcessorValueTreeState& apvts, juce::String cutoffId, juce::String resId)
{
    componentName = name;
    
    setSliderWithLabel (filterCutoffSlider, cutoffLabel, apvts, cutoffId, filterCutoffAttachment);
    setSliderWithLabel (filterResSlider, resLabel, apvts, resId, filterResAttachment);
}

FilterComponent::~FilterComponent()
{
}

void FilterComponent::paint (juce::Graphics& g)
{
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
    juce::Rectangle<int> area = getLocalBounds().reduced(40);
    
    filterCutoffSlider.setBounds (30, 90, 70, 70);
    filterResSlider.setBounds (100, 90, 70, 70);
}

using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

void FilterComponent::setSliderWithLabel (juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment)
{
    slider.setSliderStyle (juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle (juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible (slider);
    
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramId, slider);
    
    label.setColour (juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setFont (15.0f);
    label.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (label);
}