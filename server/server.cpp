#include "TxRx.h"

int main() {
    while (1) {
        
        RxEth();
        Tx();
        usleep(10000);
        Rx();
        TxEth();
        
    }


    return 0;
}