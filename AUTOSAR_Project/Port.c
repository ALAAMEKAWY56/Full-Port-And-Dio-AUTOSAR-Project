/**********************************************************************************************************
 * [MODULE]         :           PORT                                                                      *
 * [FILE NAME]      :           Port.c                                                                    *
 * [DESCRIPTION]    :           Source file for TM4C123GH6PM Microcontroller - Port Driver.               *
 * [DATE CREATED]   :           AUG 25, 2024                                                              *
 * [AURTHOR]        :           Alaa Mekawi                                                               *
 *********************************************************************************************************/

/*******************************************************************************
 *                                Inclusions                                   *
 *******************************************************************************/
#include "Port.h"
#include "Port_Regs.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and Dio Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
        || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
        || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Det.h does not match the expected version"
#endif

STATIC const Port_ConfigPin * Port_Channel_Config  = NULL_PTR;
STATIC volatile uint8 Port_Status = PORT_NOT_INITIALIZED;

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
void Port_Init(const Port_ConfigType* ConfigPtr)
{
    /* point to the required Port Registers base address */
    volatile uint32 * PortGpio_Ptr = NULL_PTR;

    Port_PinType index = 0;
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* check if the input configuration pointer is not a NULL_PTR */
    if (NULL_PTR == ConfigPtr)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
    }
    else
    {
        /* Do Nothing */
    }
#endif
    /*
     * Set the module state to initialized and point to the PB configuration structure using a global pointer.
     * This global pointer is global to be used by other functions to read the PB configuration structures
     */
    Port_Status = PORT_INITIALIZED;

    /* address of the first Channels structure --> Channels[0] */
    Port_Channel_Config = ConfigPtr->Pins;

    for(index = 0 ; index < PORT_CONFIGURED_PINS ; index++)
    {

        switch(Port_Channel_Config[index].port_num)
        {
        case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
        break;
        case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
        break;
        case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
        break;
        case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
        break;
        case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
        break;
        case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
        break;
        }

        if (((Port_Channel_Config[index].port_num == 3) && (Port_Channel_Config[index].pin_num == 7)) || ((Port_Channel_Config[index].port_num == 5) && (Port_Channel_Config[index].pin_num == 0)))
        {
            /* PD7 or PF0 */
            /* Unlock the GPIOCR register */
            *(volatile uint32*) ((volatile uint8*) PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;

            /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET),Port_Channel_Config[index].pin_num);
        }
        /* if Pins is PC0 to PC3  " JTAG pins" */
        else if(((Port_Channel_Config[index].port_num == 2) && (Port_Channel_Config[index].port_num <= 3)))
        {
            /* Do Nothing ...  this is the JTAG pins */
        }
        else
        {
            /* Do Nothing ... No need to unlock the commit register for this pin */
        }

        if((Port_Channel_Config[index].Pin_Direction == PORT_PIN_OUT))
        {

            /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Channel_Config[index].pin_num);

            if(Port_Channel_Config[index].Pin_initial_value == PORT_PIN_LEVEL_HIGH)
            {

                /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) ,  Port_Channel_Config[index].pin_num);
            }
            else
            {
                /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , Port_Channel_Config[index].pin_num);
            }
        }
        else if((Port_Channel_Config[index].Pin_Direction == PORT_PIN_IN))
        {
            /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Channel_Config[index].pin_num);

            if(Port_Channel_Config[index].Pin_Resistor == PULL_UP)
            {
                /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_Channel_Config[index].pin_num);
            }
            else if(Port_Channel_Config[index].Pin_Resistor == PULL_DOWN)
            {
                /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_Channel_Config[index].pin_num);
            }
            else
            {
                /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_Channel_Config[index].pin_num);

                /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_Channel_Config[index].pin_num);
            }
        }
        else
        {
            /* Do Nothing */
        }

        /* Setup the pin mode */
        if(Port_Channel_Config[index].Pin_Mode == PORT_PIN_MODE_DIO)
        {
            /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Channel_Config[index].pin_num);

            /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Channel_Config[index].pin_num);

            /* Clear the PMCx bits for this pin */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Channel_Config[index].pin_num * 4));

            /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Channel_Config[index].pin_num);
        }
        else if(Port_Channel_Config[index].Pin_Mode == PORT_PIN_MODE_ADC)
        {

            /* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Channel_Config[index].pin_num);

            /* Disable Alternative function for this pin by Set the corresponding bit in GPIOAFSEL register */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Channel_Config[index].pin_num);

            /* Clear the PMCx bits for this pin */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Channel_Config[index].pin_num * 4));

            /* Clear the corresponding bit in the GPIODEN register to disable digital functionality on this pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Channel_Config[index].pin_num);

        }
        /* Another Mode */
        else
        {
            /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Channel_Config[index].pin_num);

            /* Enable Alternative function for this pin by Set the corresponding bit in GPIOAFSEL register */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Channel_Config[index].pin_num);

            /* Clear the PMCx bits for this pin */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (Port_Channel_Config[index].Pin_Mode & 0X0000000F << (Port_Channel_Config[index].pin_num * 4));

            /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Channel_Config[index].pin_num);
        }
    }
}

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
void Port_SetPinDirection(Port_PinType Pin , Port_PinDirectionType Direction )
{
    /* point to the required Port Registers base address */
    volatile uint32 * PortGpio_Ptr = NULL_PTR;

    boolean error = FALSE;
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if the Driver is initialized before using this function */
    if (PORT_NOT_INITIALIZED == Port_Status)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                        PORT_SET_PIN_DIRECTION_SID , PORT_E_UNINIT);
        error = TRUE;
    }
    else
    {
        /* No Action Required */
    }
    /* Check if the used channel is within the valid range */
    if (PORT_CONFIGURED_PINS  <= Pin)
    {

        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                        PORT_SET_PIN_DIRECTION_SID, PORT_E_PARAM_PIN);
        error = TRUE;
    }
    else
    {
        /* No Action Required */
    }
    /* Check if the Port Pin not configured as changeable  */
    if (Port_Channel_Config[Pin].Pin_Direction_Changeable == STD_OFF)
    {

        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                        PORT_SET_PIN_DIRECTION_SID, PORT_E_DIRECTION_UNCHANGEABLE);
        error = TRUE;
    }
    else
    {
        /* No Action Required */
    }
