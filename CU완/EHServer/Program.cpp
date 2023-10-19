#include "..\\EHPacketLib\\EHPacket.h"
#include "..\\RegLib\\RegReq.h"
#include "..\\RegLib\\RegRes.h"
#include "..\\UserDataLib\\UserData.h"
#include "..\\OrdDataLib\\\OrdData.h"
#include "..\\common\\ehdef.h"
#include "..\\common\ordef.h"
//#include "DBControl.h"

#include <conio.h>
#pragma comment(lib,"..\\x64\\Debug\\EHPacketLib.lib")
#pragma comment(lib,"..\\x64\\Debug\\RegLib.lib")
#pragma comment(lib,"..\\x64\\Debug\\LogLib.lib")
#pragma comment(lib,"..\\x64\\Debug\\OrdLib.lib")
#pragma comment(lib,"..\\x64\\Debug\\UserDataLib.lib")
#pragma comment(lib,"..\\x64\\Debug\\OrdDataLib.lib")
#pragma comment(lib,"ws2_32")
#pragma warning(disable:4996)
DWORD DoIt(LPVOID param);

void Init()
{
	MakeDB();
	Loading();
	MakeDB_or();
	Loading_or();
}
DWORD PipeEntry(LPVOID param)
{
	//1. 소켓 생성
	SOCKET lissock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//2.네트워크 인터페이스와 결합
	SOCKADDR_IN servaddr = {};
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("192.168.0.49");
	servaddr.sin_port = htons(10200);
	if (bind(lissock, (SOCKADDR*)&servaddr, sizeof(servaddr)) == -1)
	{
		printf("네트워크 인터페이스와 결합 오류\n");
		return 0;
	}
	//3.백로그 큐 크기 결정
	listen(lissock, 5);

	//4.AcceptLoop
	SOCKET dosock;
	SOCKADDR_IN cliaddr = {};
	int len = sizeof(cliaddr);
	while (1)
	{
		dosock = accept(lissock, (SOCKADDR*)&cliaddr, &len);
		if (dosock == -1)
		{
			break;
		}
		CloseHandle(CreateThread(0, 0, DoIt, (LPVOID)dosock, 0, 0));
	}
	//5.소켓 닫기
	closesocket(dosock);
	return 0;
}

void Run()
{
	DWORD tid;
	CloseHandle(CreateThread(0, 0, PipeEntry, 0, 0, &tid));
	printf("아무키나 누르면 서버를 종료합니다.\n");
	_getche();
}
void Exit()
{
	CleanUserDB();
}
//void myExitFunction() //프로그램 종료 전에 수행하고자 하는 작업을 여기에 추가
//{
//	DBControl* dbc = DBControl::GetInstance();
//	dbc->Close();
//}
int main()
{
	//DBControl* dbc = DBControl::GetInstance();

	WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 2), &wsadata);
	Init();
	Run();
	Exit();
	WSACleanup();

	//atexit(myExitFunction);

	return 0;
}
