#pragma once

#ifdef DBCONNECTIONDLL_EXPORTS
#define DBCONNECTIONDLL_EXPORTS_DECLSPEC __declspec(dllexport)
#else
#define DBCONNECTIONDLL_EXPORTS_DECLSPEC __declspec(dllimport)
#endif
