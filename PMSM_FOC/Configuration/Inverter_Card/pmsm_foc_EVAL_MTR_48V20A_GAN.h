/**
 * @pmsm_foc_EVAL_MTR_48V20A_GAN.h
 * @Firmware PMSM_FOC_SL_XMC13_XMC14_V1_5
 * @Modified date: 2019-01-10
 * F1 port: copied from pmsm_foc_KIT_MOTOR_DC_250W_24V.h for EVAL_MTR_48V20A_GAN (board V2.4, UG154954).
 *          Only the values tagged "F1 port" differ from the template.
 * @cond
 ****************************************
 * PMSM FOC Motor Control Library
 *
 * Copyright (c) 2015-2025, Infineon Technologies AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,are permitted provided that the
 * following conditions are met:
 *
 *   Redistributions of source code must retain the above copyright notice, this list of conditions and the  following
 *   disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
 *   following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 *   Neither the name of the copyright holders nor the names of its contributors may be used to endorse or promote
 *   products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT  OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * To improve the quality of the software, users are encouraged to share modifications, enhancements or bug fixes
 * with Infineon Technologies AG (dave@infineon.com).
 ******************************************
 * @endcond
 */

/* F1 port: new include guard (template uses PMSM_FOC_CONFIGURATION_PMSM_FOC_INVERTERCARD_PARAMETERS_H_) */
#ifndef PMSM_FOC_CONFIGURATION_PMSM_FOC_EVAL_MTR_48V20A_GAN_H_
#define PMSM_FOC_CONFIGURATION_PMSM_FOC_EVAL_MTR_48V20A_GAN_H_

#include "../pmsm_foc_user_config.h"



#if(INVERTERCARD_TYPE == EVAL_MTR_48V20A_GAN)
/* ********************************************* EVAL_MTR_48V20A_GAN *************************/
#define INTERNAL_OP_GAIN                            DISABLED               /*1. ENABLED       2. DISABLED (Please configure OP-Gain manually) */
#define USER_VDC_LINK_V                             (15.0f)                 /* F1 port: was 24.0f. Bench value; raise with Vin. Hardware Inverter VDC link voltage in V  */
#define USER_CCU8_PWM_FREQ_HZ                       (20000U)              /* CCU8 PWM Switching Frequency in Hz*/
#define USER_DEAD_TIME_US                           (0.1f)                 /* F1 port: was 0.75f. 0.1 us -> (uint32_t)(0.1*120 - 0.5) = 11 counts = 91.7 ns at 120 MHz.
                                                                              UG154954 recommended initial value is 50 ns (0.05f -> 5 counts = 41.7 ns). Never 0. */

#define USER_BOOTSTRAP_PRECHARGE_TIME_MS             (20U)                 /* Initial Bootstrap precharging time in ms */
#define USER_DC_LINK_DIVIDER_RATIO                  (0.0526f)              /* F1 port: was 5.6/(5.6+56). EVAL Vin sense 52.6 mV/V (UG154954), connector-referred. */

/*      --------------------------------------------------- Motor Phase Current Measurement ---------------------------------------- */
#define USER_R_SHUNT_OHM                            (0.024f)               /* F1 port: was 0.01f. TLI4971 sensitivity 24 mV/A expressed as an equivalent
                                                                              shunt (V/A); offset 1.65 V is measured at run time as ADC bias. */
#define USER_DC_SHUNT_OHM                           (0.01f)               /* DC link shunt current resistor in ohm */

#define USER_MAX_ADC_VDD_V                          (5.0f)                 /* F1 port: connector-referred ADC full scale. 5.0f assumes the drive card's
                                                                              0.662 level shifter on the analog inputs (3.3 V / 0.662 = 5.0 V).
                                                                              Set 3.3f if Phase 5.3 shows no level shifter (Vdc_link reads ~22.7 V at 15 V in). */

