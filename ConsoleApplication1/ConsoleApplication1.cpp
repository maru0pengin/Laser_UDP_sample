#include "stdafx.h"
#include <conio.h>
#include<math.h>

#include <iostream>

const double PI = 3.1415926535897932384626433832795028841971; 

void data_set(int* data, int n) {
	for (int i = 0; i < n; i++) {
		data[i] = data[i] + 2 * i;   // �|�C���^ data �ɑ΂��� data[i] �Ə������ƂŔz��փA�N�Z�X�ł���
	}
}

// {x,y}�̏���

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

	//while (1) {
	//	sendto(sock, (char*)sendint, sizeof(sendint), 0, (struct sockaddr*)&addr, sizeof(addr));
	//}
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
				std::cout << sendint[i] << "\n";  // ���p�@�͂���܂Œʂ�
			}
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


	/** �ʐM�p�̃R���g���N�^ */
	WSAStartup(MAKEWORD(2, 0), &wsaData);
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(7);
	// mbed�̃A�h���X��ݒ�
	addr.sin_addr.S_un.S_addr = inet_addr("192.168.0.2");

	//WSADATA wsaData;
	//SOCKET sock;
	//struct sockaddr_in addr;


	///** �ʐM�p�̃R���g���N�^ */
	//WSAStartup(MAKEWORD(2, 0), &wsaData);
	//sock = socket(AF_INET, SOCK_DGRAM, 0);
	//addr.sin_family = AF_INET;
	//addr.sin_port = htons(7);
	//// mbed�̃A�h���X��ݒ�
	//addr.sin_addr.S_un.S_addr = inet_addr("192.168.0.2");


	//int r = 200;
	////int w = 600;
	////int h = 1400;
	////int sendint[6] = { 0,0,h,-w / 2,h,w };
	////int sendint[6] = { 0,0,-w / 2,-h,w / 2,-h };

	//int sendint[8] = { 0,0,r,0,r,r,0,r };
	////int sendint[8] = { 200,0,0,0,0,0,0,0 };

	//int flag = false;
	//while (1) {
	//	sendto(sock, (char*)sendint, sizeof(sendint), 0, (struct sockaddr *)&addr, sizeof(addr));
	//	if (_kbhit()) {
	//		if (getch() == '\r') // enter
	//			break;
	//	}
	//}
	//closesocket(sock);
	//WSACleanup();
	
	triangular(sock, addr,600,0.0);

	//const int n = 6;  // �z��̗v�f����萔�Œ�߂�
	//double array[n] = { 1,1,0,1,1,0 };   // int �^�̔z�� 

	//revolution(array, 0.5,6); // �z��փf�[�^��^����d����ʊ֐��ɔC����
	//														 // �z�� array �̐擪�A�h���X�� array �Ƃ������邱�Ƃ𗘗p�B����ɗv�f�� n ���n��

	//for (int i = 0; i < n; i++) {
	//	std::cout << array[i] << "\n";  // ���p�@�͂���܂Œʂ�
	//}
	//printf("x:%d y:%d", array[0], array[1]);


	return 0;
}

