/*
  ==============================================================================

    GainComponent.h
    Created: 10 May 2021 3:51:59pm
    Author:  Gimbo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


class GainComponent : public juce::Component
{
public:
    GainComponent(juce::String name, juce::AudioProcessorValueTreeState& apvts, juce::String gainId);
    ~GainComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    void setKnobWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment);

    juce::Slider gain;
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<SliderAttachment> gainAttachment;
    

    juce::Label gainLabel{ "Gain", "Gain" };
   
    juce::String componentName{ "" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GainComponent)
};