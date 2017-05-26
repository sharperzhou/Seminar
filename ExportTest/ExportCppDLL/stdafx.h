#ifndef __STDAFX_H__
#define __STDAFX_H__

#ifdef _EXPORTING
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __declspec(dllimport)
#endif

#endif

