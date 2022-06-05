#include <windows.h>

#include "TUFRGB.h"

#include <string.h>

#define ATK_ACPI_WMIFUNCTION 0x22240C

// Types

typedef struct
{
    TUFByte magic[12];
    TUFByte unknown;
    TUFByte action;
    TUFByte red;
    TUFByte green;
    TUFByte blue;
    TUFByte speed;
} Packet;

// Globals

static TUFByte const MAGIC[12] = 
{
    0x44, 0x45, 0x56, 0x53,
    0x0C, 0x00, 0x00, 0x00,
    0x56, 0x00, 0x10, 0x00,
};

// Helpers

static TUFByte getAction(const TUFAction action)
{
    switch (action)
    {
        default:
            return 0x00;
        case Breathe:
            return 0x01;
        case Strobe:
            return 0x0A;
        case Rainbow:
            return 0x02;
    }
}

static TUFByte getSpeed(const TUFSpeed speed)
{
    switch (speed)
    {
        default:
            return 0xEB;
        case Slow:
            return 0xE1;
        case Fast:
            return 0xF5;
    }
}

// TUFRGB

TUFHandle TUFRGB_Open()
{
    TUFHandle handle = NULL;

    HANDLE device = CreateFileW(
        L"\\\\.\\ATKACPI",
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        0,
        NULL);

    if (device != INVALID_HANDLE_VALUE)
        memcpy(&handle, &device, sizeof(HANDLE));

    return handle;
}

void TUFRGB_Close(TUFHandle handle)
{
    CloseHandle((HANDLE)(handle));
}

int TUFRGB_Set(
    TUFHandle handle,
    const TUFAction action,
    const TUFSpeed speed,
    const TUFByte red,
    const TUFByte green,
    const TUFByte blue)
{
    DWORD status;
    DWORD bytes;
    Packet packet;

    if (handle == NULL)
        return TUF_ERROR;

    memset(&packet, 0x00, sizeof(Packet));
    memcpy(&packet.magic[0], MAGIC, sizeof(MAGIC));

    packet.action = getAction(action);
    packet.speed = getSpeed(speed);
    packet.red = red;
    packet.green = green;
    packet.blue = blue;

    if (DeviceIoControl(
        (HANDLE)(handle),
        ATK_ACPI_WMIFUNCTION,
        &packet,
        sizeof(Packet),
        &status,
        sizeof(DWORD),
        &bytes,
        NULL) == 0)
        return TUF_ERROR;

    return status == 1 ? TUF_SUCCESS : TUF_ERROR;
}