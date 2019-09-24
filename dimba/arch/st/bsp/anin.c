/**
 *  \file       anin.c
 *  \brief      Implementation of Analog Inputs adquisition and filtering.
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
#include "rkh.h"
#include "anin.h"
#include "mTimeCfg.h"
#include "emaFilter.h"
#include "anSampler.h"
#include "cubemx.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
#define ANINS_EMA_ALPHA     2

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static adc_t anIns[NUM_ANIN_SIGNALS];
static int currChannel;
//static
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static void
anIn_adcStart(int channel)
{
	HAL_ADC_Start(&hadc1); // enable and start
}

static uint16_t
anIn_adcRead(int channel)
{   
	uint16_t analogValue = 0; 

	HAL_ADC_PollForConversion(&hadc1, 3);

	analogValue = HAL_ADC_GetValue(&hadc1);

    return analogValue;
}


/* ---------------------------- Global functions --------------------------- */
void
anIn_init(void)
{
	MX_ADC1_Init(); 
    currChannel = anIn0; 
    anIn_adcStart(currChannel);
}

void
anIn_captureAndFilter(void)
{
    uint16_t value;

    value = anIn_adcRead(currChannel);
    anIns[currChannel] = emaFilter_LowPass(value, 
                                           anIns[currChannel],
                                           ANINS_EMA_ALPHA);

    if(++currChannel > anIn3)
        currChannel = anIn0;

    anIn_adcStart(currChannel);
}

adc_t
anIn_get(int channel)
{
    if(channel > NUM_ANIN_SIGNALS)
        return 0;

    return anIns[channel];
}

void
anIn_update(void)
{
   anSampler_put();
}

/* ------------------------------ End of file ------------------------------ */
