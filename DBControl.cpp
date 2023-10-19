#include "pch.h"
#include "DBControl.h"

DBControl* DBControl::dbc = NULL;
#define INFO_DB TEXT("DSN=SYSTEM;UID=scott;PWD=tiger")

DBControl::DBControl()
{
	db.OpenEx(INFO_DB);
}

DBControl* DBControl::GetInstance()
{
	if (dbc == NULL)
	{
		dbc = new DBControl();
	}
	return dbc;
}

void DBControl::ExecuteQuery(LPCTSTR query)
{
	db.ExecuteSQL(query);
}

CRecordset* DBControl::Select()
{
	CRecordset* rs = new CRecordset(&db);
	return rs;
}

void DBControl::Close()
{
	db.Close();
}