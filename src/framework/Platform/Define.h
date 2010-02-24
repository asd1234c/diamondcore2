/*
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 *
 * Copyright (C) 2008-2010 Trinity <http://www.trinitycore.org/>
 * 
 * Copyright (C) 2010 DiamondCore <http://www.diamondcore.eu/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef DIAMOND_DEFINE_H
#define DIAMOND_DEFINE_H

#include <sys/types.h>

#include <ace/Basic_Types.h>
#include <ace/ACE_export.h>

#include "Platform/CompilerDefs.h"

#define DIAMOND_LITTLEENDIAN 0
#define DIAMOND_BIGENDIAN    1

#if !defined(DIAMOND_ENDIAN)
#  if defined (ACE_BIG_ENDIAN)
#    define DIAMOND_ENDIAN DIAMOND_BIGENDIAN
#  else //ACE_BYTE_ORDER != ACE_BIG_ENDIAN
#    define DIAMOND_ENDIAN DIAMOND_LITTLEENDIAN
#  endif //ACE_BYTE_ORDER
#endif //DIAMOND_ENDIAN

#if PLATFORM == PLATFORM_WINDOWS
#  define DIAMOND_EXPORT __declspec(dllexport)
#  define DIAMOND_LIBRARY_HANDLE HMODULE
#  define DIAMOND_LOAD_LIBRARY(a) LoadLibrary(a)
#  define DIAMOND_CLOSE_LIBRARY FreeLibrary
#  define DIAMOND_GET_PROC_ADDR GetProcAddress
#  define DIAMOND_IMPORT __cdecl
#  define DIAMOND_SCRIPT_EXT ".dll"
#  define DIAMOND_SCRIPT_NAME "DiamondScript"
#  define DIAMOND_PATH_MAX MAX_PATH
#else //PLATFORM != PLATFORM_WINDOWS
#  define DIAMOND_LIBRARY_HANDLE void*
#  define DIAMOND_EXPORT export
#  define DIAMOND_LOAD_LIBRARY(a) dlopen(a,RTLD_NOW)
#  define DIAMOND_CLOSE_LIBRARY dlclose
#  define DIAMOND_GET_PROC_ADDR dlsym
#  if defined(__APPLE_CC__) && defined(BIG_ENDIAN)
#    define DIAMOND_IMPORT __attribute__ ((longcall))
#  elif defined(__x86_64__)
#    define DIAMOND_IMPORT
#  else
#    define DIAMOND_IMPORT __attribute__ ((cdecl))
#  endif //__APPLE_CC__ && BIG_ENDIAN
#  if defined(__APPLE_CC__)
#    define DIAMOND_SCRIPT_EXT ".dylib"
#    if defined(DO_SCRIPTS)
#      define DIAMOND_SCRIPT_NAME "../lib/libdiamondscript"
#    else
#      define DIAMOND_SCRIPT_NAME "../lib/libdiamondinterface"
#    endif // DO_SCRIPTS
#  else
#    define DIAMOND_SCRIPT_EXT ".so"
#    if defined(DO_SCRIPTS)
#      define DIAMOND_SCRIPT_NAME "libdiamondscript"
#    else
#      define DIAMOND_SCRIPT_NAME "libdiamondinterface"
#    endif // DO_SCRIPTS
#  endif //__APPLE_CC__
#  define DIAMOND_PATH_MAX PATH_MAX
#endif //PLATFORM

#if PLATFORM == PLATFORM_WINDOWS
#  ifdef DIAMOND_WIN32_DLL_IMPORT
#    define DIAMOND_DLL_DECL __declspec(dllimport)
#  else //!DIAMOND_WIN32_DLL_IMPORT
#    ifdef DIAMOND_WIND_DLL_EXPORT
#      define DIAMOND_DLL_DECL __declspec(dllexport)
#    else //!DIAMOND_WIND_DLL_EXPORT
#      define DIAMOND_DLL_DECL
#    endif //DIAMOND_WIND_DLL_EXPORT
#  endif //DIAMOND_WIN32_DLL_IMPORT
#else //PLATFORM != PLATFORM_WINDOWS
#  define DIAMOND_DLL_DECL
#endif //PLATFORM

#if PLATFORM == PLATFORM_WINDOWS
#  define DIAMOND_DLL_SPEC __declspec(dllexport)
#  ifndef DECLSPEC_NORETURN
#    define DECLSPEC_NORETURN __declspec(noreturn)
#  endif //DECLSPEC_NORETURN
#else //PLATFORM != PLATFORM_WINDOWS
#  define DIAMOND_DLL_SPEC
#  define DECLSPEC_NORETURN
#endif //PLATFORM

#if !defined(DEBUG)
#  define DIAMOND_INLINE inline
#else //DEBUG
#  if !defined(DIAMOND_DEBUG)
#    define DIAMOND_DEBUG
#  endif //DIAMOND_DEBUG
#  define DIAMOND_INLINE
#endif //!DEBUG

#if COMPILER == COMPILER_GNU
#  define ATTR_NORETURN __attribute__((noreturn))
#  define ATTR_PRINTF(F,V) __attribute__ ((format (printf, F, V)))
#else //COMPILER != COMPILER_GNU
#  define ATTR_NORETURN
#  define ATTR_PRINTF(F,V)
#endif //COMPILER == COMPILER_GNU

typedef ACE_INT64 int64;
typedef ACE_INT32 int32;
typedef ACE_INT16 int16;
typedef ACE_INT8 int8;
typedef ACE_UINT64 uint64;
typedef ACE_UINT32 uint32;
typedef ACE_UINT16 uint16;
typedef ACE_UINT8 uint8;

#if COMPILER != COMPILER_MICROSOFT
typedef uint16      WORD;
typedef uint32      DWORD;
#endif //COMPILER

typedef uint64 OBJECT_HANDLE;

//commented out
//so all future merges with invalid style will drop build errors
//this way devs will at least read thru what they merge to find the error

//#define MaNGOS              Trinity
//#define DIAMONDCORE_DLL_DECL     DIAMOND_DLL_DECL
//#define DIAMONDCORE_DLL_SPEC     DIAMOND_DLL_SPEC
//#define GetMangosString     GetDiamondString

#if defined(DIAMONDCORE_DEBUG) || defined(DIAMOND_DEBUG)
#  ifndef DIAMOND_DEBUG
#    define DIAMOND_DEBUG
#  endif
#  ifndef DIAMONDCORE_DEBUG
#    define DIAMONDCORE_DEBUG
#  endif
#endif

#ifndef CLIENT_VER
#define CLIENT_VER 313
#endif

#endif //DIAMOND_DEFINE_H
