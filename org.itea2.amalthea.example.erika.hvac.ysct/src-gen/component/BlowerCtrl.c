
#include <stdlib.h>
#include <string.h>
#include "sc_types.h"
#include "BlowerCtrl.h"
/*! \file Implementation of the state machine 'BlowerCtrl'
*/

// prototypes of all internal functions

static void blowerCtrl_enact_SequenceImpl(BlowerCtrl* handle);
static void blowerCtrl_exact_SequenceImpl(BlowerCtrl* handle);
static void blowerCtrl_react_main_region_Auto_Mode__region0_Calc_Power(BlowerCtrl* handle);
static void blowerCtrl_react_main_region_PassThroughMode(BlowerCtrl* handle);
static void blowerCtrl_clearInEvents(BlowerCtrl* handle);
static void blowerCtrl_clearOutEvents(BlowerCtrl* handle);


void blowerCtrl_init(BlowerCtrl* handle)
{
	int i;

	for (i = 0; i < BLOWERCTRL_MAX_ORTHOGONAL_STATES; ++i)
		handle->stateConfVector[i] = BlowerCtrl_last_state;
	
	
	handle->stateConfVectorPosition = 0;

	blowerCtrl_clearInEvents(handle);
	blowerCtrl_clearOutEvents(handle);

	/* Default init sequence for statechart BlowerCtrl */
	handle->iface.passThroughValue = 0;
	handle->iface.interiorTemp = 0;
	handle->iface.drvRefTemp = 0;
	handle->iface.passRefTemp = 0;
	handle->iface.power = 0;
	handle->internal.drvDelta = 0;
	handle->internal.passDelta = 0;
	handle->internal.tempPwr = 0;

}

void blowerCtrl_enter(BlowerCtrl* handle)
{
	/* Default enter sequence for statechart BlowerCtrl */
	blowerCtrl_enact_SequenceImpl(handle);
	/* 'default' enter sequence for region main region */
	/* Default react sequence for initial entry  */
	/* 'default' enter sequence for state PassThroughMode */
	/* Entry action for state 'PassThroughMode'. */
	handle->iface.power = handle->iface.passThroughValue;
	handle->stateConfVector[0] = BlowerCtrl_main_region_PassThroughMode;
	handle->stateConfVectorPosition = 0;
}

void blowerCtrl_exit(BlowerCtrl* handle)
{
	/* Default exit sequence for statechart BlowerCtrl */
	/* Default exit sequence for region main region */
	/* Handle exit of all possible states (of main region) at position 0... */
	switch(handle->stateConfVector[ 0 ]) {
		case BlowerCtrl_main_region_Auto_Mode__region0_Calc_Power : {
			/* Default exit sequence for state Calc Power */
			handle->stateConfVector[0] = BlowerCtrl_last_state;
			handle->stateConfVectorPosition = 0;
			break;
		}
		case BlowerCtrl_main_region_PassThroughMode : {
			/* Default exit sequence for state PassThroughMode */
			handle->stateConfVector[0] = BlowerCtrl_last_state;
			handle->stateConfVectorPosition = 0;
			break;
		}
		default: break;
	}
	blowerCtrl_exact_SequenceImpl(handle);
}

static void blowerCtrl_clearInEvents(BlowerCtrl* handle) {
	handle->iface.autoMode_raised = bool_false;
	handle->iface.passThroughMode_raised = bool_false;
}

static void blowerCtrl_clearOutEvents(BlowerCtrl* handle) {
}

void blowerCtrl_runCycle(BlowerCtrl* handle) {
	
	blowerCtrl_clearOutEvents(handle);
	
	for (handle->stateConfVectorPosition = 0;
		handle->stateConfVectorPosition < BLOWERCTRL_MAX_ORTHOGONAL_STATES;
		handle->stateConfVectorPosition++) {
			
		switch (handle->stateConfVector[handle->stateConfVectorPosition]) {
		case BlowerCtrl_main_region_Auto_Mode__region0_Calc_Power : {
			blowerCtrl_react_main_region_Auto_Mode__region0_Calc_Power(handle);
			break;
		}
		case BlowerCtrl_main_region_PassThroughMode : {
			blowerCtrl_react_main_region_PassThroughMode(handle);
			break;
		}
		default:
			break;
		}
	}
	
	blowerCtrl_clearInEvents(handle);
}


sc_boolean blowerCtrl_isActive(BlowerCtrl* handle, BlowerCtrlStates state) {
	switch (state) {
		case BlowerCtrl_main_region_Auto_Mode : 
			return (sc_boolean) (handle->stateConfVector[0] >= BlowerCtrl_main_region_Auto_Mode
				&& handle->stateConfVector[0] <= BlowerCtrl_main_region_Auto_Mode__region0_Calc_Power);
		case BlowerCtrl_main_region_Auto_Mode__region0_Calc_Power : 
			return (sc_boolean) (handle->stateConfVector[0] == BlowerCtrl_main_region_Auto_Mode__region0_Calc_Power
			);
		case BlowerCtrl_main_region_PassThroughMode : 
			return (sc_boolean) (handle->stateConfVector[0] == BlowerCtrl_main_region_PassThroughMode
			);
		default: return bool_false;
	}
}

