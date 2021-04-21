/*
  ==============================================================================

    SynthVoice.cpp
    Created: 20 Apr 2021 4:24:21pm
    Author:  Gimbo

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr; //Checking if Sound is not pointing at a null pointer.
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    osc.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    adsr.noteOn();
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    adsr.noteOff();
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{

}


/*--------------OSCILLATOR SPEC BEFORE PLAYING-------------------*/
void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels) {

    adsr.setSampleRate(sampleRate);

    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

    osc.prepare(spec);
    gain.prepare(spec);

    gain.setGainLinear(0.01f);

   

    isPrepared = true;
}
/*---------------------------------------------------------------*/


void SynthVoice::renderNextBlock(juce::AudioBuffer< float >& outputBuffer, int startSample, int numSamples)
{
   jassert (isPrepared); //if isPrepared = false, it stops the audio.

    juce::dsp::AudioBlock<float> audioBlock{ outputBuffer };        //alias of the outputBuffer. audioBlock is outputBuffer
    osc.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    
    adsr.applyEnvelopeToBuffer(outputBuffer, startSample, numSamples); //ouputBuffer will contain all the audio data of osc.process

    
}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{

}