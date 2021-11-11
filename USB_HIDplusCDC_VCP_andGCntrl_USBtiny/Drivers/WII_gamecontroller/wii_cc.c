/***************************************************************************
 * Artekit STM32 Gamepad Demo
 * Copyright (C) 2013 Artekit Italy
 * http://www.artekit.eu
 
### wii_cc.c
 
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

#include "wii_cc.h"
#include "i2c.h"

static WII_CC_DATA_t initial_data;

static void wiiCCGetData(WII_CC_DATA_t* data)
{
	uint8_t buf[6]={0};

	HAL_I2C_Master_Transmit(&hi2c1, WII_CONTROLLER_ID, 0x00, 1, 100);
	HAL_I2C_Master_Receive(&hi2c1, WII_CONTROLLER_ID, buf, 6, 100);
	
	data->left_analog_x = (buf[0] & 0x3F);
	data->left_analog_y = (buf[1] & 0x3F);
	
	data->right_analog_x = ((buf[0] >> 6) & 0x03) << 3;
	data->right_analog_x |= ((buf[1] >> 6) & 0x03) << 1;
	data->right_analog_x |= ((buf[2] >> 7) & 0x01);
	data->right_analog_y = (int8_t)(buf[2] & 0x1F);
	
	data->left_trigger = ((buf[2] >> 5) & 0x03) << 3;
	data->left_trigger |= (buf[3] >> 5) & 0x07;
	data->right_trigger = (buf[3] & 0x1F);
	
	*((uint16_t*) &data->buttons) = ~(buf[4] | (buf[5] << 8));
	
	data->left_analog_x <<= 2;
	data->left_analog_y <<= 2;
	data->right_analog_x <<= 3;
	data->right_analog_y <<= 3;
}

/* WII Classic Controller Init */
void wiiCCInit(void)
{
	uint8_t data[2];
	data[0] = 0xF0;
	data[1] = 0x55;

	HAL_I2C_Master_Transmit(&hi2c1, WII_CONTROLLER_ID, data, 2, 100);

	data[0] = 0xFB;
	data[1] = 0x00;
	HAL_I2C_Master_Transmit(&hi2c1, WII_CONTROLLER_ID, data, 2, 100);
	for (int i = 0; i < 10; i++)
	{
		wiiCCGetData(&initial_data);
	}
}

/* WII Classic Controller Read */
void wiiCCRead(WII_CC_DATA_t* data)
{
	wiiCCGetData(data);	

	data->left_analog_x -= initial_data.left_analog_x;
	data->left_analog_y -= initial_data.left_analog_y;
	data->right_analog_x -= initial_data.right_analog_x;
	data->right_analog_y -= initial_data.right_analog_y;
	data->left_trigger -= initial_data.left_trigger;
	data->right_trigger -= initial_data.right_trigger;
}
