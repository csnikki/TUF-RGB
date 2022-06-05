#include <windows.h>

#include "TUFRGB.h"

#include <stdio.h>

int main()
{
    int index = 0;

    uint8_t colors[9] = 
    {
        0x00, 0xFF, 0x00,
        0xFF, 0xFF, 0xFF,
        0xFF, 0x00, 0x00,
    };

    TUFHandle handle = TUFRGB_Open();

    if (handle == NULL)
    {
        printf("ERROR: Could not open handle!\n");
        return 0;
    }

    while (1)
    {
        if (TUFRGB_Set(
            handle,
            Static,
            Medium,
            colors[3 * index],
            colors[3 * index + 1],
            colors[3 * index + 2]) == TUF_ERROR)
        {
            printf("ERROR: Failed to set color!\n");
            goto freeres;
        }

        index = (index + 1) % 3;

        Sleep(1000);
    }

freeres:
    TUFRGB_Close(handle);
    return 0;
}