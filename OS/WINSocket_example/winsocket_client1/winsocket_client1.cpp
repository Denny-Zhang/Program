// winsocket_client1.cpp: 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#pragma comment(lib, "Ws2_32.lib")

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <string.h>


void main()
{
	char confirm;
	char recvMsg[200], sendMsg[200];

	//開始 Winsock-DLL
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 1), &wsaData);

	//宣告給 socket 使用的 sockadder_in 結構
	SOCKADDR_IN addr;
	int addlen = sizeof(addr);

	//設定 socket
	SOCKET sConnect;
	sConnect = socket(AF_INET, SOCK_STREAM, NULL);

	//設定欲連線的Server的位址資訊
	inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1234);

	printf("connect to server?[Y] or [N] --> ");
	scanf_s("%c", &confirm, 1);

	if (confirm == 'N')
	{
		exit(1);
	}
	else {
		if (confirm == 'Y')
		{
			connect(sConnect, (SOCKADDR*)&addr, sizeof(addr));
			ZeroMemory(recvMsg, 200);
			recv(sConnect, recvMsg, sizeof(recvMsg), 0);
			printf("%s\n", recvMsg);
			while (strcmp(sendMsg, "exit") != 0) {
				//接收 server 端的訊息
				ZeroMemory(recvMsg, 200);
				recv(sConnect, recvMsg, sizeof(recvMsg), 0);
				printf("%s\n", recvMsg);
				printf("Enter Msg: ");
				scanf_s("%s", sendMsg, 200);
				send(sConnect, sendMsg, (int)strlen(sendMsg), 0);
			}
		}
	}

	closesocket(sConnect);
	WSACleanup();
	printf("bye bye...");
	system("pause");
}



