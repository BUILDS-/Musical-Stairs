#include <iostream>
#include <string>
#include <mysql.h>
#include <stdio.h>
#include <cstring>
#include <fcntl.h> /* File control definitions */
#include <errno.h> /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

using namespace std;


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

   		/*MYSQL mysql; 
  		MYSQL_RES *res; 
   		MYSQL_ROW row; 

   		char query[90]; 
   		mysql_init(&mysql); 
   		
		if (!mysql_real_connect(&mysql,"localhost","door","buildsdoor","door",0,NULL,0))
		{
   			fprintf(stderr, "Failed to connect to database: Error: %s\n",
          		mysql_error(&mysql));
		}
		

   		sprintf(query,"SELECT first FROM users where swipe=\"%s\"",id.c_str()); 
		
   		
		if(mysql_real_query(&mysql,query,(unsigned int) strlen(query))!= 0 )
		{
			cout<<mysql_error(&mysql)<<endl;
		}
   		res = mysql_use_result(&mysql); 
		*/
   		//while((row = mysql_fetch_row(res)))
		//{ 
 		//	printf("Hello %s \n",row[0]); 
			
			serialport_read_until(fd, buf, '\n');
            printf("read: %s\n",buf);
			
			/*
			write(fd, "u\r", 3);
			int nbytes;
			#define BUFSIZE		30
			char bufptr[BUFSIZE];
			while ((nbytes = read(fd, bufptr, BUFSIZE)) > 0)
 			{
				//cout<<bufptr[-1]<<endl;
  				//bufptr += nbytes;
   				if (bufptr[-1] == '\n' || bufptr[-1] == '\r')
				{
					//cout<<"broke"<<endl;
	            			break;
				}
 			}
			//cout<<bufptr[-4]<<bufptr[-3]<<bufptr[-2]<<endl;
			//cout<<bufptr<<endl;
			//cout.write(bufptr,BUFSIZE);
   		//	mysql_free_result(res); 
		//}	
		*/
	}
	return 1;
}
