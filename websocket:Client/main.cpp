
#include "header.h"




int main(int argc, char *argv[])
{

    struct sockaddr_in servadd;
    int sockfd;  //socket descriptor
    char dataPocket[MAXLINE];


    if (argc != 2)
        err_n_die("Usage: %s <server address>",argv[0]);

    //Creates  an endpoint for communication and returns a file descriptor
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0)
        err_n_die("CAN\'T CREAT A SOCKET");

    //Init socket and Specifying Addresses
    memset(&servadd, '\0', sizeof(servadd));
    servadd.sin_family = AF_INET;
    servadd.sin_port = htons(SERVER_PORT);

    //Convert second argument to binary address to using it
    if(inet_pton(AF_INET, argv[1], &servadd.sin_addr) <= 0)
        err_n_die("%s Is NOT A correct server address", argv[1]);

    //Try to Establish a connection
    if(connect(sockfd, (struct sockaddr *)&servadd, sizeof (servadd)) < 0)
        err_n_die("The Connect can't be established");
    //Connection established Successfully


    //Send Request
    sprintf(dataPocket, "Helloo Woooorld\n");
    write(sockfd, dataPocket, sizeof (dataPocket));

    //Receive Data
    memset(&dataPocket, '\0', sizeof (dataPocket));
    while (read(sockfd, dataPocket, MAXLINE-1) > 0){
        printf("%s", dataPocket);
        memset(&dataPocket, '\0', sizeof (dataPocket));
    }


    //Close the socket
    close(sockfd);


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
