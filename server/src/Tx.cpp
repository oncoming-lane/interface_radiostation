#include "TxRx.h"
#define DEV_DIR "/dev"

int Tx(unsigned char *buffer) {
    int fd;
    struct termios options;

    char *port = find_ttyUSB_port();
    printf("Found ttyUSB port: %s\n", port);

    // Открываем COM порт для передачи
    fd = open(port, O_RDWR | O_NOCTTY);
    if (fd == -1) {
        perror("open_port: Unable to open /dev/ttyUSB0 - ");
        return 1;
    }

    // Получаем текущие параметры порта
    if (tcgetattr(fd, &options) < 0)
        printf("Error getting options");

    // Устанавливаем стандартные параметры порта для передачи
    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);

    // Устанавливаем параметры порта
    options.c_cflag &= ~(CSIZE | CSTOPB | PARENB); // Очищаем биты размера байта, стоп-бита и биты контроля четности
    options.c_cflag |= CS8; // Устанавливаем 8 битов данных
    options.c_cflag |= CLOCAL | CREAD | HUPCL; // Устанавливаем флаги для локального режима, разрешения приема данных и сброса линии при закрытии
    options.c_iflag |= IGNBRK | IGNPAR; // Игнорируем BREAK-сигналы и ошибки битов четности
    options.c_oflag = 0; // Отключаем обработку выходного потока
    options.c_lflag = 0; // Отключаем обработку локального потока

    // Устанавливаем флаги управления потоком (например, RTS/CTS)
    options.c_cflag |= CRTSCTS;

    // Применяем новые параметры порта
    tcsetattr(fd, TCSANOW, &options);

    // Поднимаем сигналы DTR и RTS
    int status;
    if (ioctl(fd, TIOCMGET, &status) < 0) 
    {
        perror("Error getting status");
        close(fd);
        return 1;
    }
    status |= TIOCM_DTR; // Поднимаем DTR
    status |= TIOCM_RTS; // Поднимаем RTS
    if (ioctl(fd, TIOCMSET, &status) < 0) 
    {
        perror("Error setting status");
        close(fd);
    }

    usleep(10000);

    // Отправляем данные через COM порт
    int bytes_written = write(fd, buffer, BUFFER_SIZE);

    if (bytes_written < 0) 
    {
        perror("Error writing to port - ");
        close(fd);
        return 1;
    }

     // Опускаем сигналы DTR и RTS
    if (ioctl(fd, TIOCMGET, &status) < 0) 
    {
        perror("Error getting status");
        close(fd);
        return 1;
    }
    status |= TIOCM_DTR | TIOCM_RTS;
    if (ioctl(fd, TIOCMSET, &status) < 0) 
    {
        perror("Error getting status");
        close(fd);
        return 1;
    }
    // Закрываем файл и COM порт для передачи
    close(fd);

    return 0;
}