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
	//1. ���� ����
	SOCKET lissock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//2.��Ʈ��ũ �������̽��� ����
	SOCKADDR_IN servaddr = {};
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("192.168.0.49");
	servaddr.sin_port = htons(10200);
	if (bind(lissock, (SOCKADDR*)&servaddr, sizeof(servaddr)) == -1)
	{
		printf("��Ʈ��ũ �������̽��� ���� ����\n");
		return 0;
	}
	//3.��α� ť ũ�� ����
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
	//5.���� �ݱ�
	closesocket(dosock);
	return 0;
}

void Run()
{
	DWORD tid;
	CloseHandle(CreateThread(0, 0, PipeEntry, 0, 0, &tid));
	printf("�ƹ�Ű�� ������ ������ �����մϴ�.\n");
	_getche();
}
void Exit()
{
	CleanUserDB();
}
//void myExitFunction() //���α׷� ���� ���� �����ϰ��� �ϴ� �۾��� ���⿡ �߰�
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
