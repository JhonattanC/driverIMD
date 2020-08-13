/**
 * @file    MMA8652_registers.h
 * @brief   I2C 12bit 3-axis Accelerometes register Configuration, retrieved and addapted from SpanStamp library
 * @author  Jhonattan Camargo
 * @version 1.0
 *
 * Copyright (c) 2019
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef __MMA8652_REGS_H__
#define __MMA8652_REGS_H__

#define MMA8652_I2C_ADDRESS     (0x1D<<1) //!<This is the factory pre-configured I2C address for an MMA8652

/**  MMA8652 Sensor Internal Registers
enum
{
  MMA8652_STATUS_00 = 0,          // 0x00
  MMA8652_OUT_X_MSB,              // 0x01
  MMA8652_OUT_X_LSB,              // 0x02
  MMA8652_OUT_Y_MSB,              // 0x03
  MMA8652_OUT_Y_LSB,              // 0x04
  MMA8652_OUT_Z_MSB,              // 0x05
  MMA8652_OUT_Z_LSB,              // 0x06
  MMA8652_RSVD_0,                 // 0x07
  MMA8652_RSVD_1,                 // 0x08
  MMA8652_F_SETUP,                // 0x09
  MMA8652_TRIG_CFG,               // 0x0A
  MMA8652_SYSMOD,                 // 0x0B
  MMA8652_INT_SOURCE,             // 0x0C
  MMA8652_WHO_AM_I,               // 0x0D
  MMA8652_XYZ_DATA_CFG,           // 0x0E
  MMA8652_HP_FILTER_CUTOFF,       // 0x0F
  MMA8652_PL_STATUS,              // 0x10
  MMA8652_PL_CFG,                 // 0x11
  MMA8652_PL_COUNT,               // 0x12
  MMA8652_PL_BF_ZCOMP,            // 0x13
  MMA8652_PL_P_L_THS_REG,         // 0x14
  MMA8652_FF_MT_CFG,              // 0x15
  MMA8652_FF_MT_SRC,              // 0x16
  MMA8652_FF_MT_THS,              // 0x17
  MMA8652_FF_MT_COUNT,            // 0x18
  MMA8652_RSVD_2,                 // 0x19
  MMA8652_RSVD_3,                 // 0x1A
  MMA8652_RSVD_4,                 // 0x1B
  MMA8652_RSVD_5,                 // 0x1C
  MMA8652_TRANSIENT_CFG,          // 0x1D
  MMA8652_TRANSIENT_SRC,          // 0x1E
  MMA8652_TRANSIENT_THS,          // 0x1F
  MMA8652_TRANSIENT_COUNT,        // 0x20
  MMA8652_PULSE_CFG,              // 0x21
  MMA8652_PULSE_SRC,              // 0x22
  MMA8652_PULSE_THSX,             // 0x23
  MMA8652_PULSE_THSY,             // 0x24
  MMA8652_PULSE_THSZ,             // 0x25
  MMA8652_PULSE_TMLT,             // 0x26
  MMA8652_PULSE_LTCY,             // 0x27
  MMA8652_PULSE_WIND,             // 0x28
  MMA8652_ASLP_COUNT,             // 0x29
  MMA8652_CTRL_REG1,              // 0x2A
  MMA8652_CTRL_REG2,              // 0x2B
  MMA8652_CTRL_REG3,              // 0x2C
  MMA8652_CTRL_REG4,              // 0x2D
  MMA8652_CTRL_REG5,              // 0x2E
  MMA8652_OFF_X,                  // 0x2F
  MMA8652_OFF_Y,                  // 0x30
  MMA8652_OFF_Z                   // 0x31
};  */

/**
 *  STATUS: Data Status register
 */
#define STATUS_00_REG         0x00
/// STATUS Register Masks
#define ZYXOW_MASK            0x80
#define ZOW_MASK              0x40
#define YOW_MASK              0x20
#define XOW_MASK              0x10
#define ZYXDR_MASK            0x08
#define ZDR_MASK              0x04
#define YDR_MASK              0x02
#define XDR_MASK              0x01

/**
 *  F_STATUS: FIFO Status Register
 */
#define F_STATUS_REG          0x00
//
#define F_OVF_MASK            0x80
#define F_WMRK_FLAG_MASK      0x40
#define F_CNT5_MASK           0x20
#define F_CNT4_MASK           0x10
#define F_CNT3_MASK           0x08
#define F_CNT2_MASK           0x04
#define F_CNT1_MASK           0x02
#define F_CNT0_MASK           0x01
#define F_CNT_MASK            0x3F

/*
 *  XYZ Data Registers
 */
#define OUT_X_MSB_REG         0x01
#define OUT_X_LSB_REG         0x02
#define OUT_Y_MSB_REG         0x03
#define OUT_Y_LSB_REG         0x04
#define OUT_Z_MSB_REG         0x05
#define OUT_Z_LSB_REG         0x06

