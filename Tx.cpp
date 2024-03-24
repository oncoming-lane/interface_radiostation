#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <errno.h>

int main() {
    int fd;
    struct termios options;
    const char message[] = "\x05\x84\x01\x57\x0E";

    // Открываем COM порт для передачи
    fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY);
    if (fd == -1) {
        perror("open_port: Unable to open /dev/ttyUSB0 - ");
        return 1;
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