#ifndef __CTDEFS_H__
#define __CTDEFS_H__

#include <stdio.h>

// SDL colors
#define ColorBlack { 0,0,0,255 }
#define ColorWhite { 255,255,255,255 }
#define ColorRed { 255,0,0,255 }
#define ColorGreen { 0,255,0,255 }
#define ColorBlue { 0,0,255,255 }

#define ColorYellow { 255,255,0,255 }
#define ColorDarkGreen { 0,102,0,255 }
#define ColorBrightBlue { 0,255,255,255 }
#define ColorOrange { 255,128,0,255 }
#define ColorPink { 255,0,127,255 }
#define ColorPurple { 127,0,255,255 }
#define ColorGrey { 128,128,128,255 }
#define ColorOlive { 102,204,0,255 }
#define ColorViolet { 178,102,255,255 }

#define ColorDarkBlue { 0,0,204,255 }
#define ColorLightBlue { 102,178,255,255 }
#define ColorDarkRed { 153,0,0,255 }
#define ColorLightRed { 255,102,102,255 }

//  NULL just in case ----------------------

#ifdef NULL
#undef NULL
#endif
#define NULL  0

// Deletes a buffer
#define RELEASE( x ) \
    {                        \
    if( x != NULL )        \
	    {                      \
      delete x;            \
	  x = NULL;              \
	    }                      \
    }

// Deletes an array of buffers
#define RELEASE_ARRAY( x ) \
    {                              \
    if( x != NULL )              \
	    {                            \
      delete[] x;                \
	  x = NULL;                    \
	    }                            \
                              \
    }

#define IN_RANGE( value, min, max ) ( ((value) >= (min) && (value) <= (max)) ? 1 : 0 )
#define MIN( a, b ) ( ((a) < (b)) ? (a) : (b) )
#define MAX( a, b ) ( ((a) > (b)) ? (a) : (b) )
#define TO_BOOL( a )  ( (a != 0) ? true : false )

typedef unsigned int uint;
typedef unsigned __int32 uint32;
typedef unsigned __int64 uint64;
typedef unsigned char uchar;

template <class VALUE_TYPE> void SWAP(VALUE_TYPE& a, VALUE_TYPE& b)
{
	VALUE_TYPE tmp = a;
	a = b;
	b = tmp;
}

// Standard string size
#define SHORT_STR	32
#define MID_STR		255
#define HUGE_STR	8192

// Joins a path and file
inline const char* const PATH(const char* folder, const char* file)
{
	static char path[MID_STR];
	sprintf_s(path, MID_STR, "%s/%s", folder, file);
	return path;
}

// Performance macros
#define PERF_START(timer) timer.Start()
#define PERF_PEEK(timer) LOG("%s took %f ms", __FUNCTION__, timer.ReadMs())

// Maths calculations
#define PI 3.14159265359f
#define DEG_TO_RAD(a) a * PI / 180.0f
#define RAD_TO_DEG(a) a * 180.0f / PI

#endif