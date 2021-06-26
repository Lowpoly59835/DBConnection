#pragma once
#include <exception>
#include <string>
#include <windows.h>
#include <type_traits>

namespace NetworkCommon
{
    class CCriticalSection
        :public CRITICAL_SECTION
    {
    public:
        CCriticalSection()
        {
            InitializeCriticalSection(this);
        }
        ~CCriticalSection()
        {
            DeleteCriticalSection(this);
        }
    };

    class CCriticalSectionLock
    {
    public:
        CCriticalSectionLock(CCriticalSection& cs)
            :m_pcs(&cs)
        {
            EnterCriticalSection(m_pcs);
        }
        ~CCriticalSectionLock()
        {
            if (m_pcs != NULL)
                LeaveCriticalSection(m_pcs);
        }

        explicit operator bool() { return true; }
    private:
        CCriticalSectionLock() : m_pcs(nullptr) {}

        CCriticalSection* m_pcs;
    };
    
    #define CSLOCK( cs_ )   if( CCriticalSectionLock STRING_CAT( lock_, __LINE__ ) = cs_ )


	inline const char* Format(const char* format, ...)
	{
		va_list args;
		va_start(args, format);

		int size = _vscprintf(format, args);
		std::string result(++size, 0);
		vsnprintf_s((char*)result.data(), size, _TRUNCATE, format, args);
		va_end(args);

		return result.c_str();
	}
}

namespace NetworkCommon
{
    namespace TypeCheck
    {
        template<typename T, bool>
        struct IsType
        {

        };

    }
}

#define GetCurrentMethodName __FUNCTION__


#define PROPERT_GET(_get) _declspec(property(get = _get))
#define PROPERT_SET(_set) _declspec(property(set = _set))
#define PROPERTY(_get, _set) _declspec(property(get = _get, put = _set))

#define PROPERT_MAKE_GET(value, type, name) type Get##name() { return value; }
#define PROPERT_MAKE_SET(value, type, name) void Set##name(type _value) { value = _value; }
#define PROPERT_MAKE(value, type, name) PROPERT_MAKE_GET(value, type, name) PROPERT_MAKE_SET(value, type, name)


#define PROPERT_GETEX(value, type, name) PROPERT_MAKE_GET(value, type, name) PROPERT_GET(Get##name) type name;
#define PROPERT_SETEX(value, type, name) PROPERT_MAKE_SET(value, type, name) PROPERT_GET(Get##name) type name;

#define PROPERT_EX(value, type, name) PROPERT_MAKE(value, type, name) PROPERTY(Get##name, Set##name) type name;