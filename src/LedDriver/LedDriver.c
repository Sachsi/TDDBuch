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
#include <stdint.h>
#include "LedDriver.h"
#include <stdlib.h>
#include <memory.h>

//--- enum values ----
enum
{
    ALL_LED_OFF = 0,
    ALL_LED_ON = (uint16_t)~ALL_LED_OFF
};

static uint16_t * ledaddress;

//--- Prototype function ----
static uint16_t convertNumberToBitPosition(int number);

//could be declared as inline function as well
static uint16_t convertNumberToBitPosition(int number)
{
    return ((uint16_t)(1 << (number -1)));
}

void LedDriver_Create(uint16_t* address)
{
    ledaddress = address;
    *ledaddress = ALL_LED_OFF;
}

void LedDriver_LedOn(int number)
{
    *ledaddress |= convertNumberToBitPosition(number);
}

void LedDriver_LedOff(int number)
{
    *ledaddress &= (uint16_t)~convertNumberToBitPosition(number);
}

void LedDriver_LedAllOn(void)
{
    *ledaddress = ALL_LED_ON;
}

void LedDriver_Destroy(void)
{
}

void LedDriver_TurnOnAll(void)
{
    *ledaddress = (uint16_t)ALL_LED_ON;
}


