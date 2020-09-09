#include "lora_api.h"

enum sx127x_err sx127x_lora_init(sx127x_dev *dev)
{
    int8_t spi_ret;
    enum sx127x_err ret;
    uint8_t data;
    uint8_t agc_on = 0X04; // Automatic Gain Control

    spi_ret = dev->spi_read(SX127X_REG_VERSION, &data, 1);
    if (ret) {
        return sx127x_SPI_Error;
    }
    
    if(data != SX127X_VERSION) {
        return sx127x_Unsupported_Module;
    }

    /* Enter sleep mode */
    ret = sx127x_lora_set_mode(dev, SX127X_SLEEP);
    if (ret) {
        return ret;
    }

    /* Set Frequency */
    ret = sx127x_lora_set_freq(dev);
    if (ret) {
        return ret;
    }
}