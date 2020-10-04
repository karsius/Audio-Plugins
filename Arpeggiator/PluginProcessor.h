/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class A1StarterAudioProcessor  : public juce::AudioProcessor
{
public:
     float arpSpeed;
     bool ascending;
     int octave;
     int majNotes;
     bool skipNotes;
     bool playInThirds;
     bool octaveUp;
     juce::HashMap<juce::String, float> setDurations;
     juce::Array<int> test;

    //==============================================================================
    A1StarterAudioProcessor();
    ~A1StarterAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //Notes getNote(int noteNumber) const;

private:
    //==============================================================================
    int currentNote, lastNoteValue;
    int time;
    float rate;

    juce::String noteName = "C";
    juce::SortedSet<int> notes;
    juce::HashMap<juce::String, juce::SortedSet<int>> durationMap;
    juce::SortedSet<juce::String> noteNames;
    juce::Array<int> thirds;
    juce::Array<int> everyOther;
    juce::Array<int> majorScale;


    //==============================================================================

    juce::String getNote(int noteNumber);
    juce::Array<int> changeToThirds(juce::SortedSet<int> process);
    juce::Array<int> changeToThirds(juce::Array<int> process);
    juce::Array<int> changeToEveryOther(juce::SortedSet<int> process);
    juce::Array<int> changeToEveryOther(juce::Array<int> process);
    juce::Array<int> changeToMajor(juce::SortedSet<int> process, int majNotes);
    void notesToPlay(juce::Array<int> process, int numSamples, int noteDuration, juce::MidiBuffer& midi);
    void notesToPlay(juce::SortedSet<int> process, int numSamples, int noteDuration, juce::MidiBuffer& midi);





    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (A1StarterAudioProcessor)
};
