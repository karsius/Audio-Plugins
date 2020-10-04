/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
A1StarterAudioProcessor::A1StarterAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

A1StarterAudioProcessor::~A1StarterAudioProcessor()
{
}

//==============================================================================
const juce::String A1StarterAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool A1StarterAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool A1StarterAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool A1StarterAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double A1StarterAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int A1StarterAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int A1StarterAudioProcessor::getCurrentProgram()
{
    return 0;
}

void A1StarterAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String A1StarterAudioProcessor::getProgramName (int index)
{
    return {};
}

void A1StarterAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void A1StarterAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    notes.clear();                          // [1]
    currentNote = 0;                        // [2]
    lastNoteValue = -1;                     // [3]
    time = 0;                               // [4]
    rate = static_cast<float> (sampleRate); // [5]
    arpSpeed = 0.5;
    ascending = true;
    octave = 1;
    majNotes = 0;
    skipNotes = false;
    playInThirds = false;
    octaveUp = true;
    std::cout << arpSpeed;
    noteNames.add("C"); noteNames.add("C#"); noteNames.add("D"); noteNames.add("D#"); noteNames.add("E"); noteNames.add("F"); noteNames.add("F#"); noteNames.add("G"); noteNames.add("G#"); noteNames.add("A"); noteNames.add("A#"); noteNames.add("B");
    int j = 9;

    // name and j refer to note name, i refers to note number
    for (auto name = 0; name < 12; name++) 
    {
        durationMap.set(noteNames[name], (juce::SortedSet<int>::SortedSet()));
        for (auto i = 0; i < 11; i++)
        {
            if (!(j > 7) || !(i == 10))
                durationMap.getReference(noteNames[name]).add(j + (i * 12));
        }
        j = (j + 1) % 12;
    }

    for (auto name = 0; name < 12; name++)
    {
        setDurations.set(noteNames[name], 0.5);
    }

}

void A1StarterAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool A1StarterAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void A1StarterAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi)
{
 
    // We use the audio buffer to get timing information
    auto numSamples = buffer.getNumSamples();                                                       // [7]

    // get note duration
    auto noteDuration = static_cast<int> (std::ceil (rate * 0.25f * (0.1f + (1.0f - (setDurations.getReference(noteName))))));   // [8]

    for (const auto metadata : midi)                                                                // [9]
    {
        const auto msg = metadata.getMessage();

        if (msg.isNoteOn()) 
        {
            int i = 0;
            while (i < octave)
            {
                if (octaveUp)
                {
                    if ((msg.getNoteNumber() + (12 * i)) < 128)
                    {
                        notes.add(msg.getNoteNumber() + (12 * i));
                    }
                    i++;
                }
                else
                {
                    if ((msg.getNoteNumber() - (12 * i)) >= 0)
                    {
                        notes.add(msg.getNoteNumber() - (12 * i));
                    }
                    i++;
                }
            }
        }
        else if (msg.isNoteOff()) 
        {
            int i = 0;
            while (i < octave)
            {
                if (octaveUp)
                {
                    if ((msg.getNoteNumber() + (12 * i)) < 128)
                    {
                        notes.removeValue(msg.getNoteNumber() + (12 * i));
                    }
                    i++;
                }
                else
                {
                    if ((msg.getNoteNumber() - (12 * i)) >= 0)
                    {
                        notes.removeValue(msg.getNoteNumber() - (12 * i));
                    }
                    i++;
                }
            }

        }
    }

    midi.clear();  
                                                                                 // [10]
    if (majNotes > 0 && notes.size() > 0)
    {
        majorScale.swapWithArray(changeToMajor(notes, majNotes));
    }


    if (notes.size() > 0 && playInThirds && !skipNotes)
    {
        if (majNotes > 1)
        {
            thirds.swapWithArray(changeToThirds(majorScale));
        }
        else
        {
            thirds.swapWithArray(changeToThirds(notes));
        }
        
    }



    
    if (notes.size() > 0 && skipNotes && !playInThirds) 
    {
        
        if (majNotes > 0)
        {
            everyOther.swapWithArray(changeToEveryOther(majorScale));
        }
        else
        {
            everyOther.swapWithArray(changeToEveryOther(notes));
        }
    }
        



    //if major scale is on and thirds and note skip are off turn on the major scale modifier, otherwise this is a majorscale combo mod or a note skip

    if (majNotes > 0 && !skipNotes && !playInThirds)
    {
        notesToPlay(majorScale, numSamples, noteDuration, midi);
    }
    else if (majNotes > 1 && playInThirds)
    {
        notesToPlay(thirds, numSamples, noteDuration, midi);
    }
    else if (skipNotes)
    {
        notesToPlay(everyOther, numSamples, noteDuration, midi);
    }
    else
    {
        notesToPlay(notes, numSamples, noteDuration, midi);
    }

    thirds.clear();
    everyOther.clear();
    majorScale.clear();
    }

//==============================================================================
bool A1StarterAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* A1StarterAudioProcessor::createEditor()
{
    return new A1StarterAudioProcessorEditor (*this);
}

//==============================================================================
void A1StarterAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void A1StarterAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new A1StarterAudioProcessor();
}

//==============================================================================


