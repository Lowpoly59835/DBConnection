#pragma once

#ifdef DBCONNECTIONDLL_EXPORTS
#define DBCONNECTIONDLL_IMPORT __declspec(dllexport)
#else
#define DBCONNECTIONDLL_IMPORT __declspec(dllimport)
#endif
