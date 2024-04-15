#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <arpa/inet.h>

#include <cstring>
#include <string>
#include <fstream>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int transmit_eth(std::string message1);

std::string receive_eth();
