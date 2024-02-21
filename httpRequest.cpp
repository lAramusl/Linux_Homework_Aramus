#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <fcntl.h>


int main(){

  struct sockaddr_in server_address;

  int client_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (client_socket == -1) {
        perror("socket creation error");
        exit(errno);
  }

  char buffer[4097];

  std::string httpRequest = "GET / HTTP/1.1\r\nHost: info.cern.ch\r\n\r\n";
  server_address.sin_addr.s_addr = inet_addr("188.184.100.182");
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(80);

  int connected = connect(client_socket, (struct sockaddr*) &server_address, sizeof(server_address));

  if(connected == -1){
    perror("connection failed");
    close(client_socket);
    exit(errno);
  }

  int sent = send(client_socket, httpRequest.c_str(), httpRequest.size(), 0);
  if(sent == -1){
    perror("sent:");
    close(client_socket);
    exit(errno);
  }
  std::cout << "message sent\n";

  int fd = open("site.html",O_CREAT|O_TRUNC|O_WRONLY,0666);
  int rs = 1;
  int wrt = 0;
  while(rs != 0)
    {
      std::cout << "recieveing...\n";
      rs = recv(client_socket, buffer, 4096, 0);
      if (rs == -1) {
        perror("client socket connection error");
        close(client_socket);
        exit(1);
      }
      wrt = write(fd,buffer,4096);
      if(wrt == -1)
      {
        perror("write error");
        exit(1);
      }
    }
  std::cout << "DONE!\n";
  close(fd);
  close(client_socket);
  return 0;
}