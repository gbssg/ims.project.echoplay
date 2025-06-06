#pragma once

#include <Arduino.h>

/**
 * \file
 * \brief   Abstracts the clock source away from our application
 */

void CP_init(int offset);

String CP_getHourAsString();

String CP_getMinuteAsString();

int CP_GetTimePos1();
int CP_GetTimePos2();
int CP_GetTimePos3();
int CP_GetTimePos4();

