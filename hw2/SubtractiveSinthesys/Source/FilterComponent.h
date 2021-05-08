/*
  ==============================================================================

    FilterComponent.h
    Created: 7 May 2021 4:19:19pm
    Author:  DAVID

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FilterComponent  : public juce::Component
{
public:
    FilterComponent();
    ~FilterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider filterCutoffDial;
    juce::Slider filterResDial;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> filterCutoffValue;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> filterResValue;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};