void blowerCtrlIface_raise_autoMode(BlowerCtrl* handle) {
	handle->iface.autoMode_raised = bool_true;
}
void blowerCtrlIface_raise_passThroughMode(BlowerCtrl* handle) {
	handle->iface.passThroughMode_raised = bool_true;
}


sc_integer blowerCtrlIface_get_passThroughValue(BlowerCtrl* handle) {
	return handle->iface.passThroughValue;
}
void blowerCtrlIface_set_passThroughValue(BlowerCtrl* handle, sc_integer value) {
	handle->iface.passThroughValue = value;
}
sc_integer blowerCtrlIface_get_interiorTemp(BlowerCtrl* handle) {
	return handle->iface.interiorTemp;
}
void blowerCtrlIface_set_interiorTemp(BlowerCtrl* handle, sc_integer value) {
	handle->iface.interiorTemp = value;
}
sc_integer blowerCtrlIface_get_drvRefTemp(BlowerCtrl* handle) {
	return handle->iface.drvRefTemp;
}
void blowerCtrlIface_set_drvRefTemp(BlowerCtrl* handle, sc_integer value) {
	handle->iface.drvRefTemp = value;
}
sc_integer blowerCtrlIface_get_passRefTemp(BlowerCtrl* handle) {
	return handle->iface.passRefTemp;
}
void blowerCtrlIface_set_passRefTemp(BlowerCtrl* handle, sc_integer value) {
	handle->iface.passRefTemp = value;
}
sc_integer blowerCtrlIface_get_power(BlowerCtrl* handle) {
	return handle->iface.power;
}
void blowerCtrlIface_set_power(BlowerCtrl* handle, sc_integer value) {
	handle->iface.power = value;
}

// implementations of all internal functions

/* Entry action for statechart 'BlowerCtrl'. */
static void blowerCtrl_enact_SequenceImpl(BlowerCtrl* handle) {
}

/* Exit action for state 'BlowerCtrl'. */
static void blowerCtrl_exact_SequenceImpl(BlowerCtrl* handle) {
}

