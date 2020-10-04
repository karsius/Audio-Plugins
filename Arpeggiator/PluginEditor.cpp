/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"



//==============================================================================
A1StarterAudioProcessorEditor::A1StarterAudioProcessorEditor (A1StarterAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (550, 400);
    
    // these define the parameters of our slider object
    arpSlider.setSliderStyle (juce::Slider::LinearBarVertical);
    arpSlider.setRange (0.0, 1.0, 0.05);
    arpSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    arpSlider.setPopupDisplayEnabled (true, false, this);
    arpSlider.setTextValueSuffix (" Speed");
    arpSlider.setValue(0.5);

    // set slider id
    durationSliderC.setComponentID("C");
    durationSliderD.setComponentID("D");
    durationSliderE.setComponentID("E");
    durationSliderF.setComponentID("F");
    durationSliderG.setComponentID("G");
    durationSliderA.setComponentID("A");
    durationSliderB.setComponentID("B");

    durationSliderAsharp.setComponentID("A#");
    durationSliderCsharp.setComponentID("C#");
    durationSliderDsharp.setComponentID("D#");
    durationSliderFsharp.setComponentID("F#");
    durationSliderGsharp.setComponentID("G#");

    // define duration sliders
    durationSliderC.setSliderStyle(juce::Slider::Rotary);
    durationSliderD.setSliderStyle(juce::Slider::Rotary);
    durationSliderE.setSliderStyle(juce::Slider::Rotary);
    durationSliderF.setSliderStyle(juce::Slider::Rotary);
    durationSliderG.setSliderStyle(juce::Slider::Rotary);
    durationSliderA.setSliderStyle(juce::Slider::Rotary);
    durationSliderB.setSliderStyle(juce::Slider::Rotary);


    durationSliderAsharp.setSliderStyle(juce::Slider::Rotary);
    durationSliderCsharp.setSliderStyle(juce::Slider::Rotary);
    durationSliderDsharp.setSliderStyle(juce::Slider::Rotary);
    durationSliderFsharp.setSliderStyle(juce::Slider::Rotary);
    durationSliderGsharp.setSliderStyle(juce::Slider::Rotary);

    //set duration slider ranges
    durationSliderC.setRange(0.0, 1.0, 0.05);
    durationSliderD.setRange(0.0, 1.0, 0.05);
    durationSliderE.setRange(0.0, 1.0, 0.05);
    durationSliderF.setRange(0.0, 1.0, 0.05);
    durationSliderG.setRange(0.0, 1.0, 0.05);
    durationSliderA.setRange(0.0, 1.0, 0.05);
    durationSliderB.setRange(0.0, 1.0, 0.05);

    durationSliderAsharp.setRange(0.0, 1.0, 0.05);
    durationSliderCsharp.setRange(0.0, 1.0, 0.05);
    durationSliderDsharp.setRange(0.0, 1.0, 0.05);
    durationSliderFsharp.setRange(0.0, 1.0, 0.05);
    durationSliderGsharp.setRange(0.0, 1.0, 0.05);


    //set slider textbox
    durationSliderC.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    durationSliderD.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    durationSliderE.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    durationSliderF.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    durationSliderG.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    durationSliderA.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    durationSliderB.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);

    durationSliderAsharp.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    durationSliderCsharp.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    durationSliderDsharp.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    durationSliderFsharp.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    durationSliderGsharp.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);

    //set popup display
    durationSliderC.setPopupDisplayEnabled(true, false, this);
    durationSliderD.setPopupDisplayEnabled(true, false, this);
    durationSliderE.setPopupDisplayEnabled(true, false, this);
    durationSliderF.setPopupDisplayEnabled(true, false, this);
    durationSliderG.setPopupDisplayEnabled(true, false, this);
    durationSliderA.setPopupDisplayEnabled(true, false, this);
    durationSliderB.setPopupDisplayEnabled(true, false, this);

    durationSliderAsharp.setPopupDisplayEnabled(true, false, this);
    durationSliderCsharp.setPopupDisplayEnabled(true, false, this);
    durationSliderDsharp.setPopupDisplayEnabled(true, false, this);
    durationSliderFsharp.setPopupDisplayEnabled(true, false, this);
    durationSliderGsharp.setPopupDisplayEnabled(true, false, this);

    //set text value suffix
    durationSliderC.setTextValueSuffix("C");
    durationSliderD.setTextValueSuffix("D");
    durationSliderE.setTextValueSuffix("E");
    durationSliderF.setTextValueSuffix("F");
    durationSliderG.setTextValueSuffix("G");
    durationSliderA.setTextValueSuffix("A");
    durationSliderB.setTextValueSuffix("B");

    //set default value
    durationSliderC.setValue(0.5);
    durationSliderD.setValue(0.5);
    durationSliderE.setValue(0.5);
    durationSliderF.setValue(0.5);
    durationSliderG.setValue(0.5);
    durationSliderA.setValue(0.5);
    durationSliderB.setValue(0.5);

    durationSliderAsharp.setValue(0.5);
    durationSliderCsharp.setValue(0.5);
    durationSliderDsharp.setValue(0.5);
    durationSliderFsharp.setValue(0.5);
    durationSliderGsharp.setValue(0.5);

    //define the ascending/descending textbutton
    audioProcessor.ascending ? ascdecButton.setButtonText("Ascending") : ascdecButton.setButtonText("Descending");
    ascdecButton.setComponentID("ascdec");

    // defining the octave selector
    octaveSelect.setText("Octave");
    for (int i = 0; i < 4; i++) {
        octaveSelect.addItem(std::to_string(i), i+1);
    }

    //defining octave switch
    octaveSwitch.setButtonText("Up");
    octaveSwitch.setComponentID("octaveSwitch");

    //define thirds button
    thirdsButton.setButtonText("Play Scale In Thirds");
    thirdsButton.setComponentID("thirds");

    //define note skip button
    skipButton.setButtonText("Note Skip");
    skipButton.setComponentID("skip");

    //define major scale slider
    majScaleSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    majScaleSlider.setRange(0, 7, 1);
    majScaleSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 50, majScaleSlider.getTextBoxHeight()+20);
    majScaleSlider.setValue(0);
    majScaleSlider.setComponentID("major");
    majScaleLabel.setText("Add Major Scale Notes", juce::dontSendNotification);
    majScaleLabel.attachToComponent(&majScaleSlider, true);


 
    // this function adds the slider to the editor

    addAndMakeVisible(&ascdecButton);
    addAndMakeVisible(&octaveSelect);
    addAndMakeVisible(&majScaleSlider);
    addAndMakeVisible(&majScaleLabel);
    addAndMakeVisible(&thirdsButton);
    addAndMakeVisible(&skipButton);
    addAndMakeVisible(&octaveSwitch);

    //make duration sliders visible

    addAndMakeVisible(&durationSliderC);
    addAndMakeVisible(&durationSliderD);
    addAndMakeVisible(&durationSliderE);
    addAndMakeVisible(&durationSliderF);
    addAndMakeVisible(&durationSliderG);
    addAndMakeVisible(&durationSliderA);
    addAndMakeVisible(&durationSliderB);

    addAndMakeVisible(&durationSliderAsharp);
    addAndMakeVisible(&durationSliderCsharp);
    addAndMakeVisible(&durationSliderDsharp);
    addAndMakeVisible(&durationSliderFsharp);
    addAndMakeVisible(&durationSliderGsharp);

    arpSlider.addListener (this);
    ascdecButton.addListener(this);
    octaveSelect.addListener(this);
    majScaleSlider.addListener(this);
    thirdsButton.addListener(this);
    skipButton.addListener(this);
    octaveSwitch.addListener(this);

    //add duration slider listeners
    durationSliderC.addListener(this);
    durationSliderD.addListener(this);
    durationSliderE.addListener(this);
    durationSliderF.addListener(this);
    durationSliderG.addListener(this);
    durationSliderA.addListener(this);
    durationSliderB.addListener(this);

    durationSliderAsharp.addListener(this);
    durationSliderCsharp.addListener(this);
    durationSliderDsharp.addListener(this);
    durationSliderFsharp.addListener(this);
    durationSliderGsharp.addListener(this);

}

