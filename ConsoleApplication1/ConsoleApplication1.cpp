#include "stdafx.h"
#include <conio.h>
#include<math.h>

#include <iostream>

const double PI = 3.1415926535897932384626433832795028841971; 

void data_set(int* data, int n) {
	for (int i = 0; i < n; i++) {
		data[i] = data[i] + 2 * i;   // ポインタ data に対して data[i] と書くことで配列へアクセスできる
	}
}

// {x,y}の順番

void revolution( int* array, double theta , int n) {
	for (int i = 0; i < n; i+=2) {
		int x = array[i];
		int y = array[i+1];
		array[i] = round((double)x * cos(theta) - (double)y * sin(theta));
		array[i+1] = round((double)x * sin(theta) + (double)y * cos(theta));
	}
}

void square(SOCKET sock, sockaddr_in addr,int r) {
	int sendint[8] = { 0,0,r,0,r,r,0,r };

	int flag = false;

	while (1) {
		sendto(sock, (char*)sendint, sizeof(sendint), 0, (struct sockaddr*)&addr, sizeof(addr));
	}
	closesocket(sock);
	WSACleanup();

}

void triangular(SOCKET sock, sockaddr_in addr, int r,double theta) {
	int sendint[6] = { 1,1,r,1,1,-r };

	int count = 0;
	while (1) {
		sendto(sock, (char*)sendint, sizeof(sendint), 0, (struct sockaddr*)&addr, sizeof(addr));
		count++;

		if (count == 10000) {
			count = 0;
			revolution(sendint,-PI/4, 6);
			for (int i = 0; i < 6; i++) {
				std::cout << sendint[i] << "\n";  // 利用法はこれまで通り
			}
		}
		if (_kbhit()) {
			if (getch() == '\r') // enter
				break;
		}
	}
	closesocket(sock);
	WSACleanup();

}


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
	
	triangular(sock, addr,600,0.0);

	return 0;
}

