#pragma once
#include "ExportDefine.h"

class DBCONNECTIONDLL_EXPORTS_DECLSPEC CustomString
{
public:
	CustomString();
	CustomString(const char* value);
	CustomString(const wchar_t* value);
	CustomString(const CustomString& other);
	~CustomString();

	CustomString& operator=(const char* value);
	CustomString& operator+=(const char* value);
	CustomString& operator=(const wchar_t* value);
	CustomString& operator+=(const wchar_t* value);
	CustomString& operator=(const CustomString& other);
	operator const char* ();
	operator const wchar_t* ();

private:
	bool Write(const char* desc, size_t length);
	void Clear();
public:
	size_t Capacity();
	const char* c_str();
	const wchar_t* c_wstr();
	bool Empty();
	size_t Size();
	void Resize(size_t length);
private:
	static const int DEFAULT_SIZE = 128;

	size_t max_size;
	size_t write_size;
	char* m_Buff;
};