A1StarterAudioProcessorEditor::~A1StarterAudioProcessorEditor()
{
}

//==============================================================================
void A1StarterAudioProcessorEditor::paint (juce::Graphics& g)
{
   // fill the whole window white
   g.fillAll (juce::Colours::darkolivegreen);
 
    // set the current drawing colour to black
    g.setColour (juce::Colours::black);
 
    // set the font size and draw text to the screen
    g.setFont (15.0f);
 
    g.drawFittedText ("Arpeggiator", 0, 0, getWidth(), 30, juce::Justification::centred, 1);
    g.drawFittedText("Note Durations", 0, 160, getWidth(), 30, juce::Justification::centred, 1);

    g.drawFittedText("C", 50, 190, 20, 20, juce::Justification::centred, 1);
    g.drawFittedText("D", 130, 190, 20, 20, juce::Justification::centred, 1);
    g.drawFittedText("E", 210, 190, 20, 20, juce::Justification::centred, 1);
    g.drawFittedText("F", 290, 190, 20, 20, juce::Justification::centred, 1);
    g.drawFittedText("G", 370, 190, 20, 20, juce::Justification::centred, 1);
    g.drawFittedText("A", 450, 190, 20, 20, juce::Justification::centred, 1);
    g.drawFittedText("B", 210, 290, 20, 20, juce::Justification::centred, 1);

    g.drawFittedText("A#", 450, 290, 20, 20, juce::Justification::centred, 1);
    g.drawFittedText("C#", 50, 290, 20, 20, juce::Justification::centred, 1);
    g.drawFittedText("D#", 130, 290, 20, 20, juce::Justification::centred, 1);
    g.drawFittedText("F#", 290, 290, 20, 20, juce::Justification::centred, 1);
    g.drawFittedText("G#", 370, 290, 20, 20, juce::Justification::centred, 1);
}

