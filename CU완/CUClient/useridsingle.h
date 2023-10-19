#pragma once
class useridsingle
{
private:
	static useridsingle* instance;
	CString userid;
public:
	useridsingle();
	static useridsingle* GetInstance();
	void SetuserID(CString id);
	CString GetuserID();
};

