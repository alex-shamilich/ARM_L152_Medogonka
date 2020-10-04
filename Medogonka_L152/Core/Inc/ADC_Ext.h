#ifndef __adc_ext_H
#define __adc_ext_H

// макросы для работы с внутренним термодатчиком и рассчета реального напряжения питания (Утащено с STM32L4xx_II_adc.h)

#ifdef __cplusplus
 extern "C" {
#endif

 /* Internal temperature sensor: constants data used for indicative values in  */
 /* this example. Refer to device datasheet for min/typ/max values.            */
 /* For more accurate values, device should be calibrated on offset and slope  */
 /* for application temperature range.                                         */
 #define VDDA_APPLI                     ((uint32_t) 3305)        						/* Value of analog voltage supply Vdda (unit: mV) */
 #define RANGE_12BITS                   ((uint32_t) 4095)        						/* Max digital value with a full range of 12 bits */


/* Internal voltage reference VrefInt */
 #define VREFINT_CAL_ADDR  ((uint16_t*) ((uint32_t) 0x1FF800F8))     					/*  Embedded internal reference voltage calibration values */
 #define VREFINT_CAL_VREF               ( 3000UL)                    					/* Analog voltage reference (Vref+) value with which temperature sensor has been calibrated in production (tolerance: +-10 mV) (unit: mV). */

 #define VDDA_TEMP_CAL                  ((uint32_t) 3000)        						/* Vdda value with which temperature sensor has been calibrated in production (+-10 mV). */

 /* ADC internal channels related definitions */
  /* Temperature sensor */
 #define TEMP30_CAL_ADDR   ((uint16_t*) ((uint32_t) 0x1FF800FA))     					/* Internal temperature sensor, parameter TS_CAL1: TS ADC raw data acquired at a temperature of 110 DegC (+-5 DegC), VDDA = 3.3 V (+-10 mV). */
 #define TEMP110_CAL_ADDR  ((uint16_t*) ((uint32_t) 0x1FF800FE))     					/* Internal temperature sensor, parameter TS_CAL2: TS ADC raw data acquired at a temperature of  30 DegC (+-5 DegC), VDDA = 3.3 V (+-10 mV). */

 #define TEMPSENSOR_CAL1_ADDR               ((uint16_t*) (0x1FF800FA)) 					/* Internal temperature sensor, address of parameter TS_CAL1: On STM32L4, temperature sensor ADC raw data acquired at temperature  30 DegC (tolerance: +-5 DegC), Vref+ = 3.0 V (tolerance: +-10 mV). */
 #define TEMPSENSOR_CAL2_ADDR               ((uint16_t*) (0x1FF800FE)) 					/* Internal temperature sensor, address of parameter TS_CAL2: On STM32L4, temperature sensor ADC raw data acquired at temperature defined by TEMPSENSOR_CAL2_TEMP (tolerance: +-5 DegC), Vref+ = 3.0 V (tolerance: +-10 mV). */
 #define TEMPSENSOR_CAL1_TEMP               (( int32_t)   30L)          				/* Internal temperature sensor, temperature at which temperature sensor has been calibrated in production for data into TEMPSENSOR_CAL1_ADDR (tolerance: +-5 DegC) (unit: DegC). */
 #define TEMPSENSOR_CAL2_TEMP               (( int32_t)  110L)                       	/* Internal temperature sensor, temperature at which temperature sensor has been calibrated in production for data into TEMPSENSOR_CAL2_ADDR (tolerance: +-5 DegC) (unit: DegC). */
 #define TEMPSENSOR_CAL_VREFANALOG          (3000UL)                     				/* Analog voltage reference (Vref+) voltage with which temperature sensor has been calibrated in production (+-10 mV) (unit: mV). */


 /* ADC registers bits positions */
 #define ADC_CFGR_RES_BITOFFSET_POS         ( 3UL) 										/* Value equivalent to bitfield "ADC_CFGR_RES" position in register */
 #define ADC_CFGR_AWD1SGL_BITOFFSET_POS     (22UL) 										/* Value equivalent to bitfield "ADC_CFGR_AWD1SGL" position in register */
 #define ADC_CFGR_AWD1EN_BITOFFSET_POS      (23UL) 										/* Value equivalent to bitfield "ADC_CFGR_AWD1EN" position in register */
 #define ADC_CFGR_JAWD1EN_BITOFFSET_POS     (24UL) 										/* Value equivalent to bitfield "ADC_CFGR_JAWD1EN" position in register */
 #define ADC_TR1_HT1_BITOFFSET_POS          (16UL) 										/* Value equivalent to bitfield "ADC_TR1_HT1" position in register */


#define LL_ADC_RESOLUTION_12B              (0x00000000UL)                      			/*!< ADC resolution 12 bits */
#define LL_ADC_RESOLUTION_10B              (                 ADC_CFGR_RES_0)   			/*!< ADC resolution 10 bits */
#define LL_ADC_RESOLUTION_8B               (ADC_CFGR_RES_1                 )   			/*!< ADC resolution  8 bits */
#define LL_ADC_RESOLUTION_6B               (ADC_CFGR_RES_1 | ADC_CFGR_RES_0)   			/*!< ADC resolution  6 bits */
 //======================================================================================
/* Private macro -------------------------------------------------------------*/
/**
  * @brief  Computation of temperature (unit: degree Celsius) from the internal
  *         temperature sensor measurement by ADC.
  *         Computation is using temperature sensor calibration values done
  *         in production.
  *         Computation formula:
  *         Temperature = (TS_ADC_DATA - TS_CAL1) * (110degC - 30degC)
  *                       / (TS_CAL2 - TS_CAL1) + 30degC
  *         with TS_ADC_DATA = temperature sensor raw data measured by ADC
  *              Avg_Slope = (TS_CAL2 - TS_CAL1) / (110 - 30)
  *              TS_CAL1 = TS_ADC_DATA @30degC (calibrated in factory)
  *              TS_CAL2 = TS_ADC_DATA @110degC (calibrated in factory)
  *         Calculation validity conditioned to settings:
  *          - ADC resolution 12 bits (need to scale conversion value
  *            if using a different resolution).
  *          - Power supply of analog voltage set to literal VDDA_APPLI
  *            (need to scale value if using a different value of analog
  *            voltage supply).
  * @param TS_ADC_DATA: Temperature sensor digital value measured by ADC
  * @retval None
  */
#define COMPUTATION_TEMPERATURE_TEMP30_TEMP110(TS_ADC_DATA)                    \
  (((( ((int32_t)((TS_ADC_DATA * VDDA_APPLI) / VDDA_TEMP_CAL)                  \
        - (int32_t) *TEMP30_CAL_ADDR)                                          \
     ) * (int32_t)(110 - 30)                                                   \
    ) / (int32_t)(*TEMP110_CAL_ADDR - *TEMP30_CAL_ADDR)                        \
   ) + 30                                                                      \
  )
 //======================================================================================
/**
  * @brief  Helper macro to calculate analog reference voltage (Vref+)
  *         (unit: mVolt) from ADC conversion data of internal voltage
  *         reference VrefInt.
  * @note   Computation is using VrefInt calibration value
  *         stored in system memory for each device during production.
  * @note   This voltage depends on user board environment: voltage level
  *         connected to pin Vref+.
  *         On devices with small package, the pin Vref+ is not present
  *         and internally bonded to pin Vdda.
  * @note   On this STM32 serie, calibration data of internal voltage reference
  *         VrefInt corresponds to a resolution of 12 bits,
  *         this is the recommended ADC resolution to convert voltage of
  *         internal voltage reference VrefInt.
  *         Otherwise, this macro performs the processing to scale
  *         ADC conversion data to 12 bits.
  * @param  __VREFINT_ADC_DATA__ ADC conversion data (resolution 12 bits)
  *         of internal voltage reference VrefInt (unit: digital value).
  * @param  __ADC_RESOLUTION__ This parameter can be one of the following values:
  *         @arg @ref LL_ADC_RESOLUTION_12B
  *         @arg @ref LL_ADC_RESOLUTION_10B
  *         @arg @ref LL_ADC_RESOLUTION_8B
  *         @arg @ref LL_ADC_RESOLUTION_6B
  * @retval Analog reference voltage (unit: mV)
  */
#define __LL_ADC_CALC_VREFANALOG_VOLTAGE(__VREFINT_ADC_DATA__,\
                                         __ADC_RESOLUTION__)                   \
  (((uint32_t)(*VREFINT_CAL_ADDR) * VREFINT_CAL_VREF)                          \
   / __LL_ADC_CONVERT_DATA_RESOLUTION((__VREFINT_ADC_DATA__),                  \
                                      (__ADC_RESOLUTION__),                    \
                                      LL_ADC_RESOLUTION_12B))
