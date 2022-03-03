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

#include "unity_fixture.h"
#include "LedDriver.h"
#include "RuntimeErrorStub.h"
#include "unity_fixture.h"

TEST_GROUP(LedDriver);

static uint16_t virtualLeds;

TEST_SETUP(LedDriver)
{
    LedDriver_Create(&virtualLeds);
}

TEST_TEAR_DOWN(LedDriver)
{
}

TEST(LedDriver, LedDriver_CreateOff)
{
    virtualLeds = 0xffff;
    LedDriver_Create(&virtualLeds);
    TEST_ASSERT_EQUAL_HEX16(0x00, virtualLeds);
}

TEST(LedDriver, LedMemoryIsNotReadable)
{
    virtualLeds = 0xffff;
    LedDriver_LedOn(8);
    TEST_ASSERT_EQUAL_HEX16(0x80, virtualLeds);
}

TEST(LedDriver, TurnOn_LedOne)
{
    LedDriver_LedOn(1);
    TEST_ASSERT_EQUAL_HEX16(0x01, virtualLeds);
}

TEST(LedDriver, TurnOff_LedOne)
{
    LedDriver_LedOn(1);
    LedDriver_LedOff(1);
    TEST_ASSERT_EQUAL_HEX16(0x00, virtualLeds);
}

TEST(LedDriver, TurnOnMultipleLeds)
{
    LedDriver_LedOn(8);
    LedDriver_LedOn(9);
    TEST_ASSERT_EQUAL_HEX16(0x180, virtualLeds);
}

TEST(LedDriver, TurnOnAllLeds)
{
    LedDriver_LedOnAll();
    TEST_ASSERT_EQUAL_HEX16(0xffff, virtualLeds);
}

TEST(LedDriver, TurnOffAnyLed)
{
    LedDriver_LedOnAll();
    LedDriver_LedOff(7);
    TEST_ASSERT_EQUAL_HEX16(0xffBf, virtualLeds);
}

TEST(LedDriver, LowerUpperBounderyCheck)
{
    LedDriver_LedOn(1);
    LedDriver_LedOn(16);
    TEST_ASSERT_EQUAL_HEX16(0x8001, virtualLeds);
}

TEST(LedDriver, OutOfBoundsChangeOnNothing)
{
    LedDriver_LedOn(-1);
    TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
    LedDriver_LedOn(0);
    TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
    LedDriver_LedOn(17);
    TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
    LedDriver_LedOn(33);
    TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
    LedDriver_LedOn(2564);
    TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}


TEST(LedDriver, OutOfBoundsChangeOffNothing)
{
    LedDriver_LedOnAll();
    LedDriver_LedOff(-1);
    LedDriver_LedOff(0);
    LedDriver_LedOff(17);
    LedDriver_LedOff(33);
    LedDriver_LedOff(2564);
    TEST_ASSERT_EQUAL_HEX16(0xffff, virtualLeds);
}

TEST(LedDriver, OutOfBoundsProducesRuntimeError)
{
    LedDriver_LedOn(-1);
    
    TEST_ASSERT_EQUAL_STRING("LED Driver: out-of-bounds LED",
                             RuntimeErrorStub_GetLastError());
    TEST_ASSERT_EQUAL(-1, RuntimeErrorStub_GetLastParameter());
}

TEST(LedDriver, IsOn)
{
    TEST_ASSERT_FALSE(LedDriver_IsOn(11));
    LedDriver_LedOn(11);
    TEST_ASSERT_TRUE(LedDriver_IsOn(11));
}

TEST(LedDriver, OutOfBoundsLedsAreAlwaysOff)
{
    TEST_ASSERT_FALSE(LedDriver_IsOn(0));
    TEST_ASSERT_FALSE(LedDriver_IsOn(17));
}

TEST(LedDriver, IsOff)
{
    TEST_ASSERT_TRUE(LedDriver_IsOff(12));
    LedDriver_LedOn(12);
    TEST_ASSERT_FALSE(LedDriver_IsOff(12));
}