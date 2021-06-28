#pragma once
#include <string>
using std::allocator;
using std::char_traits;
using std::basic_string;

#ifdef DBCONNECTIONDLL_EXPORTS
#define DBCONNECTIONDLL_EXPORTS_DECLSPEC __declspec(dllexport)
#define EXPIMP_TEMPLATE
#else
#define DBCONNECTIONDLL_EXPORTS_DECLSPEC __declspec(dllimport)
#define EXPIMP_TEMPLATE extern
#endif


#define EXPORT_INTERFACE(type, ...) DBCONNECTIONDLL_EXPORTS_DECLSPEC type,##__VA_ARGS__
#define EXPORT_INTERFACE_CLASS(type, ...) EXPIMP_TEMPLATE template class DBCONNECTIONDLL_EXPORTS_DECLSPEC type,##__VA_ARGS__
#define EXPORT_INTERFACE_STRUCT(type, ...) EXPIMP_TEMPLATE template struct DBCONNECTIONDLL_EXPORTS_DECLSPEC type,##__VA_ARGS__

#define EXPORT_STL_STRING(type) EXPORT_INTERFACE_CLASS(allocator<type>); EXPORT_INTERFACE_STRUCT(char_traits<type>); EXPORT_INTERFACE_CLASS(basic_string<type, char_traits<type>, allocator<type>>);


//EXPIMP_TEMPLATE  DBCONNECTIONDLL_EXPORTS_DECLSPEC std::wstring;