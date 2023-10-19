#pragma once
#include <afxdb.h>

class DBControl
{
private:
	static DBControl* dbc;
	CDatabase db;
private:
	DBControl();
public:
	static DBControl* GetInstance();
public:
	void ExecuteQuery(LPCTSTR query);
	void Close();
public:
	CRecordset* Select();
};

