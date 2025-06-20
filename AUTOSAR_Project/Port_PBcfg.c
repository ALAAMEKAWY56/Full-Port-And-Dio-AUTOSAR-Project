/**********************************************************************************************************
 * [MODULE]         :           PORT                                                                      *
 * [FILE NAME]      :           Port_PBcfg.c                                                              *
 * [DESCRIPTION]    :           Post Build Configuration Source file                                      *
 *                              for TM4C123GH6PM Microcontroller - Port Driver                            *
 * [DATE CREATED]   :           AUG 25, 2024                                                              *
 * [AURTHOR]        :           Alaa Mekawi                                                               *
 *********************************************************************************************************/
/*******************************************************************************
 *                                Inclusions                                   *
 *******************************************************************************/
#include "Port.h"

/*
 * Module Version 1.0.0
 */
#define PORT_PBCFG_SW_MAJOR_VERSION              (1U)
#define PORT_PBCFG_SW_MINOR_VERSION              (0U)
#define PORT_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)

/* AUTOSAR Version checking between Port_PBcfg.c and Dio.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
        ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
        ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
        ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
        ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
#error "The SW version of PBcfg.c does not match the expected version"
#endif

/* PB structure used with Dio_Init API */
const Port_ConfigType Port_Configuration = {

/******************************************* PORTA **********************************************************/
PORTA_ID , PORT_PIN_0 , PORT_PIN_IN , PORT_PIN_MODE_DIO , OFF , STD_ON,STD_ON , PORT_PIN_LEVEL_LOW ,
PORTA_ID , PORT_PIN_1 , PORT_PIN_IN , PORT_PIN_MODE_DIO  , OFF , STD_ON,STD_ON , PORT_PIN_LEVEL_LOW ,
PORTA_ID , PORT_PIN_2 , PORT_PIN_IN , PORT_PIN_MODE_DIO , OFF , STD_ON,STD_ON , PORT_PIN_LEVEL_LOW ,
PORTA_ID , PORT_PIN_3 , PORT_PIN_IN , PORT_PIN_MODE_DIO , OFF , STD_ON,STD_ON , PORT_PIN_LEVEL_LOW ,
PORTA_ID , PORT_PIN_4 , PORT_PIN_IN , PORT_PIN_MODE_DIO , OFF , STD_ON,STD_ON , PORT_PIN_LEVEL_LOW ,
PORTA_ID , PORT_PIN_5 , PORT_PIN_IN , PORT_PIN_MODE_DIO , OFF , STD_ON,STD_ON , PORT_PIN_LEVEL_LOW ,
PORTA_ID , PORT_PIN_6 , PORT_PIN_IN , PORT_PIN_MODE_DIO , OFF , STD_ON,STD_ON , PORT_PIN_LEVEL_LOW ,
PORTA_ID , PORT_PIN_7 , PORT_PIN_IN , PORT_PIN_MODE_DIO , OFF , STD_ON,STD_ON , PORT_PIN_LEVEL_LOW ,


/******************************************* PORTB **********************************************************/
PORTB_ID , PORT_PIN_0 , PORT_PIN_IN , PORT_PIN_MODE_DIO , OFF , STD_ON,STD_ON , PORT_PIN_LEVEL_LOW ,
PORTB_ID , PORT_PIN_1 , PORT_PIN_IN , PORT_PIN_MODE_DIO , OFF , STD_ON,STD_ON , PORT_PIN_LEVEL_LOW ,
PORTB_ID , PORT_PIN_2 , PORT_PIN_IN , PORT_PIN_MODE_DIO , OFF , STD_ON,STD_ON , PORT_PIN_LEVEL_LOW ,
PORTB_ID , PORT_PIN_3 , PORT_PIN_IN , PORT_PIN_MODE_DIO , OFF , STD_ON,STD_ON , PORT_PIN_LEVEL_LOW ,
PORTB_ID , PORT_PIN_4 , PORT_PIN_IN , PORT_PIN_MODE_DIO , OFF , STD_ON,STD_ON , PORT_PIN_LEVEL_LOW ,
PORTB_ID , PORT_PIN_5 , PORT_PIN_IN , PORT_PIN_MODE_DIO , OFF , STD_ON,STD_ON , PORT_PIN_LEVEL_LOW ,
PORTB_ID , PORT_PIN_6 , PORT_PIN_IN , PORT_PIN_MODE_DIO , OFF , STD_ON,STD_ON , PORT_PIN_LEVEL_LOW ,
PORTB_ID , PORT_PIN_7 , PORT_PIN_IN , PORT_PIN_MODE_DIO , OFF , STD_ON,STD_ON , PORT_PIN_LEVEL_LOW ,

/******************************************* PORTC **********************************************************/
/*PORTC_ID , PORT_PIN_0 , PORT_PIN_IN , PORT_PIN_MODE_DIO , OFF , STD_ON,STD_ON , PORT_PIN_LEVEL_LOW ,
PORTC_ID , PORT_PIN_1 , PORT_PIN_IN , PORT_PIN_MODE_DIO , OFF , STD_ON,STD_ON , PORT_PIN_LEVEL_LOW ,
PORTC_ID , PORT_PIN_2 , PORT_PIN_IN , PORT_PIN_MODE_DIO , OFF , STD_ON,STD_ON , PORT_PIN_LEVEL_LOW ,
PORTC_ID , PORT_PIN_3 , PORT_PIN_IN , PORT_PIN_MODE_DIO , OFF , STD_ON,STD_ON , PORT_PIN_LEVEL_LOW ,*/
PORTC_ID , PORT_PIN_4 , PORT_PIN_IN , PORT_PIN_MODE_DIO , OFF , STD_ON,STD_ON , PORT_PIN_LEVEL_LOW ,
PORTC_ID , PORT_PIN_5 , PORT_PIN_IN , PORT_PIN_MODE_DIO , OFF , STD_ON,STD_ON , PORT_PIN_LEVEL_LOW ,
PORTC_ID , PORT_PIN_6 , PORT_PIN_IN , PORT_PIN_MODE_DIO , OFF , STD_ON,STD_ON , PORT_PIN_LEVEL_LOW ,
PORTC_ID , PORT_PIN_7 , PORT_PIN_IN , PORT_PIN_MODE_DIO , OFF , STD_ON,STD_ON , PORT_PIN_LEVEL_LOW ,

/******************************************* PORTD **********************************************************/
PORTD_ID , PORT_PIN_0 , PORT_PIN_IN , PORT_PIN_MODE_DIO , OFF , STD_ON,STD_ON , PORT_PIN_LEVEL_LOW ,
PORTD_ID , PORT_PIN_1 , PORT_PIN_IN , PORT_PIN_MODE_DIO , OFF , STD_ON,STD_ON , PORT_PIN_LEVEL_LOW ,
PORTD_ID , PORT_PIN_2 , PORT_PIN_IN , PORT_PIN_MODE_DIO , OFF , STD_ON,STD_ON , PORT_PIN_LEVEL_LOW ,
PORTD_ID , PORT_PIN_3 , PORT_PIN_IN , PORT_PIN_MODE_DIO , OFF , STD_ON,STD_ON , PORT_PIN_LEVEL_LOW ,
PORTD_ID , PORT_PIN_4 , PORT_PIN_IN , PORT_PIN_MODE_DIO , OFF , STD_ON,STD_ON , PORT_PIN_LEVEL_LOW ,
PORTD_ID , PORT_PIN_5 , PORT_PIN_IN , PORT_PIN_MODE_DIO , OFF , STD_ON,STD_ON , PORT_PIN_LEVEL_LOW ,
PORTD_ID , PORT_PIN_6 , PORT_PIN_IN , PORT_PIN_MODE_DIO , OFF , STD_ON,STD_ON , PORT_PIN_LEVEL_LOW ,
PORTD_ID , PORT_PIN_7 , PORT_PIN_IN , PORT_PIN_MODE_DIO , OFF , STD_ON,STD_ON , PORT_PIN_LEVEL_LOW ,

/******************************************* PORTE **********************************************************/
PORTE_ID , PORT_PIN_0 , PORT_PIN_IN , PORT_PIN_MODE_DIO , OFF , STD_ON,STD_ON , PORT_PIN_LEVEL_LOW ,
PORTE_ID , PORT_PIN_1 , PORT_PIN_IN , PORT_PIN_MODE_DIO , OFF , STD_ON,STD_ON , PORT_PIN_LEVEL_LOW ,
PORTE_ID , PORT_PIN_2 , PORT_PIN_IN , PORT_PIN_MODE_DIO , OFF , STD_ON,STD_ON , PORT_PIN_LEVEL_LOW ,
PORTE_ID , PORT_PIN_3 , PORT_PIN_IN , PORT_PIN_MODE_DIO , OFF , STD_ON,STD_ON , PORT_PIN_LEVEL_LOW ,
PORTE_ID , PORT_PIN_4 , PORT_PIN_IN , PORT_PIN_MODE_DIO , OFF , STD_ON,STD_ON , PORT_PIN_LEVEL_LOW ,
PORTE_ID , PORT_PIN_5 , PORT_PIN_IN , PORT_PIN_MODE_DIO , OFF , STD_ON,STD_ON , PORT_PIN_LEVEL_LOW ,

/******************************************* PORTF **********************************************************/
PORTF_ID , PORT_PIN_0 , PORT_PIN_IN , PORT_PIN_MODE_DIO , OFF , STD_ON,STD_ON , PORT_PIN_LEVEL_LOW ,
PORTF_ID , PORT_PIN_1 , PORT_PIN_OUT , PORT_PIN_MODE_DIO , OFF , STD_ON,STD_ON , PORT_PIN_LEVEL_LOW ,      /* Led 1 */
PORTF_ID , PORT_PIN_2 , PORT_PIN_IN , PORT_PIN_MODE_DIO , OFF , STD_ON,STD_ON , PORT_PIN_LEVEL_LOW ,
PORTF_ID , PORT_PIN_3 , PORT_PIN_IN , PORT_PIN_MODE_DIO , OFF , STD_ON,STD_ON , PORT_PIN_LEVEL_LOW ,
PORTF_ID , PORT_PIN_4 , PORT_PIN_IN , PORT_PIN_MODE_DIO , PULL_UP , STD_ON,STD_ON , PORT_PIN_LEVEL_LOW ,     /* SW1 */
};
