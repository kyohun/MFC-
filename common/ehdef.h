#pragma once
#define REG_PNAME	TEXT("\\\\.\\pipe\\Reg")
#define MAX_NAME_LEN	256
#define MAX_ID_LEN		100
#define MAX_PW_LEN		20

#define REG_RES_OK		0
#define REG_RES_NO		-1

#define LOGIN_RES_OK		0	//성공
#define LOGIN_RES_ALR		-1	//이미 로그인중
#define LOGIN_RES_NOC		-2	//비밀 번호 다름
#define LOGIN_RES_NOI		-3	//아이디 없음
#define LOGIN_RES_FA		-4	//아무튼 실패

#define REG_REQ		0x0001
#define REG_RES		0x0002
#define UNREG_REQ	0x0003

#define LOGIN_REQ	0x0101
#define LOGIN_RES	0x0102
#define LOGOUT_REQ	0x0103