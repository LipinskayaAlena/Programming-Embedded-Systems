#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
  int socket_id;
  struct sockaddr_in server_addr

  if((socket_id = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    perror("ERROR in creating socket\n");
    return 1;
  }
  else
    printf("Socket was created\n");

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(8888);

  if(bind(socket_id,(struct sockaddr*)&server_addr,sizeof(server_addr)) < 0)
  {
    perror("ERROR. Bind faild\n");
    return 1;
  }
  else
    printf("Bind done\n");
 
  listen(socket_id, 3);

  return 0;
}
