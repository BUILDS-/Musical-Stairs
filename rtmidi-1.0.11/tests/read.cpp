#include <iostream>
#include <string>
//#include <mysql.h>
#include <stdio.h>
#include <cstring>
#include <fcntl.h> /* File control definitions */
#include <errno.h> /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <cstdlib>
#include <stdlib.h>
#include "RtMidi.h"
#include <math.h>


// Platform-dependent sleep routines.
#if defined(__WINDOWS_MM__)
  #include <windows.h>
  #define SLEEP( milliseconds ) Sleep( (DWORD) milliseconds ) 
#else // Unix variants
  #include <unistd.h>
  #define SLEEP( milliseconds ) usleep( (unsigned long) (milliseconds * 1000.0) )
#endif


using namespace std;

template <class BidirectionalIterator>
  void reverse ( BidirectionalIterator first, BidirectionalIterator last)
{
  while ((first!=last)&&(first!=--last))
    swap (*first++,*last);
}

bool chooseMidiPort( RtMidiOut *rtmidi );
void noteOn (int);
void noteOff (int);

string binary( unsigned long n )
{
  string result;

  do result.push_back( '0' + (n & 1) );
  while (n >>= 1);

  //reverse( result.begin(), result.end() );
  return result;
}



 bool chooseMidiPort( RtMidiOut *rtmidi )
 {
  cout << "\nWould you like to open a virtual output port? [y/N] ";

  string keyHit="n";
  getline(cin, keyHit );
  if ( keyHit == "y" ) {
    rtmidi->openVirtualPort();
    return true;
  }

  string portName;
  unsigned int i = 0, nPorts = rtmidi->getPortCount();
  if ( nPorts == 0 ) {
    std::cout << "No output ports available!" << std::endl;
    return false;
  }

  if ( nPorts == 1 ) {
    cout << "\nOpening " << rtmidi->getPortName() << std::endl;
  }
  else {
    for ( i=0; i<nPorts; i++ ) {
      portName = rtmidi->getPortName(i);
      cout << "  Output port #" << i << ": " << portName << '\n';
    }

    do {
      cout << "\nChoose a port number: ";
     cin >> i;
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

	fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NONBLOCK);
	tcgetattr(fd, &options);
	
	cfsetispeed(&options, B9600);
	cfsetospeed(&options, B9600);

	unsigned char buf[256];
	
		// Program change: 192, 5
	  message.push_back( 192 );
	  message.push_back( 5 );
	  midiout->sendMessage( &message );

	  // Control Change: 176, 7, 100 (volume)
	  message[0] = 176;
	  message[1] = 7;
	  message.push_back( 125 );
	  midiout->sendMessage( &message );
	
	while(1)
	{
		serialport_read_until(fd, (char*)(buf), '\n');
   		//cout<<buf;
		if(buf[0]!='-')
		{
			if(buf[0]!='0')
			{
				string res = binary(strtoul((const char*)(buf),NULL,0));
				int i=0;
				cout<<res<<endl;;
				for(i=0;i<res.length();i++)
				{
					if(res[i]=='1')
					{
						//cout<<"Stair "<<i<<" is on"<<endl;
						message[0] = 144;
						message[1] = (i*4)+1;
						message[2] = 90;
						midiout->sendMessage( &message );
						cout<<(i*4)+1<<endl;
					}
				}
				
				sleep(1);
				for(i=0;i<res.length();i++)
				{
					if(res[i]=='1')
					{
						//cout<<"Stair "<<i<<" is off"<<endl;
						message[0] = 128;
						message[1] = (i*4)+1;
						message[2] = 40;
						midiout->sendMessage( &message );
					}
				}
				sleep (1);
			}
		}
  
		 /*  // Sysex: 240, 67, 16, 4, 3, 2, 247
		  message[0] = 240;
		  message[1] = 67;
		  message[2] = 4;
		  message.push_back( 3 );
		  message.push_back( 2 );
		  message.push_back( 247 );
		  midiout->sendMessage( &message );*/
		 // sleep(1);
	}
 
	cleanup:
  		delete midiout;
	return 0;
}
