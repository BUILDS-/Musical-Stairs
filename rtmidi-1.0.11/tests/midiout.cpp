//*****************************************//
//  midiout.cpp
//  by Gary Scavone, 2003-2004.
//
//  Simple program to test MIDI output.
//
//*****************************************//

#include <iostream>
#include <cstdlib>
#include "RtMidi.h"
using namespace std;

// Platform-dependent sleep routines.
#if defined(__WINDOWS_MM__)
  #include <windows.h>
  #define SLEEP( milliseconds ) Sleep( (DWORD) milliseconds ) 
#else // Unix variants
  #include <unistd.h>
  #define SLEEP( milliseconds ) usleep( (unsigned long) (milliseconds * 1000.0) )
#endif

// This function should be embedded in a try/catch block in case of
// an exception.  It offers the user a choice of MIDI ports to open.
// It returns false if there are no ports available.
bool chooseMidiPort( RtMidiOut *rtmidi );
void noteOn (int);
void noteOff (int);
int main( int argc, int arduino, char *argv[])
{
  RtMidiOut *midiout = 0;
  std::vector<unsigned char> message;

  // RtMidiOut constructor
  try {
    midiout = new RtMidiOut();
  }
  catch ( RtError &error ) {
    error.printMessage();
    exit( EXIT_FAILURE );
  }

  // Call function to select port.
  try {
    if ( chooseMidiPort( midiout ) == false ) goto cleanup;
  }
  catch ( RtError &error ) {
    error.printMessage();
    goto cleanup;
  }

  // Send out a series of MIDI messages.

  // Program change: 192, 5
  message.push_back( 192 );
  message.push_back( 5 );
  midiout->sendMessage( &message );

  // Control Change: 176, 7, 100 (volume)
  message[0] = 176;
  message[1] = 7;
  message.push_back( 100 );
  midiout->sendMessage( &message );

  while(1)
  {
    for (int ii=0;ii<28;ii++)
    {
      if (ii&arduino)
      {
	noteOn(ii);
      }
      else
      {
	noteOff(ii);
      }
    }
  }

  // Sysex: 240, 67, 16, 4, 3, 2, 247
  message[0] = 240;
  message[1] = 67;
  message[2] = 4;
  message.push_back( 3 );
  message.push_back( 2 );
  message.push_back( 247 );
  midiout->sendMessage( &message );

  // Clean up
 cleanup:
  delete midiout;

  return 0;
}

 bool chooseMidiPort( RtMidiOut *rtmidi )
 {
  std::cout << "\nWould you like to open a virtual output port? [y/N] ";

  std::string keyHit="n";
  if ( keyHit == "y" ) {
    rtmidi->openVirtualPort();
    return true;
  }

  std::string portName;
  unsigned int i = 0, nPorts = rtmidi->getPortCount();
  if ( nPorts == 0 ) {
    std::cout << "No output ports available!" << std::endl;
    return false;
  }

  if ( nPorts == 1 ) {
    std::cout << "\nOpening " << rtmidi->getPortName() << std::endl;
  }
  else {
    for ( i=0; i<nPorts; i++ ) {
      portName = rtmidi->getPortName(i);
      std::cout << "  Output port #" << i << ": " << portName << '\n';
    }

    do {
      std::cout << "\nChoose a port number: ";
      i=8;
    } while ( i >= nPorts );
  }

  rtmidi->openPort( i );

  return true;
}
void noteOn(int stair)
{
  RtMidiOut *midiouton = 0;
  std::vector<unsigned char> messageon;
  midiouton = new RtMidiOut();

  messageon[0] = 144;
  messageon[1] = (stair+29);
  messageon[2] = 90;
  midiouton->sendMessage( &messageon );
}

void noteOff(int stair)
{
  RtMidiOut *midioutoff = 0;
  std::vector<unsigned char> messageoff;
  midioutoff = new RtMidiOut();

  messageoff[0] = 128;
  messageoff[1] = (stair+29);
  messageoff[2] = 40;
  midioutoff->sendMessage( &messageoff );
}