//use after receiving note number from midi
juce::String A1StarterAudioProcessor::getNote(int noteNumber)
{
    bool looking = true;
    juce::String noteName = "";
    juce::HashMap<juce::String, juce::SortedSet<int>>::Iterator index(durationMap);
    while (index.next() && looking)
    {
        if (index.getValue().contains(noteNumber))
        {
            looking = false;
            noteName = index.getKey();
        }
           
    }
    return noteName;
}

//process note numbers to thirds
juce::Array<int> A1StarterAudioProcessor::changeToThirds(juce::SortedSet<int> process)
{
    juce::Array<int> temp;
    int i = 0;
    bool flag = true;
    while (i < process.size()) 
    {
        temp.add(process[i]);
        if (flag)
        {
            i += 2;
            flag = false;
        }
        else
        {
            i -= 1;
            flag = true;
        }
    }
    return temp;
}

juce::Array<int> A1StarterAudioProcessor::changeToThirds(juce::Array<int> process)
{
    juce::Array<int> temp;
    int i = 0;
    bool flag = true;
    while (i < process.size())
    {
        temp.add(process[i]);
        if (flag)
        {
            i += 2;
            flag = false;
        }
        else
        {
            i -= 1;
            flag = true;
        }
    }
    return temp;
}

//process note numbers to every other depending on odd numbered note size or even
juce::Array<int> A1StarterAudioProcessor::changeToEveryOther(juce::SortedSet<int> process)
{
    juce::Array<int> temp;
    int i = 0;
    while (temp.size() < process.size())
    {
        //go to the next index if the index is pointing to an existing note in the array
        while (temp.contains(process[i]))
            i = (i + 1) % process.size();

        temp.add(process[i]);
        i = (i + 2) % process.size();
    }
    return temp;
}

juce::Array<int> A1StarterAudioProcessor::changeToEveryOther(juce::Array<int> process)
{
    juce::Array<int> temp;
    juce::SortedSet<int> indexSeen;
    int i = 0;
    while (temp.size() < process.size())
    {
        //go to the next index if the index is pointing to an existing note in the array
        while (indexSeen.contains(i))
            i = (i + 1) % process.size();

        temp.add(process[i]);
        indexSeen.add(i);
        i = (i + 2) % process.size();
    }
    return temp;
}

//process note numbers into a major scale; makes it so that each note in the buffer is interpreted as the root of a major scale with subsequent scale notes added depending on what the user selects
juce::Array<int> A1StarterAudioProcessor::changeToMajor(juce::SortedSet<int> process, int majNotes)
{
    juce::Array<int> temp;
    int i = 0;
    while (i < process.size())
    {
        int degree = 1;
        int j = 0;
        int target = process[i];

        temp.add(process[i]);

        while (j < majNotes) 
        {
            if (degree == 3 || degree == 7)
            {
                target += 1;
                temp.add(target);
            }
            else
            {
                target += 2;
                temp.add(target);
            }
            degree++;
            j++;
        }
        i++;
    }
    return temp;
}

void A1StarterAudioProcessor::notesToPlay(juce::Array<int> process, int numSamples, int noteDuration, juce::MidiBuffer& midi)
{
    if ((time + numSamples) >= noteDuration)                                                        // [11]
    {
        auto offset = juce::jmax(0, juce::jmin((int)(noteDuration - time), numSamples - 1));     // [12]

        if (lastNoteValue > 0)                                                                      // [13]
        {
            midi.addEvent(juce::MidiMessage::noteOff(1, lastNoteValue), offset);
            lastNoteValue = -1;
        }

        if (process.size() > 0)                                                                       // [14]
        {

            ascending ? currentNote = (currentNote + 1) % process.size() : currentNote = (currentNote - 1 + process.size()) % process.size();

            lastNoteValue = process[currentNote];
            midi.addEvent(juce::MidiMessage::noteOn(1, lastNoteValue, (juce::uint8) 127), offset);

            //update note duration
            noteName = getNote(lastNoteValue);
            DBG("last note value = " << lastNoteValue);
            DBG("last note name = " << noteName << "\n");

        }
    }

    time = (time + numSamples) % noteDuration;                                                      // [15]
}

void A1StarterAudioProcessor::notesToPlay(juce::SortedSet<int> process, int numSamples, int noteDuration, juce::MidiBuffer &midi)
{
    if ((time + numSamples) >= noteDuration)                                                        // [11]
    {
        auto offset = juce::jmax(0, juce::jmin((int)(noteDuration - time), numSamples - 1));     // [12]

        if (lastNoteValue > 0)                                                                      // [13]
        {
            midi.addEvent(juce::MidiMessage::noteOff(1, lastNoteValue), offset);
            lastNoteValue = -1;
        }

        if (process.size() > 0)                                                                       // [14]
        {

            ascending ? currentNote = (currentNote + 1) % process.size() : currentNote = (currentNote - 1 + process.size()) % process.size();

            lastNoteValue = process[currentNote];
            midi.addEvent(juce::MidiMessage::noteOn(1, lastNoteValue, (juce::uint8) 127), offset);

            //update note duration
            noteName = getNote(lastNoteValue);
            DBG("last note value = " << lastNoteValue);
            DBG("last note name = " << noteName << "\n");

        }
    }

    time = (time + numSamples) % noteDuration;                                                      // [15]
}
//==============================================================================




