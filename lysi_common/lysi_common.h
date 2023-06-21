#ifndef __LYSI_COMMON_H
#define __LYSI_COMMON_H

#include "lysi_list.h"

/**
 * @brief 体系结构相关的定义
 *
 */
#define ARCH_32_BIT

/**
 * @brief 错误代码
 *
 */
#define LYSI_EPERM                              1     /* Operation not permitted */
#define LYSI_ENOENT                             2     /* No such file or directory */
#define LYSI_ESRCH                              3     /* No such process */
#define LYSI_EINTR                              4     /* Interrupted system call */
#define LYSI_EIO                                5     /* I/O error */
#define LYSI_ENXIO                              6     /* No such device or address */
#define LYSI_E2BIG                              7     /* Argument list too long */
#define LYSI_ENOEXEC                            8     /* Exec format error */
#define LYSI_EBADF                              9     /* Bad file number */
#define LYSI_ECHILD                             10    /* No child processes */
#define LYSI_EAGAIN                             11    /* Try again */
#define LYSI_ENOMEM                             12    /* Out of memory */
#define LYSI_EACCES                             13    /* Permission denied */
#define LYSI_EFAULT                             14    /* Bad address */
#define LYSI_ENOTBLK                            15    /* Block device required */
#define LYSI_EBUSY                              16    /* Device or resource busy */
#define LYSI_EEXIST                             17    /* File exists */
#define LYSI_EXDEV                              18    /* Cross-device link */
#define LYSI_ENODEV                             19    /* No such device */
#define LYSI_ENOTDIR                            20    /* Not a directory */
#define LYSI_EISDIR                             21    /* Is a directory */
#define LYSI_EINVAL                             22    /* Invalid argument */
#define LYSI_ENFILE                             23    /* File table overflow */
#define LYSI_EMFILE                             24    /* Too many open files */
#define LYSI_ENOTTY                             25    /* Not a typewriter */
#define LYSI_ETXTBSY                            26    /* Text file busy */
#define LYSI_EFBIG                              27    /* File too large */
#define LYSI_ENOSPC                             28    /* No space left on device */
#define LYSI_ESPIPE                             29    /* Illegal seek */
#define LYSI_EROFS                              30    /* Read-only file system */
#define LYSI_EMLINK                             31    /* Too many links */
#define LYSI_EPIPE                              32    /* Broken pipe */
#define LYSI_EDOM                               33    /* Math argument out of dom */
#define LYSI_ERANGE                             34    /* Math result not representable */

/**
 * @brief 总线相关的定义
 *
 */
#define IIC_BUS_TYPE                            1
#define SPI_BUS_TYPE                            2
#define USART_BUS_TYPE                          3

#define TYPE_OFF_MASK                           (0xFFFFFFFF << 16)
#define ID_OFF_MASK                             (0xFFFFFFFF << 0)

#define START_ID_NO                             1

/**
 * @brief 通用定义
 *
 */
#define LYSI_FALSE                              0
#define LYSI_TRUE                               1

#define LYSI_OK                                 0
#define LYSI_ERR                                1

/**
 * @brief 体系结构不同导致的适配差异定义
 *
 */
#ifdef ARCH_32_BIT
    #define ARCH_BUS_WIDTH                      unsigned int
#elif defined(ARCH_64_BIT)
    #define ARCH_BUS_WIDTH                      unsigned long long
#endif



#endif