#include "TxRx.h"
#define PORT 1234
#define FILENAME "received_data.txt"

int RxEth() {
    int sockfd, newsockfd;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    // Создаем сокет
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error opening socket");
        exit(1);
    }

    // Устанавливаем опцию SO_REUSEADDR
    int optval = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    // Инициализируем структуру serv_addr
    memset((char *) &serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    // Привязываем сокет к адресу и порту
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error on binding");
        exit(1);
    }

    // Слушаем входящие соединения
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    // Принимаем входящее соединение
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0) {
        perror("Error on accept");
        exit(1);
    }

    // Читаем данные из сокета
    memset(buffer, 0, sizeof(buffer));
    n = read(newsockfd, buffer, sizeof(buffer) - 1);
    if (n < 0) {
        perror("Error reading from socket");
        exit(1);
    }
    printf("Here is the message: %s\n", buffer);

    // Отправляем подтверждение клиенту
    /*n = write(newsockfd, "I got your message", 18);
    if (n < 0) {
        perror("Error writing to socket");
        exit(1);
    }*/
    
     // Записываем данные в файл
    FILE *file = fopen(FILENAME, "w");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }
    fprintf(file, "%s", buffer);
    fclose(file);
    printf("Data written to file: %s\n", FILENAME);


    // Закрываем сокеты
    close(newsockfd);
    close(sockfd);

    return 0;
}