#include "iic_core.h"

static struct iic_bus_drv_dev iic_bus_drv_dev;
static LIST_HEAD(iic_bus_head);
static unsigned int iic_bus_id = (IIC_BUS_TYPE<<16) | (START_ID_NO << 0);

int iic_write(ARCH_BUS_WIDTH addr, unsigned int size, unsigned int *data)
{
    int ret = LYSI_OK;
    int f_ret = LYSI_TRUE;

    return ret;
}

int iic_read(ARCH_BUS_WIDTH addr, unsigned int size, unsigned int *data)
{
    int ret = LYSI_OK;
    int f_ret = LYSI_TRUE;

    return ret;
}

int register_iic_bus(struct iic_bus *iic_bus)
{
    int ret = LYSI_OK;
    int f_ret = LYSI_TRUE;

    if (!iic_bus) {
        printf("ERR: iic_bus is NULL\r\n");
        return -LYSI_EINVAL;
    }

    if (!iic_bus->iic_write) {
        iic_bus->iic_write = iic_write;
    }

    if (!iic_bus->iic_read) {
        iic_bus->iic_write = iic_read;
    }

    f_ret = xSemaphoreTake(iic_bus_drv_dev.mutex_lock, portMAX_DELAY);
    if (LYSI_TRUE != ret) {
        printf("ERR: get lock timeout\r\n");
        return -LYSI_EAGAIN;
    }
    list_add(&iic_bus->bus_list, &iic_bus_head);
    iic_bus->id = iic_bus_id++;
    f_ret = xSemaphoreGive(iic_bus_drv_dev.mutex_lock);

    if (LYSI_TRUE != f_ret) {
        ret = LYSI_ERR;
    }

    return ret;
}

int iic_bus_drv_init()
{
    INIT_LIST_HEAD(&iic_bus_head);

    iic_bus_drv_dev.mutex_lock = xSemaphoreCreateMutex();
    if (!iic_bus_drv_dev.mutex_lock) {
        return -LYSI_EBUSY;
    }
}