/*
 * pus_services.c
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


#include "public/config.h"
#include "public/basic_types.h"
#include "public/serialize.h"
#include "public/sc_channel_drv_v1.h"
#include "public/adc_drv.h"
#include "public/watchdog_drv.h"
#include "public/pus_service12.h"


void pus_services_startup(void * irq_interface) {



	SC_Channel_Init(irq_interface);
	

	init_adc_channel();

	pus_service1_tx_TM_5_1_start_up();
	
	pus_service12_startup();
}

void pus_services_mng_reboot(){


	watchdog_drv_disable_signal();
}

void pus_services_do_FDIR() {

    uint16_t number_of_PMONs;
    number_of_PMONs = pus_service12_get_PMON_COUNT();

    for (uint16_t i = 0; i < number_of_PMONs; i++) {

        if (pus_service12_is_PMON_enabled(i)) {

            monitor_type_t type = pus_service12_get_PMON_type(i);
            bool_t event_triggered = false;
            uint16_t EvID;

            switch (type) {
                case (MonitorCheckTypeLimits): {
                    param_out_of_limits_info_t fault_info;
                    // Chequeamos límites
                    event_triggered = pus_service12_do_param_limits_monitoring(i, &EvID, &fault_info);

                    // Miramos si ha saltado
                    if (event_triggered) {
                        // // Miramos si está habilitado
                        if (pus_service5_is_EvID_enabled(EvID)) {
                        	// Informamos por ST[05]
                            pus_service1_tx_TM_5_X_param_out_of_limit(EvID, &fault_info);

                            // Ejecutamos la acción automática de la ST[19]
                            pus_service19_mng_event_action(EvID);
                        }
                    }
                }
                break;

                case (MonitorCheckTypeExpectedValue): {
                    param_value_fault_info_t fault_info;
                    // Chequeamos valor esperado
                    event_triggered = pus_service12_do_param_check_value_monitoring(i, &EvID, &fault_info);

                    // Miramos si ha saltado
                    if (event_triggered) {
                    	// Miramos si está habilitado
                        if (pus_service5_is_EvID_enabled(EvID)) {
                        	// Informamos por ST[05]
                            pus_service1_tx_TM_5_X_param_check_value_fail(EvID, &fault_info);

                            // Ejecutamos la acción automática de la ST[19]
                            pus_service19_mng_event_action(EvID);
                        }
                    }
                }
                break;

                default:
                    break;
            }
        }
    }
}

void pus_services_update_params(){

	//Do asw_update_sys_data_pool
	sample_sys_data_pool_params();

}

