#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

void *function(int param)
{
  int read_size, file_size;
  int client_id = param;
  char name_file[256];
  char text_in_file[256];
  FILE *file;
  read_size = recv(client_id, name_file, 256, 0);

  if(read_size == 0)
  {
     perror("Client disconnected\n");
     close(client_id);
     return;
  }
  else if(read_size == -1)
  {
     perror("recv failed\n");
     close(client_id);
     return;
  }
  
  if(access(name_file, F_OK) < 0)
  {
     perror("File not found\n");
     close(client_id);
     return; 
  }

  file = fopen(name_file, "r");

  if(file == NULL)
  {
     perror("ERROR in openning file\n");
     close(client_id);
     return;
  }

  while(1)
  {
     read_size = fread(text_in_file, 1, 256, file);
     if(read_size > 0)
        send(client_id, text_in_file, 256, 0);

     if(feof(file))
     {
	printf("File was sent\n");
	break;
     }
  }
  
  fclose(file);
  close(client_id);
}

int main(int argc, char* argv[])
{
  int socket_id, client_id, c;
  struct sockaddr_in server_addr, client_addr;

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
  
  printf("waiting for incoming connections\n");

  c = sizeof(struct sockaddr_in);
  while((client_id = accept(socket_id, (struct sockaddr *)&client_addr, (socklen_t *)&c)))
  {	
    printf("Connection accepted\n");
    function(client_id);
  }

  if(client_id < 0)
    {
       perror("ERROR in accepting\n");
       return 1;
    }

  return 0;
}
