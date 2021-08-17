#include "raw_socket.h"

 FILE *logfile;

int main()
{

    struct sockaddr saddr;
    int saddr_size=sizeof saddr,data_size,sock_raw,c;
    unsigned char *buffer = (unsigned char *) malloc(65536); //Its Big!

    //initializing
    logfile=open_log_file(logfile);
    sock_raw=open_rawSocket(sock_raw);

	while(1)
	{
	    set_mode(1);
	    while(!(c=get_key()))
	    {
		//Receive a packet
		data_size = recvfrom(sock_raw , buffer , 65536 , 0 , &saddr , (socklen_t*)&saddr_size);
		if(data_size <0 )
		{
			printf("Recvfrom error , failed to get packets\n");
			return 1;
		}
		//Now process the packet
		ProcessPacket(buffer , data_size);
		usleep(5000);
		printf("key %d\n",c);
	    }
	}
    close_all(sock_raw,logfile,buffer);
	return 0;
}

