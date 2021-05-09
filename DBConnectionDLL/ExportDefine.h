#pragma once

#ifdef DBCONNECTIONDLL_EXPORTS
#define DBCONNECTIONDLL_EXPORTS __declspec(dllexport)
#else
#define DBCONNECTIONDLL_EXPORTS __declspec(dllimport)
#endif
