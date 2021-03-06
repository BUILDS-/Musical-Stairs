#include <iostream>
#include <string>
#include <mysql.h>
#include <stdio.h>
#include <cstring>
#include <fcntl.h> /* File control definitions */
#include <errno.h> /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <cstdlib>
#include "RtMidi.h"


// Platform-dependent sleep routines.
#if defined(__WINDOWS_MM__)
  #include <windows.h>
  #define SLEEP( milliseconds ) Sleep( (DWORD) milliseconds ) 
#else // Unix variants
  #include <unistd.h>
  #define SLEEP( milliseconds ) usleep( (unsigned long) (milliseconds * 1000.0) )
#endif


using namespace std;

bool chooseMidiPort( RtMidiOut *rtmidi );
void noteOn (int);
void noteOff (int);

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

int serialport_read_until(int fd, char* buf, char until)
{
    char b[1];
    int i=0;
    do { 
        int n = read(fd, b, 1);  // read a char at a time
        if( n==-1) return -1;    // couldn't read
        if( n==0 ) {
            usleep( 10 * 1000 ); // wait 10 msec try again
            continue;
        }
        buf[i] = b[0]; i++;
    } while( b[0] != until );

    buf[i] = 0;  // null terminate the string
    return 0;
}


int main()
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
	  
	cout<<"BUILDS -- Musical Stairs"<<endl;
	
	int fd;
	struct termios options;

	fd = open("/dev/ttyUSB1", O_RDWR | O_NOCTTY | O_NONBLOCK);
	tcgetattr(fd, &options);
	
	cfsetispeed(&options, B9600);
	cfsetospeed(&options, B9600);

	char buf[256];
			
	while(1)
	{

		serialport_read_until(fd, buf, '\n');
   		printf("read: %s\n",buf);
		
		message[0] = 144;
		message[1] = (stair+29);
		message[2] = 90;
		midiout->sendMessage(&message);
		
		message[0] = 128;
		message[1] = (stair+29);
		message[2] = 40;
		midiout->sendMessage(&message);
		
	}
	return 1;
}
