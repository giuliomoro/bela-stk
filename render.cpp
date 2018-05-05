/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

The platform for ultra-low latency audio and sensor processing

http://bela.io

A project of the Augmented Instruments Laboratory within the
Centre for Digital Music at Queen Mary University of London.
http://www.eecs.qmul.ac.uk/~andrewm

(c) 2016 Augmented Instruments Laboratory: Andrew McPherson,
	Astrid Bin, Liam Donovan, Christian Heinrichs, Robert Jack,
	Giulio Moro, Laurel Pardue, Victor Zappi. All rights reserved.

The Bela software is distributed under the GNU Lesser General Public License
(LGPL 3.0), available here: https://www.gnu.org/licenses/lgpl-3.0.txt
*/

#include <Bela.h>
#include <stk/SineWave.h>

using namespace stk;

SineWave **oscs;
int channels;
StkFrames frames;
float base_freq = 220.0;
unsigned int nFrames;

bool setup(BelaContext *context, void *userData)
{
	channels = context->audioOutChannels;
	double srate = context->audioSampleRate;
	nFrames = context->audioFrames;
	int i;
	// Create our object instances.
	oscs = (SineWave **) malloc( channels * sizeof(SineWave *) );
	for ( i=0; i<channels; i++ ) oscs[i] = 0;

	// If you want to change the default sample rate (set in Stk.h), do
	// it before instantiating any objects!!
	Stk::setSampleRate( srate );

	// Define the sinewaves.
	for ( i=0; i<channels; i++ )
	{
		oscs[i] = new SineWave;
	}

	  // Set oscillator frequency(ies) here ... somewhat random.
	for ( i=0; i<channels; i++ )
		oscs[i]->setFrequency( base_freq + i*(45.0) );

	for (int i = 0; i < channels; i++)
		oscs[i]->tick(frames, i);
	frames.resize(nFrames, channels);
	return true;
}

void render(BelaContext *context, void *userData)
{
	// Here's the runtime code
	for (int i = 0; i < channels; i++)
	{
		oscs[i]->tick(frames, i);
	}
	// copy from frames to Bela audio out
	for(unsigned int n = 0; n < nFrames; ++n)
	{
		for(unsigned int ch = 0; ch < channels; ++ch)
		{
			float value = frames(n, ch);
			audioWrite(context, n , ch, value);
		}
	}
}

void cleanup(BelaContext *context, void *userData)
{

}


/**
\example sinetone/render.cpp

Producing your first bleep!
---------------------------

This sketch is the hello world of embedded interactive audio. Better known as bleep, it 
produces a sine tone.

The frequency of the sine tone is determined by a global variable, `gFrequency`. 
The sine tone is produced by incrementing the phase of a sin function 
on every audio frame.

In render() you'll see a nested for loop structure. You'll see this in all Bela projects. 
The first for loop cycles through 'audioFrames', the second through 'audioChannels' (in this case left 0 and right 1). 
It is good to familiarise yourself with this structure as it's fundamental to producing sound with the system.
*/
