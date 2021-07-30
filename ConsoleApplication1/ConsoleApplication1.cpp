#include "stdafx.h"

int main()
{
	WSADATA wsaData;
	SOCKET sock;
	struct sockaddr_in addr;

	/** 通信用のコントラクタ */
	WSAStartup(MAKEWORD(2, 0), &wsaData);
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(7);
	// mbedのアドレスを設定
	addr.sin_addr.S_un.S_addr = inet_addr("192.168.0.2");
	int r = 1000;
	int sendint[8] = { 0,0,r,0,r,r,0,r };
	//int sendint[8] = { 200,0,0,0,0,0,0,0 };

	int flag = false;
	while (1) {
		sendto(sock, (char*)sendint, sizeof(sendint), 0, (struct sockaddr *)&addr, sizeof(addr));
	}
	closesocket(sock);
	WSACleanup();

	return 0;
}

