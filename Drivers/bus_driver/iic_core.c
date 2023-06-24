#include "iic_core.h"

static struct iic_bus_drv_dev iic_bus_drv_dev;
static LIST_HEAD(iic_bus_head);
static LIST_HEAD(iic_dev_head);

int bus_id_valid(unsigned int bus_id)
{
    if ( (((bus_id & BUS_TYPE_OFF_MASK) >> BUS_TYPE_START_BIT) != IIC_BUS_TYPE) ||
         ((bus_id & BUS_DEV_ID_OFF_MASK) != 0 ) ) {
        printf("ERR: iic bus_id invalid\r\n");
        return -LYSI_EINVAL;
    }

    return LYSI_OK;
}

int register_iic_bus(struct iic_adapter *iic_adapter)
{
    int ret = LYSI_OK;
    int f_ret = LYSI_TRUE;
    int bus_no = 0;

    if (!iic_adapter) {
        printf("ERR: iic_adapter is NULL\r\n");
        return -LYSI_EINVAL;
    }

    f_ret = xSemaphoreTake(iic_bus_drv_dev.mutex_lock, portMAX_DELAY);
    if (LYSI_TRUE != f_ret) {
        printf("ERR: get lock timeout --> f_ret\r\n", f_ret);
        return -LYSI_EAGAIN;
    }

    bus_no = find_first_zero_bit(iic_bus_drv_dev.bus_bitmap, MAX_BUS_NUMS);
    if (bus_no < 0) {
        printf("ERR: Bus is full\r\n");
        return bus_no;
    }
    iic_adapter->bus_id = (IIC_BUS_TYPE << BUS_TYPE_START_BIT) |
                      (bus_no << BUS_ID_START_BIT);
    set_bitmap(&iic_bus_drv_dev.bus_bitmap, bus_no);

    list_add(&iic_adapter->bus_list, &iic_bus_head);
    f_ret = xSemaphoreGive(iic_bus_drv_dev.mutex_lock);
    if (LYSI_TRUE != f_ret) {
        ret = LYSI_ERR;
    }

    /* 硬件、体系结构相关 */
    if (HAL_I2C_Init(iic_adapter->i2c_handle) != HAL_OK) {
        printf("iic register error\r\n");
        Error_Handler();
    }

    return ret;
}

int unregister_iic_bus(struct iic_adapter *iic_adapter)
{
    int ret = LYSI_OK;
    int f_ret = LYSI_TRUE;
    int bus_no = 0;

    if (!iic_adapter) {
        printf("ERR: iic_adapter is NULL\r\n");
        return -LYSI_EINVAL;
    }

    f_ret = xSemaphoreTake(iic_bus_drv_dev.mutex_lock, portMAX_DELAY);
    if (LYSI_TRUE != ret) {
        printf("ERR: get lock timeout\r\n");
        return -LYSI_EAGAIN;
    }

    bus_no = (iic_adapter->bus_id & BUS_ID_OFF_MASK) >> BUS_ID_START_BIT;
    clear_bitmap(&iic_bus_drv_dev.bus_bitmap, bus_no);
    list_del(&iic_adapter->bus_list);

    f_ret = xSemaphoreGive(iic_bus_drv_dev.mutex_lock);
    if (LYSI_TRUE != f_ret) {
        ret = LYSI_ERR;
    }

    /* 硬件、体系结构相关 */
    if (HAL_I2C_Init(iic_adapter->i2c_handle) != HAL_OK) {
        Error_Handler();
    }

    return ret;
}

int iic_bus_drv_init(void)
{
    INIT_LIST_HEAD(&iic_bus_head);
    INIT_LIST_HEAD(&iic_dev_head);

    iic_bus_drv_dev.mutex_lock = xSemaphoreCreateMutex();
    if (!iic_bus_drv_dev.mutex_lock) {
        return -LYSI_EBUSY;
    }

    return LYSI_OK;
}

int register_iic_dev(struct iic_dev *iic_dev, struct iic_adapter *iic_adapter)
{
    int ret = LYSI_OK;
    int f_ret = LYSI_TRUE;
    int dev_no = 0;

    f_ret = xSemaphoreTake(iic_bus_drv_dev.mutex_lock, portMAX_DELAY);
    if (LYSI_TRUE != ret) {
        printf("ERR: get lock timeout\r\n");
        return -LYSI_EAGAIN;
    }

    dev_no = find_first_zero_bit(iic_bus_drv_dev.bus_bitmap, MAX_BUS_NUMS);
    if (dev_no < 0) {
        printf("ERR: Dev is full\r\n");
        return dev_no;
    }
    iic_dev->dev_id = iic_adapter->bus_id | (dev_no << BUS_DEV_ID_START_BIT);
    set_bitmap(&iic_adapter->dev_bitmap, dev_no);

    list_add(&iic_dev->dev_list, &iic_dev_head);

    f_ret = xSemaphoreGive(iic_bus_drv_dev.mutex_lock);
    if (LYSI_TRUE != f_ret) {
        ret = LYSI_ERR;
    }

    return ret;
}

int unregister_iic_dev(struct iic_dev *iic_dev, struct iic_adapter *iic_adapter)
{
    int ret = LYSI_OK;
    int f_ret = LYSI_TRUE;
    unsigned int dev_no = 0;

    f_ret = xSemaphoreTake(iic_bus_drv_dev.mutex_lock, portMAX_DELAY);
    if (LYSI_TRUE != ret) {
        printf("ERR: get lock timeout\r\n");
        return -LYSI_EAGAIN;
    }

    dev_no = (iic_dev->dev_id & BUS_DEV_ID_OFF_MASK) >> BUS_DEV_ID_START_BIT;
    clear_bitmap(&iic_adapter->dev_bitmap, dev_no);
    list_del(&iic_dev->dev_list);

    f_ret = xSemaphoreGive(iic_bus_drv_dev.mutex_lock);
    if (LYSI_TRUE != f_ret) {
        ret = LYSI_ERR;
    }

    return ret;
}

struct iic_adapter * get_iic_adpater(unsigned int bus_id)
{
    struct iic_adapter *entry;

    if (bus_id_valid(bus_id)) {
        return NULL;
    }

    list_for_each_entry(entry, &iic_bus_head, bus_list) {
        if (entry->bus_id == bus_id) {
            return entry;
        }
    }

    printf("ERR: Can not find this iic adapter\r\n");
    return NULL;
}
