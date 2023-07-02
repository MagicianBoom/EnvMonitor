#include "sht3x.h"

int get_temp_and_humi(struct sht3x_dev *sht3x_dev)
{
    int ret = 0;
    uint32_t temp = 0, humi = 0;
    uint8_t data_w[] = { 0x2C, 0x06 };
    uint8_t data_r[6] = { 0 };

    ret = HAL_I2C_Master_Transmit(sht3x_dev->iic_dev.iic_adapter->i2c_handle, sht3x_dev->iic_dev.dev_addr << 1, data_w, 2, 5000);
    if (ret != HAL_OK) {
        printf("IIC failed --> %d\r\n", ret);
    }

    ret = HAL_I2C_Master_Receive(sht3x_dev->iic_dev.iic_adapter->i2c_handle, sht3x_dev->iic_dev.dev_addr << 1, data_r, 6, 5000);
    if (ret != HAL_OK) {
        printf("IIC failed --> %d\r\n", ret);
    }

    temp = ((uint16_t)data_r[0] << 8) | (uint16_t)data_r[1];
    sht3x_dev->now_temp = -45 + 175 * ((float)temp / 65535);
    humi = ((uint16_t)data_r[3] << 8) | (uint16_t)data_r[4];
    sht3x_dev->now_humi = 100 * (((float)humi / 65535));

    return ret;
}

int sht3x_init(struct sht3x_dev* sht3x_dev, struct iic_adapter* iic_adapter, unsigned int dev_addr)
{
    sht3x_dev->iic_dev.dev_addr = dev_addr;
    sht3x_dev->iic_dev.iic_adapter = iic_adapter;
    register_iic_dev(&sht3x_dev->iic_dev);

    return LYSI_OK;
}
