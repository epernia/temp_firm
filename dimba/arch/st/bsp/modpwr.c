/**
 *  \file       modpwr_sim900.c
 *  \brief      Implementation of modpwr abstraction for SIM900 on CIAA-NXP.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2018.06.05  DaBa  v1.0.00  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  DaBa  Dario Bali�a       db@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "cubemx.h"
#include "auxiliares.h"

#include "rkh.h"
#include "modpwr.h"
#include "mTimeCfg.h"

/* ----------------------------- Local macros ------------------------------ */
//TODO pueden estar invertidos los pines de DTR y Power
#define PwrKey_init()       //gpioConfig(S800_DTR_GPIO_PORT, S800_DTR_PIN, GPIO_MODE_OUTPUT_PP)
#define PwrKey(b)           //GPIO_WritePin( S800_DTR_GPIO_PORT, S800_DTR_PIN, b)
#define Power_init()        gpioConfig(S800_PW_GPIO_PORT, S800_PW_PIN, GPIO_MODE_OUTPUT_OD)
#define Power(b)            GPIO_WritePin( S800_PW_GPIO_PORT, S800_PW_PIN, !b)

#define modPwr_toggle() \
        { \
            RKH_ENTER_CRITICAL(); \
            counter = SIM900_PWR_TIME; \
            state = Toggling; \
            RKH_EXIT_CRITICAL(); \
        }

/* ------------------------------- Constants ------------------------------- */
#define SIM900_PWR_TIME     (1000/MTIME_MODPWR_BASE)

/* ---------------------------- Local data types --------------------------- */
typedef enum ModPwrStates
{
    OnOff,
    Toggling
}ModPwrStates;

/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static ruint state, counter;

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
void
modPwr_init(void)
{
    PwrKey_init();
    PwrKey(1);
    Power_init();
    Power(1);
    state = OnOff;
}

void
modPwr_ctrl(void)
{
    switch(state)
    {
        case OnOff:
            PwrKey(1);
            break;

        case Toggling:
            PwrKey(0);
            if(counter && (--counter == 0))
            {
                state = OnOff;
            }

            break;
    }
}


void
modPwr_off(void)
{
    Power(0);
    modPwr_toggle();
}

void
modPwr_on(void)
{
    Power(1);
    modPwr_toggle();
}

/* ------------------------------ End of file ------------------------------ */
