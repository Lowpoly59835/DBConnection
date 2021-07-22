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
	void Resize(size_t length);
	bool Write(const char* desc, size_t length);
	void Clear() { memset(m_Buff, 0, max_size); write_size = 0; }
public:
	size_t Capacity();
	const char* c_str() { return m_Buff; }
	const wchar_t* c_wstr() { return (const wchar_t*)m_Buff; }
	bool empty() { return write_size == 0; }
private:
	static const int DEFAULT_SIZE = 128;

	size_t max_size;
	size_t write_size;
	char* m_Buff;
};


