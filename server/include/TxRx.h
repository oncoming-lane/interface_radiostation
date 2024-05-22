#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <dirent.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>

#define BUFFER_SIZE 255

void Rx(unsigned char *buffer);
int  Tx(unsigned char *buffer);

char *find_ttyUSB_port();

void RxEth(unsigned char *buffer);
void TxEth(unsigned char *global_buffer);
