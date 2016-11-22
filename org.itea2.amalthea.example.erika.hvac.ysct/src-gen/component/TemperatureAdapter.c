
#include <stdlib.h>
#include <string.h>
#include "sc_types.h"
#include "TemperatureAdapter.h"
/*! \file Implementation of the state machine 'TemperatureAdapter'
*/

// prototypes of all internal functions

static void temperatureAdapter_enact_SequenceImpl(TemperatureAdapter* handle);
static void temperatureAdapter_exact_SequenceImpl(TemperatureAdapter* handle);
static void temperatureAdapter_react__region0_off(TemperatureAdapter* handle);
static void temperatureAdapter_react__region0_on__region0_Calculate_Driver_Temperature(TemperatureAdapter* handle);
static void temperatureAdapter_clearInEvents(TemperatureAdapter* handle);
static void temperatureAdapter_clearOutEvents(TemperatureAdapter* handle);


void temperatureAdapter_init(TemperatureAdapter* handle)
{
	int i;

	for (i = 0; i < TEMPERATUREADAPTER_MAX_ORTHOGONAL_STATES; ++i)
		handle->stateConfVector[i] = TemperatureAdapter_last_state;
	
	
	handle->stateConfVectorPosition = 0;

	temperatureAdapter_clearInEvents(handle);
	temperatureAdapter_clearOutEvents(handle);

	/* Default init sequence for statechart TemperatureAdapter */
	handle->iface.plusTicks = 0;
	handle->iface.minusTicks = 0;
	handle->iface.temp = 200;
	handle->internal.low = 155;
	handle->internal.high = 285;
	handle->internal.step = 5;

}

void temperatureAdapter_enter(TemperatureAdapter* handle)
{
	/* Default enter sequence for statechart TemperatureAdapter */
	temperatureAdapter_enact_SequenceImpl(handle);
	/* 'default' enter sequence for region  */
	/* Default react sequence for initial entry  */
	/* 'default' enter sequence for state off */
	handle->stateConfVector[0] = TemperatureAdapter__region0_off;
	handle->stateConfVectorPosition = 0;
}

void temperatureAdapter_exit(TemperatureAdapter* handle)
{
	/* Default exit sequence for statechart TemperatureAdapter */
	/* Default exit sequence for region  */
	/* Handle exit of all possible states (of region0) at position 0... */
	switch(handle->stateConfVector[ 0 ]) {
		case TemperatureAdapter__region0_off : {
			/* Default exit sequence for state off */
			handle->stateConfVector[0] = TemperatureAdapter_last_state;
			handle->stateConfVectorPosition = 0;
			break;
		}
		case TemperatureAdapter__region0_on__region0_Calculate_Driver_Temperature : {
			/* Default exit sequence for state Calculate Driver Temperature */
			handle->stateConfVector[0] = TemperatureAdapter_last_state;
			handle->stateConfVectorPosition = 0;
			break;
		}
		default: break;
	}
	temperatureAdapter_exact_SequenceImpl(handle);
}

static void temperatureAdapter_clearInEvents(TemperatureAdapter* handle) {
	handle->iface.temperatureSet_raised = bool_false;
	handle->iface.off_raised = bool_false;
	handle->iface.on_raised = bool_false;
}

static void temperatureAdapter_clearOutEvents(TemperatureAdapter* handle) {
}

void temperatureAdapter_runCycle(TemperatureAdapter* handle) {
	
	temperatureAdapter_clearOutEvents(handle);
	
	for (handle->stateConfVectorPosition = 0;
		handle->stateConfVectorPosition < TEMPERATUREADAPTER_MAX_ORTHOGONAL_STATES;
		handle->stateConfVectorPosition++) {
			
		switch (handle->stateConfVector[handle->stateConfVectorPosition]) {
		case TemperatureAdapter__region0_off : {
			temperatureAdapter_react__region0_off(handle);
			break;
		}
		case TemperatureAdapter__region0_on__region0_Calculate_Driver_Temperature : {
			temperatureAdapter_react__region0_on__region0_Calculate_Driver_Temperature(handle);
			break;
		}
		default:
			break;
		}
	}
	
	temperatureAdapter_clearInEvents(handle);
}


sc_boolean temperatureAdapter_isActive(TemperatureAdapter* handle, TemperatureAdapterStates state) {
	switch (state) {
		case TemperatureAdapter__region0_off : 
			return (sc_boolean) (handle->stateConfVector[0] == TemperatureAdapter__region0_off
			);
		case TemperatureAdapter__region0_on : 
			return (sc_boolean) (handle->stateConfVector[0] >= TemperatureAdapter__region0_on
				&& handle->stateConfVector[0] <= TemperatureAdapter__region0_on__region0_Calculate_Driver_Temperature);
		case TemperatureAdapter__region0_on__region0_Calculate_Driver_Temperature : 
			return (sc_boolean) (handle->stateConfVector[0] == TemperatureAdapter__region0_on__region0_Calculate_Driver_Temperature
			);
		default: return bool_false;
	}
}

