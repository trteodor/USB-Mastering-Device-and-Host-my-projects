/**
  ******************************************************************************
  * @file    usbd_hid.h
  * @author  MCD Application Team
  * @brief   Header file for the usbd_hid_core.c file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2015 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                      www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_HID_H
#define __USB_HID_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include  "usbd_ioreq.h"

/** @addtogroup STM32_USB_DEVICE_LIBRARY
  * @{
  */

/** @defgroup USBD_HID
  * @brief This file is the Header file for usbd_hid.c
  * @{
  */


/** @defgroup USBD_HID_Exported_Defines
  * @{
  */ 
#define HID_EPIN_ADDR                 0x85
#define HID_EPIN_SIZE                 0x04

#define USB_HID_CONFIG_DESC_SIZ       34
#define USB_HID_DESC_SIZ              9
#define HID_GAME_CNTR_REPORT_DESC_SIZE    74

#define HID_DESCRIPTOR_TYPE           0x21
#define HID_REPORT_DESC               0x22

#define HID_HS_BINTERVAL               0x07
#define HID_FS_BINTERVAL               0x0A
#define HID_POLLING_INTERVAL           0x05

#define HID_REQ_SET_PROTOCOL          0x0B
#define HID_REQ_GET_PROTOCOL          0x03

#define HID_REQ_SET_IDLE              0x0A
#define HID_REQ_GET_IDLE              0x02

#define HID_REQ_SET_REPORT            0x09
#define HID_REQ_GET_REPORT            0x01
/**
  * @}
  */


/** @defgroup USBD_CORE_Exported_TypesDefinitions
  * @{
  */
typedef enum
{
  HID_IDLE = 0,
  HID_BUSY,
}
HID_StateTypeDef;


typedef struct
{
  uint32_t             Protocol;
  uint32_t             IdleState;
  uint32_t             AltSetting;
  HID_StateTypeDef     state;
}
USBD_HID_HandleTypeDef;
/**
  * @}
  */



/** @defgroup USBD_CORE_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup USBD_CORE_Exported_Variables
  * @{
  */

extern USBD_ClassTypeDef  USBD_HID;
#define USBD_HID_CLASS    &USBD_HID
/**
  * @}
  */

/** @defgroup USB_CORE_Exported_Functions
  * @{
  */
uint8_t USBD_HID_SendReport(USBD_HandleTypeDef *pdev,
                            uint8_t *report,
                            uint16_t len);

uint32_t USBD_HID_GetPollingInterval(USBD_HandleTypeDef *pdev);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif  /* __USB_HID_H */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
