
#include "header.h"




int main(int argc, char *argv[])
{

    struct sockaddr_in servadd;
    int sockfd;  //socket descriptor
    char dataPocket[MAXLINE];


    //Creates  an endpoint for communication and returns a file descriptor
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0)
        err_n_die("CAN\'T CREAT A SOCKET");

    servadd.sin_family = AF_INET;
    servadd.sin_addr.s_addr = htonl(INADDR_ANY);
    servadd.sin_port = htons(SERVER_PORT);


    if(bind(sockfd, (struct sockaddr *)&servadd, sizeof (servadd)) < 0)
        err_n_die("Th Server Failed to bind");

    if(listen(sockfd, 5) < 0)
        err_n_die("The Server Failed in listening");


    //receive data for multiple connections
    while (true){
        int conctfd;
        int n;

        printf("Waiting for a connection on port %d\n", SERVER_PORT);
        fflush(stdout);
        conctfd = accept(sockfd, (struct sockaddr *) NULL, NULL);
        if(conctfd > 0)
            fprintf(stdout, "Accepted\n");

        memset(&dataPocket, '\0', sizeof (dataPocket));
        while ((n = read(conctfd, dataPocket, MAXLINE-1))> 0) {
            fprintf(stdout, "%s", dataPocket);

            if (dataPocket[n-1] == '\n')
                break;
            memset(&dataPocket, '\0', sizeof(dataPocket));
        }
    //Send response
    snprintf(dataPocket,sizeof (dataPocket),"HTTP/1.0 200 OK\r\n\r\nHello \tWWWooorrllld ");
    write(conctfd, dataPocket, strlen(dataPocket));
    close(conctfd);

    }




    return 0;
}







void err_n_die(const char *str, ...)
{
    va_list argv;
    va_start(argv, str);
    vfprintf(stderr, str, argv);
    fprintf(stderr, "\n");
    va_end(argv);
    exit(1);
}
