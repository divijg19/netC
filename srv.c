/* This is a basic TCP server implementation in C. It listens for incoming connections on a specified port and handles client requests. */
/* srv.c */

#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define PORT 8181

int main()
{
    int s, c;
    socklen_t addrlen;
    struct sockaddr_in srv, cli;
    char buf[1024];
    char *data;

    memset(&srv, 0, sizeof(srv));
    memset(&cli, 0, sizeof(cli));
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) 
    {
        printf("socket() failed\n");
        return -1;
    }

    srv.sin_family = AF_INET;
    srv.sin_addr.s_addr = INADDR_ANY; // 0: Listen on all interfaces
    srv.sin_port = htons(PORT);
    if (bind(s, (struct sockaddr *)&srv, sizeof(srv)))
    {
        printf("bind() failed\n");
        close(s);
        
        return -1;
    }
    if (listen(s, 5))
    {
        printf("listen() failed\n");
        close(s);

        return -1;
    }
    printf("Server is listening on port %d...\n", PORT);

    c = accept(s, (struct sockaddr *)&cli, &addrlen);
    if (c < 0)
    {
        printf("accept() failed\n");
        close(s);

        return -1;
    }
    printf("Client connected: %s:%d\n", inet_ntoa(cli.sin_addr), ntohs(cli.sin_port));
    read(c, buf, sizeof(buf));
    printf("Received from client: %s\n", buf);
    data = "httpd v1.0\n";
    write(c, data, strlen(data));
    
    close(c);
    close(s);

    return 0;
}


