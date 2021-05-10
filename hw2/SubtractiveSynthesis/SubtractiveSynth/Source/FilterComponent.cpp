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
    auto bounds = getLocalBounds().reduced (5);
    auto labelSpace = bounds.removeFromTop (25.0f);
    
    g.fillAll (juce::Colours::black);
    g.setColour (juce::Colours::white);
    g.setFont (20.0f);
    g.drawText (componentName, labelSpace.withX (5), juce::Justification::left);
    g.drawRoundedRectangle (bounds.toFloat(), 5.0f, 2.0f);
}

void FilterComponent::resized()
{const auto bounds = getLocalBounds().reduced (10);
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth() / 4 - padding;
    const auto sliderHeight = bounds.getHeight() - 45;
    const auto sliderStartX = padding + 5;
    const auto sliderStartY = 55;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;
    const auto labelStart = sliderStartY - labelYOffset;
    
    filterCutoffSlider.setBounds (sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    cutoffLabel.setBounds (filterCutoffSlider.getX(), labelStart, sliderWidth, labelHeight);
    
    filterResSlider.setBounds (filterCutoffSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    resLabel.setBounds (filterResSlider.getX(), labelStart, sliderWidth, labelHeight);
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