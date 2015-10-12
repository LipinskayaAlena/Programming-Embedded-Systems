#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char* argv[])
{
  int socket_id;

  if((socket_id = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
     perror("ERROR in creating socket\n");
     return 1;
  }
  printf("Socket created\n");
  return 0;
}