//======================================================================================
/**
  * @brief  Helper macro to calculate analog reference voltage (Vref+)
  *         (unit: mVolt) from ADC conversion data of internal voltage
  *         reference VrefInt.
  * @note   Computation is using VrefInt calibration value
  *         stored in system memory for each device during production.
  * @note   This voltage depends on user board environment: voltage level
  *         connected to pin Vref+.
  *         On devices with small package, the pin Vref+ is not present
  *         and internally bonded to pin Vdda.
  * @note   On this STM32 serie, calibration data of internal voltage reference
  *         VrefInt corresponds to a resolution of 12 bits,
  *         this is the recommended ADC resolution to convert voltage of
  *         internal voltage reference VrefInt.
  *         Otherwise, this macro performs the processing to scale
  *         ADC conversion data to 12 bits.
  * @param  __VREFINT_ADC_DATA__ ADC conversion data (resolution 12 bits)
  *         of internal voltage reference VrefInt (unit: digital value).
  * @param  __ADC_RESOLUTION__ This parameter can be one of the following values:
  *         @arg @ref ADC_RESOLUTION_12B
  *         @arg @ref ADC_RESOLUTION_10B
  *         @arg @ref ADC_RESOLUTION_8B
  *         @arg @ref ADC_RESOLUTION_6B
  * @retval Analog reference voltage (unit: mV)
  */
