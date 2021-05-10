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
    FilterComponent (juce::String name, juce::AudioProcessorValueTreeState& apvts, juce::String cutoffId, juce::String resId);
    ~FilterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    void setKnobWithLabel (juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment);
    
    juce::Slider filterCutoffSlider;
    juce::Slider filterResSlider;
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    std::unique_ptr<SliderAttachment> filterCutoffAttachment;
    std::unique_ptr<SliderAttachment> filterResAttachment;
    
    juce::Label cutoffLabel { "Cutoff", "cutoff" };
    juce::Label resLabel { "Resonance", "resonance" };
    
    juce::String componentName {""};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};
