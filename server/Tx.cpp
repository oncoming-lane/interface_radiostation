#include "TxRx.h"
#define DEV_DIR "/dev"

int Tx() {
    int fd;
    struct termios options;
    FILE *file;
    char buffer[256];

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

    // Открываем файл для чтения
    file = fopen("received_data.txt", "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    // Читаем данные из файла
    size_t bytes_read = fread(buffer, sizeof(char), sizeof(buffer), file);
    if (bytes_read > 0) {
        // Отправляем данные через COM порт
        int bytes_written = write(fd, buffer, bytes_read);
        if (bytes_written < 0) {
            perror("Error writing to port - ");
            fclose(file);
            close(fd);
            return 1;
        }
    }

    // Закрываем файл и COM порт для передачи
    fclose(file);
    close(fd);

    return 0;
}