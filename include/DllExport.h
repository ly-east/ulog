#ifndef DLLEXPORT_H
#define DLLEXPORT_H

#ifdef _WIN32
#if ULOG_DLL
#define DllExport __declspec(dllexport)
#else
#define DllExport __declspec(dllimport)
#endif // ULOG_DLL
#else
#define DllExport
#endif // _WIN32

#endif // DLLEXPORT_H
