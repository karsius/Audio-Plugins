/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class A1StarterAudioProcessorEditor  : public juce::AudioProcessorEditor, private juce::Slider::Listener, private juce::Button::Listener, private juce::ComboBox::Listener
{
public:
    A1StarterAudioProcessorEditor (A1StarterAudioProcessor&);
    ~A1StarterAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void sliderValueChanged (juce::Slider* slider) override;
    void buttonClicked(juce::Button* button) override;
    void comboBoxChanged(juce::ComboBox* dropdown) override;


    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    A1StarterAudioProcessor& audioProcessor;

    juce::Slider arpSlider; // [1]
    juce::TextButton ascdecButton;
    juce::TextButton thirdsButton;
    juce::Label thirdsButtonLabel;
    juce::TextButton skipButton; 
    juce::Label skipButtonLabel;
    juce::ComboBox octaveSelect; 
    juce::TextButton octaveSwitch;
    juce::Slider durationSliderA;
    juce::Slider durationSliderB;
    juce::Slider durationSliderC;
    juce::Slider durationSliderD;
    juce::Slider durationSliderE;
    juce::Slider durationSliderF;
    juce::Slider durationSliderG;
    juce::Slider durationSliderAsharp;
    juce::Slider durationSliderCsharp;
    juce::Slider durationSliderDsharp;
    juce::Slider durationSliderFsharp;
    juce::Slider durationSliderGsharp;
    juce::Slider majScaleSlider;
    juce::Label majScaleLabel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (A1StarterAudioProcessorEditor)
};
