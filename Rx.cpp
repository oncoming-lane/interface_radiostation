#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <sys/ioctl.h>

#define BUFFER_SIZE 255
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

int main() {
    int fd;
    struct termios options;
    unsigned char buffer[BUFFER_SIZE];

    char *port = find_ttyUSB_port();
    printf("Found ttyUSB port: %s\n", port);
    // Открываем COM порт для передачи
    fd = open(port, O_RDWR | O_NOCTTY);
    if (fd == -1) {
        perror("open_port: Unable to open /dev/ttyUSB0 - ");
        return 1;
    }

    // Получаем текущие параметры порта
    tcgetattr(fd, &options);

    // Устанавливаем стандартные параметры порта для приёма
    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);
    options.c_cflag &= ~PARENB;    // Без контроля четности
    options.c_cflag &= ~CSTOPB;    // Один стоп-бит
    options.c_cflag &= ~CSIZE;     // Сбрасываем биты размера байта
    options.c_cflag |= CS8;        // Устанавливаем 8 битов данных

    // Отключаем сигнал DTR
    int status;
    ioctl(fd, TIOCMGET, &status); // Получаем текущее состояние сигналов
    status &= ~TIOCM_DTR; // Отключаем DTR
    ioctl(fd, TIOCMSET, &status); // Устанавливаем новое состояние сигналов
    usleep(100000);

    // Устанавливаем флаг RTS
    options.c_cflag |= CRTSCTS;
    
    // Применяем новые параметры порта
    tcsetattr(fd, TCSANOW, &options);


    // Открываем файл для записи данных
    FILE *file = fopen("received_data.txt", "w");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    usleep(100000);

    // Читаем данные из порта
    ssize_t bytes_read;
    while (1) {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read > 0) {
            //printf("Received data: ");
            for (int i = 0; i < bytes_read; ++i) {
                printf("Received data: %02X\n", buffer[i]); // Выводим байты в шестнадцатеричном формате
                fprintf(file, "%02X", buffer[i]);
            }
            fflush(stdout); // Принудительно очищаем буфер вывода в терминал
            fflush(file);
         } else if (bytes_read == -1) {
            perror("Error reading from port - ");
            break;
        }
    }

    // Закрываем файл
    fclose(file);
    
    // Закрываем COM порт для приёма
    close(fd);

    return 0;
}