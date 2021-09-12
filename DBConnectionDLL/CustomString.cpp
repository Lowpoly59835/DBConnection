#include "pch.h"
#include "CustomString.h"
#include "IConnection.h"
#include <string>
#include <clocale>
#include "IConnection.h"

using namespace std;
using NetworkCommon::DBConnection::CustomString;

CustomString::CustomString()
	:write_size(0), max_size(DEFAULT_SIZE)
{
	m_Buff = new char[max_size] {0};
}

CustomString::CustomString(const char* value)
	: CustomString::CustomString()
{
	Write(value, strlen(value));
}

CustomString::CustomString(const wchar_t* value)
	: CustomString::CustomString()
{
	Write(value, wcslen(value));
}

CustomString::CustomString(const CustomString& other)
	: CustomString::CustomString()
{
	Write(other.m_Buff, other.write_size);
}

CustomString::~CustomString()
{
	if (m_Buff != nullptr)
	{
		delete[] m_Buff;
		m_Buff = nullptr;
	}
}

CustomString& CustomString::operator=(const char* value)
{
	// TODO: ���⿡ return ���� �����մϴ�.
	Clear();
	Write(value, strlen(value));
	return *this;
}

CustomString& CustomString::operator+=(const char* value)
{
	// TODO: ���⿡ return ���� �����մϴ�.
	Write(value, strlen(value));
	return *this;
}

CustomString& CustomString::operator=(const wchar_t* value)
{
	// TODO: ���⿡ return ���� �����մϴ�.
	Clear();
	Write(value, wcslen(value));
	return *this;
}

CustomString& CustomString::operator+=(const wchar_t* value)
{
	// TODO: ���⿡ return ���� �����մϴ�.
	Write(value, wcslen(value));
	return *this;
}

CustomString& CustomString::operator=(const CustomString& other)
{
	// TODO: ���⿡ return ���� �����մϴ�.
	Clear();
	Write(other.m_Buff, other.write_size);
	return *this;
}

CustomString::operator const char* ()
{
	return c_str();
}

size_t CustomString::Size()
{
	return write_size;
}

void CustomString::Resize(size_t length)
{
	if (length <= Capacity())
	{
		return;
	}

	size_t newSize = max_size;

	do
	{
		newSize += newSize / 2;
	} while (newSize < write_size + length);

	char* newBuf = new char[newSize] {0};

	memcpy(newBuf, m_Buff, write_size);
	delete[] m_Buff;

	m_Buff = newBuf;
	max_size = newSize;
}

size_t CustomString::Max()
{
	return max_size;
}


bool CustomString::Write(const char* desc, size_t length)
{
	if (desc == nullptr) return false;

	Resize(length);

	memcpy(&m_Buff[write_size], desc, length);
	write_size += length;

	return true;
}

bool CustomString::Write(const wchar_t* desc, size_t length)
{
	if (desc == nullptr) return false;

	//length = length;
	Resize(length * 2);
	WideCharToMultiByte(CP_ACP, 0, desc, -1, &m_Buff[write_size], Capacity(), 0, 0);
	write_size += strlen(m_Buff);

	return true;
}

void CustomString::Clear()
{
	memset(m_Buff, 0, max_size); write_size = 0;
}

const char* CustomString::c_str()
{
	return m_Buff;
}



const char* CustomString::data()
{
	return m_Buff;
}

bool CustomString::Empty()
{
	return write_size == 0;
}

size_t CustomString::Capacity()
{
	return max_size - write_size;
}
