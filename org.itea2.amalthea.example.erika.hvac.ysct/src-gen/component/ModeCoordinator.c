
#include <stdlib.h>
#include <string.h>
#include "sc_types.h"
#include "ModeCoordinator.h"
/*! \file Implementation of the state machine 'ModeCoordinator'
*/

// prototypes of all internal functions

static void modeCoordinator_enact_SequenceImpl(ModeCoordinator* handle);
static void modeCoordinator_exact_SequenceImpl(ModeCoordinator* handle);
static void modeCoordinator_dhenseq_SequenceImpl(ModeCoordinator* handle);
static void modeCoordinator_dhenseq_modeProcessing_On__region0_Manual_SequenceImpl(ModeCoordinator* handle);
static void modeCoordinator_shenseq_SequenceImpl(ModeCoordinator* handle);
static void modeCoordinator_shenseq_ExecutionFlowImpl_SequenceImpl(ModeCoordinator* handle);
static void modeCoordinator_react_modeProcessing_Off(ModeCoordinator* handle);
static void modeCoordinator_react_modeProcessing_On__region0_Defrost(ModeCoordinator* handle);
static void modeCoordinator_react_modeProcessing_On__region0_Auto(ModeCoordinator* handle);
static void modeCoordinator_react_modeProcessing_On__region0_Manual__region0_Floor(ModeCoordinator* handle);
static void modeCoordinator_react_modeProcessing_On__region0_Manual__region0_BiLevel(ModeCoordinator* handle);
static void modeCoordinator_react_modeProcessing_On__region0_Manual__region0_Vent(ModeCoordinator* handle);
static void modeCoordinator_react_modeProcessing_On__region0_Manual__region0_Mix(ModeCoordinator* handle);
static void modeCoordinator_react_blowerProcessing_Off(ModeCoordinator* handle);
static void modeCoordinator_react_blowerProcessing_Calc_Blower_Power(ModeCoordinator* handle);
static void modeCoordinator_react_ac_Aircondition_Disabled(ModeCoordinator* handle);
static void modeCoordinator_react_ac_Aircondition_Enabled(ModeCoordinator* handle);
static void modeCoordinator_react_recirc_Recirc_Disabled(ModeCoordinator* handle);
static void modeCoordinator_react_recirc_Recirc_Enabled(ModeCoordinator* handle);
static void modeCoordinator_clearInEvents(ModeCoordinator* handle);
static void modeCoordinator_clearOutEvents(ModeCoordinator* handle);


void modeCoordinator_init(ModeCoordinator* handle)
{
	int i;

	for (i = 0; i < MODECOORDINATOR_MAX_ORTHOGONAL_STATES; ++i)
		handle->stateConfVector[i] = ModeCoordinator_last_state;
	
	for (i = 0; i < MODECOORDINATOR_MAX_HISTORY_STATES; ++i)
		handle->historyVector[i] = ModeCoordinator_last_state;
	
	handle->stateConfVectorPosition = 0;

	modeCoordinator_clearInEvents(handle);
	modeCoordinator_clearOutEvents(handle);

	/* Default init sequence for statechart ModeCoordinator */
	handle->ifaceHMI.recircSwitch = bool_false;
	handle->ifaceHMI.AC_Switch = bool_false;
	handle->ifaceHMI.levelSwitch = 0;
	handle->ifaceHMI.levelState = 0;
	handle->ifaceBlower.power = 0;
	handle->ifaceBlower.autoPower = 0;
	handle->ifaceBlower.maxSteps = 10;
	handle->ifaceBlower.increaseTicks = 0;
	handle->ifaceBlower.decreaseTicks = 0;
	handle->ifaceTemperature.AC_State = bool_false;
	handle->ifaceAirFlaps.recircState = bool_false;
	handle->ifaceAirFlaps.defrostLeftSet = 0;
	handle->ifaceAirFlaps.defrostRightSet = 0;
	handle->ifaceAirFlaps.ventLeftSet = 0;
	handle->ifaceAirFlaps.ventRightSet = 0;
	handle->ifaceAirFlaps.floorLeftSet = 0;
	handle->ifaceAirFlaps.floorRightSet = 0;
	handle->ifaceAirFlaps.recircSet = 0;

}

void modeCoordinator_enter(ModeCoordinator* handle)
{
	/* Default enter sequence for statechart ModeCoordinator */
	modeCoordinator_enact_SequenceImpl(handle);
	/* 'default' enter sequence for region modeProcessing */
	/* Default react sequence for initial entry  */
	/* 'default' enter sequence for state Off */
	/* Entry action for state 'Off'. */
	handle->ifaceTemperature.off_raised = bool_true;
	handle->internal.blwOff_raised = bool_true;
	handle->ifaceBlower.manual_raised = bool_true;
	handle->ifaceAirFlaps.recircState = bool_false;
	handle->ifaceTemperature.AC_State = bool_false;
	handle->ifaceHMI.levelState = 7;
	handle->stateConfVector[0] = ModeCoordinator_modeProcessing_Off;
	handle->stateConfVectorPosition = 0;
	/* 'default' enter sequence for region blowerProcessing */
	/* Default react sequence for initial entry  */
	/* 'default' enter sequence for state Off */
	/* Entry action for state 'Off'. */
	handle->ifaceBlower.power = 0;
	handle->stateConfVector[1] = ModeCoordinator_blowerProcessing_Off;
	handle->stateConfVectorPosition = 1;
	/* 'default' enter sequence for region ac */
	/* Default react sequence for shallow history entry  */
	/* Enter the region with shallow history */
	if (handle->historyVector[2] != ModeCoordinator_last_state) {
		modeCoordinator_shenseq_SequenceImpl(handle);
	} else {
		/* 'default' enter sequence for state Aircondition Disabled */
		handle->stateConfVector[2] = ModeCoordinator_ac_Aircondition_Disabled;
		handle->stateConfVectorPosition = 2;
		handle->historyVector[2] = handle->stateConfVector[2];
	} 
	/* 'default' enter sequence for region recirc */
	/* Default react sequence for shallow history entry  */
	/* Enter the region with shallow history */
	if (handle->historyVector[3] != ModeCoordinator_last_state) {
		modeCoordinator_shenseq_ExecutionFlowImpl_SequenceImpl(handle);
	} else {
		/* 'default' enter sequence for state Recirc Disabled */
		/* Entry action for state 'Recirc Disabled'. */
		handle->ifaceAirFlaps.recircSet = 0;
		handle->stateConfVector[3] = ModeCoordinator_recirc_Recirc_Disabled;
		handle->stateConfVectorPosition = 3;
		handle->historyVector[3] = handle->stateConfVector[3];
	} 
}

void modeCoordinator_exit(ModeCoordinator* handle)
{
	/* Default exit sequence for statechart ModeCoordinator */
	/* Default exit sequence for region modeProcessing */
	/* Handle exit of all possible states (of modeProcessing) at position 0... */
	switch(handle->stateConfVector[ 0 ]) {
		case ModeCoordinator_modeProcessing_Off : {
			/* Default exit sequence for state Off */
			handle->stateConfVector[0] = ModeCoordinator_last_state;
			handle->stateConfVectorPosition = 0;
			break;
		}
		case ModeCoordinator_modeProcessing_On__region0_Defrost : {
			/* Default exit sequence for state Defrost */
			handle->stateConfVector[0] = ModeCoordinator_last_state;
			handle->stateConfVectorPosition = 0;
			break;
		}
		case ModeCoordinator_modeProcessing_On__region0_Auto : {
			/* Default exit sequence for state Auto */
			handle->stateConfVector[0] = ModeCoordinator_last_state;
			handle->stateConfVectorPosition = 0;
			break;
		}
		case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Floor : {
			/* Default exit sequence for state Floor */
			handle->stateConfVector[0] = ModeCoordinator_last_state;
			handle->stateConfVectorPosition = 0;
			break;
		}
		case ModeCoordinator_modeProcessing_On__region0_Manual__region0_BiLevel : {
			/* Default exit sequence for state BiLevel */
			handle->stateConfVector[0] = ModeCoordinator_last_state;
			handle->stateConfVectorPosition = 0;
			break;
		}
		case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Vent : {
			/* Default exit sequence for state Vent */
			handle->stateConfVector[0] = ModeCoordinator_last_state;
			handle->stateConfVectorPosition = 0;
			break;
		}
		case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Mix : {
			/* Default exit sequence for state Mix */
			handle->stateConfVector[0] = ModeCoordinator_last_state;
			handle->stateConfVectorPosition = 0;
			break;
		}
		default: break;
	}
	/* Default exit sequence for region blowerProcessing */
	/* Handle exit of all possible states (of blowerProcessing) at position 1... */
	switch(handle->stateConfVector[ 1 ]) {
		case ModeCoordinator_blowerProcessing_Off : {
			/* Default exit sequence for state Off */
			handle->stateConfVector[1] = ModeCoordinator_last_state;
			handle->stateConfVectorPosition = 1;
			break;
		}
		case ModeCoordinator_blowerProcessing_Calc_Blower_Power : {
			/* Default exit sequence for state Calc Blower Power */
			handle->stateConfVector[1] = ModeCoordinator_last_state;
			handle->stateConfVectorPosition = 1;
			break;
		}
		default: break;
	}
	/* Default exit sequence for region ac */
	/* Handle exit of all possible states (of ac) at position 2... */
	switch(handle->stateConfVector[ 2 ]) {
		case ModeCoordinator_ac_Aircondition_Disabled : {
			/* Default exit sequence for state Aircondition Disabled */
			handle->stateConfVector[2] = ModeCoordinator_last_state;
			handle->stateConfVectorPosition = 2;
			break;
		}
		case ModeCoordinator_ac_Aircondition_Enabled : {
			/* Default exit sequence for state Aircondition Enabled */
			handle->stateConfVector[2] = ModeCoordinator_last_state;
			handle->stateConfVectorPosition = 2;
			break;
		}
		default: break;
	}
	/* Default exit sequence for region recirc */
	/* Handle exit of all possible states (of recirc) at position 3... */
	switch(handle->stateConfVector[ 3 ]) {
		case ModeCoordinator_recirc_Recirc_Disabled : {
			/* Default exit sequence for state Recirc Disabled */
			handle->stateConfVector[3] = ModeCoordinator_last_state;
			handle->stateConfVectorPosition = 3;
			break;
		}
		case ModeCoordinator_recirc_Recirc_Enabled : {
			/* Default exit sequence for state Recirc Enabled */
			handle->stateConfVector[3] = ModeCoordinator_last_state;
			handle->stateConfVectorPosition = 3;
			break;
		}
		default: break;
	}
	modeCoordinator_exact_SequenceImpl(handle);
}

static void modeCoordinator_clearInEvents(ModeCoordinator* handle) {
	handle->ifaceHMI.ComToggle_raised = bool_false;
	handle->internal.blwOff_raised = bool_false; 
}

static void modeCoordinator_clearOutEvents(ModeCoordinator* handle) {
	handle->ifaceBlower.auto_raised = bool_false;
	handle->ifaceBlower.manual_raised = bool_false;
	handle->ifaceTemperature.on_raised = bool_false;
	handle->ifaceTemperature.off_raised = bool_false;
}

void modeCoordinator_runCycle(ModeCoordinator* handle) {
	
	modeCoordinator_clearOutEvents(handle);
	
	for (handle->stateConfVectorPosition = 0;
		handle->stateConfVectorPosition < MODECOORDINATOR_MAX_ORTHOGONAL_STATES;
		handle->stateConfVectorPosition++) {
			
		switch (handle->stateConfVector[handle->stateConfVectorPosition]) {
		case ModeCoordinator_modeProcessing_Off : {
			modeCoordinator_react_modeProcessing_Off(handle);
			break;
		}
		case ModeCoordinator_modeProcessing_On__region0_Defrost : {
			modeCoordinator_react_modeProcessing_On__region0_Defrost(handle);
			break;
		}
		case ModeCoordinator_modeProcessing_On__region0_Auto : {
			modeCoordinator_react_modeProcessing_On__region0_Auto(handle);
			break;
		}
		case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Floor : {
			modeCoordinator_react_modeProcessing_On__region0_Manual__region0_Floor(handle);
			break;
		}
		case ModeCoordinator_modeProcessing_On__region0_Manual__region0_BiLevel : {
			modeCoordinator_react_modeProcessing_On__region0_Manual__region0_BiLevel(handle);
			break;
		}
		case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Vent : {
			modeCoordinator_react_modeProcessing_On__region0_Manual__region0_Vent(handle);
			break;
		}
		case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Mix : {
			modeCoordinator_react_modeProcessing_On__region0_Manual__region0_Mix(handle);
			break;
		}
		case ModeCoordinator_blowerProcessing_Off : {
			modeCoordinator_react_blowerProcessing_Off(handle);
			break;
		}
		case ModeCoordinator_blowerProcessing_Calc_Blower_Power : {
			modeCoordinator_react_blowerProcessing_Calc_Blower_Power(handle);
			break;
		}
		case ModeCoordinator_ac_Aircondition_Disabled : {
			modeCoordinator_react_ac_Aircondition_Disabled(handle);
			break;
		}
		case ModeCoordinator_ac_Aircondition_Enabled : {
			modeCoordinator_react_ac_Aircondition_Enabled(handle);
			break;
		}
		case ModeCoordinator_recirc_Recirc_Disabled : {
			modeCoordinator_react_recirc_Recirc_Disabled(handle);
			break;
		}
		case ModeCoordinator_recirc_Recirc_Enabled : {
			modeCoordinator_react_recirc_Recirc_Enabled(handle);
			break;
		}
		default:
			break;
		}
	}
	
	modeCoordinator_clearInEvents(handle);
}


