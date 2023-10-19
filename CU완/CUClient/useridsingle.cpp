#include "pch.h"
#include "useridsingle.h"

useridsingle* useridsingle::instance = NULL;
useridsingle::useridsingle() {

}
useridsingle* useridsingle::GetInstance() {
	if (instance == NULL) {
		instance = new useridsingle();
	}
	return instance;
}
void useridsingle::SetuserID(CString id) {
	this->userid = id;
}
CString useridsingle::GetuserID() {
	return userid;
}