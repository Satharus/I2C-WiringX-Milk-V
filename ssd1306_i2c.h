/**
 * Copyright (c) 2023 Milk-V
 *
 * SPDX-License-Identifier: BSD-3-Clause
 **/

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

#include <wiringx.h>

 /* 
    Example code to SSD1306 OLED Display Module

    
    NOTE: Ensure the device is capable of being driven at 3.3v NOT 5v. The Duo
    GPIO (and therefore I2C) cannot be used at 5v.

    You will need to use a level shifter on the I2C lines if you want to run the
    board at 5v.

    Please wire according to the notes below and make sure 
    the pins are set for the correct function before running the program.

    I2C1_SDA -> SDA on SSD1306 Moudle
    I2C1_SCL -> SCL on SSD1306 Moudle
    3.3v -> VCC on SSD1306 Moudle
    GND -> GND on SSD1306 Moudle
 */

// Device address
#define SSD1306_ADDR 0x3C
extern int fd_i2c;

#define OLED_CMD     0
#define OLED_DATA    1

#define PAGE_SIZE    8
#define XLevelL		 0x00
#define XLevelH		 0x10
#define YLevel       0xB0
#define	Brightness	 0xFF 
#define WIDTH 	     128
#define HEIGHT 	     32	


extern const unsigned char asc2_0806[][6];
extern const unsigned char asc2_1608[][16];

void ssd1306_write_byte(unsigned dat,unsigned cmd);
void ssd1306_set_position(unsigned char x, unsigned char y);
void ssd1306_clear_full_screen(unsigned dat);
void ssd1306_init(int fd);
void ssd1306_push_char(uint8_t x,uint8_t y,uint8_t chr,uint8_t sizey);
void ssd1306_push_string(uint8_t x,uint8_t y,uint8_t *chr,uint8_t sizey);
