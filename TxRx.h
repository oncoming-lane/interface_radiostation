#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <iostream>


char *find_ttyUSB_port();



int transmit(std::string message1);

void recieve();
