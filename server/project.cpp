#include "TxRx.h"

int main() {
    while (1) {
        // Считываем данные с Ethernet порта и записываем их в файл
        RxEth();
        // Отправляем данные из файла на радиостанцию
        Tx();
    }


    return 0;
}