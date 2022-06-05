#ifndef _TUFRGB_H
#define _TUFRGB_H

#include <stdint.h>

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

TUFHandle TUFRGB_Open();
void TUFRGB_Close(TUFHandle handle);

int TUFRGB_Set(
    TUFHandle handle,
    const TUFAction action,
    const TUFSpeed speed,
    const TUFByte red,
    const TUFByte green,
    const TUFByte blue);

#endif /* _TUFRGB_H */