sc_boolean modeCoordinator_isActive(ModeCoordinator* handle, ModeCoordinatorStates state) {
	switch (state) {
		case ModeCoordinator_modeProcessing_Off : 
			return (sc_boolean) (handle->stateConfVector[0] == ModeCoordinator_modeProcessing_Off
			);
		case ModeCoordinator_modeProcessing_On : 
			return (sc_boolean) (handle->stateConfVector[0] >= ModeCoordinator_modeProcessing_On
				&& handle->stateConfVector[0] <= ModeCoordinator_modeProcessing_On__region0_Manual__region0_Mix);
		case ModeCoordinator_modeProcessing_On__region0_Defrost : 
			return (sc_boolean) (handle->stateConfVector[0] == ModeCoordinator_modeProcessing_On__region0_Defrost
			);
		case ModeCoordinator_modeProcessing_On__region0_Auto : 
			return (sc_boolean) (handle->stateConfVector[0] == ModeCoordinator_modeProcessing_On__region0_Auto
			);
		case ModeCoordinator_modeProcessing_On__region0_Manual : 
			return (sc_boolean) (handle->stateConfVector[0] >= ModeCoordinator_modeProcessing_On__region0_Manual
				&& handle->stateConfVector[0] <= ModeCoordinator_modeProcessing_On__region0_Manual__region0_Mix);
		case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Floor : 
			return (sc_boolean) (handle->stateConfVector[0] == ModeCoordinator_modeProcessing_On__region0_Manual__region0_Floor
			);
		case ModeCoordinator_modeProcessing_On__region0_Manual__region0_BiLevel : 
			return (sc_boolean) (handle->stateConfVector[0] == ModeCoordinator_modeProcessing_On__region0_Manual__region0_BiLevel
			);
		case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Vent : 
			return (sc_boolean) (handle->stateConfVector[0] == ModeCoordinator_modeProcessing_On__region0_Manual__region0_Vent
			);
		case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Mix : 
			return (sc_boolean) (handle->stateConfVector[0] == ModeCoordinator_modeProcessing_On__region0_Manual__region0_Mix
			);
		case ModeCoordinator_blowerProcessing_Off : 
			return (sc_boolean) (handle->stateConfVector[1] == ModeCoordinator_blowerProcessing_Off
			);
		case ModeCoordinator_blowerProcessing_Calc_Blower_Power : 
			return (sc_boolean) (handle->stateConfVector[1] == ModeCoordinator_blowerProcessing_Calc_Blower_Power
			);
		case ModeCoordinator_ac_Aircondition_Disabled : 
			return (sc_boolean) (handle->stateConfVector[2] == ModeCoordinator_ac_Aircondition_Disabled
			);
		case ModeCoordinator_ac_Aircondition_Enabled : 
			return (sc_boolean) (handle->stateConfVector[2] == ModeCoordinator_ac_Aircondition_Enabled
			);
		case ModeCoordinator_recirc_Recirc_Disabled : 
			return (sc_boolean) (handle->stateConfVector[3] == ModeCoordinator_recirc_Recirc_Disabled
			);
		case ModeCoordinator_recirc_Recirc_Enabled : 
			return (sc_boolean) (handle->stateConfVector[3] == ModeCoordinator_recirc_Recirc_Enabled
			);
		default: return bool_false;
	}
}

void modeCoordinatorIfaceHMI_raise_comToggle(ModeCoordinator* handle) {
	handle->ifaceHMI.ComToggle_raised = bool_true;
}


sc_boolean modeCoordinatorIfaceHMI_get_recircSwitch(ModeCoordinator* handle) {
	return handle->ifaceHMI.recircSwitch;
}
void modeCoordinatorIfaceHMI_set_recircSwitch(ModeCoordinator* handle, sc_boolean value) {
	handle->ifaceHMI.recircSwitch = value;
}
sc_boolean modeCoordinatorIfaceHMI_get_aC_Switch(ModeCoordinator* handle) {
	return handle->ifaceHMI.AC_Switch;
}
void modeCoordinatorIfaceHMI_set_aC_Switch(ModeCoordinator* handle, sc_boolean value) {
	handle->ifaceHMI.AC_Switch = value;
}
sc_integer modeCoordinatorIfaceHMI_get_levelSwitch(ModeCoordinator* handle) {
	return handle->ifaceHMI.levelSwitch;
}
void modeCoordinatorIfaceHMI_set_levelSwitch(ModeCoordinator* handle, sc_integer value) {
	handle->ifaceHMI.levelSwitch = value;
}
sc_integer modeCoordinatorIfaceHMI_get_levelState(ModeCoordinator* handle) {
	return handle->ifaceHMI.levelState;
}
void modeCoordinatorIfaceHMI_set_levelState(ModeCoordinator* handle, sc_integer value) {
	handle->ifaceHMI.levelState = value;
}

sc_boolean modeCoordinatorIfaceBlower_israised_auto(ModeCoordinator* handle) {
	return handle->ifaceBlower.auto_raised;
}
sc_boolean modeCoordinatorIfaceBlower_israised_manual(ModeCoordinator* handle) {
	return handle->ifaceBlower.manual_raised;
}

sc_integer modeCoordinatorIfaceBlower_get_power(ModeCoordinator* handle) {
	return handle->ifaceBlower.power;
}
void modeCoordinatorIfaceBlower_set_power(ModeCoordinator* handle, sc_integer value) {
	handle->ifaceBlower.power = value;
}
sc_integer modeCoordinatorIfaceBlower_get_autoPower(ModeCoordinator* handle) {
	return handle->ifaceBlower.autoPower;
}
void modeCoordinatorIfaceBlower_set_autoPower(ModeCoordinator* handle, sc_integer value) {
	handle->ifaceBlower.autoPower = value;
}
sc_integer modeCoordinatorIfaceBlower_get_maxSteps(ModeCoordinator* handle) {
	return handle->ifaceBlower.maxSteps;
}
void modeCoordinatorIfaceBlower_set_maxSteps(ModeCoordinator* handle, sc_integer value) {
	handle->ifaceBlower.maxSteps = value;
}
sc_integer modeCoordinatorIfaceBlower_get_increaseTicks(ModeCoordinator* handle) {
	return handle->ifaceBlower.increaseTicks;
}
void modeCoordinatorIfaceBlower_set_increaseTicks(ModeCoordinator* handle, sc_integer value) {
	handle->ifaceBlower.increaseTicks = value;
}
sc_integer modeCoordinatorIfaceBlower_get_decreaseTicks(ModeCoordinator* handle) {
	return handle->ifaceBlower.decreaseTicks;
}
void modeCoordinatorIfaceBlower_set_decreaseTicks(ModeCoordinator* handle, sc_integer value) {
	handle->ifaceBlower.decreaseTicks = value;
}

sc_boolean modeCoordinatorIfaceTemperature_israised_on(ModeCoordinator* handle) {
	return handle->ifaceTemperature.on_raised;
}
sc_boolean modeCoordinatorIfaceTemperature_israised_off(ModeCoordinator* handle) {
	return handle->ifaceTemperature.off_raised;
}

sc_boolean modeCoordinatorIfaceTemperature_get_aC_State(ModeCoordinator* handle) {
	return handle->ifaceTemperature.AC_State;
}
void modeCoordinatorIfaceTemperature_set_aC_State(ModeCoordinator* handle, sc_boolean value) {
	handle->ifaceTemperature.AC_State = value;
}


sc_boolean modeCoordinatorIfaceAirFlaps_get_recircState(ModeCoordinator* handle) {
	return handle->ifaceAirFlaps.recircState;
}
void modeCoordinatorIfaceAirFlaps_set_recircState(ModeCoordinator* handle, sc_boolean value) {
	handle->ifaceAirFlaps.recircState = value;
}
sc_integer modeCoordinatorIfaceAirFlaps_get_defrostLeftSet(ModeCoordinator* handle) {
	return handle->ifaceAirFlaps.defrostLeftSet;
}
void modeCoordinatorIfaceAirFlaps_set_defrostLeftSet(ModeCoordinator* handle, sc_integer value) {
	handle->ifaceAirFlaps.defrostLeftSet = value;
}
sc_integer modeCoordinatorIfaceAirFlaps_get_defrostRightSet(ModeCoordinator* handle) {
	return handle->ifaceAirFlaps.defrostRightSet;
}
void modeCoordinatorIfaceAirFlaps_set_defrostRightSet(ModeCoordinator* handle, sc_integer value) {
	handle->ifaceAirFlaps.defrostRightSet = value;
}
sc_integer modeCoordinatorIfaceAirFlaps_get_ventLeftSet(ModeCoordinator* handle) {
	return handle->ifaceAirFlaps.ventLeftSet;
}
void modeCoordinatorIfaceAirFlaps_set_ventLeftSet(ModeCoordinator* handle, sc_integer value) {
	handle->ifaceAirFlaps.ventLeftSet = value;
}
sc_integer modeCoordinatorIfaceAirFlaps_get_ventRightSet(ModeCoordinator* handle) {
	return handle->ifaceAirFlaps.ventRightSet;
}
void modeCoordinatorIfaceAirFlaps_set_ventRightSet(ModeCoordinator* handle, sc_integer value) {
	handle->ifaceAirFlaps.ventRightSet = value;
}
sc_integer modeCoordinatorIfaceAirFlaps_get_floorLeftSet(ModeCoordinator* handle) {
	return handle->ifaceAirFlaps.floorLeftSet;
}
void modeCoordinatorIfaceAirFlaps_set_floorLeftSet(ModeCoordinator* handle, sc_integer value) {
	handle->ifaceAirFlaps.floorLeftSet = value;
}
sc_integer modeCoordinatorIfaceAirFlaps_get_floorRightSet(ModeCoordinator* handle) {
	return handle->ifaceAirFlaps.floorRightSet;
}
void modeCoordinatorIfaceAirFlaps_set_floorRightSet(ModeCoordinator* handle, sc_integer value) {
	handle->ifaceAirFlaps.floorRightSet = value;
}
sc_integer modeCoordinatorIfaceAirFlaps_get_recircSet(ModeCoordinator* handle) {
	return handle->ifaceAirFlaps.recircSet;
}
void modeCoordinatorIfaceAirFlaps_set_recircSet(ModeCoordinator* handle, sc_integer value) {
	handle->ifaceAirFlaps.recircSet = value;
}

// implementations of all internal functions

/* Entry action for statechart 'ModeCoordinator'. */
static void modeCoordinator_enact_SequenceImpl(ModeCoordinator* handle) {
}

/* Exit action for state 'ModeCoordinator'. */
static void modeCoordinator_exact_SequenceImpl(ModeCoordinator* handle) {
}

/* deep enterSequence with history in child null */
static void modeCoordinator_dhenseq_SequenceImpl(ModeCoordinator* handle) {
	/* deep enterSequence with history in child null */
	/* Handle deep history entry of null */
	switch(handle->historyVector[ 0 ]) {
		case ModeCoordinator_modeProcessing_On__region0_Defrost : {
			/* enterSequence with history in child Defrost for leaf Defrost */
			/* 'default' enter sequence for state Defrost */
			/* Entry action for state 'Defrost'. */
			handle->ifaceBlower.manual_raised = bool_true;
			handle->ifaceBlower.power = 80;
			handle->ifaceTemperature.AC_State = bool_true;
			handle->ifaceAirFlaps.recircState = bool_false;
			handle->ifaceAirFlaps.defrostLeftSet = 100;
			handle->ifaceAirFlaps.defrostRightSet = 100;
			handle->ifaceAirFlaps.ventLeftSet = 0;
			handle->ifaceAirFlaps.ventRightSet = 0;
			handle->ifaceAirFlaps.floorLeftSet = 0;
			handle->ifaceAirFlaps.floorRightSet = 0;
			handle->ifaceHMI.levelState = 1;
			handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Defrost;
			handle->stateConfVectorPosition = 0;
			handle->historyVector[0] = handle->stateConfVector[0];
			break;
		}
		case ModeCoordinator_modeProcessing_On__region0_Auto : {
			/* enterSequence with history in child Auto for leaf Auto */
			/* 'default' enter sequence for state Auto */
			/* Entry action for state 'Auto'. */
			handle->ifaceBlower.auto_raised = bool_true;
			handle->ifaceTemperature.AC_State = bool_true;
			handle->ifaceAirFlaps.recircState = bool_false;
			handle->ifaceHMI.levelState = 4;
			handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Auto;
			handle->stateConfVectorPosition = 0;
			handle->historyVector[0] = handle->stateConfVector[0];
			break;
		}
		case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Floor : {
			/* enterSequence with history in child Manual for leaf Floor */
			/* Entry action for state 'Manual'. */
			handle->ifaceBlower.manual_raised = bool_true;
			modeCoordinator_dhenseq_modeProcessing_On__region0_Manual_SequenceImpl(handle);
			break;
		}
		case ModeCoordinator_modeProcessing_On__region0_Manual__region0_BiLevel : {
			/* enterSequence with history in child Manual for leaf BiLevel */
			/* Entry action for state 'Manual'. */
			handle->ifaceBlower.manual_raised = bool_true;
			modeCoordinator_dhenseq_modeProcessing_On__region0_Manual_SequenceImpl(handle);
			break;
		}
		case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Vent : {
			/* enterSequence with history in child Manual for leaf Vent */
			/* Entry action for state 'Manual'. */
			handle->ifaceBlower.manual_raised = bool_true;
			modeCoordinator_dhenseq_modeProcessing_On__region0_Manual_SequenceImpl(handle);
			break;
		}
		case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Mix : {
			/* enterSequence with history in child Manual for leaf Mix */
			/* Entry action for state 'Manual'. */
			handle->ifaceBlower.manual_raised = bool_true;
			modeCoordinator_dhenseq_modeProcessing_On__region0_Manual_SequenceImpl(handle);
			break;
		}
		default: break;
	}
}

