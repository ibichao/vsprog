/**************************************************************************
 *  Copyright (C) 2008 - 2010 by Simon Qian                               *
 *  SimonQian@SimonQian.com                                               *
 *                                                                        *
 *  Project:    Versaloon                                                 *
 *  File:       interfaces.c                                              *
 *  Author:     SimonQian                                                 *
 *  Versaion:   See changelog                                             *
 *  Purpose:    interfaces implementation file                            *
 *  License:    See license                                               *
 *------------------------------------------------------------------------*
 *  Change Log:                                                           *
 *      YYYY-MM-DD:     What(by Who)                                      *
 *      2010-12-05:     created(by SimonQian)                             *
 **************************************************************************/

#include "app_cfg.h"
#include "interfaces.h"

vsf_err_t peripheral_commit(void)
{
	return VSFERR_NONE;
}

const struct interfaces_info_t core_interfaces = 
{
	CORE_INIT(__TARGET_CHIP__),
	CORE_FINI(__TARGET_CHIP__),
	CORE_RESET(__TARGET_CHIP__),
	
	// flash
	{
		CORE_FLASH_INIT(__TARGET_CHIP__),
		CORE_FLASH_FINI(__TARGET_CHIP__),
		CORE_FLASH_LOCK(__TARGET_CHIP__),
		CORE_FLASH_UNLOCK(__TARGET_CHIP__),
		CORE_FLASH_GETCAPACITY(__TARGET_CHIP__),
		CORE_FLASH_READ(__TARGET_CHIP__),
		CORE_FLASH_READ_ISREADY(__TARGET_CHIP__),
		CORE_FLASH_WRITE(__TARGET_CHIP__),
		CORE_FLASH_WRITE_ISREADY(__TARGET_CHIP__),
		CORE_FLASH_READPAGE(__TARGET_CHIP__),
		CORE_FLASH_READPAGE_ISREADY(__TARGET_CHIP__),
		CORE_FLASH_ERASEPAGE(__TARGET_CHIP__),
		CORE_FLASH_ERASEPAGE_ISREADY(__TARGET_CHIP__),
		CORE_FLASH_WRITEPAGE(__TARGET_CHIP__),
		CORE_FLASH_WRITEPAGE_ISREADY(__TARGET_CHIP__),
		CORE_FLASH_ISPROTECTED(__TARGET_CHIP__),
		CORE_FLASH_PROTECT(__TARGET_CHIP__),
	},
	{
		// gpio
		CORE_GPIO_INIT(__TARGET_CHIP__),
		CORE_GPIO_FINI(__TARGET_CHIP__),
		CORE_GPIO_CONFIG_PIN(__TARGET_CHIP__),
		CORE_GPIO_CONFIG(__TARGET_CHIP__),
		CORE_GPIO_SET(__TARGET_CHIP__),
		CORE_GPIO_CLEAR(__TARGET_CHIP__),
		CORE_GPIO_OUT(__TARGET_CHIP__),
		CORE_GPIO_IN(__TARGET_CHIP__),
		CORE_GPIO_GET(__TARGET_CHIP__)
	},
	{
		// timer
		CORE_TIMER_INIT(__TARGET_CHIP__),
		CORE_TIMER_FINI(__TARGET_CHIP__),
		CORE_TIMER_CONFIG(__TARGET_CHIP__),
		CORE_TIMER_START(__TARGET_CHIP__),
		CORE_TIMER_STOP(__TARGET_CHIP__),
		CORE_TIMER_GET_COUNT(__TARGET_CHIP__),
		CORE_TIMER_SET_COUNT(__TARGET_CHIP__),
		CORE_TIMER_CONFIG_CHANNEL(__TARGET_CHIP__),
		CORE_TIMER_GET_CHANNEL(__TARGET_CHIP__),
		CORE_TIMER_SET_CHANNEL(__TARGET_CHIP__),
	},
	{
		// eint
		CORE_EINT_INIT(__TARGET_CHIP__),
		CORE_EINT_FINI(__TARGET_CHIP__),
		CORE_EINT_CONFIG(__TARGET_CHIP__),
		CORE_EINT_ENABLE(__TARGET_CHIP__),
		CORE_EINT_DISABLE(__TARGET_CHIP__),
		CORE_EINT_TRIGGER(__TARGET_CHIP__),
	},
	{
		// usart
		CORE_USART_INIT(__TARGET_CHIP__),
		CORE_USART_FINI(__TARGET_CHIP__),
		CORE_USART_CONFIG(__TARGET_CHIP__),
		CORE_USART_CONFIG_CALLBACK(__TARGET_CHIP__),
		CORE_USART_TX(__TARGET_CHIP__),
		CORE_USART_TX_ISREADY(__TARGET_CHIP__),
		CORE_USART_RX(__TARGET_CHIP__),
		CORE_USART_RX_ISREADY(__TARGET_CHIP__),
	},
	{
		// spi
		CORE_SPI_INIT(__TARGET_CHIP__),
		CORE_SPI_FINI(__TARGET_CHIP__),
		CORE_SPI_GET_ABILITY(__TARGET_CHIP__),
		CORE_SPI_ENABLE(__TARGET_CHIP__),
		CORE_SPI_DISABLE(__TARGET_CHIP__),
		CORE_SPI_CONFIG(__TARGET_CHIP__),
		CORE_SPI_IO_TX(__TARGET_CHIP__),
		CORE_SPI_IO_TX_ISREADY(__TARGET_CHIP__),
		CORE_SPI_IO_RX(__TARGET_CHIP__),
		CORE_SPI_IO_RX_ISREADY(__TARGET_CHIP__),
		CORE_SPI_IO(__TARGET_CHIP__),
		CORE_SPI_IO_DMA_START(__TARGET_CHIP__),
		CORE_SPI_IO_DMA_ISREADY(__TARGET_CHIP__),
		CORE_SPI_IO_DMA_END(__TARGET_CHIP__)
	},
	{
		// adc
		CORE_ADC_INIT(__TARGET_CHIP__),
		CORE_ADC_FINI(__TARGET_CHIP__),
		CORE_ADC_CONFIG(__TARGET_CHIP__),
		CORE_ADC_CONFIG_CHANNEL(__TARGET_CHIP__),
		CORE_ADC_CALIBRATE(__TARGET_CHIP__),
		CORE_ADC_START(__TARGET_CHIP__),
		CORE_ADC_ISREADY(__TARGET_CHIP__),
		CORE_ADC_GET(__TARGET_CHIP__),
	},
	{
		// i2c
		NULL, NULL, NULL, NULL, NULL
	},
	{
		// usbd
		CORE_USBD_INIT(__TARGET_CHIP__),
		CORE_USBD_FINI(__TARGET_CHIP__),
		CORE_USBD_RESET(__TARGET_CHIP__),
		CORE_USBD_POLL(__TARGET_CHIP__),
		CORE_USBD_CONNECT(__TARGET_CHIP__),
		CORE_USBD_DISCONNECT(__TARGET_CHIP__),
		CORE_USBD_SET_ADDRESS(__TARGET_CHIP__),
		CORE_USBD_GET_ADDRESS(__TARGET_CHIP__),
		CORE_USBD_SUSPEND(__TARGET_CHIP__),
		CORE_USBD_RESUME(__TARGET_CHIP__),
		CORE_USBD_LOWPOWER(__TARGET_CHIP__),
		CORE_USBD_GET_FRAME_NUM(__TARGET_CHIP__),
		// ep
		{
			&CORE_USBD_EP_NUM(__TARGET_CHIP__),
			CORE_USBD_EP_RESET(__TARGET_CHIP__),
			CORE_USBD_EP_SET_TYPE(__TARGET_CHIP__),
			CORE_USBD_EP_GET_TYPE(__TARGET_CHIP__),
			
			CORE_USBD_EP_SET_IN_HANDLER(__TARGET_CHIP__),
			CORE_USBD_EP_SET_IN_DBUFFER(__TARGET_CHIP__),
			CORE_USBD_EP_IS_IN_DBUFFER(__TARGET_CHIP__),
			CORE_USBD_EP_SWITCH_IN_BUFFER(__TARGET_CHIP__),
			CORE_USBD_EP_SET_IN_EPSIZE(__TARGET_CHIP__),
			CORE_USBD_EP_GET_IN_EPSIZE(__TARGET_CHIP__),
			CORE_USBD_EP_RESET_IN_TOGGLE(__TARGET_CHIP__),
			CORE_USBD_EP_TOGGLE_IN_TOGGLE(__TARGET_CHIP__),
			CORE_USBD_EP_GET_IN_STATE(__TARGET_CHIP__),
			CORE_USBD_EP_SET_IN_STATE(__TARGET_CHIP__),
			CORE_USBD_EP_SET_IN_COUNT(__TARGET_CHIP__),
			CORE_USBD_EP_WRITE_IN_BUFFER(__TARGET_CHIP__),
			
			CORE_USBD_EP_SET_OUT_HANDLER(__TARGET_CHIP__),
			CORE_USBD_EP_SET_OUT_DBUFFER(__TARGET_CHIP__),
			CORE_USBD_EP_IS_OUT_DBUFFER(__TARGET_CHIP__),
			CORE_USBD_EP_SWITCH_OUT_BUFFER(__TARGET_CHIP__),
			CORE_USBD_EP_SET_OUT_EPSIZE(__TARGET_CHIP__),
			CORE_USBD_EP_GET_OUT_EPSIZE(__TARGET_CHIP__),
			CORE_USBD_EP_RESET_OUT_TOGGLE(__TARGET_CHIP__),
			CORE_USBD_EP_TOGGLE_OUT_TOGGLE(__TARGET_CHIP__),
			CORE_USBD_EP_GET_OUT_STATE(__TARGET_CHIP__),
			CORE_USBD_EP_SET_OUT_STATE(__TARGET_CHIP__),
			CORE_USBD_EP_GET_OUT_COUNT(__TARGET_CHIP__),
			CORE_USBD_EP_READ_OUT_BUFFER(__TARGET_CHIP__),
		},
	},
	{
		// pwm
		NULL, NULL, NULL, NULL, NULL
	},
	{
		// microwre
		NULL, NULL, NULL, NULL, NULL
	},
	{
		// delay
		CORE_DELAY_INIT(__TARGET_CHIP__),
		CORE_DELAY_DELAYMS(__TARGET_CHIP__),
		CORE_DELAY_DELAYUS(__TARGET_CHIP__)
	},
	{
		// ebi
		CORE_EBI_INIT(__TARGET_CHIP__),
		CORE_EBI_FINI(__TARGET_CHIP__),
		
		CORE_EBI_CONFIG(__TARGET_CHIP__),
		CORE_EBI_CONFIG_SRAM(__TARGET_CHIP__),
		CORE_EBI_CONFIG_PSRAM(__TARGET_CHIP__),
		CORE_EBI_CONFIG_NOR(__TARGET_CHIP__),
		CORE_EBI_CONFIG_NAND(__TARGET_CHIP__),
		CORE_EBI_CONFIG_SDRAM(__TARGET_CHIP__),
		CORE_EBI_CONFIG_DDRAM(__TARGET_CHIP__),
		CORE_EBI_CONFIG_PCCARD(__TARGET_CHIP__),
		
		CORE_EBI_READ(__TARGET_CHIP__),
		CORE_EBI_WRITE(__TARGET_CHIP__),
		CORE_EBI_READ8(__TARGET_CHIP__),
		CORE_EBI_WRITE8(__TARGET_CHIP__),
		CORE_EBI_READ16(__TARGET_CHIP__),
		CORE_EBI_WRITE16(__TARGET_CHIP__),
		CORE_EBI_READ32(__TARGET_CHIP__),
		CORE_EBI_WRITE32(__TARGET_CHIP__),
		
		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
	},
	peripheral_commit
};

struct interfaces_info_t *interfaces = 
								(struct interfaces_info_t *)&core_interfaces;