/* The reactions of state Calc Power. */
static void blowerCtrl_react_main_region_Auto_Mode__region0_Calc_Power(BlowerCtrl* handle) {
	/* The reactions of state Calc Power. */
	if (handle->iface.passThroughMode_raised) { 
		/* Default exit sequence for state Auto Mode */
		/* Default exit sequence for region  */
		/* Handle exit of all possible states (of region0) at position 0... */
		switch(handle->stateConfVector[ 0 ]) {
			case BlowerCtrl_main_region_Auto_Mode__region0_Calc_Power : {
				/* Default exit sequence for state Calc Power */
				handle->stateConfVector[0] = BlowerCtrl_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			default: break;
		}
		/* 'default' enter sequence for state PassThroughMode */
		/* Entry action for state 'PassThroughMode'. */
		handle->iface.power = handle->iface.passThroughValue;
		handle->stateConfVector[0] = BlowerCtrl_main_region_PassThroughMode;
		handle->stateConfVectorPosition = 0;
	}  else {
		handle->internal.drvDelta = handle->iface.drvRefTemp - handle->iface.interiorTemp;
		handle->internal.passDelta = handle->iface.passRefTemp - handle->iface.interiorTemp;
		if ((bool_true) && handle->internal.drvDelta < 0) { 
			handle->internal.drvDelta = handle->internal.drvDelta * - 1;
		} 
		if ((bool_true) && handle->internal.passDelta < 0) { 
			handle->internal.passDelta = handle->internal.passDelta * - 1;
		} 
		/* Default exit sequence for state Calc Power */
		handle->stateConfVector[0] = BlowerCtrl_last_state;
		handle->stateConfVectorPosition = 0;
		/* The reactions of state null. */
		if (handle->internal.passDelta > handle->internal.drvDelta) { 
			handle->internal.tempPwr = 10 * handle->internal.passDelta / 10;
			/* The reactions of state null. */
			if (handle->internal.tempPwr > 100) { 
				handle->iface.power = 100;
				/* 'default' enter sequence for state Calc Power */
				handle->stateConfVector[0] = BlowerCtrl_main_region_Auto_Mode__region0_Calc_Power;
				handle->stateConfVectorPosition = 0;
			}  else {
				if (handle->internal.tempPwr <= 10) { 
					handle->iface.power = 10;
					/* 'default' enter sequence for state Calc Power */
					handle->stateConfVector[0] = BlowerCtrl_main_region_Auto_Mode__region0_Calc_Power;
					handle->stateConfVectorPosition = 0;
				}  else {
					handle->iface.power = handle->internal.tempPwr;
					/* 'default' enter sequence for state Calc Power */
					handle->stateConfVector[0] = BlowerCtrl_main_region_Auto_Mode__region0_Calc_Power;
					handle->stateConfVectorPosition = 0;
				}
			}
		}  else {
			handle->internal.tempPwr = 10 * handle->internal.drvDelta / 10;
			/* The reactions of state null. */
			if (handle->internal.tempPwr > 100) { 
				handle->iface.power = 100;
				/* 'default' enter sequence for state Calc Power */
				handle->stateConfVector[0] = BlowerCtrl_main_region_Auto_Mode__region0_Calc_Power;
				handle->stateConfVectorPosition = 0;
			}  else {
				if (handle->internal.tempPwr <= 10) { 
					handle->iface.power = 10;
					/* 'default' enter sequence for state Calc Power */
					handle->stateConfVector[0] = BlowerCtrl_main_region_Auto_Mode__region0_Calc_Power;
					handle->stateConfVectorPosition = 0;
				}  else {
					handle->iface.power = handle->internal.tempPwr;
					/* 'default' enter sequence for state Calc Power */
					handle->stateConfVector[0] = BlowerCtrl_main_region_Auto_Mode__region0_Calc_Power;
					handle->stateConfVectorPosition = 0;
				}
			}
		}
	}
}

/* The reactions of state PassThroughMode. */
static void blowerCtrl_react_main_region_PassThroughMode(BlowerCtrl* handle) {
	/* The reactions of state PassThroughMode. */
	if (handle->iface.autoMode_raised) { 
		/* Default exit sequence for state PassThroughMode */
		handle->stateConfVector[0] = BlowerCtrl_last_state;
		handle->stateConfVectorPosition = 0;
		/* Entry action for state 'Auto Mode'. */
		handle->internal.drvDelta = handle->iface.drvRefTemp - handle->iface.interiorTemp;
		handle->internal.passDelta = handle->iface.passRefTemp - handle->iface.interiorTemp;
		if (handle->internal.drvDelta < 0) { 
			handle->internal.drvDelta = handle->internal.drvDelta * - 1;
		} 
		if (handle->internal.passDelta < 0) { 
			handle->internal.passDelta = handle->internal.passDelta * - 1;
		} 
		/* The reactions of state null. */
		if (handle->internal.passDelta > handle->internal.drvDelta) { 
			handle->internal.tempPwr = 10 * handle->internal.passDelta / 10;
			/* The reactions of state null. */
			if (handle->internal.tempPwr > 100) { 
				handle->iface.power = 100;
				/* 'default' enter sequence for state Calc Power */
				handle->stateConfVector[0] = BlowerCtrl_main_region_Auto_Mode__region0_Calc_Power;
				handle->stateConfVectorPosition = 0;
			}  else {
				if (handle->internal.tempPwr <= 10) { 
					handle->iface.power = 10;
					/* 'default' enter sequence for state Calc Power */
					handle->stateConfVector[0] = BlowerCtrl_main_region_Auto_Mode__region0_Calc_Power;
					handle->stateConfVectorPosition = 0;
				}  else {
					handle->iface.power = handle->internal.tempPwr;
					/* 'default' enter sequence for state Calc Power */
					handle->stateConfVector[0] = BlowerCtrl_main_region_Auto_Mode__region0_Calc_Power;
					handle->stateConfVectorPosition = 0;
				}
			}
		}  else {
			handle->internal.tempPwr = 10 * handle->internal.drvDelta / 10;
			/* The reactions of state null. */
			if (handle->internal.tempPwr > 100) { 
				handle->iface.power = 100;
				/* 'default' enter sequence for state Calc Power */
				handle->stateConfVector[0] = BlowerCtrl_main_region_Auto_Mode__region0_Calc_Power;
				handle->stateConfVectorPosition = 0;
			}  else {
				if (handle->internal.tempPwr <= 10) { 
					handle->iface.power = 10;
					/* 'default' enter sequence for state Calc Power */
					handle->stateConfVector[0] = BlowerCtrl_main_region_Auto_Mode__region0_Calc_Power;
					handle->stateConfVectorPosition = 0;
				}  else {
					handle->iface.power = handle->internal.tempPwr;
					/* 'default' enter sequence for state Calc Power */
					handle->stateConfVector[0] = BlowerCtrl_main_region_Auto_Mode__region0_Calc_Power;
					handle->stateConfVectorPosition = 0;
				}
			}
		}
	}  else {
		handle->iface.power = handle->iface.passThroughValue;
	}
}