/* deep enterSequence with history in child null */
static void modeCoordinator_dhenseq_modeProcessing_On__region0_Manual_SequenceImpl(ModeCoordinator* handle) {
	/* deep enterSequence with history in child null */
	/* Handle deep history entry of null */
	switch(handle->historyVector[ 1 ]) {
		case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Floor : {
			/* enterSequence with history in child Floor for leaf Floor */
			/* 'default' enter sequence for state Floor */
			/* Entry action for state 'Floor'. */
			handle->ifaceAirFlaps.defrostLeftSet = 0;
			handle->ifaceAirFlaps.defrostRightSet = 0;
			handle->ifaceAirFlaps.ventLeftSet = 0;
			handle->ifaceAirFlaps.ventRightSet = 0;
			handle->ifaceAirFlaps.floorLeftSet = 100;
			handle->ifaceAirFlaps.floorRightSet = 100;
			handle->ifaceHMI.levelState = 6;
			handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Manual__region0_Floor;
			handle->stateConfVectorPosition = 0;
			handle->historyVector[1] = handle->stateConfVector[0];
			break;
		}
		case ModeCoordinator_modeProcessing_On__region0_Manual__region0_BiLevel : {
			/* enterSequence with history in child BiLevel for leaf BiLevel */
			/* 'default' enter sequence for state BiLevel */
			/* Entry action for state 'BiLevel'. */
			handle->ifaceAirFlaps.defrostLeftSet = 0;
			handle->ifaceAirFlaps.defrostRightSet = 0;
			handle->ifaceAirFlaps.ventLeftSet = 50;
			handle->ifaceAirFlaps.ventRightSet = 50;
			handle->ifaceAirFlaps.floorLeftSet = 50;
			handle->ifaceAirFlaps.floorRightSet = 50;
			handle->ifaceHMI.levelState = 5;
			handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Manual__region0_BiLevel;
			handle->stateConfVectorPosition = 0;
			handle->historyVector[1] = handle->stateConfVector[0];
			break;
		}
		case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Vent : {
			/* enterSequence with history in child Vent for leaf Vent */
			/* 'default' enter sequence for state Vent */
			/* Entry action for state 'Vent'. */
			handle->ifaceAirFlaps.defrostLeftSet = 0;
			handle->ifaceAirFlaps.defrostRightSet = 0;
			handle->ifaceAirFlaps.ventLeftSet = 100;
			handle->ifaceAirFlaps.ventRightSet = 100;
			handle->ifaceAirFlaps.floorLeftSet = 0;
			handle->ifaceAirFlaps.floorRightSet = 0;
			handle->ifaceHMI.levelState = 2;
			handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Manual__region0_Vent;
			handle->stateConfVectorPosition = 0;
			handle->historyVector[1] = handle->stateConfVector[0];
			break;
		}
		case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Mix : {
			/* enterSequence with history in child Mix for leaf Mix */
			/* 'default' enter sequence for state Mix */
			/* Entry action for state 'Mix'. */
			handle->ifaceAirFlaps.defrostLeftSet = 50;
			handle->ifaceAirFlaps.defrostRightSet = 50;
			handle->ifaceAirFlaps.ventLeftSet = 0;
			handle->ifaceAirFlaps.ventRightSet = 0;
			handle->ifaceAirFlaps.floorLeftSet = 50;
			handle->ifaceAirFlaps.floorRightSet = 50;
			handle->ifaceHMI.levelState = 3;
			handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Manual__region0_Mix;
			handle->stateConfVectorPosition = 0;
			handle->historyVector[1] = handle->stateConfVector[0];
			break;
		}
		default: break;
	}
}

/* shallow enterSequence with history in child ac */
static void modeCoordinator_shenseq_SequenceImpl(ModeCoordinator* handle) {
	/* shallow enterSequence with history in child ac */
	/* Handle shallow history entry of ac */
	switch(handle->historyVector[ 2 ]) {
		case ModeCoordinator_ac_Aircondition_Disabled : {
			/* 'default' enter sequence for state Aircondition Disabled */
			handle->stateConfVector[2] = ModeCoordinator_ac_Aircondition_Disabled;
			handle->stateConfVectorPosition = 2;
			handle->historyVector[2] = handle->stateConfVector[2];
			break;
		}
		case ModeCoordinator_ac_Aircondition_Enabled : {
			/* 'default' enter sequence for state Aircondition Enabled */
			handle->stateConfVector[2] = ModeCoordinator_ac_Aircondition_Enabled;
			handle->stateConfVectorPosition = 2;
			handle->historyVector[2] = handle->stateConfVector[2];
			break;
		}
		default: break;
	}
}

/* shallow enterSequence with history in child recirc */
static void modeCoordinator_shenseq_ExecutionFlowImpl_SequenceImpl(ModeCoordinator* handle) {
	/* shallow enterSequence with history in child recirc */
	/* Handle shallow history entry of recirc */
	switch(handle->historyVector[ 3 ]) {
		case ModeCoordinator_recirc_Recirc_Disabled : {
			/* 'default' enter sequence for state Recirc Disabled */
			/* Entry action for state 'Recirc Disabled'. */
			handle->ifaceAirFlaps.recircSet = 0;
			handle->stateConfVector[3] = ModeCoordinator_recirc_Recirc_Disabled;
			handle->stateConfVectorPosition = 3;
			handle->historyVector[3] = handle->stateConfVector[3];
			break;
		}
		case ModeCoordinator_recirc_Recirc_Enabled : {
			/* 'default' enter sequence for state Recirc Enabled */
			/* Entry action for state 'Recirc Enabled'. */
			handle->ifaceAirFlaps.recircSet = 100;
			handle->stateConfVector[3] = ModeCoordinator_recirc_Recirc_Enabled;
			handle->stateConfVectorPosition = 3;
			handle->historyVector[3] = handle->stateConfVector[3];
			break;
		}
		default: break;
	}
}

/* The reactions of state Off. */
static void modeCoordinator_react_modeProcessing_Off(ModeCoordinator* handle) {
	/* The reactions of state Off. */
	if ((handle->ifaceHMI.ComToggle_raised) && handle->ifaceHMI.levelSwitch != 0) { 
		/* Default exit sequence for state Off */
		handle->stateConfVector[0] = ModeCoordinator_last_state;
		handle->stateConfVectorPosition = 0;
		/* The reactions of state null. */
		if (handle->ifaceHMI.levelSwitch == 7) { 
			/* 'default' enter sequence for state On */
			/* Entry action for state 'On'. */
			handle->ifaceTemperature.on_raised = bool_true;
			/* 'default' enter sequence for region null */
			/* Default react sequence for deep history entry  */
			/* Enter the region with deep history */
			if (handle->historyVector[0] != ModeCoordinator_last_state) {
				modeCoordinator_dhenseq_SequenceImpl(handle);
			} else {
				/* 'default' enter sequence for state Auto */
				/* Entry action for state 'Auto'. */
				handle->ifaceBlower.auto_raised = bool_true;
				handle->ifaceTemperature.AC_State = bool_true;
				handle->ifaceAirFlaps.recircState = bool_false;
				handle->ifaceHMI.levelState = 4;
				handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Auto;
				handle->stateConfVectorPosition = 0;
				handle->historyVector[0] = handle->stateConfVector[0];
			} 
		}  else {
			/* Entry action for state 'On'. */
			handle->ifaceTemperature.on_raised = bool_true;
			/* The reactions of state null. */
			if (handle->ifaceHMI.levelSwitch == 4) { 
				/* 'default' enter sequence for state Auto */
				/* Entry action for state 'Auto'. */
				handle->ifaceBlower.auto_raised = bool_true;
				handle->ifaceTemperature.AC_State = bool_true;
				handle->ifaceAirFlaps.recircState = bool_false;
				handle->ifaceHMI.levelState = 4;
				handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Auto;
				handle->stateConfVectorPosition = 0;
				handle->historyVector[0] = handle->stateConfVector[0];
			}  else {
				if (handle->ifaceHMI.levelSwitch == 1) { 
					/* 'default' enter sequence for state Defrost */
					/* Entry action for state 'Defrost'. */
					handle->ifaceBlower.manual_raised = bool_true;
					handle->ifaceBlower.power = 80;
					handle->ifaceTemperature.AC_State = bool_true;
					handle->ifaceAirFlaps.recircState = bool_false;
					handle->ifaceAirFlaps.defrostLeftSet = 100;
					handle->ifaceAirFlaps.defrostRightSet = 100;
					handle->ifaceAirFlaps.ventLeftSet = 0;
					handle->ifaceAirFlaps.ventRightSet = 0;
					handle->ifaceAirFlaps.floorLeftSet = 0;
					handle->ifaceAirFlaps.floorRightSet = 0;
					handle->ifaceHMI.levelState = 1;
					handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Defrost;
					handle->stateConfVectorPosition = 0;
					handle->historyVector[0] = handle->stateConfVector[0];
				}  else {
					/* Entry action for state 'Manual'. */
					handle->ifaceBlower.manual_raised = bool_true;
					/* The reactions of state null. */
					if (handle->ifaceHMI.levelSwitch == 2) { 
						/* 'default' enter sequence for state Vent */
						/* Entry action for state 'Vent'. */
						handle->ifaceAirFlaps.defrostLeftSet = 0;
						handle->ifaceAirFlaps.defrostRightSet = 0;
						handle->ifaceAirFlaps.ventLeftSet = 100;
						handle->ifaceAirFlaps.ventRightSet = 100;
						handle->ifaceAirFlaps.floorLeftSet = 0;
						handle->ifaceAirFlaps.floorRightSet = 0;
						handle->ifaceHMI.levelState = 2;
						handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Manual__region0_Vent;
						handle->stateConfVectorPosition = 0;
						handle->historyVector[1] = handle->stateConfVector[0];
					}  else {
						if (handle->ifaceHMI.levelSwitch == 5) { 
							/* 'default' enter sequence for state BiLevel */
							/* Entry action for state 'BiLevel'. */
							handle->ifaceAirFlaps.defrostLeftSet = 0;
							handle->ifaceAirFlaps.defrostRightSet = 0;
							handle->ifaceAirFlaps.ventLeftSet = 50;
							handle->ifaceAirFlaps.ventRightSet = 50;
							handle->ifaceAirFlaps.floorLeftSet = 50;
							handle->ifaceAirFlaps.floorRightSet = 50;
							handle->ifaceHMI.levelState = 5;
							handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Manual__region0_BiLevel;
							handle->stateConfVectorPosition = 0;
							handle->historyVector[1] = handle->stateConfVector[0];
						}  else {
							if (handle->ifaceHMI.levelSwitch == 6) { 
								/* 'default' enter sequence for state Floor */
								/* Entry action for state 'Floor'. */
								handle->ifaceAirFlaps.defrostLeftSet = 0;
								handle->ifaceAirFlaps.defrostRightSet = 0;
								handle->ifaceAirFlaps.ventLeftSet = 0;
								handle->ifaceAirFlaps.ventRightSet = 0;
								handle->ifaceAirFlaps.floorLeftSet = 100;
								handle->ifaceAirFlaps.floorRightSet = 100;
								handle->ifaceHMI.levelState = 6;
								handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Manual__region0_Floor;
								handle->stateConfVectorPosition = 0;
								handle->historyVector[1] = handle->stateConfVector[0];
							}  else {
								/* 'default' enter sequence for state Mix */
								/* Entry action for state 'Mix'. */
								handle->ifaceAirFlaps.defrostLeftSet = 50;
								handle->ifaceAirFlaps.defrostRightSet = 50;
								handle->ifaceAirFlaps.ventLeftSet = 0;
								handle->ifaceAirFlaps.ventRightSet = 0;
								handle->ifaceAirFlaps.floorLeftSet = 50;
								handle->ifaceAirFlaps.floorRightSet = 50;
								handle->ifaceHMI.levelState = 3;
								handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Manual__region0_Mix;
								handle->stateConfVectorPosition = 0;
								handle->historyVector[1] = handle->stateConfVector[0];
							}
						}
					}
					handle->historyVector[0] = handle->stateConfVector[0];
				}
			}
		}
	} 
}