#if(INTERNAL_OP_GAIN == ENABLED)
#define OP_GAIN_FACTOR                              (3U)                       /* Different HW Board has different OP Gain factor, XMC14 built-in Gain Factor available 1, 3, 6 and 12 only*/
#define USER_RIN_OFFSET_KOHM                        (2.0f)                      /* this reistence is on Control Card to generate ADC input offset */
#define USER_RIN_PULL_UP_KOHM                       (10.0f)                     /* this reistence is on Control Card to generate ADC input offset */
#define CIRCUIT_GAIN_FACTOR                         (OP_GAIN_FACTOR * (USER_RIN_PULL_UP_KOHM / (USER_RIN_OFFSET_KOHM + USER_RIN_PULL_UP_KOHM)))
#elif(INTERNAL_OP_GAIN == DISABLED)
#define USER_RIN_PHASECURRENT_KOHM                  (1.0f)                 /* R_IN (of equivalent amplifier) kohm */
#define USER_R_PHASECURRENT_FEEDBACK_KOHM           (1.0f)                 /* F1 port: was 12.0f. TLI4971 output goes straight to the connector: gain 1. */
#define USER_RIN_DCCURRENT_KOHM                     (1.0f)                  /* Rf for dc current sensing */
#define USER_R_DCCURRENT_FEEDBACK_KOHM              (12.0f)                   /* Rin for dc current sensing */
#define G_OPAMP_PER_PHASECURRENT                    (USER_R_PHASECURRENT_FEEDBACK_KOHM / USER_RIN_PHASECURRENT_KOHM)
#define CIRCUIT_GAIN_FACTOR                              G_OPAMP_PER_PHASECURRENT
#endif

#define I_MAX_A                                    ((VAREF_V/(USER_R_SHUNT_OHM * CIRCUIT_GAIN_FACTOR))/ 2U)   /* F1 port note: = 5.0/(0.024*1)/2 = 104 A
                                                                                                               normalisation, not a usable range */

#define GATE_DRIVER_INPUT_LOGIC                    PASSIVE_LOW                   /*1. PASSIVE_HIGH       2. PASSIVE_LOW (Please refer the gate driver datasheet) */
#if(GATE_DRIVER_INPUT_LOGIC == PASSIVE_HIGH)
#define MOTOR_COASTING_HIGH_SIDE                    XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_HIGH
#define MOTOR_COASTING_LOW_SIDE                     XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_LOW

#define MOTOR_RUN_HIGH_SIDE                         XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_HIGH
#define MOTOR_RUN_LOW_SIDE                          XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_HIGH
#elif(GATE_DRIVER_INPUT_LOGIC == PASSIVE_LOW)
#define MOTOR_COASTING_HIGH_SIDE                    XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_LOW
#define MOTOR_COASTING_LOW_SIDE                     XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_HIGH

#define MOTOR_RUN_HIGH_SIDE                         XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_LOW
#define MOTOR_RUN_LOW_SIDE                          XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_LOW
#endif


#define CCU8_INPUT_TRAP_LEVEL  XMC_CCU8_SLICE_EVENT_LEVEL_SENSITIVITY_ACTIVE_LOW    /* EVAL OCD (41 A) is active low on CTRAP */



#define INVERTER_ENABLE_PIN    (1U)             /* F1 port: was 0U. EVAL EN is active high (UG154954). 1 = Active High, 0 Active Low*/

#if(INVERTER_ENABLE_PIN == 0U)
  #define ENABLE_LEVEL XMC_GPIO_OUTPUT_LEVEL_LOW
  #define DISABLE_LEVEL XMC_GPIO_OUTPUT_LEVEL_HIGH
#elif(INVERTER_ENABLE_PIN == 1U)
  #define ENABLE_LEVEL XMC_GPIO_OUTPUT_LEVEL_HIGH
  #define DISABLE_LEVEL XMC_GPIO_OUTPUT_LEVEL_LOW
#endif

#endif

#endif /* PMSM_FOC_CONFIGURATION_PMSM_FOC_EVAL_MTR_48V20A_GAN_H_ */
