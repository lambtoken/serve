#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PORT 8080

int main(void) {
    int server_fd;
    struct sockaddr_in serv_address = {0};
    socklen_t addrlen = sizeof(serv_address);

    char* hello = 
        "HTTP/1.1 200 OK\r\n"
        "Content-Length: 23\r\n"
        "Content-Type: text/plain\r\n"
        "\r\n"
        "Hello from the server!\n";

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    serv_address.sin_family = AF_INET;
    serv_address.sin_port = htons(PORT);
    serv_address.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (struct sockaddr *)&serv_address, sizeof(serv_address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 5) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Listening on 8080!\n");

    while (420) {
        int client_fd = accept(server_fd, (struct sockaddr*)&serv_address, (socklen_t*)&addrlen);
        send(client_fd, hello, strlen(hello), 0);

        close(client_fd);
    }
    close(server_fd);
}
