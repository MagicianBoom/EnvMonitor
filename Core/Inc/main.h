/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
#include "task.h"
#include "stdio.h"
#include "iic_core.h"
#include "sht3x.h"
#include "lysi_common.h"
#include "lysi_list.h"

void Error_Handler(void);

/* Private defines -----------------------------------------------------------*/
#define LED_Pin                                                     GPIO_PIN_13
#define LED_GPIO_Port                                               GPIOC
#define HUMAN_SENSOR_Pin                                            GPIO_PIN_12
#define HUMAN_SENSOR_GPIO_Port                                      GPIOB
#define KEY_Pin                                                     GPIO_PIN_14
#define KEY_GPIO_Port                                               GPIOB

#define TASK_STATUS_MASK                                            0xF
#define TASK_ACTIVE_FLAG_BIT                                        4
#define TASK_SUSPEND_FLAG_BIT                                       5
#define TASK_DELETE_FLAG_BIT                                        6

typedef enum {
    TASK_ACTIVE = 0,
    TASK_SUSPEND,
    TASK_DELETE,
    TASK_STATUS_NUMS,
};

struct task_info {
    unsigned char status;
    unsigned char task_priority;
    unsigned short stack_size;
    void *task_args;
    char *task_name;
    void (*task_func)(void* pvParameters);
    TaskHandle_t* task_handle;
    struct list_head task_list;
};

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
