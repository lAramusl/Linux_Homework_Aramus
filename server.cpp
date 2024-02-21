#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <vector>
#include <thread>
#include <atomic>
#include <sstream>
#include <chrono>

static std::atomic<std::size_t> clientNum(0);

void clientHandler(int client_socket, std::string clientIP)
{
  // Receive messages from client
  std::size_t client_num = clientNum;
  while(true)
  {
      std::stringstream ss;
      char buffer[3001];
      int rs = recv(client_socket, buffer, 3000, 0);
      if (rs == -1) {
        perror("client socket connection error");
        close(client_socket);
        exit(1);
      }
      
      ss << "From client " << clientIP << " number " << client_num << " ";
      
      std::string message(buffer);
      if(message == "disconnect" && rs > 0)
      {
        ss << "client is disconnecting\n";//вот тут когда disconnect получает то падает в беск. цикл
        close(client_socket);
        clientNum.fetch_sub(1);
        std::cout << ss.str();
        break;
      }
      else if (rs > 0) {
        ss << "Got message:\n";
        buffer[rs] = '\0';
        ss << buffer << "\n";
      }
      std::cout << ss.str();
      std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  }
  return;
}

int main() {
  // create a socket  
  int server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (server_socket == -1) {
      perror("socket creation error");
      exit(errno);
  }

  // create an endpoint

  // socket address
  struct sockaddr_in server_address;
  // internet protocol = AF_INET
  server_address.sin_family = AF_INET;
  // accept or any address (bind the socket to all available interfaces)
  server_address.sin_addr.s_addr = htonl(INADDR_ANY);
  // port
  server_address.sin_port = htons(9888);

  // Bind server_socket to server_address
  if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
      perror("bind failed");
      exit(errno);
  }

  // Listen for incoming connections
  if (listen(server_socket, 1024) < 0) {
    perror("listen failed");
    exit(errno);
  }
  std::cout << "Waiting for connection\n";

  std::vector<std::thread> threadPool;
  while(true) 
  {
      int client_socket;
      struct sockaddr_in client_address;
      unsigned int client_addr_len = sizeof(client_address);

      // Accept incoming connection
      if ((client_socket = accept(server_socket, (struct sockaddr*) &client_address, &client_addr_len)) < 0) {
          perror("accept failed");
          exit(errno);
      }

      std::cout<< " Connected client with address: " << inet_ntoa(client_address.sin_addr) << "\n";

      threadPool.emplace_back(std::thread(clientHandler,client_socket,inet_ntoa(client_address.sin_addr)));
      clientNum.fetch_add(1);
  }
  for (auto& thread : threadPool)
  {
    if (thread.joinable())
    {
        thread.join();
    }
  }
  
  //close
  close(server_socket);
  return 0;
}