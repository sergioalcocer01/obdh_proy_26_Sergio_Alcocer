/*
 * emu_tc_programming.cpp
 *
 *  Created on: Oct 26, 2024
 *      Author: Oscar Rodriguez Polo
 */

/****************************************************************************
 *
 *   This program is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU General Public License
 *   as published by the Free Software Foundation; either version 2
 *   of the License, or (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307,USA.
 *
 *
 ****************************************************************************/

#include <public/emu_hw_timecode_drv_v1.h>
#include <public/emu_sc_channel_drv_v1.h>
#include <public/emu_gss_v1.h>

#define OBT_START_FT_ST05_12 (OBT_AFTER_POWER_ON )

//#define FT_UAH_ASW_ICU_SERVS_5_12_Limits_Monitoring_0080

//#define FT_UAH_ASW_ICU_SERVS_5_12_EvDisabled_0090
//#define FT_UAH_ASW_ICU_SERVS_5_12_MonMaskedValue_0100



//TODO Complete FT_UAH_ASW_ICU_SERVS_5_12_Limits_Monitoring_0080 and check log with expected log
#ifdef FT_UAH_ASW_ICU_SERVS_5_12_Limits_Monitoring_0080


#define FT_0080_TIME_step0 (OBT_START_FT_ST05_12 + 3)
#define FT_0080_TIME_step1 (OBT_START_FT_ST05_12 + 5)
#define FT_0080_TIME_step2 (OBT_START_FT_ST05_12 + 7)
#define FT_0080_TIME_step3 (OBT_START_FT_ST05_12 + 18)
#define FT_0080_TIME_step4 (OBT_START_FT_ST05_12 + 40)
#define FT_0080_TIME_step5 (OBT_START_FT_ST05_12 + 60)


EmuGSS_TCProgram20_3_uint8 prog_FT_0080_step_0(FT_0080_TIME_step0,
		"FT_UAH_ASW_ICU_SERVS_5_12_Limits_Monitoring_0080 step 0, Set PID 15 to 10 (within limits)", 15, 10);

EmuGSS_TCProgram12_5_Limit_UINT8 prog_FT_0080_step_1(FT_0080_TIME_step1,
		"FT_UAH_ASW_ICU_SERVS_5_12_Limits_Monitoring_0080 step 1, Config PMODID 0 for monitoring PID 15 with limits [1,20]",
		0, 15, 1, 2, 1, 0x4001, 20, 0x4002);

// Habilitamos eventos en el Servicio 5 en el mismo tiempo que la configuración (step 1)
EmuGSS_TCProgram5_5 prog_FT_0080_en_ev_4001(FT_0080_TIME_step1,
		"Enable Event Report for EvID 0x4001 (Low Limit)", 0x4001);

EmuGSS_TCProgram5_5 prog_FT_0080_en_ev_4002(FT_0080_TIME_step1,
		"Enable Event Report for EvID 0x4002 (High Limit)", 0x4002);

EmuGSS_TCProgram12_1 prog_FT_0080_step_2(FT_0080_TIME_step2,
		"FT_UAH_ASW_ICU_SERVS_5_12_Limits_Monitoring_0080 step 2, Enable Monitoring PMODID 0", 0);

EmuGSS_TCProgram20_3_uint8 prog_FT_0080_step_3(FT_0080_TIME_step3,
		"FT_UAH_ASW_ICU_SERVS_5_12_Limits_Monitoring_0080 step 3, Update PID 15 to 99", 15, 99);

EmuGSS_TCProgram20_3_uint8 prog_FT_0080_step_4(FT_0080_TIME_step4,
		"FT_UAH_ASW_ICU_SERVS_5_12_Limits_Monitoring_0080 step 4, Update PID 15 to 5", 15, 5);

EmuGSS_TCProgram20_3_uint8 prog_FT_0080_step_5(FT_0080_TIME_step5,
		"FT_UAH_ASW_ICU_SERVS_5_12_Limits_Monitoring_0080 step 5, Update PID 15 to 0", 15, 0);

#endif

//TODO  CREATE TEST FT_UAH_ASW_ICU_SERVS_5_12_EvDisabled_0090
//Same steps than FT_UAH_ASW_ICU_SERVS_5_12_Limits_Monitoring_0080 but use
//EmuGSS_TCProgram5_6 to disable event 0x4002 at OBT_START_FT_ST05_12 + 12

#ifdef FT_UAH_ASW_ICU_SERVS_5_12_EvDisabled_0090

#define FT_0090_TIME_step0 (OBT_START_FT_ST05_12 + 3)
#define FT_0090_TIME_step1 (OBT_START_FT_ST05_12 + 5)
#define FT_0090_TIME_step2 (OBT_START_FT_ST05_12 + 7)
#define FT_0090_TIME_step3 (OBT_START_FT_ST05_12 + 12)
#define FT_0090_TIME_step4 (OBT_START_FT_ST05_12 + 18)
#define FT_0090_TIME_step5 (OBT_START_FT_ST05_12 + 40)
#define FT_0090_TIME_step6 (OBT_START_FT_ST05_12 + 60)


#endif

//TODO  CREATE TEST FT_UAH_ASW_ICU_SERVS_5_12_MonMaskedValue_0100

/* Use EmuGSS_TCProgram12_5_Value_UINT8 class to monitor Param 16
 * with a mask = 0x0F and expected value 0x03.
 *  EvID shal be 0x4003. Use the PMONID =1
 * 	EmuGSS_TCProgram12_5_Value_UINT8(uint32_t uniTime2YK
 * 			, const char *brief, uint16_t pmonid,
 *           uint16_t pid, uint8_t interval, uint8_t repetition,
 *           uint8_t mask,
 *           uint8_t expectedValue,
 *           uint16_t unexpectedValEvID);
 *
 */
//Use EmuGSS_TCProgram20_3_uint8 to set PID=16 value to 0x03
//before enable monitoring, and change it to 0x02 after monitoring to obtain
//0x4003 event. After that restore PID to 0x03 and check TM[12,2] transition

#ifdef FT_UAH_ASW_ICU_SERVS_5_12_MonMaskedValue_0100


#endif