#define __HAL_ADC_CALC_VREFANALOG_VOLTAGE(__VREFINT_ADC_DATA__,\
                                          __ADC_RESOLUTION__)                  \
  __LL_ADC_CALC_VREFANALOG_VOLTAGE((__VREFINT_ADC_DATA__),                     \
                                  (__ADC_RESOLUTION__))
//======================================================================================
/**
  * @brief  Helper macro to convert the ADC conversion data from
  *         a resolution to another resolution.
  * @param  __DATA__ ADC conversion data to be converted
  * @param  __ADC_RESOLUTION_CURRENT__ Resolution of the data to be converted
  *         This parameter can be one of the following values:
  *         @arg @ref LL_ADC_RESOLUTION_12B
  *         @arg @ref LL_ADC_RESOLUTION_10B
  *         @arg @ref LL_ADC_RESOLUTION_8B
  *         @arg @ref LL_ADC_RESOLUTION_6B
  * @param  __ADC_RESOLUTION_TARGET__ Resolution of the data after conversion
  *         This parameter can be one of the following values:
  *         @arg @ref LL_ADC_RESOLUTION_12B
  *         @arg @ref LL_ADC_RESOLUTION_10B
  *         @arg @ref LL_ADC_RESOLUTION_8B
  *         @arg @ref LL_ADC_RESOLUTION_6B
  * @retval ADC conversion data to the requested resolution
  */
#define __LL_ADC_CONVERT_DATA_RESOLUTION(__DATA__,\
                                         __ADC_RESOLUTION_CURRENT__,\
                                         __ADC_RESOLUTION_TARGET__)            \
  (((__DATA__)                                                                 \
    << ((__ADC_RESOLUTION_CURRENT__) >> (ADC_CFGR_RES_BITOFFSET_POS - 1UL)))   \
   >> ((__ADC_RESOLUTION_TARGET__) >> (ADC_CFGR_RES_BITOFFSET_POS - 1UL))      \
  )
 //======================================================================================

 /**
   * @brief  Helper macro to calculate the voltage (unit: mVolt)
   *         corresponding to a ADC conversion data (unit: digital value).
   * @note   Analog reference voltage (Vref+) must be either known from
   *         user board environment or can be calculated using ADC measurement
   *         and ADC helper macro @ref __LL_ADC_CALC_VREFANALOG_VOLTAGE().
   * @param  __VREFANALOG_VOLTAGE__ Analog reference voltage (unit: mV)
   * @param  __ADC_DATA__ ADC conversion data (resolution 12 bits)
   *                       (unit: digital value).
   * @param  __ADC_RESOLUTION__ This parameter can be one of the following values:
   *         @arg @ref LL_ADC_RESOLUTION_12B
   *         @arg @ref LL_ADC_RESOLUTION_10B
   *         @arg @ref LL_ADC_RESOLUTION_8B
   *         @arg @ref LL_ADC_RESOLUTION_6B
   * @retval ADC conversion data equivalent voltage value (unit: mVolt)
   */
 #define __LL_ADC_CALC_DATA_TO_VOLTAGE(__VREFANALOG_VOLTAGE__,\
                                       __ADC_DATA__,\
                                       __ADC_RESOLUTION__)                      \
   ((__ADC_DATA__) * (__VREFANALOG_VOLTAGE__)                                   \
    / __LL_ADC_DIGITAL_SCALE(__ADC_RESOLUTION__)                                \
   )

 /* Legacy define */
 #define __LL_ADC_CALC_DATA_VOLTAGE()  __LL_ADC_CALC_DATA_TO_VOLTAGE()
