#include "pch.h"
#include "CustomString.h"

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
	Write((const char*)value, wcslen(value) / 2);
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
	// TODO: 여기에 return 문을 삽입합니다.
	Clear();
	Write(value, strlen(value));
	return *this;
}

CustomString& CustomString::operator+=(const char* value)
{
	// TODO: 여기에 return 문을 삽입합니다.
	Write(value, strlen(value));
	return *this;
}

CustomString& CustomString::operator=(const wchar_t* value)
{
	// TODO: 여기에 return 문을 삽입합니다.
	Clear();
	Write((const char*)value, wcslen(value) / 2);
	return *this;
}

CustomString& CustomString::operator+=(const wchar_t* value)
{
	// TODO: 여기에 return 문을 삽입합니다.
	Write((const char*)value, wcslen(value) / 2);
	return *this;
}

CustomString& CustomString::operator=(const CustomString& other)
{
	// TODO: 여기에 return 문을 삽입합니다.
	Clear();
	Write(other.m_Buff, other.write_size);
	return *this;
}

CustomString::operator const char* ()
{
	return c_str();
}

CustomString::operator const wchar_t* ()
{
	return c_wstr();
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

	char* newBuf = new char[newSize];

	memcpy(newBuf, m_Buff, write_size);
	delete[] m_Buff;

	m_Buff = newBuf;
	max_size = newSize;
}

bool CustomString::Write(const char* desc, size_t length)
{
	if (desc == nullptr) return false;

	Resize(length);

	memcpy(&m_Buff[write_size], desc, length);
	write_size += length;

	return true;
}

size_t CustomString::Capacity()
{
	return max_size - write_size;
}
