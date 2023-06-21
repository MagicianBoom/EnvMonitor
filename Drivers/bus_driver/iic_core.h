#ifndef __IIC_CORE_H
#define __IIC_CORE_H

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "lysi_common.h"

struct iic_bus_drv_dev {
    SemaphoreHandle_t mutex_lock;
};

struct iic_bus {
    unsigned int id;
    unsigned int rate;
    unsigned int scl_port;
    unsigned int scl_pin;
    unsigned int sda_port;
    unsigned int sda_pin;
    struct list_head bus_list;

    int (*iic_write)(ARCH_BUS_WIDTH addr, unsigned int size, unsigned int *data);
    int (*iic_read)(ARCH_BUS_WIDTH addr, unsigned int size, unsigned int *data);
};

#endif