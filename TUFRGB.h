#ifndef _TUFRGB_H
#define _TUFRGB_H

#include <stdint.h>

#define TUF_API

#define TUF_SUCCESS 0
#define TUF_ERROR 1

typedef enum
{
    Static,
    Breathe,
    Strobe,
    Rainbow,
} TUFAction;

typedef enum
{
    Slow,
    Medium,
    Fast,
} TUFSpeed;

typedef void* TUFHandle;
typedef uint8_t TUFByte;

#if defined(__cplusplus)
extern "C"
{
#endif

TUF_API TUFHandle TUFRGB_Open();
TUF_API void TUFRGB_Close(TUFHandle handle);

TUF_API int TUFRGB_Set(
    TUFHandle handle,
    const TUFAction action,
    const TUFSpeed speed,
    const TUFByte red,
    const TUFByte green,
    const TUFByte blue);

#if defined(__cplusplus)
}
#endif

#endif /* _TUFRGB_H */