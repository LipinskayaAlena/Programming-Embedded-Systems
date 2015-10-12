#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char* argv[])
{
  int socket_id, read_size;
  struct sockaddr_in addr;
  char text[256], nameFile[256];

  if((socket_id = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
     perror("ERROR in creating socket\n");
     return 1;
  }
  printf("Socket created\n");

  addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8888);

  if(connect(socket_id, (struct sockaddr *)&addr, sizeof(addr)) < 0)
  {
     perror("ERROR. Connect failed\n");
     close(socket_id);
     return 1;
  }
  printf("Connected\n");

  printf("Enter name file:\n");
  scanf("%s", nameFile);
  if(send(socket_id, nameFile, 256, 0) < 0)
  {
      perror("Send nameFile failed\n");
      close(socket_id);
      return 1;
  }
  
  while((read_size = recv(socket_id, text, 256, 0)) > 0)
     printf("%s\n",text);       

  if(read_size < 0)
  {
     perror("recv failed\n");
     close(socket_id);
     return 1;
  }

  printf("Reading finished\n");
  close(socket_id);
  
  return 0;
}
