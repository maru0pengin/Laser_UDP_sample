#include "stdafx.h"
#include <conio.h>
#include<math.h>

#include <iostream>
#include <fstream>

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



// M文字を描画する
void m(SOCKET sock, sockaddr_in addr, int r, int gap_y) {

	std::string filename("m.txt");
	std::ifstream input_file(filename);
	int sendint[2][12];
	int temp;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 10; j++) {
			input_file >> temp;
			sendint[i][j] = temp * 1000;
			std::cout << sendint[i][j];
		}
	}
	sendint[0][10] = 1;
	sendint[0][11] = 5;
	sendint[1][10] = 1;
	sendint[1][11] = 5;
	//int sendint[10] = { -r / 2, (r / 2) + gap_y ,-r / 2,(-r / 2) + gap_y,0,(r / 2) + gap_y,-r / 2,(r / 2) + gap_y,r / 2,(r / 2) + gap_y };
	double theta = 0.0;
	int count = 0;
	while (1) {
		printf("送ってます\n");
		Sleep(1000);
		sendto(sock, (char*)sendint[count%2], sizeof(sendint[count % 2]), 0, (struct sockaddr*)&addr, sizeof(addr));
		count++;
	}
	closesocket(sock);
	WSACleanup();

}

// M文字を描画する
void arrow(SOCKET sock, sockaddr_in addr, int r, int gap_y) {

	std::string filename("arrow.txt");
	std::ifstream input_file(filename);
	int sendint[8][20];
	int temp;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 18; j++) {
			input_file >> temp;
			sendint[i][j] = temp * 100;
			std::cout << sendint[i][j];

		}
		sendint[i][18] = 1;
		sendint[i][19] = 5;
	}
	//int sendint[10] = { -r / 2, (r / 2) + gap_y ,-r / 2,(-r / 2) + gap_y,0,(r / 2) + gap_y,-r / 2,(r / 2) + gap_y,r / 2,(r / 2) + gap_y };
	double theta = 0.0;
	while (1) {
		printf("送ってます\n");
		for (int i = 0; i < 8; i++) {
			Sleep(100);
			sendto(sock, (char*)sendint[i], sizeof(sendint[i]), 0, (struct sockaddr*)&addr, sizeof(addr));
		}

	}
	closesocket(sock);
	WSACleanup();

}


// ハ文字を描画する
void okumy(SOCKET sock, sockaddr_in addr) {

	int sendint[] = { 15571,12300,15948,12286,16209,12453,16234,13551,15996,13826,15548,13878,15279,13673,15274,12562,15571,12300,99,99,
		6012,11668,4885,12685,4081,12793,5246,11760,6012,11668,99,99,
		14933,8138,14264,8971,99,99,
		14721,7652,14057,8486,99,99,
		6540,7493,5877,8327,99,99,
		6373,6970,5712,7803,99,99,
		10018,5497,10162,5611,10170,6416,10398,7098,10867,7529,11548,7723,12884,7671,13014,7830,12888,8003,11169,8027,10356,7622,9930,6891,9826,6182,9858,5579,10017,5497,99,99,
		9654,6300,9679,6530,9302,6874,8694,7162,8012,7231,7871,7045,7983,6884,8493,6838,9061,6608,9425,6287,9654,6300,99,99,
		12166,4741,12480,4746,12693,4985,12692,5305,12486,5503,12150,5506,11936,5304,11936,4981,12164,4744,99,99,
		8374,4384,8737,4388,8927,4639,8928,5000,8718,5197,8370,5198,8161,4972,8162,4643,8374,4386,99,99,
		9207,416,10132,187,10808,1480,9877,1756,9207,416,99,99,
	115,8488,954,8173,2443,8991,4068,9736,3533,8885,3223,7875,3184,6811,3577,5577,4343,4492,5400,3483,6670,2732,7955,2205,9605,1902,11088,1831,12892,2082,14088,2431,15301,2975,16763,4084,17832,5378,18326,6702,18497,8094,18334,9119,17888,10123,17096,10737,16048,11049,16920,10306,17358,9427,17511,8500,17469,7291,16960,5761,16151,4622,15184,3804,13461,2818,11640,2198,10032,2065,8383,2238,7212,2747,6177,3437,5256,4289,4569,5372,4230,6298,4156,7421,4481,8632,5076,9573,5776,10323,7140,10794,9030,11230,10705,11526.12250,11722,14636,11820,16518,11670,18008,11353,18927,10940,20008,10231,20931,10031,18812,11155,17068,11705,15384,11990,13584,12103,11759,12044,9189,11744,6640,11190,4567,10614,2208,9674,115,8488
	};




	for (int i = 0; i < 292; i+=2) {
		if (sendint[i] != 99) {
			sendint[i] -= 10500;
			sendint[i] /= 10;
			sendint[i + 1] -= 7000;
			sendint[i + 1] /= 10;
		}
	}



	while (1) {
		//printf("hogehoge");
		sendto(sock, (char*)sendint, sizeof(sendint), 0, (struct sockaddr*)&addr, sizeof(addr));
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
	//addr.sin_addr.S_un.S_addr = inet_addr("192.168.11.12");
	
	arrow(sock, addr, 200, 0);



	/** 通信用のコントラクタ */
	//WSAStartup(MAKEWORD(2, 0), &wsaData);
	//sock = socket(AF_INET, SOCK_DGRAM, 0);
	//addr.sin_family = AF_INET;
	//addr.sin_port = htons(7);
	//// mbedのアドレスを設定
	//addr.sin_addr.S_un.S_addr = inet_addr("192.168.11.12");


	//int r = 1000;
	//int sendint[8] = { 0,0,r,0,r,r,0,r };

	//int cnt = 0;
	//while (1) {
	//	printf("送ってます\n");
	//	sendto(sock, (char*)sendint, sizeof(sendint), 0, (struct sockaddr*)&addr, sizeof(addr));
	//	Sleep(1000);
	//	cnt++;
	//	printf("%d\n",cnt);
	//}
	//closesocket(sock);
	//WSACleanup();


	return 0;
}

