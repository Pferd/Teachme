/***********************************
************************************
Author: RC (Ludwing)
Friday 31 May 2013 12:29:10 PM IST *
LGPL *******************************
***********************************/ 

#include <iostream>
#include <cstring>      // Needed for memset
#include <sys/socket.h> // Needed for the socket functions
#include <netdb.h>      // Needed for the socket functions
#include <errno.h>	// Needed for error description

int main()
{

  int status; // status check for connections!
  int socketfd; // Socket descriptor
  struct addrinfo host_info;       // The struct that getaddrinfo() fills up with data.
  struct addrinfo *host_info_list; // Pointer to the to the linked list of host_info's.
     
  memset(&host_info, 0, sizeof host_info);

  std::cout << "Setting up the structs..."  << std::endl;

  host_info.ai_family = AF_UNSPEC;     // IP version not specified. Can be both.
  host_info.ai_socktype = SOCK_STREAM; // Use SOCK_STREAM for TCP or SOCK_DGRAM for UDP.

  // Now fill up the linked list of host_info structs with google's address information.
  status = getaddrinfo("www.google.com", "80", &host_info, &host_info_list);
  // getaddrinfo returns 0 on succes, or some other value when an error occured.
  // (translated into human readable text by the gai_gai_strerror function).
  if (status != 0)  std::cout << "getaddrinfo error" << gai_strerror(status) ;

  // Having information, now try to connect to a google.

  std::cout << "Creating socket to connect google" << std::endl;

socketfd=socket(host_info_list->ai_family,host_info_list->ai_socktype,host_info_list->ai_protocol);

if(socketfd==-1)
std::cout<< "Unable to create socket"<< std::endl;
else
{
std::cout<< "Successfully socket created with number "<<socketfd<< std::endl;
}

std::cout << "connecting ......" << std::endl;

status = connect(socketfd,host_info_list->ai_addr,host_info_list->ai_addrlen); // connect to google with the address and socket information

if(status==-1)
std::cout<< "unable to connect" << std::endl;\
else
{
std::cout<< "connected" << std::endl;
}

// send the information	

std::cout << "sending information" << std::endl;

char msg[50] = "GET / HTTP/1.1 host: www.google.com \n\n";
int len;
ssize_t bytes_sent;
len=strlen(msg);
bytes_sent=send(socketfd,msg,len,0);

// Receive information

std::cout << "Waiting to recieve data..."  << std::endl;
ssize_t bytes_recieved;
char incoming_data_buffer[1000];
bytes_recieved = recv(socketfd, incoming_data_buffer,1000, 0);
// If no data arrives, the program will just wait here until some data arrives.
if (bytes_recieved == 0) std::cout << "host shut down." << std::endl ;
if (bytes_recieved == -1)std::cout << "recieve error!" << std::endl ;
std::cout << bytes_recieved << " bytes recieved :" << std::endl ;
std::cout << incoming_data_buffer << std::endl;

std::cout<<"Receiveing Complete"<<std::endl;
// Free memory!
freeaddrinfo(host_info_list);

}    
