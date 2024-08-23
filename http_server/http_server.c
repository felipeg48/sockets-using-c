#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <unistd.h>

int main() {
    // open a file to serve
    FILE *html_data = fopen("/Users/felipeg/Progs/Langs/CPP/C/socket/http/index.html", "r");
    char response_data[1024];
    fgets(response_data, 1024, html_data) ;

    // create a socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Error creating socket");
        exit(1);
    }

    // define the address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8001);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Error binding socket");
        exit(1);
    }


    if (listen(server_socket, 5) < 0) {
        perror("Error listening on socket");
        exit(1);
    }


    int client_socket;

    while(1) {
        client_socket = accept (server_socket, NULL, NULL) ;
        if (client_socket < 0) {
            perror("Error accepting connection");
            continue; // Continue to the next iteration of the loop
        }

        // Add Content-Type and Content-Length headers
        char http_header[2048] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: ";
        char content_length_str[20];
        sprintf(content_length_str, "%zu\r\n\r\n", strlen(response_data));
        strcat(http_header, content_length_str);
        strcat(http_header, response_data);

        // Send the response
        if (send(client_socket, http_header, strlen(http_header), 0) < 0) {
            perror("Error sending data");
        }

        close(client_socket);
    }
    return 0;
}