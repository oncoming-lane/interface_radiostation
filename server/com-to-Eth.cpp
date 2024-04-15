#include "TxRx.h"

int main() {
    while (1) {
        // Считываем данные с Ethernet порта и записываем их в файл
        Rx();
        // Отправляем данные из файла на радиостанцию
        TxEth();
    }


    return 0;
}