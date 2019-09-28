/**
 *  \file       dIn.c
 *  \brief      Implementation of Digital Inputs HAL and change detection.
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
#include "cubemx.h"
#include "auxiliares.h"
#include "IOChgDet.h"
#include "din.h"
#include "mTimeCfg.h"

/* ----------------------------- Local macros ------------------------------ */
#define DEBOUNCE_NSAMPLE    3
#define DEBOUNCE_MASK       ((uint8_t)((1 << DEBOUNCE_NSAMPLE) - 1))
#define DEBOUNCE_CHG        ((uint8_t)((1 << (DEBOUNCE_NSAMPLE - 1)) - 1))
#define DEBOUNCE_NOT_MASK	((uint8_t)~DEBOUNCE_MASK)
#define DEBOUNCE_NOT_CHG	((uint8_t)~DEBOUNCE_CHG)

#define EnablePin_Init()       gpioConfig(OUT_EN_Port, OUT_EN_Pin, GPIO_MODE_OUTPUT_PP)
#define ParSerPin_Init()       gpioConfig(IN_P_S_Port, IN_P_S_Pin, GPIO_MODE_OUTPUT_PP)
#define ClkPin_Init()          gpioConfig(IN_CLK_Port, IN_CLK_Pin, GPIO_MODE_OUTPUT_PP)
#define SerInPin_Init()        gpioConfig(IN_READ_Port, IN_READ_Pin, GPIO_MODE_INPUT)

#define SerInPin_Read()        GPIO_ReadPin(IN_READ_Port, IN_READ_Pin)
#define EnablePin_Set(b)       GPIO_WritePin(OUT_EN_Port, OUT_EN_Pin, b)
#define ClkPin_Set(b)          GPIO_WritePin(IN_CLK_Port, IN_CLK_Pin, b)
#define Parallel_load()        GPIO_WritePin(IN_P_S_Port, IN_P_S_Pin, 1)
#define Serial_mode()		   GPIO_WritePin(IN_P_S_Port, IN_P_S_Pin, 0)


//#define CANTIDAD_ENTRADAS	8
//#define TAMANIO_REGISTROS	8		// Entradas por cada módulo
//#define CANTIDAD_MODULOS	(CANTIDAD_ENTRADAS % TAMANIO_REGISTROS)? ((CANTIDAD_ENTRADAS % TAMANIO_REGISTROS) +1): (CANTIDAD_ENTRADAS % TAMANIO_REGISTROS)


//static uint8_t registros[CANTIDAD_MODULOS];

/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */

/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static uint8_t dIns[NUM_DIN_SIGNALS];
static uint8_t dInsSt[NUM_DIN_SIGNALS];
static uint8_t clk = 0;
static int i = NUM_DIN_SIGNALS -1;


/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */

/* ---------------------------- Global functions --------------------------- */
void
dIn_init(void)
{
	EnablePin_Init();
	ParSerPin_Init();
	ClkPin_Init();
	SerInPin_Init();

	EnablePin_Set(0);

}

void
dIn_scan(void)
{

    uint8_t din;


    if(clk == 1)
    {
    	ClkPin_Set(0); clk = 0;

        if(i == 0)
        {
        	i = NUM_DIN_SIGNALS;
        	Parallel_load();
        }

    	i--;
    }
    else
    {
    	Serial_mode();
        din = (dIns[i] << 1) | SerInPin_Read();
    	ClkPin_Set(1); clk = 1;


        if((dIns[i] == DEBOUNCE_CHG) && (din == DEBOUNCE_MASK) && (dInsSt[i] == 0))
        {
            dInsSt[i] = 1;
            IOChgDet_put(i, 1);
        }
        else if((dIns[i] == DEBOUNCE_NOT_CHG) && (din == DEBOUNCE_NOT_MASK) && (dInsSt[i] == 1))
        {
            dInsSt[i] = 0;
            IOChgDet_put(i, 0);
        }

        dIns[i] = din;

    }

}

/* ------------------------------ End of file ------------------------------ */
