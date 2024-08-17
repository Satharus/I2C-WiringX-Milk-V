/**
 * Copyright (c) 2023 Milk-V
 *
 * SPDX-License-Identifier: BSD-3-Clause
 **/

#ifndef BMP280_I2C_H_
#define BMP280_I2C_H_

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

#include <wiringx.h>

/* Example code to talk to a BMP280 temperature and pressure sensor

    NOTE: Ensure the device is capable of being driven at 3.3v NOT 5v. The Duo
    GPIO (and therefore I2C) cannot be used at 5v.

    You will need to use a level shifter on the I2C lines if you want to run the
    board at 5v.

    Connections on Milk-V Duo board, other boards may vary.

    I2C1_SDA (on Duo this is GPIOC9 (pin 14))  -> SDA on BMP280 board
    I2C1_SCL (on Duo this is GPIOC10 (pin 15)) -> SCL on BMP280 board
    3.3v (pin 36) -> VCC on BMP280 board
    GND (pin 38)  -> GND on BMP280 board
 */

// Device has default bus address of 0x76
#define BMP280_ADDR  0x76

// Hardware registers
#define REG_CONFIG    0xF5
#define REG_CTRL_MEAS 0xF4
#define REG_RESET     0xE0

#define REG_TEMP_XLSB 0xFC
#define REG_TEMP_LSB  0xFB
#define REG_TEMP_MSB  0xFA

#define REG_PRESSURE_XLSB 0xF9
#define REG_PRESSURE_LSB  0xF8
#define REG_PRESSURE_MSB  0xF7

// Calibration registers
#define REG_DIG_T1 0x88
#define REG_DIG_T2 0x8A
#define REG_DIG_T3 0x8C

#define REG_DIG_P1 0x8E
#define REG_DIG_P2 0x90
#define REG_DIG_P3 0x92
#define REG_DIG_P4 0x94
#define REG_DIG_P5 0x96
#define REG_DIG_P6 0x98
#define REG_DIG_P7 0x9A
#define REG_DIG_P8 0x9C
#define REG_DIG_P9 0x9E

/*
* Immutable calibration data read from bmp280
*/
struct bmp280_calib_param
{
    // Temperature params
    uint16_t dig_t1;
    int16_t dig_t2;
    int16_t dig_t3;

    // Pressure params
    uint16_t dig_p1;
    int16_t dig_p2;
    int16_t dig_p3;
    int16_t dig_p4;
    int16_t dig_p5;
    int16_t dig_p6;
    int16_t dig_p7;
    int16_t dig_p8;
    int16_t dig_p9;
};

void bmp280_read_raw(int fd, int32_t* temp, int32_t* pressure);
void bmp280_init(int fd);
void bmp280_get_calib_params(int fd, struct bmp280_calib_param* params);
int32_t bmp280_convert(int32_t temp, struct bmp280_calib_param* params);
int32_t bmp280_convert_temp(int32_t temp, struct bmp280_calib_param* params);
int32_t bmp280_convert_pressure(int32_t pressure, int32_t temp, struct bmp280_calib_param* params);


#endif
