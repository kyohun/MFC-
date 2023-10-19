#pragma once
#define REG_PNAME	TEXT("\\\\.\\pipe\\Reg")
#define MAX_NAME_LEN	256
#define MAX_ID_LEN		100
#define MAX_PW_LEN		20

#define REG_RES_OK		0
#define REG_RES_NO		-1

#define LOGIN_RES_OK		0	//����
#define LOGIN_RES_ALR		-1	//�̹� �α�����
#define LOGIN_RES_NOC		-2	//��� ��ȣ �ٸ�
#define LOGIN_RES_NOI		-3	//���̵� ����
#define LOGIN_RES_FA		-4	//�ƹ�ư ����

#define REG_REQ		0x0001
#define REG_RES		0x0002
#define UNREG_REQ	0x0003

#define LOGIN_REQ	0x0101
#define LOGIN_RES	0x0102
#define LOGOUT_REQ	0x0103