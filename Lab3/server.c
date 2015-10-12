#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
  int socket_id;

  if((socket_id = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    perror("ERROR in creating socket\n");
    return 1;
  }
  else
    printf("Socket was created\n");

  

  return 0;
}
