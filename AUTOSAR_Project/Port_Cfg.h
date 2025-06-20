/**********************************************************************************************************
 * [MODULE]         :           PORT                                                                      *
 * [FILE NAME]      :           PORT_Cfg.h                                                                *
 * [DESCRIPTION]    :           Pre-Compile Configuration Header file for                                 *
 *                              TM4C123GH6PM Microcontroller - PORT Driver                                *
 * [DATE CREATED]   :           AUG 21, 2024                                                              *
 * [AURTHOR]        :           Alaa Mekawi                                                               *
 *********************************************************************************************************/
#ifndef PORT_CFG_H_
#define PORT_CFG_H_
/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION              (1U)
#define PORT_CFG_SW_MINOR_VERSION              (0U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION     (3U)

/* Pre-compile option for Development Error Detect */
#define PORT_DEV_ERROR_DETECT               (STD_ON)

/* Pre-compile option for switch to enable / disable the use of the function Port_SetPinDirection(). */
#define PORT_SET_PIN_DIRECTION_API          (STD_ON)

/* Pre-compile option for switch to enable / disable the use of the function Port_SetPinMode().*/
#define PORT_SET_PIN_MODE_API               (STD_ON)

/* Pre-compile option for switch to enable / disable the API to read out the modules version information.*/
#define PORT_VERSION_INFO_API               (STD_ON)

/* Parameter to indicate if the direction is changeable on a port pin during
 * runtime. true: Port Pin direction changeable enabled. false: Port Pin
 * direction changeable disabled. */
#define PORT_PIN_DIRECTION_CHANGEABLE       (STD_ON)

/*Parameter to indicate if the mode is changeable on a port pin during
 * runtime. True: Port Pin mode changeable allowed. False: Port Pin mode
 * changeable not permitted. */
#define PORT_PIN_MODE_CHANGEABLE            (STD_ON)

/*
 Number of the configured Port Pins
#define PORT_CONFIGURED_PINS                (43U)
*/

/* Number of the configured Port Pins */
#define PORT_CONFIGURED_PINS                (39U)

typedef enum
{
    PORTA_ID,  /* 0 */
    PORTB_ID,  /* 1 */
    PORTC_ID,  /* 2 */
    PORTD_ID,  /* 3 */
    PORTE_ID,  /* 4 */
    PORTF_ID   /* 5 */
}Port_PortID;

/*Port Pin ID number Used For as a parameters to SetPin_Direction();*/
/******************************************* PORTA **********************************************************/
#define PORTA_PIN_0     (1U)
#define PORTA_PIN_1     (2U)
#define PORTA_PIN_2     (3U)
#define PORTA_PIN_3     (4U)
#define PORTA_PIN_4     (5U)
#define PORTA_PIN_5     (6U)
#define PORTA_PIN_6     (7U)
#define PORTA_PIN_7     (8U)

/******************************************* PORTB **********************************************************/
#define PORTB_PIN_0     (9U)
#define PORTB_PIN_1     (10U)
#define PORTB_PIN_2     (11U)
#define PORTB_PIN_3     (12U)
#define PORTB_PIN_4     (13U)
#define PORTB_PIN_5     (14U)
#define PORTB_PIN_6     (15U)
#define PORTB_PIN_7     (16U)

/******************************************* PORTC **********************************************************/
#define PORTC_PIN_4     (17U)
#define PORTC_PIN_5     (18U)
#define PORTC_PIN_6     (19U)
#define PORTC_PIN_7     (20U)

/******************************************* PORTD **********************************************************/
#define PORTD_PIN_0     (21U)
#define PORTD_PIN_1     (22U)
#define PORTD_PIN_2     (23U)
#define PORTD_PIN_3     (24U)
#define PORTD_PIN_4     (25U)
#define PORTD_PIN_5     (26U)
#define PORTD_PIN_6     (27U)
#define PORTD_PIN_7     (28U)

/******************************************* PORTE **********************************************************/
#define PORTE_PIN_0     (29U)
#define PORTE_PIN_1     (30U)
#define PORTE_PIN_2     (31U)
#define PORTE_PIN_3     (32U)
#define PORTE_PIN_4     (33U)
#define PORTE_PIN_5     (34U)

/******************************************* PORTF **********************************************************/
#define PORTF_PIN_0     (35U)
#define PORTF_PIN_1     (36U)
#define PORTF_PIN_2     (37U)
#define PORTF_PIN_3     (38U)
#define PORTF_PIN_4     (39U)
/*Pin Id of the port pin. This value will be assigned to the symbolic
 *name derived from the port pin container short name.*/
typedef enum
{
    PORT_PIN_0,     /* 0 */
    PORT_PIN_1,     /* 1 */
    PORT_PIN_2,     /* 2 */
    PORT_PIN_3,     /* 3 */
    PORT_PIN_4,     /* 4 */
    PORT_PIN_5,     /* 5 */
    PORT_PIN_6,     /* 6 */
    PORT_PIN_7      /* 7 */
}PortPinId;



#endif /* PORT_CFG_H_ */
