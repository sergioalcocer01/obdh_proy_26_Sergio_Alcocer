/*
 * cdtchandler.cpp
 *
 *  Created on: Dec 29, 2023
 *      Author: opolo70
 */

#include <public/pus_services_iface_v1.h>
#include "public/cdtchandler.h"
#include "public/serialize.h"
#include "public/crc.h"
#include "public/sc_channel_drv_v1.h"

#include "public/cdtcexecctrl_iface_v1.h"

CDTCHandler::CDTCHandler() {

	mTCHandler.raw_tc_mem_descriptor.p_tc_bytes = NULL;
	mTCHandler.raw_tc_mem_descriptor.tc_num_bytes = 0;

}

void CDTCHandler::BuildFromDescriptor(CDTCMemDescriptor &descriptor) {

	tc_handler_build_from_descriptor(&mTCHandler, descriptor.mTCMemDescriptor);

}

CDTCAcceptReport CDTCHandler::DoAcceptation() {

	CDTCAcceptReport acceptReport;
	acceptReport.mAcceptReport = pus_service1_tc_acceptation(&mTCHandler);

	return acceptReport;
}

void CDTCHandler::MngTCRejection(CDTCAcceptReport &acceptReport) {

	pus_service1_tx_TM_1_2(&mTCHandler, acceptReport.mAcceptReport);

	tc_handler_free_memory(&mTCHandler);
}

//Complete TC Aceptation
void CDTCHandler::MngTCAcceptation() {

	pus_service1_tx_TM_1_1(&mTCHandler);

}

CDTCExecCtrl CDTCHandler::GetExecCtrl() {

	//Get TC type
	uint8_t type = mTCHandler.tc_df_header.type;

	CDTCExecCtrl execCtrl;
	switch (type) {

	//TODO 05 Set ST[17,X] as prioTC
	case (17):
		execCtrl.mExecCtrl = ExecCtrlPrioTC;
		break;

	// Set ST[03,X] as HK_TC
	case (3):
		execCtrl.mExecCtrl = ExecCtrlHK_FDIRTC;
		break;
	// Set ST[20,X] as BKGTC
	case (20):
		execCtrl.mExecCtrl = ExecCtrlBKGTC;
		break;

	default:

		execCtrl.mExecCtrl = ExecCtrlPrioTC;
		break;

	}

	return execCtrl;
}

void CDTCHandler::ExecPrioTC() {

	error_code_t error;
	error = tc_handler_start_up_execution(&mTCHandler);

	if (!error) {

		//Get TC type
		uint8_t type = mTCHandler.tc_df_header.type;

		switch (type) {

		//TODO 07 call pus_service17_exec_tc(&mTCHandler);

		case (17):
			pus_service17_exec_tc(&mTCHandler);
			break;

		default:
			//No defined code for this TC. Design error
			pus_service1_tx_TM_1_4_TC_X_Y_NO_EXEC_CODE(&mTCHandler);
			break;

		}

		tc_handler_free_memory(&mTCHandler);
	}

}

void CDTCHandler::ExecHK_FDIRTC() {

	error_code_t error;
	error = tc_handler_start_up_execution(&mTCHandler);

	if (!error) {

		//Get TC type
		uint8_t type = mTCHandler.tc_df_header.type;

		switch (type) {

		// call pus_service3_exec_tc(&mTCHandler);

		case (3):
			pus_service3_exec_tc(&mTCHandler);
			break;

		default:
			//No defined code for this TC. Design error
			pus_service1_tx_TM_1_4_TC_X_Y_NO_EXEC_CODE(&mTCHandler);
			break;

		}

		tc_handler_free_memory(&mTCHandler);
	}

}


void CDTCHandler::ExecBKGTC() {

	error_code_t error;
	error = tc_handler_start_up_execution(&mTCHandler);

	if (!error) {

		//Get TC type
		uint8_t type = mTCHandler.tc_df_header.type;

		switch (type) {

		// call pus_service20_exec_tc(&mTCHandler);

		case (20):
			pus_service20_exec_tc(&mTCHandler);
			break;

		default:
			//No defined code for this TC. Design error
			pus_service1_tx_TM_1_4_TC_X_Y_NO_EXEC_CODE(&mTCHandler);
			break;

		}

		tc_handler_free_memory(&mTCHandler);
	}

}

void CDTCHandler::ExecRebootTC() {

	error_code_t error;
	error = tc_handler_start_up_execution(&mTCHandler);

	if (!error) {

		//Get TC type
		uint8_t type = mTCHandler.tc_df_header.type;

		switch (type) {



		default:
			//No defined code for this TC. ASW design error
			pus_service1_tx_TM_1_4_TC_X_Y_NO_EXEC_CODE(&mTCHandler);
			break;

		}

		tc_handler_free_memory(&mTCHandler);
	}

}