/* The reactions of state Defrost. */
static void modeCoordinator_react_modeProcessing_On__region0_Defrost(ModeCoordinator* handle) {
	/* The reactions of state Defrost. */
	if ((handle->ifaceHMI.ComToggle_raised) && handle->ifaceHMI.levelSwitch == 7) { 
		/* Default exit sequence for state On */
		/* Default exit sequence for region null */
		/* Handle exit of all possible states (of region0) at position 0... */
		switch(handle->stateConfVector[ 0 ]) {
			case ModeCoordinator_modeProcessing_On__region0_Defrost : {
				/* Default exit sequence for state Defrost */
				handle->stateConfVector[0] = ModeCoordinator_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case ModeCoordinator_modeProcessing_On__region0_Auto : {
				/* Default exit sequence for state Auto */
				handle->stateConfVector[0] = ModeCoordinator_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Floor : {
				/* Default exit sequence for state Floor */
				handle->stateConfVector[0] = ModeCoordinator_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case ModeCoordinator_modeProcessing_On__region0_Manual__region0_BiLevel : {
				/* Default exit sequence for state BiLevel */
				handle->stateConfVector[0] = ModeCoordinator_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Vent : {
				/* Default exit sequence for state Vent */
				handle->stateConfVector[0] = ModeCoordinator_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Mix : {
				/* Default exit sequence for state Mix */
				handle->stateConfVector[0] = ModeCoordinator_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			default: break;
		}
		/* 'default' enter sequence for state Off */
		/* Entry action for state 'Off'. */
		handle->ifaceTemperature.off_raised = bool_true;
		handle->internal.blwOff_raised = bool_true;
		handle->ifaceBlower.manual_raised = bool_true;
		handle->ifaceAirFlaps.recircState = bool_false;
		handle->ifaceTemperature.AC_State = bool_false;
		handle->ifaceHMI.levelState = 7;
		handle->stateConfVector[0] = ModeCoordinator_modeProcessing_Off;
		handle->stateConfVectorPosition = 0;
	}  else {
		if ((handle->ifaceHMI.ComToggle_raised) && handle->ifaceHMI.AC_Switch) { 
			handle->ifaceTemperature.AC_State = ! handle->ifaceTemperature.AC_State;
		} 
		if ((handle->ifaceHMI.ComToggle_raised) && handle->ifaceHMI.recircSwitch) { 
			handle->ifaceAirFlaps.recircState = ! handle->ifaceAirFlaps.recircState;
		} 
		if ((handle->ifaceHMI.ComToggle_raised) && handle->ifaceHMI.levelSwitch == 1) { 
			/* Default exit sequence for state Defrost */
			handle->stateConfVector[0] = ModeCoordinator_last_state;
			handle->stateConfVectorPosition = 0;
			/* Default react sequence for deep history entry  */
			/* Enter the region with deep history */
			if (handle->historyVector[0] != ModeCoordinator_last_state) {
				modeCoordinator_dhenseq_SequenceImpl(handle);
			} else {
				/* 'default' enter sequence for state Auto */
				/* Entry action for state 'Auto'. */
				handle->ifaceBlower.auto_raised = bool_true;
				handle->ifaceTemperature.AC_State = bool_true;
				handle->ifaceAirFlaps.recircState = bool_false;
				handle->ifaceHMI.levelState = 4;
				handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Auto;
				handle->stateConfVectorPosition = 0;
				handle->historyVector[0] = handle->stateConfVector[0];
			} 
		}  else {
			if ((handle->ifaceHMI.ComToggle_raised) && handle->ifaceHMI.levelSwitch != 0) { 
				/* Default exit sequence for state Defrost */
				handle->stateConfVector[0] = ModeCoordinator_last_state;
				handle->stateConfVectorPosition = 0;
				/* The reactions of state null. */
				if (handle->ifaceHMI.levelSwitch == 4) { 
					/* 'default' enter sequence for state Auto */
					/* Entry action for state 'Auto'. */
					handle->ifaceBlower.auto_raised = bool_true;
					handle->ifaceTemperature.AC_State = bool_true;
					handle->ifaceAirFlaps.recircState = bool_false;
					handle->ifaceHMI.levelState = 4;
					handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Auto;
					handle->stateConfVectorPosition = 0;
					handle->historyVector[0] = handle->stateConfVector[0];
				}  else {
					if (handle->ifaceHMI.levelSwitch == 1) { 
						/* 'default' enter sequence for state Defrost */
						/* Entry action for state 'Defrost'. */
						handle->ifaceBlower.manual_raised = bool_true;
						handle->ifaceBlower.power = 80;
						handle->ifaceTemperature.AC_State = bool_true;
						handle->ifaceAirFlaps.recircState = bool_false;
						handle->ifaceAirFlaps.defrostLeftSet = 100;
						handle->ifaceAirFlaps.defrostRightSet = 100;
						handle->ifaceAirFlaps.ventLeftSet = 0;
						handle->ifaceAirFlaps.ventRightSet = 0;
						handle->ifaceAirFlaps.floorLeftSet = 0;
						handle->ifaceAirFlaps.floorRightSet = 0;
						handle->ifaceHMI.levelState = 1;
						handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Defrost;
						handle->stateConfVectorPosition = 0;
						handle->historyVector[0] = handle->stateConfVector[0];
					}  else {
						/* Entry action for state 'Manual'. */
						handle->ifaceBlower.manual_raised = bool_true;
						/* The reactions of state null. */
						if (handle->ifaceHMI.levelSwitch == 2) { 
							/* 'default' enter sequence for state Vent */
							/* Entry action for state 'Vent'. */
							handle->ifaceAirFlaps.defrostLeftSet = 0;
							handle->ifaceAirFlaps.defrostRightSet = 0;
							handle->ifaceAirFlaps.ventLeftSet = 100;
							handle->ifaceAirFlaps.ventRightSet = 100;
							handle->ifaceAirFlaps.floorLeftSet = 0;
							handle->ifaceAirFlaps.floorRightSet = 0;
							handle->ifaceHMI.levelState = 2;
							handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Manual__region0_Vent;
							handle->stateConfVectorPosition = 0;
							handle->historyVector[1] = handle->stateConfVector[0];
						}  else {
							if (handle->ifaceHMI.levelSwitch == 5) { 
								/* 'default' enter sequence for state BiLevel */
								/* Entry action for state 'BiLevel'. */
								handle->ifaceAirFlaps.defrostLeftSet = 0;
								handle->ifaceAirFlaps.defrostRightSet = 0;
								handle->ifaceAirFlaps.ventLeftSet = 50;
								handle->ifaceAirFlaps.ventRightSet = 50;
								handle->ifaceAirFlaps.floorLeftSet = 50;
								handle->ifaceAirFlaps.floorRightSet = 50;
								handle->ifaceHMI.levelState = 5;
								handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Manual__region0_BiLevel;
								handle->stateConfVectorPosition = 0;
								handle->historyVector[1] = handle->stateConfVector[0];
							}  else {
								if (handle->ifaceHMI.levelSwitch == 6) { 
									/* 'default' enter sequence for state Floor */
									/* Entry action for state 'Floor'. */
									handle->ifaceAirFlaps.defrostLeftSet = 0;
									handle->ifaceAirFlaps.defrostRightSet = 0;
									handle->ifaceAirFlaps.ventLeftSet = 0;
									handle->ifaceAirFlaps.ventRightSet = 0;
									handle->ifaceAirFlaps.floorLeftSet = 100;
									handle->ifaceAirFlaps.floorRightSet = 100;
									handle->ifaceHMI.levelState = 6;
									handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Manual__region0_Floor;
									handle->stateConfVectorPosition = 0;
									handle->historyVector[1] = handle->stateConfVector[0];
								}  else {
									/* 'default' enter sequence for state Mix */
									/* Entry action for state 'Mix'. */
									handle->ifaceAirFlaps.defrostLeftSet = 50;
									handle->ifaceAirFlaps.defrostRightSet = 50;
									handle->ifaceAirFlaps.ventLeftSet = 0;
									handle->ifaceAirFlaps.ventRightSet = 0;
									handle->ifaceAirFlaps.floorLeftSet = 50;
									handle->ifaceAirFlaps.floorRightSet = 50;
									handle->ifaceHMI.levelState = 3;
									handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Manual__region0_Mix;
									handle->stateConfVectorPosition = 0;
									handle->historyVector[1] = handle->stateConfVector[0];
								}
							}
						}
						handle->historyVector[0] = handle->stateConfVector[0];
					}
				}
			} 
		}
	}
}

/* The reactions of state Auto. */
static void modeCoordinator_react_modeProcessing_On__region0_Auto(ModeCoordinator* handle) {
	/* The reactions of state Auto. */
	if ((handle->ifaceHMI.ComToggle_raised) && handle->ifaceHMI.levelSwitch == 7) { 
		/* Default exit sequence for state On */
		/* Default exit sequence for region null */
		/* Handle exit of all possible states (of region0) at position 0... */
		switch(handle->stateConfVector[ 0 ]) {
			case ModeCoordinator_modeProcessing_On__region0_Defrost : {
				/* Default exit sequence for state Defrost */
				handle->stateConfVector[0] = ModeCoordinator_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case ModeCoordinator_modeProcessing_On__region0_Auto : {
				/* Default exit sequence for state Auto */
				handle->stateConfVector[0] = ModeCoordinator_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Floor : {
				/* Default exit sequence for state Floor */
				handle->stateConfVector[0] = ModeCoordinator_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case ModeCoordinator_modeProcessing_On__region0_Manual__region0_BiLevel : {
				/* Default exit sequence for state BiLevel */
				handle->stateConfVector[0] = ModeCoordinator_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Vent : {
				/* Default exit sequence for state Vent */
				handle->stateConfVector[0] = ModeCoordinator_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Mix : {
				/* Default exit sequence for state Mix */
				handle->stateConfVector[0] = ModeCoordinator_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			default: break;
		}
		/* 'default' enter sequence for state Off */
		/* Entry action for state 'Off'. */
		handle->ifaceTemperature.off_raised = bool_true;
		handle->internal.blwOff_raised = bool_true;
		handle->ifaceBlower.manual_raised = bool_true;
		handle->ifaceAirFlaps.recircState = bool_false;
		handle->ifaceTemperature.AC_State = bool_false;
		handle->ifaceHMI.levelState = 7;
		handle->stateConfVector[0] = ModeCoordinator_modeProcessing_Off;
		handle->stateConfVectorPosition = 0;
	}  else {
		if ((handle->ifaceHMI.ComToggle_raised) && handle->ifaceHMI.AC_Switch) { 
			handle->ifaceTemperature.AC_State = ! handle->ifaceTemperature.AC_State;
		} 
		if ((handle->ifaceHMI.ComToggle_raised) && handle->ifaceHMI.recircSwitch) { 
			handle->ifaceAirFlaps.recircState = ! handle->ifaceAirFlaps.recircState;
		} 
		if ((handle->ifaceHMI.ComToggle_raised) && handle->ifaceHMI.levelSwitch == 4) { 
			/* Default exit sequence for state Auto */
			handle->stateConfVector[0] = ModeCoordinator_last_state;
			handle->stateConfVectorPosition = 0;
			/* Default react sequence for deep history entry  */
			/* Enter the region with deep history */
			if (handle->historyVector[0] != ModeCoordinator_last_state) {
				modeCoordinator_dhenseq_SequenceImpl(handle);
			} else {
				/* 'default' enter sequence for state Auto */
				/* Entry action for state 'Auto'. */
				handle->ifaceBlower.auto_raised = bool_true;
				handle->ifaceTemperature.AC_State = bool_true;
				handle->ifaceAirFlaps.recircState = bool_false;
				handle->ifaceHMI.levelState = 4;
				handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Auto;
				handle->stateConfVectorPosition = 0;
				handle->historyVector[0] = handle->stateConfVector[0];
			} 
		}  else {
			if ((handle->ifaceHMI.ComToggle_raised) && handle->ifaceHMI.levelSwitch != 0) { 
				/* Default exit sequence for state Auto */
				handle->stateConfVector[0] = ModeCoordinator_last_state;
				handle->stateConfVectorPosition = 0;
				/* The reactions of state null. */
				if (handle->ifaceHMI.levelSwitch == 4) { 
					/* 'default' enter sequence for state Auto */
					/* Entry action for state 'Auto'. */
					handle->ifaceBlower.auto_raised = bool_true;
					handle->ifaceTemperature.AC_State = bool_true;
					handle->ifaceAirFlaps.recircState = bool_false;
					handle->ifaceHMI.levelState = 4;
					handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Auto;
					handle->stateConfVectorPosition = 0;
					handle->historyVector[0] = handle->stateConfVector[0];
				}  else {
					if (handle->ifaceHMI.levelSwitch == 1) { 
						/* 'default' enter sequence for state Defrost */
						/* Entry action for state 'Defrost'. */
						handle->ifaceBlower.manual_raised = bool_true;
						handle->ifaceBlower.power = 80;
						handle->ifaceTemperature.AC_State = bool_true;
						handle->ifaceAirFlaps.recircState = bool_false;
						handle->ifaceAirFlaps.defrostLeftSet = 100;
						handle->ifaceAirFlaps.defrostRightSet = 100;
						handle->ifaceAirFlaps.ventLeftSet = 0;
						handle->ifaceAirFlaps.ventRightSet = 0;
						handle->ifaceAirFlaps.floorLeftSet = 0;
						handle->ifaceAirFlaps.floorRightSet = 0;
						handle->ifaceHMI.levelState = 1;
						handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Defrost;
						handle->stateConfVectorPosition = 0;
						handle->historyVector[0] = handle->stateConfVector[0];
					}  else {
						/* Entry action for state 'Manual'. */
						handle->ifaceBlower.manual_raised = bool_true;
						/* The reactions of state null. */
						if (handle->ifaceHMI.levelSwitch == 2) { 
							/* 'default' enter sequence for state Vent */
							/* Entry action for state 'Vent'. */
							handle->ifaceAirFlaps.defrostLeftSet = 0;
							handle->ifaceAirFlaps.defrostRightSet = 0;
							handle->ifaceAirFlaps.ventLeftSet = 100;
							handle->ifaceAirFlaps.ventRightSet = 100;
							handle->ifaceAirFlaps.floorLeftSet = 0;
							handle->ifaceAirFlaps.floorRightSet = 0;
							handle->ifaceHMI.levelState = 2;
							handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Manual__region0_Vent;
							handle->stateConfVectorPosition = 0;
							handle->historyVector[1] = handle->stateConfVector[0];
						}  else {
							if (handle->ifaceHMI.levelSwitch == 5) { 
								/* 'default' enter sequence for state BiLevel */
								/* Entry action for state 'BiLevel'. */
								handle->ifaceAirFlaps.defrostLeftSet = 0;
								handle->ifaceAirFlaps.defrostRightSet = 0;
								handle->ifaceAirFlaps.ventLeftSet = 50;
								handle->ifaceAirFlaps.ventRightSet = 50;
								handle->ifaceAirFlaps.floorLeftSet = 50;
								handle->ifaceAirFlaps.floorRightSet = 50;
								handle->ifaceHMI.levelState = 5;
								handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Manual__region0_BiLevel;
								handle->stateConfVectorPosition = 0;
								handle->historyVector[1] = handle->stateConfVector[0];
							}  else {
								if (handle->ifaceHMI.levelSwitch == 6) { 
									/* 'default' enter sequence for state Floor */
									/* Entry action for state 'Floor'. */
									handle->ifaceAirFlaps.defrostLeftSet = 0;
									handle->ifaceAirFlaps.defrostRightSet = 0;
									handle->ifaceAirFlaps.ventLeftSet = 0;
									handle->ifaceAirFlaps.ventRightSet = 0;
									handle->ifaceAirFlaps.floorLeftSet = 100;
									handle->ifaceAirFlaps.floorRightSet = 100;
									handle->ifaceHMI.levelState = 6;
									handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Manual__region0_Floor;
									handle->stateConfVectorPosition = 0;
									handle->historyVector[1] = handle->stateConfVector[0];
								}  else {
									/* 'default' enter sequence for state Mix */
									/* Entry action for state 'Mix'. */
									handle->ifaceAirFlaps.defrostLeftSet = 50;
									handle->ifaceAirFlaps.defrostRightSet = 50;
									handle->ifaceAirFlaps.ventLeftSet = 0;
									handle->ifaceAirFlaps.ventRightSet = 0;
									handle->ifaceAirFlaps.floorLeftSet = 50;
									handle->ifaceAirFlaps.floorRightSet = 50;
									handle->ifaceHMI.levelState = 3;
									handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Manual__region0_Mix;
									handle->stateConfVectorPosition = 0;
									handle->historyVector[1] = handle->stateConfVector[0];
								}
							}
						}
						handle->historyVector[0] = handle->stateConfVector[0];
					}
				}
			}  else {
				handle->ifaceBlower.power = handle->ifaceBlower.autoPower;
			}
		}
	}
}

/* The reactions of state Floor. */
static void modeCoordinator_react_modeProcessing_On__region0_Manual__region0_Floor(ModeCoordinator* handle) {
	/* The reactions of state Floor. */
	if ((handle->ifaceHMI.ComToggle_raised) && handle->ifaceHMI.levelSwitch == 7) { 
		/* Default exit sequence for state On */
		/* Default exit sequence for region null */
		/* Handle exit of all possible states (of region0) at position 0... */
		switch(handle->stateConfVector[ 0 ]) {
			case ModeCoordinator_modeProcessing_On__region0_Defrost : {
				/* Default exit sequence for state Defrost */
				handle->stateConfVector[0] = ModeCoordinator_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case ModeCoordinator_modeProcessing_On__region0_Auto : {
				/* Default exit sequence for state Auto */
				handle->stateConfVector[0] = ModeCoordinator_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Floor : {
				/* Default exit sequence for state Floor */
				handle->stateConfVector[0] = ModeCoordinator_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case ModeCoordinator_modeProcessing_On__region0_Manual__region0_BiLevel : {
				/* Default exit sequence for state BiLevel */
				handle->stateConfVector[0] = ModeCoordinator_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Vent : {
				/* Default exit sequence for state Vent */
				handle->stateConfVector[0] = ModeCoordinator_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Mix : {
				/* Default exit sequence for state Mix */
				handle->stateConfVector[0] = ModeCoordinator_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			default: break;
		}
		/* 'default' enter sequence for state Off */
		/* Entry action for state 'Off'. */
		handle->ifaceTemperature.off_raised = bool_true;
		handle->internal.blwOff_raised = bool_true;
		handle->ifaceBlower.manual_raised = bool_true;
		handle->ifaceAirFlaps.recircState = bool_false;
		handle->ifaceTemperature.AC_State = bool_false;
		handle->ifaceHMI.levelState = 7;
		handle->stateConfVector[0] = ModeCoordinator_modeProcessing_Off;
		handle->stateConfVectorPosition = 0;
	}  else {
		if ((handle->ifaceHMI.ComToggle_raised) && handle->ifaceHMI.AC_Switch) { 
			handle->ifaceTemperature.AC_State = ! handle->ifaceTemperature.AC_State;
		} 
		if ((handle->ifaceHMI.ComToggle_raised) && handle->ifaceHMI.recircSwitch) { 
			handle->ifaceAirFlaps.recircState = ! handle->ifaceAirFlaps.recircState;
		} 
		if ((handle->ifaceHMI.ComToggle_raised) && handle->ifaceHMI.levelSwitch == 4) { 
			/* Default exit sequence for state Manual */
			/* Default exit sequence for region null */
			/* Handle exit of all possible states (of region0) at position 0... */
			switch(handle->stateConfVector[ 0 ]) {
				case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Floor : {
					/* Default exit sequence for state Floor */
					handle->stateConfVector[0] = ModeCoordinator_last_state;
					handle->stateConfVectorPosition = 0;
					break;
				}
				case ModeCoordinator_modeProcessing_On__region0_Manual__region0_BiLevel : {
					/* Default exit sequence for state BiLevel */
					handle->stateConfVector[0] = ModeCoordinator_last_state;
					handle->stateConfVectorPosition = 0;
					break;
				}
				case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Vent : {
					/* Default exit sequence for state Vent */
					handle->stateConfVector[0] = ModeCoordinator_last_state;
					handle->stateConfVectorPosition = 0;
					break;
				}
				case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Mix : {
					/* Default exit sequence for state Mix */
					handle->stateConfVector[0] = ModeCoordinator_last_state;
					handle->stateConfVectorPosition = 0;
					break;
				}
				default: break;
			}
			/* 'default' enter sequence for state Auto */
			/* Entry action for state 'Auto'. */
			handle->ifaceBlower.auto_raised = bool_true;
			handle->ifaceTemperature.AC_State = bool_true;
			handle->ifaceAirFlaps.recircState = bool_false;
			handle->ifaceHMI.levelState = 4;
			handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Auto;
			handle->stateConfVectorPosition = 0;
			handle->historyVector[0] = handle->stateConfVector[0];
		}  else {
			if ((handle->ifaceHMI.ComToggle_raised) && handle->ifaceHMI.levelSwitch == 1) { 
				/* Default exit sequence for state Manual */
				/* Default exit sequence for region null */
				/* Handle exit of all possible states (of region0) at position 0... */
				switch(handle->stateConfVector[ 0 ]) {
					case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Floor : {
						/* Default exit sequence for state Floor */
						handle->stateConfVector[0] = ModeCoordinator_last_state;
						handle->stateConfVectorPosition = 0;
						break;
					}
					case ModeCoordinator_modeProcessing_On__region0_Manual__region0_BiLevel : {
						/* Default exit sequence for state BiLevel */
						handle->stateConfVector[0] = ModeCoordinator_last_state;
						handle->stateConfVectorPosition = 0;
						break;
					}
					case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Vent : {
						/* Default exit sequence for state Vent */
						handle->stateConfVector[0] = ModeCoordinator_last_state;
						handle->stateConfVectorPosition = 0;
						break;
					}
					case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Mix : {
						/* Default exit sequence for state Mix */
						handle->stateConfVector[0] = ModeCoordinator_last_state;
						handle->stateConfVectorPosition = 0;
						break;
					}
					default: break;
				}
				/* 'default' enter sequence for state Defrost */
				/* Entry action for state 'Defrost'. */
				handle->ifaceBlower.manual_raised = bool_true;
				handle->ifaceBlower.power = 80;
				handle->ifaceTemperature.AC_State = bool_true;
				handle->ifaceAirFlaps.recircState = bool_false;
				handle->ifaceAirFlaps.defrostLeftSet = 100;
				handle->ifaceAirFlaps.defrostRightSet = 100;
				handle->ifaceAirFlaps.ventLeftSet = 0;
				handle->ifaceAirFlaps.ventRightSet = 0;
				handle->ifaceAirFlaps.floorLeftSet = 0;
				handle->ifaceAirFlaps.floorRightSet = 0;
				handle->ifaceHMI.levelState = 1;
				handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Defrost;
				handle->stateConfVectorPosition = 0;
				handle->historyVector[0] = handle->stateConfVector[0];
			}  else {
				if ((handle->ifaceHMI.ComToggle_raised) && handle->ifaceHMI.levelSwitch == 6) { 
					/* Default exit sequence for state Floor */
					handle->stateConfVector[0] = ModeCoordinator_last_state;
					handle->stateConfVectorPosition = 0;
					/* The reactions of exit history. */
					/* Default exit sequence for state Manual */
					/* Default exit sequence for region null */
					/* Handle exit of all possible states (of region0) at position 0... */
					switch(handle->stateConfVector[ 0 ]) {
						case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Floor : {
							/* Default exit sequence for state Floor */
							handle->stateConfVector[0] = ModeCoordinator_last_state;
							handle->stateConfVectorPosition = 0;
							break;
						}
						case ModeCoordinator_modeProcessing_On__region0_Manual__region0_BiLevel : {
							/* Default exit sequence for state BiLevel */
							handle->stateConfVector[0] = ModeCoordinator_last_state;
							handle->stateConfVectorPosition = 0;
							break;
						}
						case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Vent : {
							/* Default exit sequence for state Vent */
							handle->stateConfVector[0] = ModeCoordinator_last_state;
							handle->stateConfVectorPosition = 0;
							break;
						}
						case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Mix : {
							/* Default exit sequence for state Mix */
							handle->stateConfVector[0] = ModeCoordinator_last_state;
							handle->stateConfVectorPosition = 0;
							break;
						}
						default: break;
					}
					/* Default react sequence for deep history entry  */
					/* Enter the region with deep history */
					if (handle->historyVector[0] != ModeCoordinator_last_state) {
						modeCoordinator_dhenseq_SequenceImpl(handle);
					} else {
						/* 'default' enter sequence for state Auto */
						/* Entry action for state 'Auto'. */
						handle->ifaceBlower.auto_raised = bool_true;
						handle->ifaceTemperature.AC_State = bool_true;
						handle->ifaceAirFlaps.recircState = bool_false;
						handle->ifaceHMI.levelState = 4;
						handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Auto;
						handle->stateConfVectorPosition = 0;
						handle->historyVector[0] = handle->stateConfVector[0];
					} 
				}  else {
					if ((handle->ifaceHMI.ComToggle_raised) && handle->ifaceHMI.levelSwitch != 0) { 
						/* Default exit sequence for state Floor */
						handle->stateConfVector[0] = ModeCoordinator_last_state;
						handle->stateConfVectorPosition = 0;
						/* The reactions of state null. */
						if (handle->ifaceHMI.levelSwitch == 2) { 
							/* 'default' enter sequence for state Vent */
							/* Entry action for state 'Vent'. */
							handle->ifaceAirFlaps.defrostLeftSet = 0;
							handle->ifaceAirFlaps.defrostRightSet = 0;
							handle->ifaceAirFlaps.ventLeftSet = 100;
							handle->ifaceAirFlaps.ventRightSet = 100;
							handle->ifaceAirFlaps.floorLeftSet = 0;
							handle->ifaceAirFlaps.floorRightSet = 0;
							handle->ifaceHMI.levelState = 2;
							handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Manual__region0_Vent;
							handle->stateConfVectorPosition = 0;
							handle->historyVector[1] = handle->stateConfVector[0];
						}  else {
							if (handle->ifaceHMI.levelSwitch == 5) { 
								/* 'default' enter sequence for state BiLevel */
								/* Entry action for state 'BiLevel'. */
								handle->ifaceAirFlaps.defrostLeftSet = 0;
								handle->ifaceAirFlaps.defrostRightSet = 0;
								handle->ifaceAirFlaps.ventLeftSet = 50;
								handle->ifaceAirFlaps.ventRightSet = 50;
								handle->ifaceAirFlaps.floorLeftSet = 50;
								handle->ifaceAirFlaps.floorRightSet = 50;
								handle->ifaceHMI.levelState = 5;
								handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Manual__region0_BiLevel;
								handle->stateConfVectorPosition = 0;
								handle->historyVector[1] = handle->stateConfVector[0];
							}  else {
								if (handle->ifaceHMI.levelSwitch == 6) { 
									/* 'default' enter sequence for state Floor */
									/* Entry action for state 'Floor'. */
									handle->ifaceAirFlaps.defrostLeftSet = 0;
									handle->ifaceAirFlaps.defrostRightSet = 0;
									handle->ifaceAirFlaps.ventLeftSet = 0;
									handle->ifaceAirFlaps.ventRightSet = 0;
									handle->ifaceAirFlaps.floorLeftSet = 100;
									handle->ifaceAirFlaps.floorRightSet = 100;
									handle->ifaceHMI.levelState = 6;
									handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Manual__region0_Floor;
									handle->stateConfVectorPosition = 0;
									handle->historyVector[1] = handle->stateConfVector[0];
								}  else {
									/* 'default' enter sequence for state Mix */
									/* Entry action for state 'Mix'. */
									handle->ifaceAirFlaps.defrostLeftSet = 50;
									handle->ifaceAirFlaps.defrostRightSet = 50;
									handle->ifaceAirFlaps.ventLeftSet = 0;
									handle->ifaceAirFlaps.ventRightSet = 0;
									handle->ifaceAirFlaps.floorLeftSet = 50;
									handle->ifaceAirFlaps.floorRightSet = 50;
									handle->ifaceHMI.levelState = 3;
									handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Manual__region0_Mix;
									handle->stateConfVectorPosition = 0;
									handle->historyVector[1] = handle->stateConfVector[0];
								}
							}
						}
					} 
				}
			}
		}
	}
}

/* The reactions of state BiLevel. */
static void modeCoordinator_react_modeProcessing_On__region0_Manual__region0_BiLevel(ModeCoordinator* handle) {
	/* The reactions of state BiLevel. */
	if ((handle->ifaceHMI.ComToggle_raised) && handle->ifaceHMI.levelSwitch == 7) { 
		/* Default exit sequence for state On */
		/* Default exit sequence for region null */
		/* Handle exit of all possible states (of region0) at position 0... */
		switch(handle->stateConfVector[ 0 ]) {
			case ModeCoordinator_modeProcessing_On__region0_Defrost : {
				/* Default exit sequence for state Defrost */
				handle->stateConfVector[0] = ModeCoordinator_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case ModeCoordinator_modeProcessing_On__region0_Auto : {
				/* Default exit sequence for state Auto */
				handle->stateConfVector[0] = ModeCoordinator_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Floor : {
				/* Default exit sequence for state Floor */
				handle->stateConfVector[0] = ModeCoordinator_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case ModeCoordinator_modeProcessing_On__region0_Manual__region0_BiLevel : {
				/* Default exit sequence for state BiLevel */
				handle->stateConfVector[0] = ModeCoordinator_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Vent : {
				/* Default exit sequence for state Vent */
				handle->stateConfVector[0] = ModeCoordinator_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Mix : {
				/* Default exit sequence for state Mix */
				handle->stateConfVector[0] = ModeCoordinator_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			default: break;
		}
		/* 'default' enter sequence for state Off */
		/* Entry action for state 'Off'. */
		handle->ifaceTemperature.off_raised = bool_true;
		handle->internal.blwOff_raised = bool_true;
		handle->ifaceBlower.manual_raised = bool_true;
		handle->ifaceAirFlaps.recircState = bool_false;
		handle->ifaceTemperature.AC_State = bool_false;
		handle->ifaceHMI.levelState = 7;
		handle->stateConfVector[0] = ModeCoordinator_modeProcessing_Off;
		handle->stateConfVectorPosition = 0;
	}  else {
		if ((handle->ifaceHMI.ComToggle_raised) && handle->ifaceHMI.AC_Switch) { 
			handle->ifaceTemperature.AC_State = ! handle->ifaceTemperature.AC_State;
		} 
		if ((handle->ifaceHMI.ComToggle_raised) && handle->ifaceHMI.recircSwitch) { 
			handle->ifaceAirFlaps.recircState = ! handle->ifaceAirFlaps.recircState;
		} 
		if ((handle->ifaceHMI.ComToggle_raised) && handle->ifaceHMI.levelSwitch == 4) { 
			/* Default exit sequence for state Manual */
			/* Default exit sequence for region null */
			/* Handle exit of all possible states (of region0) at position 0... */
			switch(handle->stateConfVector[ 0 ]) {
				case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Floor : {
					/* Default exit sequence for state Floor */
					handle->stateConfVector[0] = ModeCoordinator_last_state;
					handle->stateConfVectorPosition = 0;
					break;
				}
				case ModeCoordinator_modeProcessing_On__region0_Manual__region0_BiLevel : {
					/* Default exit sequence for state BiLevel */
					handle->stateConfVector[0] = ModeCoordinator_last_state;
					handle->stateConfVectorPosition = 0;
					break;
				}
				case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Vent : {
					/* Default exit sequence for state Vent */
					handle->stateConfVector[0] = ModeCoordinator_last_state;
					handle->stateConfVectorPosition = 0;
					break;
				}
				case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Mix : {
					/* Default exit sequence for state Mix */
					handle->stateConfVector[0] = ModeCoordinator_last_state;
					handle->stateConfVectorPosition = 0;
					break;
				}
				default: break;
			}
			/* 'default' enter sequence for state Auto */
			/* Entry action for state 'Auto'. */
			handle->ifaceBlower.auto_raised = bool_true;
			handle->ifaceTemperature.AC_State = bool_true;
			handle->ifaceAirFlaps.recircState = bool_false;
			handle->ifaceHMI.levelState = 4;
			handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Auto;
			handle->stateConfVectorPosition = 0;
			handle->historyVector[0] = handle->stateConfVector[0];
		}  else {
			if ((handle->ifaceHMI.ComToggle_raised) && handle->ifaceHMI.levelSwitch == 1) { 
				/* Default exit sequence for state Manual */
				/* Default exit sequence for region null */
				/* Handle exit of all possible states (of region0) at position 0... */
				switch(handle->stateConfVector[ 0 ]) {
					case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Floor : {
						/* Default exit sequence for state Floor */
						handle->stateConfVector[0] = ModeCoordinator_last_state;
						handle->stateConfVectorPosition = 0;
						break;
					}
					case ModeCoordinator_modeProcessing_On__region0_Manual__region0_BiLevel : {
						/* Default exit sequence for state BiLevel */
						handle->stateConfVector[0] = ModeCoordinator_last_state;
						handle->stateConfVectorPosition = 0;
						break;
					}
					case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Vent : {
						/* Default exit sequence for state Vent */
						handle->stateConfVector[0] = ModeCoordinator_last_state;
						handle->stateConfVectorPosition = 0;
						break;
					}
					case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Mix : {
						/* Default exit sequence for state Mix */
						handle->stateConfVector[0] = ModeCoordinator_last_state;
						handle->stateConfVectorPosition = 0;
						break;
					}
					default: break;
				}
				/* 'default' enter sequence for state Defrost */
				/* Entry action for state 'Defrost'. */
				handle->ifaceBlower.manual_raised = bool_true;
				handle->ifaceBlower.power = 80;
				handle->ifaceTemperature.AC_State = bool_true;
				handle->ifaceAirFlaps.recircState = bool_false;
				handle->ifaceAirFlaps.defrostLeftSet = 100;
				handle->ifaceAirFlaps.defrostRightSet = 100;
				handle->ifaceAirFlaps.ventLeftSet = 0;
				handle->ifaceAirFlaps.ventRightSet = 0;
				handle->ifaceAirFlaps.floorLeftSet = 0;
				handle->ifaceAirFlaps.floorRightSet = 0;
				handle->ifaceHMI.levelState = 1;
				handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Defrost;
				handle->stateConfVectorPosition = 0;
				handle->historyVector[0] = handle->stateConfVector[0];
			}  else {
				if ((handle->ifaceHMI.ComToggle_raised) && handle->ifaceHMI.levelSwitch == 5) { 
					/* Default exit sequence for state BiLevel */
					handle->stateConfVector[0] = ModeCoordinator_last_state;
					handle->stateConfVectorPosition = 0;
					/* The reactions of exit history. */
					/* Default exit sequence for state Manual */
					/* Default exit sequence for region null */
					/* Handle exit of all possible states (of region0) at position 0... */
					switch(handle->stateConfVector[ 0 ]) {
						case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Floor : {
							/* Default exit sequence for state Floor */
							handle->stateConfVector[0] = ModeCoordinator_last_state;
							handle->stateConfVectorPosition = 0;
							break;
						}
						case ModeCoordinator_modeProcessing_On__region0_Manual__region0_BiLevel : {
							/* Default exit sequence for state BiLevel */
							handle->stateConfVector[0] = ModeCoordinator_last_state;
							handle->stateConfVectorPosition = 0;
							break;
						}
						case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Vent : {
							/* Default exit sequence for state Vent */
							handle->stateConfVector[0] = ModeCoordinator_last_state;
							handle->stateConfVectorPosition = 0;
							break;
						}
						case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Mix : {
							/* Default exit sequence for state Mix */
							handle->stateConfVector[0] = ModeCoordinator_last_state;
							handle->stateConfVectorPosition = 0;
							break;
						}
						default: break;
					}
					/* Default react sequence for deep history entry  */
					/* Enter the region with deep history */
					if (handle->historyVector[0] != ModeCoordinator_last_state) {
						modeCoordinator_dhenseq_SequenceImpl(handle);
					} else {
						/* 'default' enter sequence for state Auto */
						/* Entry action for state 'Auto'. */
						handle->ifaceBlower.auto_raised = bool_true;
						handle->ifaceTemperature.AC_State = bool_true;
						handle->ifaceAirFlaps.recircState = bool_false;
						handle->ifaceHMI.levelState = 4;
						handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Auto;
						handle->stateConfVectorPosition = 0;
						handle->historyVector[0] = handle->stateConfVector[0];
					} 
				}  else {
					if ((handle->ifaceHMI.ComToggle_raised) && handle->ifaceHMI.levelSwitch != 0) { 
						/* Default exit sequence for state BiLevel */
						handle->stateConfVector[0] = ModeCoordinator_last_state;
						handle->stateConfVectorPosition = 0;
						/* The reactions of state null. */
						if (handle->ifaceHMI.levelSwitch == 2) { 
							/* 'default' enter sequence for state Vent */
							/* Entry action for state 'Vent'. */
							handle->ifaceAirFlaps.defrostLeftSet = 0;
							handle->ifaceAirFlaps.defrostRightSet = 0;
							handle->ifaceAirFlaps.ventLeftSet = 100;
							handle->ifaceAirFlaps.ventRightSet = 100;
							handle->ifaceAirFlaps.floorLeftSet = 0;
							handle->ifaceAirFlaps.floorRightSet = 0;
							handle->ifaceHMI.levelState = 2;
							handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Manual__region0_Vent;
							handle->stateConfVectorPosition = 0;
							handle->historyVector[1] = handle->stateConfVector[0];
						}  else {
							if (handle->ifaceHMI.levelSwitch == 5) { 
								/* 'default' enter sequence for state BiLevel */
								/* Entry action for state 'BiLevel'. */
								handle->ifaceAirFlaps.defrostLeftSet = 0;
								handle->ifaceAirFlaps.defrostRightSet = 0;
								handle->ifaceAirFlaps.ventLeftSet = 50;
								handle->ifaceAirFlaps.ventRightSet = 50;
								handle->ifaceAirFlaps.floorLeftSet = 50;
								handle->ifaceAirFlaps.floorRightSet = 50;
								handle->ifaceHMI.levelState = 5;
								handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Manual__region0_BiLevel;
								handle->stateConfVectorPosition = 0;
								handle->historyVector[1] = handle->stateConfVector[0];
							}  else {
								if (handle->ifaceHMI.levelSwitch == 6) { 
									/* 'default' enter sequence for state Floor */
									/* Entry action for state 'Floor'. */
									handle->ifaceAirFlaps.defrostLeftSet = 0;
									handle->ifaceAirFlaps.defrostRightSet = 0;
									handle->ifaceAirFlaps.ventLeftSet = 0;
									handle->ifaceAirFlaps.ventRightSet = 0;
									handle->ifaceAirFlaps.floorLeftSet = 100;
									handle->ifaceAirFlaps.floorRightSet = 100;
									handle->ifaceHMI.levelState = 6;
									handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Manual__region0_Floor;
									handle->stateConfVectorPosition = 0;
									handle->historyVector[1] = handle->stateConfVector[0];
								}  else {
									/* 'default' enter sequence for state Mix */
									/* Entry action for state 'Mix'. */
									handle->ifaceAirFlaps.defrostLeftSet = 50;
									handle->ifaceAirFlaps.defrostRightSet = 50;
									handle->ifaceAirFlaps.ventLeftSet = 0;
									handle->ifaceAirFlaps.ventRightSet = 0;
									handle->ifaceAirFlaps.floorLeftSet = 50;
									handle->ifaceAirFlaps.floorRightSet = 50;
									handle->ifaceHMI.levelState = 3;
									handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Manual__region0_Mix;
									handle->stateConfVectorPosition = 0;
									handle->historyVector[1] = handle->stateConfVector[0];
								}
							}
						}
					} 
				}
			}
		}
	}
}

/* The reactions of state Vent. */
static void modeCoordinator_react_modeProcessing_On__region0_Manual__region0_Vent(ModeCoordinator* handle) {
	/* The reactions of state Vent. */
	if ((handle->ifaceHMI.ComToggle_raised) && handle->ifaceHMI.levelSwitch == 7) { 
		/* Default exit sequence for state On */
		/* Default exit sequence for region null */
		/* Handle exit of all possible states (of region0) at position 0... */
		switch(handle->stateConfVector[ 0 ]) {
			case ModeCoordinator_modeProcessing_On__region0_Defrost : {
				/* Default exit sequence for state Defrost */
				handle->stateConfVector[0] = ModeCoordinator_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case ModeCoordinator_modeProcessing_On__region0_Auto : {
				/* Default exit sequence for state Auto */
				handle->stateConfVector[0] = ModeCoordinator_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Floor : {
				/* Default exit sequence for state Floor */
				handle->stateConfVector[0] = ModeCoordinator_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case ModeCoordinator_modeProcessing_On__region0_Manual__region0_BiLevel : {
				/* Default exit sequence for state BiLevel */
				handle->stateConfVector[0] = ModeCoordinator_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Vent : {
				/* Default exit sequence for state Vent */
				handle->stateConfVector[0] = ModeCoordinator_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Mix : {
				/* Default exit sequence for state Mix */
				handle->stateConfVector[0] = ModeCoordinator_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			default: break;
		}
		/* 'default' enter sequence for state Off */
		/* Entry action for state 'Off'. */
		handle->ifaceTemperature.off_raised = bool_true;
		handle->internal.blwOff_raised = bool_true;
		handle->ifaceBlower.manual_raised = bool_true;
		handle->ifaceAirFlaps.recircState = bool_false;
		handle->ifaceTemperature.AC_State = bool_false;
		handle->ifaceHMI.levelState = 7;
		handle->stateConfVector[0] = ModeCoordinator_modeProcessing_Off;
		handle->stateConfVectorPosition = 0;
	}  else {
		if ((handle->ifaceHMI.ComToggle_raised) && handle->ifaceHMI.AC_Switch) { 
			handle->ifaceTemperature.AC_State = ! handle->ifaceTemperature.AC_State;
		} 
		if ((handle->ifaceHMI.ComToggle_raised) && handle->ifaceHMI.recircSwitch) { 
			handle->ifaceAirFlaps.recircState = ! handle->ifaceAirFlaps.recircState;
		} 
		if ((handle->ifaceHMI.ComToggle_raised) && handle->ifaceHMI.levelSwitch == 4) { 
			/* Default exit sequence for state Manual */
			/* Default exit sequence for region null */
			/* Handle exit of all possible states (of region0) at position 0... */
			switch(handle->stateConfVector[ 0 ]) {
				case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Floor : {
					/* Default exit sequence for state Floor */
					handle->stateConfVector[0] = ModeCoordinator_last_state;
					handle->stateConfVectorPosition = 0;
					break;
				}
				case ModeCoordinator_modeProcessing_On__region0_Manual__region0_BiLevel : {
					/* Default exit sequence for state BiLevel */
					handle->stateConfVector[0] = ModeCoordinator_last_state;
					handle->stateConfVectorPosition = 0;
					break;
				}
				case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Vent : {
					/* Default exit sequence for state Vent */
					handle->stateConfVector[0] = ModeCoordinator_last_state;
					handle->stateConfVectorPosition = 0;
					break;
				}
				case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Mix : {
					/* Default exit sequence for state Mix */
					handle->stateConfVector[0] = ModeCoordinator_last_state;
					handle->stateConfVectorPosition = 0;
					break;
				}
				default: break;
			}
			/* 'default' enter sequence for state Auto */
			/* Entry action for state 'Auto'. */
			handle->ifaceBlower.auto_raised = bool_true;
			handle->ifaceTemperature.AC_State = bool_true;
			handle->ifaceAirFlaps.recircState = bool_false;
			handle->ifaceHMI.levelState = 4;
			handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Auto;
			handle->stateConfVectorPosition = 0;
			handle->historyVector[0] = handle->stateConfVector[0];
		}  else {
			if ((handle->ifaceHMI.ComToggle_raised) && handle->ifaceHMI.levelSwitch == 1) { 
				/* Default exit sequence for state Manual */
				/* Default exit sequence for region null */
				/* Handle exit of all possible states (of region0) at position 0... */
				switch(handle->stateConfVector[ 0 ]) {
					case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Floor : {
						/* Default exit sequence for state Floor */
						handle->stateConfVector[0] = ModeCoordinator_last_state;
						handle->stateConfVectorPosition = 0;
						break;
					}
					case ModeCoordinator_modeProcessing_On__region0_Manual__region0_BiLevel : {
						/* Default exit sequence for state BiLevel */
						handle->stateConfVector[0] = ModeCoordinator_last_state;
						handle->stateConfVectorPosition = 0;
						break;
					}
					case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Vent : {
						/* Default exit sequence for state Vent */
						handle->stateConfVector[0] = ModeCoordinator_last_state;
						handle->stateConfVectorPosition = 0;
						break;
					}
					case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Mix : {
						/* Default exit sequence for state Mix */
						handle->stateConfVector[0] = ModeCoordinator_last_state;
						handle->stateConfVectorPosition = 0;
						break;
					}
					default: break;
				}
				/* 'default' enter sequence for state Defrost */
				/* Entry action for state 'Defrost'. */
				handle->ifaceBlower.manual_raised = bool_true;
				handle->ifaceBlower.power = 80;
				handle->ifaceTemperature.AC_State = bool_true;
				handle->ifaceAirFlaps.recircState = bool_false;
				handle->ifaceAirFlaps.defrostLeftSet = 100;
				handle->ifaceAirFlaps.defrostRightSet = 100;
				handle->ifaceAirFlaps.ventLeftSet = 0;
				handle->ifaceAirFlaps.ventRightSet = 0;
				handle->ifaceAirFlaps.floorLeftSet = 0;
				handle->ifaceAirFlaps.floorRightSet = 0;
				handle->ifaceHMI.levelState = 1;
				handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Defrost;
				handle->stateConfVectorPosition = 0;
				handle->historyVector[0] = handle->stateConfVector[0];
			}  else {
				if ((handle->ifaceHMI.ComToggle_raised) && handle->ifaceHMI.levelSwitch == 2) { 
					/* Default exit sequence for state Vent */
					handle->stateConfVector[0] = ModeCoordinator_last_state;
					handle->stateConfVectorPosition = 0;
					/* The reactions of exit history. */
					/* Default exit sequence for state Manual */
					/* Default exit sequence for region null */
					/* Handle exit of all possible states (of region0) at position 0... */
					switch(handle->stateConfVector[ 0 ]) {
						case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Floor : {
							/* Default exit sequence for state Floor */
							handle->stateConfVector[0] = ModeCoordinator_last_state;
							handle->stateConfVectorPosition = 0;
							break;
						}
						case ModeCoordinator_modeProcessing_On__region0_Manual__region0_BiLevel : {
							/* Default exit sequence for state BiLevel */
							handle->stateConfVector[0] = ModeCoordinator_last_state;
							handle->stateConfVectorPosition = 0;
							break;
						}
						case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Vent : {
							/* Default exit sequence for state Vent */
							handle->stateConfVector[0] = ModeCoordinator_last_state;
							handle->stateConfVectorPosition = 0;
							break;
						}
						case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Mix : {
							/* Default exit sequence for state Mix */
							handle->stateConfVector[0] = ModeCoordinator_last_state;
							handle->stateConfVectorPosition = 0;
							break;
						}
						default: break;
					}
					/* Default react sequence for deep history entry  */
					/* Enter the region with deep history */
					if (handle->historyVector[0] != ModeCoordinator_last_state) {
						modeCoordinator_dhenseq_SequenceImpl(handle);
					} else {
						/* 'default' enter sequence for state Auto */
						/* Entry action for state 'Auto'. */
						handle->ifaceBlower.auto_raised = bool_true;
						handle->ifaceTemperature.AC_State = bool_true;
						handle->ifaceAirFlaps.recircState = bool_false;
						handle->ifaceHMI.levelState = 4;
						handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Auto;
						handle->stateConfVectorPosition = 0;
						handle->historyVector[0] = handle->stateConfVector[0];
					} 
				}  else {
					if ((handle->ifaceHMI.ComToggle_raised) && handle->ifaceHMI.levelSwitch != 0) { 
						/* Default exit sequence for state Vent */
						handle->stateConfVector[0] = ModeCoordinator_last_state;
						handle->stateConfVectorPosition = 0;
						/* The reactions of state null. */
						if (handle->ifaceHMI.levelSwitch == 2) { 
							/* 'default' enter sequence for state Vent */
							/* Entry action for state 'Vent'. */
							handle->ifaceAirFlaps.defrostLeftSet = 0;
							handle->ifaceAirFlaps.defrostRightSet = 0;
							handle->ifaceAirFlaps.ventLeftSet = 100;
							handle->ifaceAirFlaps.ventRightSet = 100;
							handle->ifaceAirFlaps.floorLeftSet = 0;
							handle->ifaceAirFlaps.floorRightSet = 0;
							handle->ifaceHMI.levelState = 2;
							handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Manual__region0_Vent;
							handle->stateConfVectorPosition = 0;
							handle->historyVector[1] = handle->stateConfVector[0];
						}  else {
							if (handle->ifaceHMI.levelSwitch == 5) { 
								/* 'default' enter sequence for state BiLevel */
								/* Entry action for state 'BiLevel'. */
								handle->ifaceAirFlaps.defrostLeftSet = 0;
								handle->ifaceAirFlaps.defrostRightSet = 0;
								handle->ifaceAirFlaps.ventLeftSet = 50;
								handle->ifaceAirFlaps.ventRightSet = 50;
								handle->ifaceAirFlaps.floorLeftSet = 50;
								handle->ifaceAirFlaps.floorRightSet = 50;
								handle->ifaceHMI.levelState = 5;
								handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Manual__region0_BiLevel;
								handle->stateConfVectorPosition = 0;
								handle->historyVector[1] = handle->stateConfVector[0];
							}  else {
								if (handle->ifaceHMI.levelSwitch == 6) { 
									/* 'default' enter sequence for state Floor */
									/* Entry action for state 'Floor'. */
									handle->ifaceAirFlaps.defrostLeftSet = 0;
									handle->ifaceAirFlaps.defrostRightSet = 0;
									handle->ifaceAirFlaps.ventLeftSet = 0;
									handle->ifaceAirFlaps.ventRightSet = 0;
									handle->ifaceAirFlaps.floorLeftSet = 100;
									handle->ifaceAirFlaps.floorRightSet = 100;
									handle->ifaceHMI.levelState = 6;
									handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Manual__region0_Floor;
									handle->stateConfVectorPosition = 0;
									handle->historyVector[1] = handle->stateConfVector[0];
								}  else {
									/* 'default' enter sequence for state Mix */
									/* Entry action for state 'Mix'. */
									handle->ifaceAirFlaps.defrostLeftSet = 50;
									handle->ifaceAirFlaps.defrostRightSet = 50;
									handle->ifaceAirFlaps.ventLeftSet = 0;
									handle->ifaceAirFlaps.ventRightSet = 0;
									handle->ifaceAirFlaps.floorLeftSet = 50;
									handle->ifaceAirFlaps.floorRightSet = 50;
									handle->ifaceHMI.levelState = 3;
									handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Manual__region0_Mix;
									handle->stateConfVectorPosition = 0;
									handle->historyVector[1] = handle->stateConfVector[0];
								}
							}
						}
					} 
				}
			}
		}
	}
}

/* The reactions of state Mix. */
static void modeCoordinator_react_modeProcessing_On__region0_Manual__region0_Mix(ModeCoordinator* handle) {
	/* The reactions of state Mix. */
	if ((handle->ifaceHMI.ComToggle_raised) && handle->ifaceHMI.levelSwitch == 7) { 
		/* Default exit sequence for state On */
		/* Default exit sequence for region null */
		/* Handle exit of all possible states (of region0) at position 0... */
		switch(handle->stateConfVector[ 0 ]) {
			case ModeCoordinator_modeProcessing_On__region0_Defrost : {
				/* Default exit sequence for state Defrost */
				handle->stateConfVector[0] = ModeCoordinator_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case ModeCoordinator_modeProcessing_On__region0_Auto : {
				/* Default exit sequence for state Auto */
				handle->stateConfVector[0] = ModeCoordinator_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Floor : {
				/* Default exit sequence for state Floor */
				handle->stateConfVector[0] = ModeCoordinator_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case ModeCoordinator_modeProcessing_On__region0_Manual__region0_BiLevel : {
				/* Default exit sequence for state BiLevel */
				handle->stateConfVector[0] = ModeCoordinator_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Vent : {
				/* Default exit sequence for state Vent */
				handle->stateConfVector[0] = ModeCoordinator_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Mix : {
				/* Default exit sequence for state Mix */
				handle->stateConfVector[0] = ModeCoordinator_last_state;
				handle->stateConfVectorPosition = 0;
				break;
			}
			default: break;
		}
		/* 'default' enter sequence for state Off */
		/* Entry action for state 'Off'. */
		handle->ifaceTemperature.off_raised = bool_true;
		handle->internal.blwOff_raised = bool_true;
		handle->ifaceBlower.manual_raised = bool_true;
		handle->ifaceAirFlaps.recircState = bool_false;
		handle->ifaceTemperature.AC_State = bool_false;
		handle->ifaceHMI.levelState = 7;
		handle->stateConfVector[0] = ModeCoordinator_modeProcessing_Off;
		handle->stateConfVectorPosition = 0;
	}  else {
		if ((handle->ifaceHMI.ComToggle_raised) && handle->ifaceHMI.AC_Switch) { 
			handle->ifaceTemperature.AC_State = ! handle->ifaceTemperature.AC_State;
		} 
		if ((handle->ifaceHMI.ComToggle_raised) && handle->ifaceHMI.recircSwitch) { 
			handle->ifaceAirFlaps.recircState = ! handle->ifaceAirFlaps.recircState;
		} 
		if ((handle->ifaceHMI.ComToggle_raised) && handle->ifaceHMI.levelSwitch == 4) { 
			/* Default exit sequence for state Manual */
			/* Default exit sequence for region null */
			/* Handle exit of all possible states (of region0) at position 0... */
			switch(handle->stateConfVector[ 0 ]) {
				case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Floor : {
					/* Default exit sequence for state Floor */
					handle->stateConfVector[0] = ModeCoordinator_last_state;
					handle->stateConfVectorPosition = 0;
					break;
				}
				case ModeCoordinator_modeProcessing_On__region0_Manual__region0_BiLevel : {
					/* Default exit sequence for state BiLevel */
					handle->stateConfVector[0] = ModeCoordinator_last_state;
					handle->stateConfVectorPosition = 0;
					break;
				}
				case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Vent : {
					/* Default exit sequence for state Vent */
					handle->stateConfVector[0] = ModeCoordinator_last_state;
					handle->stateConfVectorPosition = 0;
					break;
				}
				case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Mix : {
					/* Default exit sequence for state Mix */
					handle->stateConfVector[0] = ModeCoordinator_last_state;
					handle->stateConfVectorPosition = 0;
					break;
				}
				default: break;
			}
			/* 'default' enter sequence for state Auto */
			/* Entry action for state 'Auto'. */
			handle->ifaceBlower.auto_raised = bool_true;
			handle->ifaceTemperature.AC_State = bool_true;
			handle->ifaceAirFlaps.recircState = bool_false;
			handle->ifaceHMI.levelState = 4;
			handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Auto;
			handle->stateConfVectorPosition = 0;
			handle->historyVector[0] = handle->stateConfVector[0];
		}  else {
			if ((handle->ifaceHMI.ComToggle_raised) && handle->ifaceHMI.levelSwitch == 1) { 
				/* Default exit sequence for state Manual */
				/* Default exit sequence for region null */
				/* Handle exit of all possible states (of region0) at position 0... */
				switch(handle->stateConfVector[ 0 ]) {
					case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Floor : {
						/* Default exit sequence for state Floor */
						handle->stateConfVector[0] = ModeCoordinator_last_state;
						handle->stateConfVectorPosition = 0;
						break;
					}
					case ModeCoordinator_modeProcessing_On__region0_Manual__region0_BiLevel : {
						/* Default exit sequence for state BiLevel */
						handle->stateConfVector[0] = ModeCoordinator_last_state;
						handle->stateConfVectorPosition = 0;
						break;
					}
					case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Vent : {
						/* Default exit sequence for state Vent */
						handle->stateConfVector[0] = ModeCoordinator_last_state;
						handle->stateConfVectorPosition = 0;
						break;
					}
					case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Mix : {
						/* Default exit sequence for state Mix */
						handle->stateConfVector[0] = ModeCoordinator_last_state;
						handle->stateConfVectorPosition = 0;
						break;
					}
					default: break;
				}
				/* 'default' enter sequence for state Defrost */
				/* Entry action for state 'Defrost'. */
				handle->ifaceBlower.manual_raised = bool_true;
				handle->ifaceBlower.power = 80;
				handle->ifaceTemperature.AC_State = bool_true;
				handle->ifaceAirFlaps.recircState = bool_false;
				handle->ifaceAirFlaps.defrostLeftSet = 100;
				handle->ifaceAirFlaps.defrostRightSet = 100;
				handle->ifaceAirFlaps.ventLeftSet = 0;
				handle->ifaceAirFlaps.ventRightSet = 0;
				handle->ifaceAirFlaps.floorLeftSet = 0;
				handle->ifaceAirFlaps.floorRightSet = 0;
				handle->ifaceHMI.levelState = 1;
				handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Defrost;
				handle->stateConfVectorPosition = 0;
				handle->historyVector[0] = handle->stateConfVector[0];
			}  else {
				if ((handle->ifaceHMI.ComToggle_raised) && handle->ifaceHMI.levelSwitch == 3) { 
					/* Default exit sequence for state Mix */
					handle->stateConfVector[0] = ModeCoordinator_last_state;
					handle->stateConfVectorPosition = 0;
					/* The reactions of exit history. */
					/* Default exit sequence for state Manual */
					/* Default exit sequence for region null */
					/* Handle exit of all possible states (of region0) at position 0... */
					switch(handle->stateConfVector[ 0 ]) {
						case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Floor : {
							/* Default exit sequence for state Floor */
							handle->stateConfVector[0] = ModeCoordinator_last_state;
							handle->stateConfVectorPosition = 0;
							break;
						}
						case ModeCoordinator_modeProcessing_On__region0_Manual__region0_BiLevel : {
							/* Default exit sequence for state BiLevel */
							handle->stateConfVector[0] = ModeCoordinator_last_state;
							handle->stateConfVectorPosition = 0;
							break;
						}
						case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Vent : {
							/* Default exit sequence for state Vent */
							handle->stateConfVector[0] = ModeCoordinator_last_state;
							handle->stateConfVectorPosition = 0;
							break;
						}
						case ModeCoordinator_modeProcessing_On__region0_Manual__region0_Mix : {
							/* Default exit sequence for state Mix */
							handle->stateConfVector[0] = ModeCoordinator_last_state;
							handle->stateConfVectorPosition = 0;
							break;
						}
						default: break;
					}
					/* Default react sequence for deep history entry  */
					/* Enter the region with deep history */
					if (handle->historyVector[0] != ModeCoordinator_last_state) {
						modeCoordinator_dhenseq_SequenceImpl(handle);
					} else {
						/* 'default' enter sequence for state Auto */
						/* Entry action for state 'Auto'. */
						handle->ifaceBlower.auto_raised = bool_true;
						handle->ifaceTemperature.AC_State = bool_true;
						handle->ifaceAirFlaps.recircState = bool_false;
						handle->ifaceHMI.levelState = 4;
						handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Auto;
						handle->stateConfVectorPosition = 0;
						handle->historyVector[0] = handle->stateConfVector[0];
					} 
				}  else {
					if ((handle->ifaceHMI.ComToggle_raised) && handle->ifaceHMI.levelSwitch != 0) { 
						/* Default exit sequence for state Mix */
						handle->stateConfVector[0] = ModeCoordinator_last_state;
						handle->stateConfVectorPosition = 0;
						/* The reactions of state null. */
						if (handle->ifaceHMI.levelSwitch == 2) { 
							/* 'default' enter sequence for state Vent */
							/* Entry action for state 'Vent'. */
							handle->ifaceAirFlaps.defrostLeftSet = 0;
							handle->ifaceAirFlaps.defrostRightSet = 0;
							handle->ifaceAirFlaps.ventLeftSet = 100;
							handle->ifaceAirFlaps.ventRightSet = 100;
							handle->ifaceAirFlaps.floorLeftSet = 0;
							handle->ifaceAirFlaps.floorRightSet = 0;
							handle->ifaceHMI.levelState = 2;
							handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Manual__region0_Vent;
							handle->stateConfVectorPosition = 0;
							handle->historyVector[1] = handle->stateConfVector[0];
						}  else {
							if (handle->ifaceHMI.levelSwitch == 5) { 
								/* 'default' enter sequence for state BiLevel */
								/* Entry action for state 'BiLevel'. */
								handle->ifaceAirFlaps.defrostLeftSet = 0;
								handle->ifaceAirFlaps.defrostRightSet = 0;
								handle->ifaceAirFlaps.ventLeftSet = 50;
								handle->ifaceAirFlaps.ventRightSet = 50;
								handle->ifaceAirFlaps.floorLeftSet = 50;
								handle->ifaceAirFlaps.floorRightSet = 50;
								handle->ifaceHMI.levelState = 5;
								handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Manual__region0_BiLevel;
								handle->stateConfVectorPosition = 0;
								handle->historyVector[1] = handle->stateConfVector[0];
							}  else {
								if (handle->ifaceHMI.levelSwitch == 6) { 
									/* 'default' enter sequence for state Floor */
									/* Entry action for state 'Floor'. */
									handle->ifaceAirFlaps.defrostLeftSet = 0;
									handle->ifaceAirFlaps.defrostRightSet = 0;
									handle->ifaceAirFlaps.ventLeftSet = 0;
									handle->ifaceAirFlaps.ventRightSet = 0;
									handle->ifaceAirFlaps.floorLeftSet = 100;
									handle->ifaceAirFlaps.floorRightSet = 100;
									handle->ifaceHMI.levelState = 6;
									handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Manual__region0_Floor;
									handle->stateConfVectorPosition = 0;
									handle->historyVector[1] = handle->stateConfVector[0];
								}  else {
									/* 'default' enter sequence for state Mix */
									/* Entry action for state 'Mix'. */
									handle->ifaceAirFlaps.defrostLeftSet = 50;
									handle->ifaceAirFlaps.defrostRightSet = 50;
									handle->ifaceAirFlaps.ventLeftSet = 0;
									handle->ifaceAirFlaps.ventRightSet = 0;
									handle->ifaceAirFlaps.floorLeftSet = 50;
									handle->ifaceAirFlaps.floorRightSet = 50;
									handle->ifaceHMI.levelState = 3;
									handle->stateConfVector[0] = ModeCoordinator_modeProcessing_On__region0_Manual__region0_Mix;
									handle->stateConfVectorPosition = 0;
									handle->historyVector[1] = handle->stateConfVector[0];
								}
							}
						}
					} 
				}
			}
		}
	}
}

/* The reactions of state Off. */
static void modeCoordinator_react_blowerProcessing_Off(ModeCoordinator* handle) {
	/* The reactions of state Off. */
	if (handle->ifaceBlower.manual_raised || handle->ifaceBlower.auto_raised) { 
		/* Default exit sequence for state Off */
		handle->stateConfVector[1] = ModeCoordinator_last_state;
		handle->stateConfVectorPosition = 1;
		/* The reactions of state null. */
		if (handle->ifaceBlower.power + (handle->ifaceBlower.increaseTicks - handle->ifaceBlower.decreaseTicks) * 100 / handle->ifaceBlower.maxSteps >= 100) { 
			handle->ifaceBlower.power = 100;
			/* 'default' enter sequence for state Calc Blower Power */
			/* Entry action for state 'Calc Blower Power'. */
			handle->ifaceBlower.increaseTicks = 0;
			handle->ifaceBlower.decreaseTicks = 0;
			handle->stateConfVector[1] = ModeCoordinator_blowerProcessing_Calc_Blower_Power;
			handle->stateConfVectorPosition = 1;
		}  else {
			if (handle->ifaceBlower.power + (handle->ifaceBlower.increaseTicks - handle->ifaceBlower.decreaseTicks) * 100 / handle->ifaceBlower.maxSteps <= 0) { 
				handle->ifaceBlower.power = 0;
				/* 'default' enter sequence for state Calc Blower Power */
				/* Entry action for state 'Calc Blower Power'. */
				handle->ifaceBlower.increaseTicks = 0;
				handle->ifaceBlower.decreaseTicks = 0;
				handle->stateConfVector[1] = ModeCoordinator_blowerProcessing_Calc_Blower_Power;
				handle->stateConfVectorPosition = 1;
			}  else {
				handle->ifaceBlower.power += (handle->ifaceBlower.increaseTicks - handle->ifaceBlower.decreaseTicks) * 100 / handle->ifaceBlower.maxSteps;
				/* 'default' enter sequence for state Calc Blower Power */
				/* Entry action for state 'Calc Blower Power'. */
				handle->ifaceBlower.increaseTicks = 0;
				handle->ifaceBlower.decreaseTicks = 0;
				handle->stateConfVector[1] = ModeCoordinator_blowerProcessing_Calc_Blower_Power;
				handle->stateConfVectorPosition = 1;
			}
		}
	}  else {
		handle->ifaceBlower.power = 0;
	}
}

/* The reactions of state Calc Blower Power. */
static void modeCoordinator_react_blowerProcessing_Calc_Blower_Power(ModeCoordinator* handle) {
	/* The reactions of state Calc Blower Power. */
	if ((handle->ifaceHMI.ComToggle_raised) && (handle->ifaceBlower.increaseTicks > 0 || handle->ifaceBlower.decreaseTicks > 0)) { 
		/* Default exit sequence for state Calc Blower Power */
		handle->stateConfVector[1] = ModeCoordinator_last_state;
		handle->stateConfVectorPosition = 1;
		handle->ifaceBlower.manual_raised = bool_true;
		/* The reactions of state null. */
		if (handle->ifaceBlower.power + (handle->ifaceBlower.increaseTicks - handle->ifaceBlower.decreaseTicks) * 100 / handle->ifaceBlower.maxSteps >= 100) { 
			handle->ifaceBlower.power = 100;
			/* 'default' enter sequence for state Calc Blower Power */
			/* Entry action for state 'Calc Blower Power'. */
			handle->ifaceBlower.increaseTicks = 0;
			handle->ifaceBlower.decreaseTicks = 0;
			handle->stateConfVector[1] = ModeCoordinator_blowerProcessing_Calc_Blower_Power;
			handle->stateConfVectorPosition = 1;
		}  else {
			if (handle->ifaceBlower.power + (handle->ifaceBlower.increaseTicks - handle->ifaceBlower.decreaseTicks) * 100 / handle->ifaceBlower.maxSteps <= 0) { 
				handle->ifaceBlower.power = 0;
				/* 'default' enter sequence for state Calc Blower Power */
				/* Entry action for state 'Calc Blower Power'. */
				handle->ifaceBlower.increaseTicks = 0;
				handle->ifaceBlower.decreaseTicks = 0;
				handle->stateConfVector[1] = ModeCoordinator_blowerProcessing_Calc_Blower_Power;
				handle->stateConfVectorPosition = 1;
			}  else {
				handle->ifaceBlower.power += (handle->ifaceBlower.increaseTicks - handle->ifaceBlower.decreaseTicks) * 100 / handle->ifaceBlower.maxSteps;
				/* 'default' enter sequence for state Calc Blower Power */
				/* Entry action for state 'Calc Blower Power'. */
				handle->ifaceBlower.increaseTicks = 0;
				handle->ifaceBlower.decreaseTicks = 0;
				handle->stateConfVector[1] = ModeCoordinator_blowerProcessing_Calc_Blower_Power;
				handle->stateConfVectorPosition = 1;
			}
		}
	}  else {
		if (handle->internal.blwOff_raised) { 
			/* Default exit sequence for state Calc Blower Power */
			handle->stateConfVector[1] = ModeCoordinator_last_state;
			handle->stateConfVectorPosition = 1;
			/* 'default' enter sequence for state Off */
			/* Entry action for state 'Off'. */
			handle->ifaceBlower.power = 0;
			handle->stateConfVector[1] = ModeCoordinator_blowerProcessing_Off;
			handle->stateConfVectorPosition = 1;
		} 
	}
}

/* The reactions of state Aircondition Disabled. */
static void modeCoordinator_react_ac_Aircondition_Disabled(ModeCoordinator* handle) {
	/* The reactions of state Aircondition Disabled. */
	if (handle->ifaceTemperature.AC_State) { 
		/* Default exit sequence for state Aircondition Disabled */
		handle->stateConfVector[2] = ModeCoordinator_last_state;
		handle->stateConfVectorPosition = 2;
		/* 'default' enter sequence for state Aircondition Enabled */
		handle->stateConfVector[2] = ModeCoordinator_ac_Aircondition_Enabled;
		handle->stateConfVectorPosition = 2;
		handle->historyVector[2] = handle->stateConfVector[2];
	} 
}

/* The reactions of state Aircondition Enabled. */
static void modeCoordinator_react_ac_Aircondition_Enabled(ModeCoordinator* handle) {
	/* The reactions of state Aircondition Enabled. */
	if (! handle->ifaceTemperature.AC_State) { 
		/* Default exit sequence for state Aircondition Enabled */
		handle->stateConfVector[2] = ModeCoordinator_last_state;
		handle->stateConfVectorPosition = 2;
		/* 'default' enter sequence for state Aircondition Disabled */
		handle->stateConfVector[2] = ModeCoordinator_ac_Aircondition_Disabled;
		handle->stateConfVectorPosition = 2;
		handle->historyVector[2] = handle->stateConfVector[2];
	} 
}

/* The reactions of state Recirc Disabled. */
static void modeCoordinator_react_recirc_Recirc_Disabled(ModeCoordinator* handle) {
	/* The reactions of state Recirc Disabled. */
	if (handle->ifaceAirFlaps.recircState) { 
		/* Default exit sequence for state Recirc Disabled */
		handle->stateConfVector[3] = ModeCoordinator_last_state;
		handle->stateConfVectorPosition = 3;
		/* 'default' enter sequence for state Recirc Enabled */
		/* Entry action for state 'Recirc Enabled'. */
		handle->ifaceAirFlaps.recircSet = 100;
		handle->stateConfVector[3] = ModeCoordinator_recirc_Recirc_Enabled;
		handle->stateConfVectorPosition = 3;
		handle->historyVector[3] = handle->stateConfVector[3];
	} 
}

/* The reactions of state Recirc Enabled. */
static void modeCoordinator_react_recirc_Recirc_Enabled(ModeCoordinator* handle) {
	/* The reactions of state Recirc Enabled. */
	if (! handle->ifaceAirFlaps.recircState) { 
		/* Default exit sequence for state Recirc Enabled */
		handle->stateConfVector[3] = ModeCoordinator_last_state;
		handle->stateConfVectorPosition = 3;
		/* 'default' enter sequence for state Recirc Disabled */
		/* Entry action for state 'Recirc Disabled'. */
		handle->ifaceAirFlaps.recircSet = 0;
		handle->stateConfVector[3] = ModeCoordinator_recirc_Recirc_Disabled;
		handle->stateConfVectorPosition = 3;
		handle->historyVector[3] = handle->stateConfVector[3];
	} 
}


