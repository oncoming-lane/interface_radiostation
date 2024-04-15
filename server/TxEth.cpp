#include "TxRx.h"
#define SERVER_IP "192.168.1.2" // IP адрес сервера
#define SERVER_PORT 1234 // Порт сервера
#define MAX_BUFFER_SIZE 1024     // Максимальный размер буфера для данных


int TxEth() {
    FILE *file;
    char buffer[MAX_BUFFER_SIZE];
    int sockfd;
    struct sockaddr_in server_addr;

    printf("TX_ETH EXECS NOW\n");

    // Открыть файл для чтения
    file = fopen("received_data.txt", "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    
    usleep(100000);
    
    // Прочитать данные из файла
    if (fgets(buffer, MAX_BUFFER_SIZE, file) == NULL) {
        perror("Error reading from file");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // Закрыть файл
    fclose(file);

    //printf("Buffer: %s\n", buffer);

    // Создание сокета
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    // Настройка структуры адреса сервера
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    // Подключение к серверу
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    // Отправка сообщения на сервер
    send(sockfd, buffer, strlen(buffer), 0);
    printf("Message sent to server: %s\n", buffer);

    close(sockfd);

    return 0;
}