/**
 *  F_SETUP: FIFO Setup Register
 */
#define F_SETUP_REG           0x09
//< F_SETUP Masks
#define F_MODE1_MASK          0x80
#define F_MODE0_MASK          0x40
#define F_WMRK5_MASK          0x20
#define F_WMRK4_MASK          0x10
#define F_WMRK3_MASK          0x08
#define F_WMRK2_MASK          0x04
#define F_WMRK1_MASK          0x02
#define F_WMRK0_MASK          0x01
#define F_MODE_MASK           0xC0
#define F_WMRK_MASK           0x3F
// F_SETUP Config Macros
#define F_MODE_DISABLED       0x00
#define F_MODE_CIRCULAR       (F_MODE0_MASK)
#define F_MODE_FILL           (F_MODE1_MASK)
#define F_MODE_TRIGGER        (F_MODE1_MASK+F_MODE0_MASK)

/*
 *  TRIG_CFG: FIFO Trigger Configuration Register
 */
#define TRIG_CFG_REG          0x0A
//< TRIG_CFG Masks
#define TRIG_TRANS_MASK       0x20
#define TRIG_LNDPRT_MASK      0x10
#define TRIG_PULSE_MASK       0x08
#define TRIG_FF_MT_MASK       0x04

/**
 *  SYSMOD: System Mode Register
 */
#define SYSMOD_REG            0x0B
//! SYSMOD Mask
#define FGERR_MASK            0x80
#define FGT_4_MASK            0x40
#define FGT_3_MASK            0x20
#define FGT_2_MASK            0x10
#define FGT_1_MASK            0x08
#define FGT_0_MASK            0x04
#define FGT_MASK              0x7C
#define SYSMOD1_MASK          0x02
#define SYSMOD0_MASK          0x01
#define SYSMOD_MASK           0x03
//< SYSMOD Configuration Macros
#define SYSMOD_STANDBY        0x00
#define SYSMOD_WAKE           (SYSMOD0_MASK)
#define SYSMOD_SLEEP          (SYSMOD1_MASK)

/**
 *  INT_SOURCE: System Interrupt Status Register
 */
#define INT_SOURCE_REG        0x0C
/// INT_SOURCE Masks
#define SRC_ASLP_MASK         0x80
#define SRC_FIFO_MASK         0x40    // MMA8652 only
#define SRC_TRANS_MASK        0x20
#define SRC_LNDPRT_MASK       0x10
#define SRC_PULSE_MASK        0x08
#define SRC_FF_MT_MASK        0x04
#define SRC_DRDY_MASK         0x01

/**
 *  XYZ_DATA_CFG: Sensor Data Configuration Register
 */
#define XYZ_DATA_CFG_REG      0x0E
//
#define HPF_OUT_MASK          0x10    // MMA8652 only
#define FS1_MASK              0x02
#define FS0_MASK              0x01
#define FS_MASK               0x03
//
#define FULL_SCALE_2G         0x00
#define FULL_SCALE_4G         (FS0_MASK)
#define FULL_SCALE_8G         (FS1_MASK)

/*
 *  HP_FILTER_CUTOFF High Pass Filter Register
 */
#define HP_FILTER_CUTOFF_REG  0x0F
//
#define PULSE_HPF_BYP_MASK    0x20
#define PULSE_LPF_EN_MASK     0x10
#define SEL1_MASK             0x02
#define SEL0_MASK             0x01
#define SEL_MASK              0x03

/**
 *  PL_STATUS Portrait/Landscape Status Register
 */
#define PL_STATUS_REG         0x10
//
#define NEWLP_MASK            0x80
#define LO_MASK               0x40
#define LAPO1_MASK            0x04
#define LAPO0_MASK            0x02
#define BAFRO_MASK            0x01
#define LAPO_MASK             0x06

/**
 *  PL_CFG Portrait/Landscape Configuration Register
 */
#define PL_CFG_REG            0x11
//
#define DBCNTM_MASK           0x80
#define PL_EN_MASK            0x40

/**
 *  PL_COUNT Portrait/Landscape Debounce Register
 */
#define PL_COUNT_REG          0x12

/**
 *  PL_BF_ZCOMP Back/Front and Z Compensation Register
 */
#define PL_BF_ZCOMP_REG       0x13
//
#define BKFR1_MASK            0x80
#define BKFR0_MASK            0x40
#define ZLOCK2_MASK           0x04
#define ZLOCK1_MASK           0x02
#define ZLOCK0_MASK           0x01
#define BKFR_MASK             0xC0
#define ZLOCK_MASK            0x07

/**
 *  PL_P_L_THS Portrait to Landscape Threshold Register
 */