#endif
    /* In-case there are no errors */
    if (FALSE == error)
    {
        switch(Port_Channel_Config[Pin].port_num)
        {
        case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
        break;
        case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
        break;
        case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
        break;
        case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
        break;
        case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
        break;
        case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
        break;
        }

        if((Port_Channel_Config[Pin].Pin_Direction == PORT_PIN_OUT))
        {

            /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Channel_Config[Pin].pin_num);

        }
        else if((Port_Channel_Config[Pin].Pin_Direction == PORT_PIN_IN))
        {
            /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Channel_Config[Pin].pin_num);

        }
    }

}
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
void Port_RefreshPortDirection(void)
{
    /* point to the required Port Registers base address */
    volatile uint32 * PortGpio_Ptr = NULL_PTR;

    Port_PinType index = 0;
    boolean error = FALSE;
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if the Driver is initialized before using this function */
    if (PORT_NOT_INITIALIZED == Port_Status)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                        PORT_SET_PIN_DIRECTION_SID , PORT_E_UNINIT);
        error = TRUE;
    }
    else
    {
        /* No Action Required */
    }
#endif

    /* In-case there are no errors */
    if (FALSE == error)
    {

        for(index = 0 ; index < PORT_CONFIGURED_PINS ; index++)
        {

            switch(Port_Channel_Config[index].port_num)
            {
            case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
            break;
            case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
            break;
            case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
            break;
            case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
            break;
            case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
            break;
            case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
            break;
            }

            /*The function Port_RefreshPortDirection shall exclude those port
             * pins from refreshing that are configured as ‘pin direction changeable during runtime‘.*/
            if((Port_Channel_Config[index].Pin_Direction_Changeable == STD_ON))
            {
                continue;
            }

            /*shall refresh the direction
             * of all configured ports to the configured direction (PortPinDirection). */
            else if((Port_Channel_Config[index].Pin_Direction == PORT_PIN_OUT))
            {

                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Channel_Config[index].pin_num);

            }
            else if((Port_Channel_Config[index].Pin_Direction == PORT_PIN_IN))
            {
                /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Channel_Config[index].pin_num);

            }
            else
            {
                /* Do Nothing */
            }
        }
    }

}

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
void Port_GetVersionInfo( Std_VersionInfoType* versioninfo )
{
    boolean error = FALSE;
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if the Driver is initialized before using this function */
    if (PORT_NOT_INITIALIZED == Port_Status)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                        PORT_SET_PIN_DIRECTION_SID , PORT_E_UNINIT);
        error = TRUE;
    }
    else
    {
        /* No Action Required */
    }
    /* Check if input pointer is not Null pointer */
    if(NULL_PTR == versioninfo)
    {
        /* Report to DET  */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                        PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
    }
    else
    {

    }
