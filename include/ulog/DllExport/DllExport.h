#ifndef ULOG_DLLEXPORT_H
#define ULOG_DLLEXPORT_H

#ifdef _WIN32
#ifdef DllExport
#undef DllExport
#endif
#if ULOG_DLL
#define DllExport __declspec(dllexport)
#else
#define DllExport __declspec(dllimport)
#endif // ULOG_DLL
#else
#ifdef DllExport
#undef DllExport
#endif
#define DllExport
#endif // _WIN32

#endif // ULOG_DLLEXPORT_H
