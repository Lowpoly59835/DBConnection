#pragma once
#include "ExportDefine.h"

class DBCONNECTIONDLL_EXPORTS_DECLSPEC CustomString
{
public:
	CustomString();
	CustomString(const char* value);
	CustomString(CustomString& other) = delete;
	~CustomString();

	CustomString& operator=(const char* value);
	CustomString& operator+=(const char* value);
	CustomString& operator=(CustomString& other) = delete;

private:
	void Resize(int length);
	bool Write(const char* desc, int length);
	inline void Clear() { memset(m_Buff, 0, max_size); write_size = 0; }
public:
	size_t Capacity();

private:
	static const int DEFAULT_SIZE = 128;

	int max_size;
	unsigned int write_size;
	char* m_Buff;
};


