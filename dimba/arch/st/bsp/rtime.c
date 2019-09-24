/**
 *  \file       rtime.c
 *  \brief      Implementation of RTC abstraction for CIAA-NXP bsp.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2018.05.17  DaBa  v1.0.00  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  DaBa  Dario Baliña       db@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rtime.h"
#include "cubemx.h"



/* ----------------------------- Local macros ------------------------------ */
#define RunLed_init()      gpioConfig(LED1_GPIO_PORT, LED1_PIN, GPIO_MODE_OUTPUT_PP) 
#define RunLed_toggle()    GPIO_TogglePin( LED1_GPIO_PORT, LED1_PIN)

/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static Time t;
extern RTC_HandleTypeDef hrtc;
//static rtc_t rtc;
//static rtc_t rtcDft = { 1970, 1, 1, 1, 0, 0, 0 };

static RTC_TimeTypeDef sTime = {0};
static RTC_DateTypeDef sDate = {0};

/* ----------------------- Local function prototypes ----------------------- */
static void rtime_default(void);
/* ---------------------------- Local functions ---------------------------- */
static void 
rtime_default(void)
{
	  /** Initialize RTC and set the Time and Date */

  sTime.Hours = 0x0;
  sTime.Minutes = 0x0;
  sTime.Seconds = 0x0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
  
  sDate.WeekDay = RTC_WEEKDAY_MONDAY;
  sDate.Month = RTC_MONTH_JANUARY;
  sDate.Date = 0x1;
  sDate.Year = 49;

  HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
  
}
/* ---------------------------- Global functions --------------------------- */
void
rtime_init(void)
{
    RunLed_init();
    RunLed_toggle();
	
	MX_RTC_Init();
	
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	//TODO Capaz que sea menor a cero
    if( (sDate.Year < 1970) ||
		(sDate.Month < 1) || (sDate.Month > 12) ||
    	(sDate.Date < 1) || (sDate.Date > 31) ||
		(sDate.WeekDay < 1) || (sDate.WeekDay > 7) ||
		(sTime.Hours < 0) || (sTime.Hours > 23) ||
		(sTime.Minutes < 0) || (sTime.Minutes > 59) ||
		(sTime.Seconds < 0) || (sTime.Seconds > 59)
      )
    {
    	//rtcWrite(&rtcDft);
		rtime_default();
    }
}

Time *
rtime_get(void)
{
    RunLed_toggle();

	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	
    t.tm_sec = sTime.Seconds;
    t.tm_min = sTime.Minutes;
    t.tm_hour = sTime.Hours;
	
    t.tm_mday = sDate.Date;
    t.tm_mon = sDate.Month;
    t.tm_year = sDate.Year + 1970;
    t.tm_wday = sDate.WeekDay;
    t.tm_isdst = 0;

    return &t;
}

void
rtime_set(Time *pt)
{
    sTime.Seconds = pt->tm_sec;
    sTime.Minutes = pt->tm_min;
    sTime.Hours = pt->tm_hour;
	
    sDate.WeekDay = pt->tm_wday;
    sDate.Date = pt->tm_mday;
    sDate.Month = pt->tm_mon;
    sDate.Year = pt->tm_year - 1970;

	HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	
}

/* ------------------------------ End of file ------------------------------ */