#define PL_P_L_THS_REG        0x14
//
#define P_L_THS4_MASK         0x80
#define P_L_THS3_MASK         0x40
#define P_L_THS2_MASK         0x20
#define P_L_THS1_MASK         0x10
#define P_L_THS0_MASK         0x08
#define HYS2_MASK             0x04
#define HYS1_MASK             0x02
#define HYS0_MASK             0x01
#define P_L_THS_MASK          0xF8
#define HYS_MASK              0x07

/**
 *  FF_MT_CFG Freefall and Motion Configuration Register
 */
#define FF_MT_CFG_REG         0x15
//
#define ELE_MASK              0x80
#define OAE_MASK              0x40
#define ZEFE_MASK             0x20
#define YEFE_MASK             0x10
#define XEFE_MASK             0x08

/**
 *  FF_MT_SRC Freefall and Motion Source Registers
 */
#define FF_MT_SRC_REG         0x16
//
#define EA_MASK               0x80
#define ZHE_MASK              0x20
#define ZHP_MASK              0x10
#define YHE_MASK              0x08
#define YHP_MASK              0x04
#define XHE_MASK              0x02
#define XHP_MASK              0x01

/*
**  FF_MT_THS Freefall and Motion Threshold Registers
**  TRANSIENT_THS Transient Threshold Register
*/
#define FT_MT_THS_REG         0x17
#define TRANSIENT_THS_REG     0x1F
//
#define DBCNTM_MASK           0x80
#define THS6_MASK             0x40
#define THS5_MASK             0x20
#define THS4_MASK             0x10
#define THS3_MASK             0x08
#define THS2_MASK             0x04
#define TXS1_MASK             0x02
#define THS0_MASK             0x01
#define THS_MASK              0x7F

/**
 *  FF_MT_COUNT Freefall Motion Count Registers
 */
#define FF_MT_COUNT_REG       0x18

/**
 *  TRANSIENT_CFG Transient Configuration Register
 */
#define TRANSIENT_CFG_REG     0x1D
//
#define TELE_MASK             0x10
#define ZTEFE_MASK            0x08
#define YTEFE_MASK            0x04
#define XTEFE_MASK            0x02
#define HPF_BYP_MASK          0x01

/**
 *  TRANSIENT_SRC Transient Source Register
 */
#define TRANSIENT_SRC_REG     0x1E
//
#define TEA_MASK              0x40
#define ZTRANSE_MASK          0x20
#define Z_TRANS_POL_MASK      0x10
#define YTRANSE_MASK          0x08
#define Y_TRANS_POL_MASK      0x04
#define XTRANSE_MASK          0x02
#define X_TRANS_POL_MASK      0x01

/**
 *  TRANSIENT_COUNT Transient Debounce Register
 */
#define TRANSIENT_COUNT_REG   0x20

/*
 *  PULSE_CFG Pulse Configuration Register
 */
#define PULSE_CFG_REG         0x21
//
#define DPA_MASK              0x80
#define PELE_MASK             0x40
#define ZDPEFE_MASK           0x20
#define ZSPEFE_MASK           0x10
#define YDPEFE_MASK           0x08
#define YSPEFE_MASK           0x04
#define XDPEFE_MASK           0x02
#define XSPEFE_MASK           0x01

/**
 *  PULSE_SRC Pulse Source Register
 */
#define PULSE_SRC_REG         0x22
//
#define PEA_MASK              0x80
#define AXZ_MASK              0x40
#define AXY_MASK              0x20
#define AXX_MASK              0x10
#define DPE_MASK              0x08
#define POLZ_MASK             0x04
#define POLY_MASK             0x02
#define POLX_MASK             0x01

/**
 *  PULSE_THS XYZ Pulse Threshold Registers
 */
#define PULSE_THSX_REG        0x23
#define PULSE_THSY_REG        0x24
#define PULSE_THSZ_REG        0x25
//
#define PTHS_MASK             0x7F

/**
 *  PULSE_TMLT Pulse Time Window Register
 */
#define PULSE_TMLT_REG        0x26

/**
 *  PULSE_LTCY Pulse Latency Timer Register
 */
#define PULSE_LTCY_REG        0x27

/**
 *  PULSE_WIND Second Pulse Time Window Register
 */
#define PULSE_WIND_REG        0x28

/**
 *  ASLP_COUNT Auto Sleep Inactivity Timer Register
 */
#define ASLP_COUNT_REG        0x29

/**
 *  CTRL_REG1 System Control 1 Register
 */
