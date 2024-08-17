#include "bmp280_i2c.h"
#include "ssd1306_i2c.h"

#define I2C_DEV "/dev/i2c-1" // Use I2C port 1

int main()
{
    // File descriptors for the I2C peripherals
    int i2cTemperatureSensorfd = 0;
    int i2cOLEDfd = 0;

    if(wiringXSetup("milkv_duos", NULL) == -1)
    {
        wiringXGC();
        return -1;
    }

    // Get fd for OLED sensor
    i2cOLEDfd = wiringXI2CSetup(I2C_DEV, SSD1306_ADDR);

    if (i2cOLEDfd < 0)
    {
        fprintf(stderr, "I2C setup of slave  at address %x via device %s failed: %x\n", SSD1306_ADDR, I2C_DEV, i2cOLEDfd);
        return -1;
    }

    // Get fd for temperature sensor    
    i2cTemperatureSensorfd = wiringXI2CSetup(I2C_DEV, BMP280_ADDR);

    if (i2cTemperatureSensorfd < 0)
    {
        fprintf(stderr, "I2C setup of slave  at address %x via device %s failed: %x\n", BMP280_ADDR, I2C_DEV, i2cTemperatureSensorfd);
        return -1;
    }

    // Initialise Temperature Sensor
    bmp280_init(i2cTemperatureSensorfd);

    // Initialise OLED
    ssd1306_init(i2cOLEDfd);
    ssd1306_clear_full_screen(0);


    // Retrieve fixed compensation params
    struct bmp280_calib_param params;
    bmp280_get_calib_params(i2cTemperatureSensorfd, &params);

    usleep(250000); // Sleep so that data polling and register update don't collide

    int32_t raw_temperature;
    int32_t raw_pressure;

    char temperatureString[24];
    char pressureString[24];
    while (1) 
    {
        bmp280_read_raw(i2cTemperatureSensorfd, &raw_temperature, &raw_pressure);
        int32_t temperature = bmp280_convert_temp(raw_temperature, &params);
        int32_t pressure = bmp280_convert_pressure(raw_pressure, raw_temperature, &params);

        snprintf(temperatureString, 24, "Temp. = %.2f C", temperature / 100.f);
        snprintf(pressureString, 24, "Pressure = %.2f kPa", pressure / 1000.f);
        
        ssd1306_push_string(0, 0, "Good day, sir!" , 8);
        ssd1306_push_string(0, 2, temperatureString, 8);
        ssd1306_push_string(0, 3, pressureString, 8);

        // Poll every 500ms
        usleep(500000);
    }
}
