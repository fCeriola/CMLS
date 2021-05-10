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
class FilterComponent : public juce::Component
{
public:
    FilterComponent (juce::String name, juce::AudioProcessorValueTreeState& apvts, juce::String filterTypeSelectorId, juce::String cutoffId, juce::String resId);
    ~FilterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox filterTypeSelector { "Filter Type" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeSelectorAttachment;
    
    juce::Slider filterCutoffSlider;
    juce::Slider filterResSlider;
    
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    std::unique_ptr<Attachment> filterFreqAttachment;
    std::unique_ptr<Attachment> filterResAttachment;
    
    juce::Label filterSelectorLabel { "Filter Type", "Filter Type" };
    juce::Label cutoffLabel { "Filter Freq", "Filter Freq" };
    juce::Label resLabel { "Filter Res", "FilterRes" };
    
    void setSliderWithLabel (juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment);

    juce::String componentName{ "" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};