#ifndef FCDTCHandlerH
#define FCDTCHandlerH

#include "public/config.h"
#include "public/basic_types.h"
#include "public/ccsds_pus.h"
#include "public/tmtc_dyn_mem.h"
#include "public/pus_tc_handler.h"
#include "public/pus_service01.h"

#include "public/cdtcmemdescriptor_iface_v1.h"
#include "public/cdtcacceptreport_iface_v1.h"
#include "public/cdtcexecctrl_iface_v1.h"


class CDTCHandler {

	friend class CDEvAction;


protected:

	tc_handler_t mTCHandler;

public:

	//!Constructor
	CDTCHandler();

	//!Build From Descriptor
	void BuildFromDescriptor(CDTCMemDescriptor &descriptor);

	//!Do TC Acceptation
	CDTCAcceptReport DoAcceptation();

	//!Mng TC Rejection
	void MngTCRejection(CDTCAcceptReport & acceptReport);

	//!Mng TC Accetation
	void MngTCAcceptation();

	//!Set Execution Control 
	CDTCExecCtrl GetExecCtrl();

	//!Exec the prio telecommands
	void ExecPrioTC();

	//!Exec the reboot telecommands
	void ExecRebootTC();

	//!Exec the reboot telecommands
	void ExecHK_FDIRTC();

	//!Exec the reboot telecommands
	void ExecBKGTC();

	//!Exec the reboot telecommands
	void ExecDroneTC();

	//!Mng TC Rejection during flight
	void MngTCRejectionInFlight(CDTCAcceptReport & acceptReport){
		acceptReport.mAcceptReport.accept_status=TCAcceptationTypeError; //Error de tipo
		pus_service1_tx_TM_1_2(&mTCHandler, acceptReport.mAcceptReport);
		tc_handler_free_memory(&mTCHandler);
	}

};

#endif