#endif

    /* In-case there are no errors */
    if (FALSE == error)
    {
        /* Copy the vendor Id */
        versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
        /* Copy the module Id */
        versioninfo->moduleID = (uint16)PORT_MODULE_ID;
        /* Copy Software Major Version */
        versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
        /* Copy Software Minor Version */
        versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
        /* Copy Software Patch Version */
        versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
    }
}
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
void Port_SetPinMode(Port_PinType Pin,Port_PinModeType Mode)
{
    /* point to the required Port Registers base address */
    volatile uint32 * PortGpio_Ptr = NULL_PTR;
    boolean error = FALSE;
    Port_PinType index = 0;
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if the Driver is initialized before using this function */
    if (PORT_NOT_INITIALIZED == Port_Status)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                        PORT_SET_PIN_DIRECTION_SID , PORT_E_UNINIT);
        error = TRUE;
    }
    else
    {
        /* No Action Required */
    }
    /* Check if the used pin is within the valid range */
    if (PORT_CONFIGURED_PINS  <= Pin)
    {

        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_PARAM_PIN);
        error = TRUE;
    }
    else
    {
        /* Do Nothing */
    }
    /* Check if Port Pin Mode passed not valid */
    if ((PORT_PIN_MODE_DIO  > Mode) || (PORT_PIN_MODE_ADC  < Mode) || (PORT_PIN_MODE_ALT9 < Mode && PORT_PIN_MODE_ALT14 > Mode))
    {

        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_PARAM_INVALID_MODE);
        error = TRUE;
    }
    else
    {
        /* Do Nothing */
    }
    /* Check if Port_SetPinMode service called when the mode is unchangeable */
    if (Port_Channel_Config[index].Pin_Direction_Changeable == STD_OFF)
    {

        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_MODE_UNCHANGEABLE);
        error = TRUE;
    }
    else
    {
        /* Do Nothing */
    }
#endif

    for(index = 0 ; index < PORT_CONFIGURED_PINS ; index++)
    {

        switch(Port_Channel_Config[index].port_num)
        {
        case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
        break;
        case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
        break;
        case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
        break;
        case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
        break;
        case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
        break;
        case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
        break;
        }

        /* In-case there are no errors */
        if (FALSE == error)
        {

            /* Setup the pin mode */
            if(Port_Channel_Config[index].Pin_Mode == PORT_PIN_MODE_DIO)
            {
                /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Channel_Config[index].pin_num);

                /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Channel_Config[index].pin_num);

                /* Clear the PMCx bits for this pin */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Channel_Config[index].pin_num * 4));

                /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Channel_Config[index].pin_num);
            }
            else if(Port_Channel_Config[index].Pin_Mode == PORT_PIN_MODE_ADC)
            {
                /* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Channel_Config[index].pin_num);

                /* Enable Alternative function for this pin by Set the corresponding bit in GPIOAFSEL register */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Channel_Config[index].pin_num);

                /* Clear the PMCx bits for this pin */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Channel_Config[index].pin_num * 4));

                /* Clear the corresponding bit in the GPIODEN register to disable digital functionality on this pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Channel_Config[index].pin_num);
            }
            /* Another Mode */
            else
            {
                /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Channel_Config[index].pin_num);

                /* Enable Alternative function for this pin by Set the corresponding bit in GPIOAFSEL register */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Channel_Config[index].pin_num);

                /* Clear the PMCx bits for this pin */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= ((Port_Channel_Config[index].Pin_Mode & 0X0000000F) << (Port_Channel_Config[index].pin_num * 4));

                /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Channel_Config[index].pin_num);
            }
        }
    }
}
#endif

#endif
