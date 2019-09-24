/**
 *  \file       bsp.c
 *  \brief      BSP for CIAA-NXP Prototype
 *
 *  \ingroup    bsp
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.04.14  DaBa  v0.0.01  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  DaBa  Dario Baliña       db@vortexmakes.com
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include <stdio.h>
#include "rkh.h"
#include "auxiliares.h"
#include "cubemx.h"
#include "bsp.h"

#include "signals.h"
#include "modpwr.h"
#include "modmgr.h"
#include "modcmd.h"
#include "conmgr.h"
#include "CirBuffer.h"
#include "mTime.h"
#include "din.h"
#include "anin.h"
#include "anSampler.h"
#include "ioChgDet.h"
#include "epoch.h"
#include "rtime.h"

RKH_THIS_MODULE



/* ----------------------------- Local macros ------------------------------ */
#define ModStatus_init()    gpioConfig(LED2_GPIO_PORT, LED2_PIN, GPIO_MODE_OUTPUT_PP)
#define ModStatus(b)        GPIO_WritePin( LED2_GPIO_PORT , LED2_PIN, b) // gpioWrite(DO5, b)
#define ModStatus_toggle()  GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN) //gpioToggle(DO5)
#define RegStatus_init()    gpioConfig(LED3_GPIO_PORT, LED3_PIN, GPIO_MODE_OUTPUT_PP)
#define RegStatus(b)        GPIO_WritePin( LED3_GPIO_PORT , LED3_PIN, b) //gpioWrite(DO6, b)
#define NetStatus_init()    gpioConfig(LED4_GPIO_PORT, LED4_PIN, GPIO_MODE_OUTPUT_PP)
#define NetStatus(b)        GPIO_WritePin( LED4_GPIO_PORT , LED4_PIN, b) //gpioWrite(DO7, b)

/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static RKH_TS_T tstamp;
static ModCmdRcvHandler cmdParser;

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
void
bsp_init(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();
    /* Configure the system clock */
    SystemClock_Config();
    /* Initialize all configured peripherals */
   // MX_GPIO_Init();
  //  MX_ADC1_Init();
  //  MX_CAN1_Init();
  //  MX_I2C1_Init();
  //  MX_I2C3_Init();
   // MX_RTC_Init();
  //  MX_SDIO_SD_Init();
  //  MX_SPI1_Init();
    MX_UART4_Init();
  //  MX_USART1_UART_Init();
  //  MX_USART2_UART_Init();
  //  MX_USART3_UART_Init();
    MX_USART6_UART_Init();

    //boardConfig();
    ModStatus_init();
    ModStatus(0);
    RegStatus(UnregisteredSt);
    NetStatus_init();
    NetStatus(DisconnectedSt);

    modPwr_init();
    dIn_init();
	anIn_init();

    rtime_init();
}

void
bsp_timeTick(void)
{
    ++tstamp;
    
    modPwr_ctrl();
    mTime_tick();
}

RKH_TS_T
rkh_trc_getts(void)
{
    return tstamp;
}


static uint8_t uart1RxBuff[10];
static uint8_t uart2RxBuff[10];
static uint8_t uart3RxBuff[10];
static uint8_t uart4RxBuff[10];
static uint8_t uart6RxBuff[10];
static uint8_t Buff[200];
static uint8_t x;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
	//TODO faltan los otros handlers
    if (UartHandle->Instance == USART1)
    {
        //tplink_rx_isr(uart1RxBuff[0]);

        HAL_UART_Receive_IT(&huart1, uart1RxBuff, 1);
    }
    else if (UartHandle->Instance == UART4)
    {
        if (cmdParser != NULL)
        {
            cmdParser(uart4RxBuff[0]);
            Buff[x] = uart4RxBuff[0];
            x++;
            if(x == 200){
            	x=0;
            }
        }

        HAL_UART_Receive_IT(&huart4, uart4RxBuff, 1);
    }
    else if (UartHandle->Instance == USART3)
    {
        HAL_UART_Receive_IT(&huart3, uart3RxBuff, 1);
    }
}

void
bsp_serial_open(int ch)
{
    //(void)ch;
	    switch(ch)
    {	
		case ESP_PORT:
            MX_USART1_UART_Init();
			HAL_UART_Receive_IT(&huart1, uart1RxBuff, 1);
            break;		
        case A6_PORT:
            MX_USART2_UART_Init();
			HAL_UART_Receive_IT(&huart2, uart2RxBuff, 1);
            break;
        case RS485_PORT:
            MX_USART3_UART_Init();
			HAL_UART_Receive_IT(&huart3, uart3RxBuff, 1);
            break;
        case SIM800_PORT:
		default:
			cmdParser = ModCmd_init();
            MX_UART4_Init();
			HAL_UART_Receive_IT(&huart4, uart4RxBuff, 1);
            break;
        case DEBUG_PORT:
            MX_USART6_UART_Init();
			HAL_UART_Receive_IT(&huart6, uart6RxBuff, 1);
            break;
    }

    //cmdParser = ModCmd_init();
    //uartConfig(UART_232, 19200);
    //uartIsr_rxEnable(UART_232, gsm_rx_isr);
}

void
bsp_serial_close(int ch)
{
    (void)ch;
}

void
bsp_serial_putchar(int ch, unsigned char c)
{
	UART_HandleTypeDef *pUart;

    switch(ch)
    {	
		case ESP_PORT:
            pUart = &huart1;
            break;		
        case A6_PORT:
            pUart = &huart2;
            break;
        case RS485_PORT:
            pUart = &huart3;
            break;
        case SIM800_PORT:
		default:
            pUart = &huart4;
            break;
        case DEBUG_PORT:
            pUart = &huart6;
            break;
    }
    
    HAL_UART_Transmit(pUart, &c, 1, 100);
}

void
bsp_serial_puts(int ch, char *p)
{
    while(*p!='\0')
    {
		bsp_serial_putchar(ch, *p);
        ++p;
    }

}

void
bsp_serial_putnchar(int ch, unsigned char *p, ruint ndata)
{
    while(ndata && (ndata-- != 0))
    {
        bsp_serial_putchar(ch, *p);
        ++p;
    }

}

void
bsp_regStatus(Status_t status)
{
    RegStatus(status);
}

void 
bsp_netStatus(Status_t status)
{
    NetStatus(status);
}

void 
bsp_modStatusToggle(void)
{
    ModStatus_toggle();
}

void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* ------------------------------ File footer ------------------------------ */
