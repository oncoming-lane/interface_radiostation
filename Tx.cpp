#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <iostream>

#include "Tx.h"


#define DEV_DIR "/dev"

char *find_ttyUSB_port() {
    DIR *dir;
    struct dirent *entry;
    char *port = NULL;

    dir = opendir(DEV_DIR);
    if (!dir) {
        perror("Failed to open /dev directory");
        return NULL;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strncmp(entry->d_name, "ttyUSB", 6) == 0) {
            port = (char*)malloc(strlen(DEV_DIR) + strlen(entry->d_name) + 2);
            if (!port) {
                perror("Memory allocation error");
                closedir(dir);
                return NULL;
            }
            sprintf(port, "%s/%s", DEV_DIR, entry->d_name);
            break;
        }
    }

    closedir(dir);
    return port;
}

int transmit(std::string message1) {
    int fd;
    struct termios options;
    const char * message = message1.c_str();
    char *port = find_ttyUSB_port();
    //printf("Found ttyUSB port: %s\n", port);
    
    // Открываем COM порт для передачи
    fd = open(port, O_RDWR | O_NOCTTY);
    if (fd == -1) {
        perror("open_port: Unable to open /dev/ttyUSB0 - ");
        //return 1;
    }

    // Получаем текущие параметры порта
    tcgetattr(fd, &options);

    // Устанавливаем стандартные параметры порта для передачи
    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);
    options.c_cflag &= ~PARENB;    // Без контроля четности
    options.c_cflag &= ~CSTOPB;    // Один стоп-бит
    options.c_cflag &= ~CSIZE;     // Сбрасываем биты размера байта
    options.c_cflag |= CS8;        // Устанавливаем 8 битов данных

    // Устанавливаем флаг HUPCL
    options.c_cflag |= HUPCL;

    // Применяем новые параметры порта
    tcsetattr(fd, TCSANOW, &options);

    usleep(10000);

    // Записываем сообщение в порт
    int bytes_written = write(fd, message, strlen(message));
    if (bytes_written < 0) {
        perror("Error writing to port - ");
        return 1;
    }

    // Закрываем COM порт для передачи
    close(fd);

    return 0;
}