//======================================================================================
 /**
   * @brief  Helper macro to define the ADC conversion data full-scale digital
   *         value corresponding to the selected ADC resolution.
   * @note   ADC conversion data full-scale corresponds to voltage range
   *         determined by analog voltage references Vref+ and Vref-
   *         (refer to reference manual).
   * @param  __ADC_RESOLUTION__ This parameter can be one of the following values:
   *         @arg @ref LL_ADC_RESOLUTION_12B
   *         @arg @ref LL_ADC_RESOLUTION_10B
   *         @arg @ref LL_ADC_RESOLUTION_8B
   *         @arg @ref LL_ADC_RESOLUTION_6B
   * @retval ADC conversion data full-scale digital value (unit: digital value of ADC conversion data)
   */
 #define __LL_ADC_DIGITAL_SCALE(__ADC_RESOLUTION__)                             \
   (0xFFFUL >> ((__ADC_RESOLUTION__) >> (ADC_CFGR_RES_BITOFFSET_POS - 1UL)))
//======================================================================================
 /**
   * @brief  Helper macro to calculate the temperature (unit: degree Celsius)
   *         from ADC conversion data of internal temperature sensor.
   * @note   Computation is using temperature sensor calibration values
   *         stored in system memory for each device during production.
   * @note   Calculation formula:
   *           Temperature = ((TS_ADC_DATA - TS_CAL1)
   *                           * (TS_CAL2_TEMP - TS_CAL1_TEMP))
   *                         / (TS_CAL2 - TS_CAL1) + TS_CAL1_TEMP
   *           with TS_ADC_DATA = temperature sensor raw data measured by ADC
   *                Avg_Slope = (TS_CAL2 - TS_CAL1)
   *                            / (TS_CAL2_TEMP - TS_CAL1_TEMP)
   *                TS_CAL1   = equivalent TS_ADC_DATA at temperature
   *                            TEMP_DEGC_CAL1 (calibrated in factory)
   *                TS_CAL2   = equivalent TS_ADC_DATA at temperature
   *                            TEMP_DEGC_CAL2 (calibrated in factory)
   *         Caution: Calculation relevancy under reserve that calibration
   *                  parameters are correct (address and data).
   *                  To calculate temperature using temperature sensor
   *                  datasheet typical values (generic values less, therefore
   *                  less accurate than calibrated values),
   *                  use helper macro @ref __LL_ADC_CALC_TEMPERATURE_TYP_PARAMS().
   * @note   As calculation input, the analog reference voltage (Vref+) must be
   *         defined as it impacts the ADC LSB equivalent voltage.
   * @note   Analog reference voltage (Vref+) must be either known from
   *         user board environment or can be calculated using ADC measurement
   *         and ADC helper macro @ref __LL_ADC_CALC_VREFANALOG_VOLTAGE().
   * @note   On this STM32 serie, calibration data of temperature sensor
   *         corresponds to a resolution of 12 bits,
   *         this is the recommended ADC resolution to convert voltage of
   *         temperature sensor.
   *         Otherwise, this macro performs the processing to scale
   *         ADC conversion data to 12 bits.
   * @param  __VREFANALOG_VOLTAGE__  Analog reference voltage (unit: mV)
   * @param  __TEMPSENSOR_ADC_DATA__ ADC conversion data of internal
   *                                 temperature sensor (unit: digital value).
   * @param  __ADC_RESOLUTION__      ADC resolution at which internal temperature
   *                                 sensor voltage has been measured.
   *         This parameter can be one of the following values:
   *         @arg @ref LL_ADC_RESOLUTION_12B
   *         @arg @ref LL_ADC_RESOLUTION_10B
   *         @arg @ref LL_ADC_RESOLUTION_8B
   *         @arg @ref LL_ADC_RESOLUTION_6B
   * @retval Temperature (unit: degree Celsius)
   */
 #define __LL_ADC_CALC_TEMPERATURE(__VREFANALOG_VOLTAGE__,\
                                   __TEMPSENSOR_ADC_DATA__,\
                                   __ADC_RESOLUTION__)                              \
   (((( ((int32_t)((__LL_ADC_CONVERT_DATA_RESOLUTION((__TEMPSENSOR_ADC_DATA__),     \
                                                     (__ADC_RESOLUTION__),          \
                                                     LL_ADC_RESOLUTION_12B)         \
                    * (__VREFANALOG_VOLTAGE__))                                     \
                   / TEMPSENSOR_CAL_VREFANALOG)                                     \
         - (int32_t) *TEMPSENSOR_CAL1_ADDR)                                         \
      ) * (int32_t)(TEMPSENSOR_CAL2_TEMP - TEMPSENSOR_CAL1_TEMP)                    \
     ) / (int32_t)((int32_t)*TEMPSENSOR_CAL2_ADDR - (int32_t)*TEMPSENSOR_CAL1_ADDR) \
    ) + TEMPSENSOR_CAL1_TEMP                                                        \
   )
//======================================================================================

#ifdef __cplusplus
}
#endif

 #endif /*__ adc_ext_H */
