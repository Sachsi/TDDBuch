/***
 * Excerpted from "Test-Driven Development for Embedded C",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
***/
/*- ------------------------------------------------------------------ -*/
/*-    Copyright (c) James W. Grenning -- All Rights Reserved          -*/
/*-    For use by owners of Test-Driven Development for Embedded C,    -*/
/*-    and attendees of Renaissance Software Consulting, Co. training  -*/
/*-    classes.                                                        -*/
/*-                                                                    -*/
/*-    Available at http://pragprog.com/titles/jgade/                  -*/
/*-        ISBN 1-934356-62-X, ISBN13 978-1-934356-62-3                -*/
/*-                                                                    -*/
/*-    Authorized users may use this source code in your own           -*/
/*-    projects, however the source code may not be used to            -*/
/*-    create training material, courses, books, articles, and         -*/
/*-    the like. We make no guarantees that this source code is        -*/
/*-    fit for any purpose.                                            -*/
/*-                                                                    -*/
/*-    www.renaissancesoftware.net james@renaissancesoftware.net       -*/
/*- ------------------------------------------------------------------ -*/

#include "LedDriver.h"
#include "RuntimeError.h"
#include <stdlib.h>
#include <memory.h>

//--- enum values ----
enum
{
    ALL_LED_OFF = 0,
    ALL_LED_ON = (uint16_t)~ALL_LED_OFF
};

static uint16_t * ledaddress;
static uint16_t ledImage;

//--- Prototype function ----
static uint16_t convertNumberToBitPosition(int number);
static void setLedImageBit(int number);
static void clearLedImageBit(int number);
static bool IsLedOutOfBoundery(int number);
//could be declared as inline function as well
static uint16_t convertNumberToBitPosition(int number)
{
    return ((uint16_t)(1 << (number -1)));
}
/**
 * @brief Set the Led Image Bit object
 * 
 * @param number Bit position of LED
 */
static void setLedImageBit(int number)
{
    ledImage |= convertNumberToBitPosition(number);
}
/**
 * @brief clear led image bit position
 * 
 * @param number led bit position
 */
static void clearLedImageBit(int number)
{
    ledImage &= (uint16_t)~convertNumberToBitPosition(number);
}
/**
 * @brief test if number out of 16bit boundery
 * 
 * @param number Led Bit position
 * @return true position is out of boundery
 * @return false position is okay
 */
static bool IsLedOutOfBoundery(int number)
{
    return (number <= 0 || number > 16);
}
/**
 * @brief 
 * 
 * @param address 
 */
void LedDriver_Create(uint16_t* address)
{
    ledaddress = address;
    ledImage = ALL_LED_OFF;
    LedDriver_UpdateHardare();
}
/**
 * @brief 
 * 
 * @param number 
 */
void LedDriver_LedOn(int number)
{
    if(IsLedOutOfBoundery(number))
    {
        RUNTIME_ERROR("LED Driver: out-of-bounds LED", number);
        return;
    }
    setLedImageBit(number);
    LedDriver_UpdateHardare();
}
/**
 * @brief 
 * 
 * @param number 
 */
void LedDriver_LedOff(int number)
{
    if(IsLedOutOfBoundery(number))
    {
        RUNTIME_ERROR("LED Driver: out-of-bounds LED", number);
        return;
    }   
    clearLedImageBit(number);
    LedDriver_UpdateHardare();
}
/**
 * @brief 
 * 
 */
void LedDriver_LedOnAll(void)
{
    ledImage = (uint16_t)ALL_LED_ON;
    LedDriver_UpdateHardare();
}
/**
 * @brief 
 * 
 */
void LedDriver_UpdateHardare(void)
{
    *ledaddress = ledImage;
}
/**
 * @brief 
 * 
 * @param number 
 * @return true 
 * @return false 
 */
bool LedDriver_IsOn(int number)
{
    if(IsLedOutOfBoundery(number))
        return false;
    return ledImage & (convertNumberToBitPosition(number));
}

bool LedDriver_IsOff(int number)
{
    return !LedDriver_IsOn(number);
}
/**
 * @brief 
 * 
 */
void LedDriver_Destroy(void)
{

}

