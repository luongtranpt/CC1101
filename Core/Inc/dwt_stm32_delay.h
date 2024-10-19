#ifndef DWT_STM32_DELAY_H
#define DWT_STM32_DELAY_H

#ifdef __cplusplus
extern "C" {
#endif


#ifndef __STM32F4xx_LL_H
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_rcc.h"
#include "stm32f4xx_ll_system.h"
#endif


/**
 * @brief  Initializes DWT_Cycle_Count for DWT_Delay_us function
 * @return Error DWT counter
 *         1: DWT counter Error
 *         0: DWT counter works
 */
uint32_t DWT_Delay_Init(void);



/**
 * @brief  This function provides a delay (in microseconds)
 * @param  microseconds: delay in microseconds
 */
//__STATIC_INLINE void DWT_Delay_us(volatile uint32_t microseconds)
//{
//  uint32_t clk_cycle_start = DWT->CYCCNT;
//
//  /* Go to number of cycles for system */
//  microseconds *= (HAL_RCC_GetHCLKFreq() / 1000000);
//
//  /* Delay till end */
//  while ((DWT->CYCCNT - clk_cycle_start) < microseconds);
//}
__STATIC_INLINE void DWT_Delay_us(volatile uint32_t microseconds) {
    uint32_t clk_cycle_start = DWT->CYCCNT;

    /* Get the system clock frequency */
    LL_RCC_ClocksTypeDef rcc_clocks;
    LL_RCC_GetSystemClocksFreq(&rcc_clocks);
    uint32_t hclk_frequency = rcc_clocks.HCLK_Frequency;

    /* Convert microseconds to clock cycles */
    microseconds *= (hclk_frequency / 1000000);

    /* Delay till end */
    while ((DWT->CYCCNT - clk_cycle_start) < microseconds);
}


#ifdef __cplusplus
}
#endif

#endif
