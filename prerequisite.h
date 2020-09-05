#ifndef PREREQUISITE_H
#define PREREQUISITE_H

#ifdef _WIN32
	#include <winsock2.h>
	#include <windows.h>
	#include <conio.h>
#else
	#include <sys/socket.h>
	#include <errno.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <exception>

struct error_output : public std::exception
{
	void ErrorOutput(const char* Msg = "")
	{
		printf("ERROR: %s\n", Msg);
	}
};

void MySleep(int s)
{
#ifdef _WIN32
	Sleep(s * 1000);
#else
	sleep(s);
#endif
}

#endif

