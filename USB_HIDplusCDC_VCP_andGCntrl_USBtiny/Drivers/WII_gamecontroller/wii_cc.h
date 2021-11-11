/***************************************************************************
 * Artekit STM32 Gamepad Demo
 * Copyright (C) 2013 Artekit Italy
 * http://www.artekit.eu
 
### wii_cc.h
 
#   This program is free software; you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation; either version 2 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program; if not, write to the Free Software
#   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
***************************************************************************/

#include <stm32f1xx_hal.h>
#include "i2c.h"

#define WII_CONTROLLER_ID	(0x52 << 1)

typedef struct wiiCCButtonsTag
{
	uint8_t dummy:1;
	uint8_t rtrigger_push:1;
	uint8_t plus:1;
	uint8_t home:1;
	uint8_t minus:1;
	uint8_t ltrigger_push:1;
	uint8_t down:1;
	uint8_t right:1;
	
	uint8_t up:1;
	uint8_t left:1;
	uint8_t zr:1;
	uint8_t x:1;
	uint8_t a:1;
	uint8_t y:1;
	uint8_t b:1;
	uint8_t zl:1;
	
}WII_CC_BUTTONS;

/* WII Classic Controller Data */
typedef struct  __attribute__((packed, aligned(4))) wiiCCDataTag
{
	int8_t left_analog_x;
	int8_t left_analog_y;
	
	int8_t right_analog_x;
	int8_t right_analog_y;
	
	int8_t left_trigger;
	int8_t right_trigger;
	
	WII_CC_BUTTONS buttons;	
	
} __attribute__((packed, aligned(4))) WII_CC_DATA_t;

void wiiCCInit(void);
void wiiCCRead(WII_CC_DATA_t* data);
