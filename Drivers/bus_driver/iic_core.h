#ifndef __IIC_CORE_H
#define __IIC_CORE_H

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "lysi_common.h"
#include "stm32f1xx_hal_def.h"

struct iic_bus_drv_dev {
    unsigned long long bus_bitmap;
    SemaphoreHandle_t mutex_lock;
};

struct iic_adapter {
    unsigned int bus_id;
    unsigned long long dev_bitmap;
    I2C_HandleTypeDef *i2c_args;

    struct list_head bus_list;
};

struct iic_dev {
    unsigned int dev_id;
    unsigned short dev_addr;
    struct iic_adapter *iic_adapter;

    struct list_head dev_list;
}

int register_iic_bus(struct iic_adapter *iic_adapter);

#endif