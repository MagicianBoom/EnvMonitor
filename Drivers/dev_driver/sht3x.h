#ifndef __SHT3X_H
#define __SHT3X_H

#include "lysi_common.h"
#include "iic_core.h"
#include "stm32f1xx_hal.h"

#define SHT30_DEV_ADDR                                      0x44

struct sht3x_dev {
    char *dev_name;
    unsigned short work_mode;
    float now_temp;
    float now_humi;
    struct iic_dev iic_dev;
};

int sht3x_init(struct sht3x_dev* sht3x_dev, struct iic_adapter* iic_adapter, unsigned int dev_addr);
int get_temp_and_humi(struct sht3x_dev *sht3x_dev);

#endif