#define CTRL_REG1             0x2A
//
#define ASLP_RATE1_MASK       0x80
#define ASLP_RATE0_MASK       0x40
#define DR2_MASK              0x20
#define DR1_MASK              0x10
#define DR0_MASK              0x08
#define LNOISE_MASK           0x04
#define FREAD_MASK            0x02
#define ACTIVE_MASK           0x01
#define ASLP_RATE_MASK        0xC0
#define DR_MASK               0x38
//
#define ASLP_RATE_20MS        0x00
#define ASLP_RATE_80MS        (ASLP_RATE0_MASK)
#define ASLP_RATE_160MS       (ASLP_RATE1_MASK)
#define ASLP_RATE_640MS       (ASLP_RATE1_MASK | ASLP_RATE0_MASK)
//
#define ASLP_RATE_50HZ        (ASLP_RATE_20MS)
#define ASLP_RATE_12_5HZ      (ASLP_RATE_80MS)
#define ASLP_RATE_6_25HZ      (ASLP_RATE_160MS)
#define ASLP_RATE_1_56HZ      (ASLP_RATE_640MS)
//
#define DATA_RATE_1250US      0x00
#define DATA_RATE_2500US      (DR0_MASK)
#define DATA_RATE_5MS         (DR1_MASK)
#define DATA_RATE_10MS        (DR1_MASK | DR0_MASK)
#define DATA_RATE_20MS        (DR2_MASK)
#define DATA_RATE_80MS        (DR2_MASK | DR0_MASK)
#define DATA_RATE_160MS       (DR2_MASK | DR1_MASK)
#define DATA_RATE_640MS       (DR2_MASK | DR1_MASK | DR0_MASK)
//
#define DATA_RATE_800HZ       (DATA_RATE_1250US)
#define DATA_RATE_400HZ       (DATA_RATE_2500US)
#define DATA_RATE_200HZ       (DATA_RATE_5MS)
#define DATA_RATE_100HZ       (DATA_RATE_10MS)
#define DATA_RATE_50HZ        (DATA_RATE_20MS)
#define DATA_RATE_12_5HZ      (DATA_RATE_80MS)
#define DATA_RATE_6_25HZ      (DATA_RATE_160MS)
#define DATA_RATE_1_56HZ      (DATA_RATE_640MS)
//
#define ACTIVE                (ACTIVE_MASK)
#define STANDBY               0x00

/**
 *  CTRL_REG2 System Control 2 Register
 */
#define CTRL_REG2             0x2B
//
#define ST_MASK               0x80
#define RST_MASK              0x40
#define SMODS1_MASK           0x10
#define SMODS0_MASK           0x08
#define SLPE_MASK             0x04
#define MODS1_MASK            0x02
#define MODS0_MASK            0x01
#define SMODS_MASK            0x18
#define MODS_MASK             0x03
//
#define SMOD_NORMAL           0x00
#define SMOD_LOW_NOISE        (SMODS0_MASK)
#define SMOD_HIGH_RES         (SMODS1_MASK)
#define SMOD_LOW_POWER        (SMODS1_MASK | SMODS0_MASK)
//
#define MOD_NORMAL            0x00
#define MOD_LOW_NOISE         (MODS0_MASK)
#define MOD_HIGH_RES          (MODS1_MASK)
#define MOD_LOW_POWER         (MODS1_MASK | MODS0_MASK)
/**
 *  CTRL_REG3 Interrupt Control Register
 */
#define CTRL_REG3             0x2C
//
#define FIFO_GATE_MASK        0x80    // MMA8652 only
#define WAKE_TRANS_MASK       0x40    // MMA8652 only
#define WAKE_LNDPRT_MASK      0x20
#define WAKE_PULSE_MASK       0x10    // MMA8652 only
#define WAKE_FF_MT_MASK       0x08
#define IPOL_MASK             0x02
#define PP_OD_MASK            0x01

/**
 *  CTRL_REG4 Interrupt Enable Register
 */
#define CTRL_REG4             0x2D
//
#define INT_EN_ASLP_MASK      0x80
#define INT_EN_FIFO_MASK      0x40    // MMA8652 only
#define INT_EN_TRANS_MASK     0x20    // MMA8652 only
#define INT_EN_LNDPRT_MASK    0x10
#define INT_EN_PULSE_MASK     0x08    // MMA8652 only
#define INT_EN_FF_MT_MASK     0x04
#define INT_EN_DRDY_MASK      0x01

/**
 *  CTRL_REG5 Interrupt Configuration Register
 */
#define CTRL_REG5             0x2E
//
#define INT_CFG_ASLP_MASK     0x80
#define INT_CFG_FIFO_MASK     0x40     // MMA8652 only
#define INT_CFG_TRANS_MASK    0x20     // MMA8652 only
#define INT_CFG_LNDPRT_MASK   0x10
#define INT_CFG_PULSE_MASK    0x08     // MMA8652 only
#define INT_CFG_FF_MT_MASK    0x04
#define INT_CFG_DRDY_MASK     0x01

/*
**  XYZ Offset Correction Registers
*/
#define OFF_X_REG             0x2F
#define OFF_Y_REG             0x30
#define OFF_Z_REG             0x31

#endif
