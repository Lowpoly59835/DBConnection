#pragma once
#include "ExportDefine.h"

namespace NetworkCommon
{
	namespace DBConnection
	{
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

		private:
			bool Write(const char* desc, size_t length);
			bool Write(const wchar_t* desc, size_t length);
			void Clear();
		public:
			size_t Capacity();
			const char* c_str();
			const char* data();
			void ToWchar();
			bool Empty();
			size_t Size();
			void Resize(size_t length);
			size_t Max();
		private:
			static const int DEFAULT_SIZE = 128;

			size_t max_size;
			size_t write_size;
			char* m_Buff;
		};
	}
}