
#include <stdlib.h>
#include <string.h>
#include "sc_types.h"
#include "TemperatureFlapCtrl.h"
/*! \file Implementation of the state machine 'TemperatureFlapCtrl'
*/

// prototypes of all internal functions

static void temperatureFlapCtrl_enact_SequenceImpl(TemperatureFlapCtrl* handle);
static void temperatureFlapCtrl_exact_SequenceImpl(TemperatureFlapCtrl* handle);
static void temperatureFlapCtrl_react_main_region_Set_Temp_Flap(TemperatureFlapCtrl* handle);
static void temperatureFlapCtrl_clearInEvents(TemperatureFlapCtrl* handle);
static void temperatureFlapCtrl_clearOutEvents(TemperatureFlapCtrl* handle);


void temperatureFlapCtrl_init(TemperatureFlapCtrl* handle)
{
	int i;

	for (i = 0; i < TEMPERATUREFLAPCTRL_MAX_ORTHOGONAL_STATES; ++i)
		handle->stateConfVector[i] = TemperatureFlapCtrl_last_state;
	
	
	handle->stateConfVectorPosition = 0;

	temperatureFlapCtrl_clearInEvents(handle);
	temperatureFlapCtrl_clearOutEvents(handle);

	/* Default init sequence for statechart TemperatureFlapCtrl */
	handle->iface.interiorTemp = 0;
	handle->iface.setTemp = 0;
	handle->iface.tempFlapSet = 0;
	handle->internal.counter = 0;
	handle->internal.max = 1000;
	handle->internal.min = 0;

}

void temperatureFlapCtrl_enter(TemperatureFlapCtrl* handle)
{
	/* Default enter sequence for statechart TemperatureFlapCtrl */
	temperatureFlapCtrl_enact_SequenceImpl(handle);
	/* 'default' enter sequence for region main region */
	/* Default react sequence for initial entry  */
	/* 'default' enter sequence for state Set Temp Flap */
	/* Entry action for state 'Set Temp Flap'. */
	handle->iface.tempFlapSet = handle->internal.counter * 100 / handle->internal.max;
	handle->stateConfVector[0] = TemperatureFlapCtrl_main_region_Set_Temp_Flap;
	handle->stateConfVectorPosition = 0;
}

void temperatureFlapCtrl_exit(TemperatureFlapCtrl* handle)
{
	/* Default exit sequence for statechart TemperatureFlapCtrl */
	/* Default exit sequence for region main region */
	/* Handle exit of all possible states (of main region) at position 0... */
	switch(handle->stateConfVector[ 0 ]) {
		case TemperatureFlapCtrl_main_region_Set_Temp_Flap : {
			/* Default exit sequence for state Set Temp Flap */
			handle->stateConfVector[0] = TemperatureFlapCtrl_last_state;
			handle->stateConfVectorPosition = 0;
			break;
		}
		default: break;
	}
	temperatureFlapCtrl_exact_SequenceImpl(handle);
}

static void temperatureFlapCtrl_clearInEvents(TemperatureFlapCtrl* handle) {
}

static void temperatureFlapCtrl_clearOutEvents(TemperatureFlapCtrl* handle) {
}

void temperatureFlapCtrl_runCycle(TemperatureFlapCtrl* handle) {
	
	temperatureFlapCtrl_clearOutEvents(handle);
	
	for (handle->stateConfVectorPosition = 0;
		handle->stateConfVectorPosition < TEMPERATUREFLAPCTRL_MAX_ORTHOGONAL_STATES;
		handle->stateConfVectorPosition++) {
			
		switch (handle->stateConfVector[handle->stateConfVectorPosition]) {
		case TemperatureFlapCtrl_main_region_Set_Temp_Flap : {
			temperatureFlapCtrl_react_main_region_Set_Temp_Flap(handle);
			break;
		}
		default:
			break;
		}
	}
	
	temperatureFlapCtrl_clearInEvents(handle);
}


sc_boolean temperatureFlapCtrl_isActive(TemperatureFlapCtrl* handle, TemperatureFlapCtrlStates state) {
	switch (state) {
		case TemperatureFlapCtrl_main_region_Set_Temp_Flap : 
			return (sc_boolean) (handle->stateConfVector[0] == TemperatureFlapCtrl_main_region_Set_Temp_Flap
			);
		default: return bool_false;
	}
}



sc_integer temperatureFlapCtrlIface_get_interiorTemp(TemperatureFlapCtrl* handle) {
	return handle->iface.interiorTemp;
}
void temperatureFlapCtrlIface_set_interiorTemp(TemperatureFlapCtrl* handle, sc_integer value) {
	handle->iface.interiorTemp = value;
}
sc_integer temperatureFlapCtrlIface_get_setTemp(TemperatureFlapCtrl* handle) {
	return handle->iface.setTemp;
}
void temperatureFlapCtrlIface_set_setTemp(TemperatureFlapCtrl* handle, sc_integer value) {
	handle->iface.setTemp = value;
}
sc_integer temperatureFlapCtrlIface_get_tempFlapSet(TemperatureFlapCtrl* handle) {
	return handle->iface.tempFlapSet;
}
void temperatureFlapCtrlIface_set_tempFlapSet(TemperatureFlapCtrl* handle, sc_integer value) {
	handle->iface.tempFlapSet = value;
}

// implementations of all internal functions

/* Entry action for statechart 'TemperatureFlapCtrl'. */
static void temperatureFlapCtrl_enact_SequenceImpl(TemperatureFlapCtrl* handle) {
}

/* Exit action for state 'TemperatureFlapCtrl'. */
static void temperatureFlapCtrl_exact_SequenceImpl(TemperatureFlapCtrl* handle) {
}

/* The reactions of state Set Temp Flap. */
static void temperatureFlapCtrl_react_main_region_Set_Temp_Flap(TemperatureFlapCtrl* handle) {
	/* The reactions of state Set Temp Flap. */
	/* Default exit sequence for state Set Temp Flap */
	handle->stateConfVector[0] = TemperatureFlapCtrl_last_state;
	handle->stateConfVectorPosition = 0;
	/* The reactions of state null. */
	if (handle->iface.setTemp - handle->iface.interiorTemp > 2 && handle->internal.counter < handle->internal.max) { 
		handle->internal.counter += 1;
		/* 'default' enter sequence for state Set Temp Flap */
		/* Entry action for state 'Set Temp Flap'. */
		handle->iface.tempFlapSet = handle->internal.counter * 100 / handle->internal.max;
		handle->stateConfVector[0] = TemperatureFlapCtrl_main_region_Set_Temp_Flap;
		handle->stateConfVectorPosition = 0;
	}  else {
		if (handle->iface.setTemp - handle->iface.interiorTemp < - 2 && handle->internal.counter > handle->internal.min) { 
			handle->internal.counter -= 1;
			/* 'default' enter sequence for state Set Temp Flap */
			/* Entry action for state 'Set Temp Flap'. */
			handle->iface.tempFlapSet = handle->internal.counter * 100 / handle->internal.max;
			handle->stateConfVector[0] = TemperatureFlapCtrl_main_region_Set_Temp_Flap;
			handle->stateConfVectorPosition = 0;
		}  else {
			/* 'default' enter sequence for state Set Temp Flap */
			/* Entry action for state 'Set Temp Flap'. */
			handle->iface.tempFlapSet = handle->internal.counter * 100 / handle->internal.max;
			handle->stateConfVector[0] = TemperatureFlapCtrl_main_region_Set_Temp_Flap;
			handle->stateConfVectorPosition = 0;
		}
	}
}


