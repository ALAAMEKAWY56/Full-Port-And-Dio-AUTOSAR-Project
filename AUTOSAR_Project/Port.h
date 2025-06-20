/**********************************************************************************************************
 * [MODULE]         :           PORT                                                                      *
 * [FILE NAME]      :           Port.h                                                                    *
 * [DESCRIPTION]    :           Header file for TM4C123GH6PM Microcontroller - Port Driver.               *
 * [DATE CREATED]   :           AUG 25, 2024                                                              *
 * [AURTHOR]        :           Alaa Mekawi                                                               *
 *********************************************************************************************************/
#ifndef PORT_H
#define PORT_H

/* Id for the company in the AUTOSAR
 * * for example Alaa Mekawi's ID = 346 :) */
#define PORT_VENDOR_ID    (346U)

/* PORT Module Id */
#define PORT_MODULE_ID    (124U)

/* PORT Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Macros for Dio Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and PORT Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
        ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
        ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Std_Types.h does not match the expected version"
#endif

/* PORT Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between PORT_Cfg.h and PORT.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
        ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
        ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of PORT_Cfg.h does not match the expected version"
#endif

/* Software Version checking between PORT_Cfg.h and Dio.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
        ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
        ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
#error "The SW version of PORT_Cfg.h does not match the expected version"
#endif

/* Non AUTOSAR files */
#include "Common_Macros.h"

/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
/* Service ID for Port_Init */
#define PORT_INIT_SID                        (uint8)0x00

/* Service ID for Port_SetPinDirection */
#define PORT_SET_PIN_DIRECTION_SID           (uint8)0x01

/* Service ID for Port_RefreshPortDirection  */
#define PORT_REFRESH_PORT_DIRECTION_SID      (uint8)0x02

/* Service ID for Port_GetVersionInfo   */
#define PORT_GET_VERSION_INFO_SID            (uint8)0x03

/* Service ID for Port_SetPinMode   */
#define PORT_SET_PIN_MODE_SID                (uint8)0x04

/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/

/* DET code to report Invalid Port Pin ID requested  */
#define PORT_E_PARAM_PIN                (uint8)0x0A

/* DET code to report Port Pin not configured as changeable   */
#define PORT_E_DIRECTION_UNCHANGEABLE   (uint8)0x0B

/* DET code to report PORT_Init API service called with NULL pointer parameter */
#define PORT_E_PARAM_CONFIG             (uint8)0x0C

/* DET code to report API Port_SetPinMode service called with Invalid Mode. */
#define PORT_E_PARAM_INVALID_MODE       (uint8)0x0D

/* DET code to report API Port_SetPinMode service called when mode is unchangeable. */
#define PORT_E_MODE_UNCHANGEABLE        (uint8)0x0E

/* DET code to report API service called without module initialization  */
#define PORT_E_UNINIT                   (uint8)0x0F

/* DET code to report APIs called with a Null Pointer  */
#define PORT_E_PARAM_POINTER            (uint8)0x10

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/* Type definition for the symbolic name of a port pin. */
typedef uint8 Port_PinType ;

/* Type definition for Different port pin modes. */
typedef uint8 Port_PinModeType ;

/*The initial direction of the pin (IN or OUT).*/
typedef enum
{
    PORT_PIN_IN,
    PORT_PIN_OUT
} Port_PinDirectionType;


/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
    OFF,PULL_UP,PULL_DOWN
}Port_InternalResistor;
/*Port pin mode from mode list for use with Port_Init() function. */
typedef enum
{
    PORT_PIN_MODE_DIO,
    PORT_PIN_MODE_ALT1,
    PORT_PIN_MODE_ALT2,
    PORT_PIN_MODE_ALT3,
    PORT_PIN_MODE_ALT4,
    PORT_PIN_MODE_ALT5,
    PORT_PIN_MODE_ALT6,
    PORT_PIN_MODE_ALT7,
    PORT_PIN_MODE_ALT8,
    PORT_PIN_MODE_ALT9,
    PORT_PIN_MODE_ALT14 = 14,
    PORT_PIN_MODE_ADC
}PortPinInitialMode ;

/*Port Pin Level value from Port pin list. */
typedef enum
{
    PORT_PIN_LEVEL_LOW , /*Port Pin level is LOW  */
    PORT_PIN_LEVEL_HIGH  /*Port Pin level is High */

}PORTPinLevelValueType;


/* Description: Structure to configure each individual PIN:
 *  1. the PORT Which the pin belongs to. 0, 1, 2, 3, 4 or 5
 *  2. the number of the pin in the PORT.
 *      3. the direction of pin --> INPUT or OUTPUT
 *      4. the Mode of pin
 *      5. the internal resistor --> Disable, Pull up or Pull down
 *      6. uint8 Pin_Direction_Changeable;
 *      7. uint8 Pin_Mode_Changeable;
 *      8. initial value of pin --> HIGH  or LOW
 */
typedef struct
{
    Port_PortID port_num;
    PortPinId pin_num;
    Port_PinDirectionType Pin_Direction;
    Port_PinModeType Pin_Mode;
    Port_InternalResistor Pin_Resistor;
    uint8 Pin_Direction_Changeable;
    uint8 Pin_Mode_Changeable;
    PORTPinLevelValueType Pin_initial_value;
}Port_ConfigPin;

/* Data Structure required for initializing the Port Driver */
typedef struct Port_ConfigType
{
    Port_ConfigPin Pins[PORT_CONFIGURED_PINS];
} Port_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/


/************************************************************************************
 * Service Name: Port_Init
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): ConfigPtr - Pointer to post-build configuration data
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to Initialize the Port Driver module.
 ************************************************************************************/
void Port_Init(
    const Port_ConfigType* ConfigPtr
);

#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
/************************************************************************************
 * Service Name: Port_SetPinDirection
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Pin:Port Pin ID number
 *                  Direction: Pin Direction
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Sets the port pin direction
 ************************************************************************************/
void Port_SetPinDirection(
    Port_PinType Pin,
    Port_PinDirectionType Direction
);
#endif

/************************************************************************************
 * Service Name: Port_RefreshPortDirection
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Refreshes port direction.
 ************************************************************************************/
void Port_RefreshPortDirection(
    void
);

#if (PORT_VERSION_INFO_API  == STD_ON)
/************************************************************************************
 * Service Name: Port_GetVersionInfo
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): Pointer to where to store the version information of this module.
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Returns the version information of this module.
 ************************************************************************************/
void Port_GetVersionInfo(
    Std_VersionInfoType* versioninfo
);
#endif

#if (PORT_SET_PIN_MODE_API == STD_ON)
/************************************************************************************
 * Service Name: Port_SetPinMode
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Pin: Port Pin ID number
 *                  Mode: New Port Pin mode to be set on port pin.
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Sets the port pin mode.
 ************************************************************************************/
void Port_SetPinMode(
    Port_PinType Pin,
    Port_PinModeType Mode
);
#endif

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by PORT and other modules */
extern const Port_ConfigType Port_Configuration;


#endif /* PORT_H */