void temperatureAdapterIface_raise_temperatureSet(TemperatureAdapter* handle) {
	handle->iface.temperatureSet_raised = bool_true;
}
void temperatureAdapterIface_raise_off(TemperatureAdapter* handle) {
	handle->iface.off_raised = bool_true;
}
void temperatureAdapterIface_raise_on(TemperatureAdapter* handle) {
	handle->iface.on_raised = bool_true;
}


sc_integer temperatureAdapterIface_get_plusTicks(TemperatureAdapter* handle) {
	return handle->iface.plusTicks;
}
void temperatureAdapterIface_set_plusTicks(TemperatureAdapter* handle, sc_integer value) {
	handle->iface.plusTicks = value;
}
sc_integer temperatureAdapterIface_get_minusTicks(TemperatureAdapter* handle) {
	return handle->iface.minusTicks;
}
void temperatureAdapterIface_set_minusTicks(TemperatureAdapter* handle, sc_integer value) {
	handle->iface.minusTicks = value;
}
sc_integer temperatureAdapterIface_get_temp(TemperatureAdapter* handle) {
	return handle->iface.temp;
}
void temperatureAdapterIface_set_temp(TemperatureAdapter* handle, sc_integer value) {
	handle->iface.temp = value;
}

// implementations of all internal functions

/* Entry action for statechart 'TemperatureAdapter'. */
static void temperatureAdapter_enact_SequenceImpl(TemperatureAdapter* handle) {
}

/* Exit action for state 'TemperatureAdapter'. */
static void temperatureAdapter_exact_SequenceImpl(TemperatureAdapter* handle) {
}

/* The reactions of state off. */
static void temperatureAdapter_react__region0_off(TemperatureAdapter* handle) {
	/* The reactions of state off. */
	if (handle->iface.on_raised) { 
		/* Default exit sequence for state off */
		handle->stateConfVector[0] = TemperatureAdapter_last_state;
		handle->stateConfVectorPosition = 0;
		/* 'default' enter sequence for state on */
		/* 'default' enter sequence for region  */
		/* Default react sequence for initial entry  */
		/* 'default' enter sequence for state Calculate Driver Temperature */
		/* Entry action for state 'Calculate Driver Temperature'. */
		handle->iface.plusTicks = 0;
		handle->iface.minusTicks = 0;
		handle->stateConfVector[0] = TemperatureAdapter__region0_on__region0_Calculate_Driver_Temperature;
		handle->stateConfVectorPosition = 0;
	} 
}

/* The reactions of state Calculate Driver Temperature. */
static void temperatureAdapter_react__region0_on__region0_Calculate_Driver_Temperature(TemperatureAdapter* handle) {
	/* The reactions of state Calculate Driver Temperature. */
	if (handle->iface.off_raised) { 
		/* Default exit sequence for state on */
		/* Default exit sequence for region  */
		/* Handle exit of all possible states (of region0) at position 0... */
		switch(handle->stateConfVector[ 0 ]) {
			case TemperatureAdapter__region0_on__region0_Calculate_Driver_Temperature : {
				/* Default exit sequence for state Calculate Driver Temperature */
				handle->stateConfVector[0] = TemperatureAdapter_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			default: break;
		}
		/* 'default' enter sequence for state off */
		handle->stateConfVector[0] = TemperatureAdapter__region0_off;
		handle->stateConfVectorPosition = 0;
	}  else {
		if (handle->iface.temperatureSet_raised) { 
			/* Default exit sequence for state Calculate Driver Temperature */
			handle->stateConfVector[0] = TemperatureAdapter_last_state;
			handle->stateConfVectorPosition = 0;
			/* The reactions of state null. */
			if ((handle->iface.plusTicks - handle->iface.minusTicks) * handle->internal.step + handle->iface.temp <= handle->internal.low) { 
				handle->iface.temp = handle->internal.low;
				/* 'default' enter sequence for state Calculate Driver Temperature */
				/* Entry action for state 'Calculate Driver Temperature'. */
				handle->iface.plusTicks = 0;
				handle->iface.minusTicks = 0;
				handle->stateConfVector[0] = TemperatureAdapter__region0_on__region0_Calculate_Driver_Temperature;
				handle->stateConfVectorPosition = 0;
			}  else {
				if ((handle->iface.plusTicks - handle->iface.minusTicks) * handle->internal.step + handle->iface.temp >= handle->internal.high) { 
					handle->iface.temp = handle->internal.high;
					/* 'default' enter sequence for state Calculate Driver Temperature */
					/* Entry action for state 'Calculate Driver Temperature'. */
					handle->iface.plusTicks = 0;
					handle->iface.minusTicks = 0;
					handle->stateConfVector[0] = TemperatureAdapter__region0_on__region0_Calculate_Driver_Temperature;
					handle->stateConfVectorPosition = 0;
				}  else {
					handle->iface.temp += (handle->iface.plusTicks - handle->iface.minusTicks) * handle->internal.step;
					/* 'default' enter sequence for state Calculate Driver Temperature */
					/* Entry action for state 'Calculate Driver Temperature'. */
					handle->iface.plusTicks = 0;
					handle->iface.minusTicks = 0;
					handle->stateConfVector[0] = TemperatureAdapter__region0_on__region0_Calculate_Driver_Temperature;
					handle->stateConfVectorPosition = 0;
				}
			}
		} 
	}
}


