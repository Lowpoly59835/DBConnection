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

void CustomString::Resize(int length)
{
	if (length <= Capacity())
	{
		return;
	}

	int newSize = max_size;

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

bool CustomString::Write(const char* desc, int length)
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
