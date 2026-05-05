/*
 * emu_tc_programming.cpp
 *
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

#define OBT_START_FT_ST04 (OBT_AFTER_POWER_ON + 0)

// #define FT_SOLO_EPD_ICU_SERV_4_TC_0110


#ifdef FT_SOLO_EPD_ICU_SERV_4_TC_0110


#define FT_SOLO_EPD_ICU_SERV_4_0110_TIME_step0 (OBT_START_FT_ST04 + 1)
#define FT_SOLO_EPD_ICU_SERV_4_0110_TIME_step1 (OBT_START_FT_ST04 + 1)

#define FT_SOLO_EPD_ICU_SERV_4_0110_TIME_step2 (OBT_START_FT_ST04 + 30)

#define FT_SOLO_EPD_ICU_SERV_4_0110_TIME_step3 (OBT_START_FT_ST04 + 32)

#define FT_SOLO_EPD_ICU_SERV_4_0110_TIME_step4 (OBT_START_FT_ST04 + 60)


EmuGSS_TCProgram4_6 prog_FT_0110_step_0(FT_SOLO_EPD_ICU_SERV_4_0110_TIME_step0,
		"FT_SOLO_EPD_ICU_SERV_4_0110 step 0, Define Stats PID 1",1);

EmuGSS_TCProgram4_6 prog_FT_0110_step_1(FT_SOLO_EPD_ICU_SERV_4_0110_TIME_step1,
		"FT_SOLO_EPD_ICU_SERV_4_0110 step 1, Define Stats PID 3",3);

EmuGSS_TCProgram4_1 prog_FT_0110_step_2(FT_SOLO_EPD_ICU_SERV_4_0110_TIME_step2,
		"FT_SOLO_EPD_ICU_SERV_4_0110 step 2, Tx Stats");


//TODO 08 Delete PID 3 Stats as step 3

EmuGSS_TCProgram4_6 prog_FT_0110_step_3(FT_SOLO_EPD_ICU_SERV_4_0110_TIME_step3,
		"FT_SOLO_EPD_ICU_SERV_4_0110 step 3, Delete Stats PID 3", 3);

//TODO 09 Request Stats as step 4
EmuGSS_TCProgram4_1 prog_FT_0110_step_4(FT_SOLO_EPD_ICU_SERV_4_0110_TIME_step4,
		"FT_SOLO_EPD_ICU_SERV_4_0110 step 4, Tx Stats");


#endif