void A1StarterAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    // sets the position and size of the slider with arguments (x, y, width, height)
    arpSlider.setBounds (40, 30, 20, getHeight() - 60);
    ascdecButton.setBounds(20, 30, 75, 40);
    octaveSelect.setBounds(getWidth() - 120, 30, 100, 30);
    octaveSwitch.setBounds(getWidth() - 170, 30, 50, 30);

    thirdsButton.setBounds((getWidth() - 200 + 75), 115, 80, 50);
    skipButton.setBounds(105, 30, 60, 40);

    //set duration slider positions
    
    durationSliderC.setBounds(20, 200, 80, getHeight()/4);
    durationSliderD.setBounds(100, 200, 80, getHeight()/4);
    durationSliderE.setBounds(180, 200, 80, getHeight()/4);
    durationSliderF.setBounds(260, 200, 80, getHeight()/4);
    durationSliderG.setBounds(340, 200, 80, getHeight()/4);
    durationSliderA.setBounds(420, 200, 80, getHeight()/4);
    durationSliderB.setBounds(180, 300, 80, getHeight()/4);

    durationSliderAsharp.setBounds(420, 300, 80, getHeight() / 4);
    durationSliderCsharp.setBounds(20, 300, 80, getHeight() / 4);
    durationSliderDsharp.setBounds(100, 300, 80, getHeight() / 4);
    durationSliderFsharp.setBounds(260, 300, 80, getHeight() / 4);
    durationSliderGsharp.setBounds(340, 300, 80, getHeight() / 4);

    //set majscale slider position
    majScaleSlider.setBounds(125, 125, getWidth() - 250, 20);



}

void A1StarterAudioProcessorEditor::sliderValueChanged (juce::Slider* slider)
{
    audioProcessor.arpSpeed = arpSlider.getValue();

    
    if (slider->getComponentID() == "major")
    {
        audioProcessor.majNotes = slider->getValue();
    }
    else
    {
        //set new note duration value
        juce::HashMap<juce::String, float>::Iterator index(audioProcessor.setDurations);
        while (index.next())
        {
            if (index.getKey() == slider->getComponentID())
            {
                audioProcessor.setDurations.set(index.getKey(), slider->getValue());
            }

        }
    }

    if (slider->getComponentID() == "major" && slider->getValue() < 2)
    {
        thirdsButton.setButtonText("Play Scale In Thirds Off");
        audioProcessor.playInThirds = false;
    }
}

void A1StarterAudioProcessorEditor::buttonClicked(juce::Button* button) 
{
    //if skip notes button is on, turn off upon turning on thirds button and vice versa
    //if major scale notes set to lower than 1 upon turning on playing in thirds, set to 2
    if (button->getComponentID() == "thirds")
    {
        !audioProcessor.playInThirds ? audioProcessor.playInThirds = true : audioProcessor.playInThirds = false;
        if (audioProcessor.playInThirds && audioProcessor.skipNotes)
        {
            skipButton.setButtonText("Note Skip Off");
            audioProcessor.skipNotes = false;
        }
        if (audioProcessor.playInThirds && audioProcessor.majNotes < 1)
        {
            audioProcessor.majNotes = 2;
            majScaleSlider.setValue(2);
        }
        //button highlight
        if (audioProcessor.playInThirds)
        {
            thirdsButton.setButtonText("Play Scale In Thirds On");
        }
        else
        {
            thirdsButton.setButtonText("Play Scale In Thirds Off");
        }
    }
    else if (button->getComponentID() == "skip")
    {
        !audioProcessor.skipNotes ? audioProcessor.skipNotes = true : audioProcessor.skipNotes = false;
        if (audioProcessor.playInThirds && audioProcessor.skipNotes)
        {
            thirdsButton.setButtonText("Play Scale In Thirds Off");
            audioProcessor.playInThirds = false;
        }
        if (audioProcessor.skipNotes)
        {
            skipButton.setButtonText("Note Skip On");
        }
        else
        {
            skipButton.setButtonText("Note Skip Off");
        }
    }
    if (button->getComponentID() == "ascdec")
    {
        if (ascdecButton.getButtonText().containsOnly("Ascending")) {
            ascdecButton.setButtonText("Descending");
            audioProcessor.ascending = false;
        }
        else {
            ascdecButton.setButtonText("Ascending");
            audioProcessor.ascending = true;
        }
    }
    if (button->getComponentID() == "octaveSwitch")
    {
        if (octaveSwitch.getButtonText().containsOnly("Up"))
        {
            octaveSwitch.setButtonText("Down");
            audioProcessor.octaveUp = false;
        }
        else
        {
            octaveSwitch.setButtonText("Up");
            audioProcessor.octaveUp = true;
        }
    }
}

void A1StarterAudioProcessorEditor::comboBoxChanged(juce::ComboBox* dropdown)
{

    audioProcessor.octave = std::max(1, (octaveSelect.getSelectedId()));
 
}