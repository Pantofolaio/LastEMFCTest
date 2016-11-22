
#ifndef MODECOORDINATOR_H_
#define MODECOORDINATOR_H_

#include "sc_types.h"

#ifdef __cplusplus
extern "C" { 
#endif 

/*! \file Header of the state machine 'ModeCoordinator'.
*/

//! enumeration of all states 
typedef enum {
	ModeCoordinator_modeProcessing_Off,
	ModeCoordinator_modeProcessing_On,
	ModeCoordinator_modeProcessing_On__region0_Defrost,
	ModeCoordinator_modeProcessing_On__region0_Auto,
	ModeCoordinator_modeProcessing_On__region0_Manual,
	ModeCoordinator_modeProcessing_On__region0_Manual__region0_Floor,
	ModeCoordinator_modeProcessing_On__region0_Manual__region0_BiLevel,
	ModeCoordinator_modeProcessing_On__region0_Manual__region0_Vent,
	ModeCoordinator_modeProcessing_On__region0_Manual__region0_Mix,
	ModeCoordinator_blowerProcessing_Off,
	ModeCoordinator_blowerProcessing_Calc_Blower_Power,
	ModeCoordinator_ac_Aircondition_Disabled,
	ModeCoordinator_ac_Aircondition_Enabled,
	ModeCoordinator_recirc_Recirc_Disabled,
	ModeCoordinator_recirc_Recirc_Enabled,
	ModeCoordinator_last_state
} ModeCoordinatorStates;

//! Type definition of the data structure for the ModeCoordinatorIfaceHMI interface scope.
typedef struct {
	sc_boolean ComToggle_raised;
	sc_boolean recircSwitch;
	sc_boolean AC_Switch;
	sc_integer levelSwitch;
	sc_integer levelState;
} ModeCoordinatorIfaceHMI;

//! Type definition of the data structure for the ModeCoordinatorIfaceBlower interface scope.
typedef struct {
	sc_boolean auto_raised;
	sc_boolean manual_raised;
	sc_integer power;
	sc_integer autoPower;
	sc_integer maxSteps;
	sc_integer increaseTicks;
	sc_integer decreaseTicks;
} ModeCoordinatorIfaceBlower;

//! Type definition of the data structure for the ModeCoordinatorIfaceTemperature interface scope.
typedef struct {
	sc_boolean AC_State;
	sc_boolean on_raised;
	sc_boolean off_raised;
} ModeCoordinatorIfaceTemperature;

//! Type definition of the data structure for the ModeCoordinatorIfaceAirFlaps interface scope.
typedef struct {
	sc_boolean recircState;
	sc_integer defrostLeftSet;
	sc_integer defrostRightSet;
	sc_integer ventLeftSet;
	sc_integer ventRightSet;
	sc_integer floorLeftSet;
	sc_integer floorRightSet;
	sc_integer recircSet;
} ModeCoordinatorIfaceAirFlaps;

//! Type definition of the data structure for the ModeCoordinatorInternal interface scope.
typedef struct {
	sc_boolean blwOff_raised;
} ModeCoordinatorInternal;


//! the maximum number of orthogonal states defines the dimension of the state configuration vector.
#define MODECOORDINATOR_MAX_ORTHOGONAL_STATES 4
//! dimension of the state configuration vector for history states
#define MODECOORDINATOR_MAX_HISTORY_STATES 4

/*! Type definition of the data structure for the ModeCoordinator state machine.
This data structure has to be allocated by the client code. */
typedef struct {
	ModeCoordinatorStates stateConfVector[MODECOORDINATOR_MAX_ORTHOGONAL_STATES];
	ModeCoordinatorStates historyVector[MODECOORDINATOR_MAX_HISTORY_STATES];
	sc_ushort stateConfVectorPosition; 
	
	ModeCoordinatorIfaceHMI ifaceHMI;
	ModeCoordinatorIfaceBlower ifaceBlower;
	ModeCoordinatorIfaceTemperature ifaceTemperature;
	ModeCoordinatorIfaceAirFlaps ifaceAirFlaps;
	ModeCoordinatorInternal internal;
} ModeCoordinator;

/*! Initializes the ModeCoordinator state machine data structures. Must be called before first usage.*/
extern void modeCoordinator_init(ModeCoordinator* handle);

/*! Activates the state machine */
extern void modeCoordinator_enter(ModeCoordinator* handle);

/*! Deactivates the state machine */
extern void modeCoordinator_exit(ModeCoordinator* handle);

/*! Performs a 'run to completion' step. */
extern void modeCoordinator_runCycle(ModeCoordinator* handle);


/*! Raises the in event 'ComToggle' that is defined in the interface scope 'HMI'. */ 
extern void modeCoordinatorIfaceHMI_raise_comToggle(ModeCoordinator* handle);

/*! Gets the value of the variable 'recircSwitch' that is defined in the interface scope 'HMI'. */ 
extern sc_boolean modeCoordinatorIfaceHMI_get_recircSwitch(ModeCoordinator* handle);
/*! Sets the value of the variable 'recircSwitch' that is defined in the interface scope 'HMI'. */ 
extern void modeCoordinatorIfaceHMI_set_recircSwitch(ModeCoordinator* handle, sc_boolean value);
/*! Gets the value of the variable 'AC_Switch' that is defined in the interface scope 'HMI'. */ 
extern sc_boolean modeCoordinatorIfaceHMI_get_aC_Switch(ModeCoordinator* handle);
/*! Sets the value of the variable 'AC_Switch' that is defined in the interface scope 'HMI'. */ 
extern void modeCoordinatorIfaceHMI_set_aC_Switch(ModeCoordinator* handle, sc_boolean value);
/*! Gets the value of the variable 'levelSwitch' that is defined in the interface scope 'HMI'. */ 
extern sc_integer modeCoordinatorIfaceHMI_get_levelSwitch(ModeCoordinator* handle);
/*! Sets the value of the variable 'levelSwitch' that is defined in the interface scope 'HMI'. */ 
extern void modeCoordinatorIfaceHMI_set_levelSwitch(ModeCoordinator* handle, sc_integer value);
/*! Gets the value of the variable 'levelState' that is defined in the interface scope 'HMI'. */ 
extern sc_integer modeCoordinatorIfaceHMI_get_levelState(ModeCoordinator* handle);
/*! Sets the value of the variable 'levelState' that is defined in the interface scope 'HMI'. */ 
extern void modeCoordinatorIfaceHMI_set_levelState(ModeCoordinator* handle, sc_integer value);

/*! Checks if the out event 'auto' that is defined in the interface scope 'Blower' has been raised. */ 
extern sc_boolean modeCoordinatorIfaceBlower_israised_auto(ModeCoordinator* handle);

/*! Checks if the out event 'manual' that is defined in the interface scope 'Blower' has been raised. */ 
extern sc_boolean modeCoordinatorIfaceBlower_israised_manual(ModeCoordinator* handle);

/*! Gets the value of the variable 'power' that is defined in the interface scope 'Blower'. */ 
extern sc_integer modeCoordinatorIfaceBlower_get_power(ModeCoordinator* handle);
/*! Sets the value of the variable 'power' that is defined in the interface scope 'Blower'. */ 
extern void modeCoordinatorIfaceBlower_set_power(ModeCoordinator* handle, sc_integer value);
/*! Gets the value of the variable 'autoPower' that is defined in the interface scope 'Blower'. */ 
extern sc_integer modeCoordinatorIfaceBlower_get_autoPower(ModeCoordinator* handle);
/*! Sets the value of the variable 'autoPower' that is defined in the interface scope 'Blower'. */ 
extern void modeCoordinatorIfaceBlower_set_autoPower(ModeCoordinator* handle, sc_integer value);
/*! Gets the value of the variable 'maxSteps' that is defined in the interface scope 'Blower'. */ 
extern sc_integer modeCoordinatorIfaceBlower_get_maxSteps(ModeCoordinator* handle);
/*! Sets the value of the variable 'maxSteps' that is defined in the interface scope 'Blower'. */ 
extern void modeCoordinatorIfaceBlower_set_maxSteps(ModeCoordinator* handle, sc_integer value);
/*! Gets the value of the variable 'increaseTicks' that is defined in the interface scope 'Blower'. */ 
extern sc_integer modeCoordinatorIfaceBlower_get_increaseTicks(ModeCoordinator* handle);
/*! Sets the value of the variable 'increaseTicks' that is defined in the interface scope 'Blower'. */ 
extern void modeCoordinatorIfaceBlower_set_increaseTicks(ModeCoordinator* handle, sc_integer value);
/*! Gets the value of the variable 'decreaseTicks' that is defined in the interface scope 'Blower'. */ 
extern sc_integer modeCoordinatorIfaceBlower_get_decreaseTicks(ModeCoordinator* handle);
/*! Sets the value of the variable 'decreaseTicks' that is defined in the interface scope 'Blower'. */ 
extern void modeCoordinatorIfaceBlower_set_decreaseTicks(ModeCoordinator* handle, sc_integer value);

/*! Gets the value of the variable 'AC_State' that is defined in the interface scope 'Temperature'. */ 
extern sc_boolean modeCoordinatorIfaceTemperature_get_aC_State(ModeCoordinator* handle);
/*! Sets the value of the variable 'AC_State' that is defined in the interface scope 'Temperature'. */ 
extern void modeCoordinatorIfaceTemperature_set_aC_State(ModeCoordinator* handle, sc_boolean value);
/*! Checks if the out event 'on' that is defined in the interface scope 'Temperature' has been raised. */ 
extern sc_boolean modeCoordinatorIfaceTemperature_israised_on(ModeCoordinator* handle);

/*! Checks if the out event 'off' that is defined in the interface scope 'Temperature' has been raised. */ 
extern sc_boolean modeCoordinatorIfaceTemperature_israised_off(ModeCoordinator* handle);


/*! Gets the value of the variable 'recircState' that is defined in the interface scope 'AirFlaps'. */ 
extern sc_boolean modeCoordinatorIfaceAirFlaps_get_recircState(ModeCoordinator* handle);
/*! Sets the value of the variable 'recircState' that is defined in the interface scope 'AirFlaps'. */ 
extern void modeCoordinatorIfaceAirFlaps_set_recircState(ModeCoordinator* handle, sc_boolean value);
/*! Gets the value of the variable 'defrostLeftSet' that is defined in the interface scope 'AirFlaps'. */ 
extern sc_integer modeCoordinatorIfaceAirFlaps_get_defrostLeftSet(ModeCoordinator* handle);
/*! Sets the value of the variable 'defrostLeftSet' that is defined in the interface scope 'AirFlaps'. */ 
extern void modeCoordinatorIfaceAirFlaps_set_defrostLeftSet(ModeCoordinator* handle, sc_integer value);
/*! Gets the value of the variable 'defrostRightSet' that is defined in the interface scope 'AirFlaps'. */ 
extern sc_integer modeCoordinatorIfaceAirFlaps_get_defrostRightSet(ModeCoordinator* handle);
/*! Sets the value of the variable 'defrostRightSet' that is defined in the interface scope 'AirFlaps'. */ 
extern void modeCoordinatorIfaceAirFlaps_set_defrostRightSet(ModeCoordinator* handle, sc_integer value);
/*! Gets the value of the variable 'ventLeftSet' that is defined in the interface scope 'AirFlaps'. */ 
extern sc_integer modeCoordinatorIfaceAirFlaps_get_ventLeftSet(ModeCoordinator* handle);
/*! Sets the value of the variable 'ventLeftSet' that is defined in the interface scope 'AirFlaps'. */ 
extern void modeCoordinatorIfaceAirFlaps_set_ventLeftSet(ModeCoordinator* handle, sc_integer value);
/*! Gets the value of the variable 'ventRightSet' that is defined in the interface scope 'AirFlaps'. */ 
extern sc_integer modeCoordinatorIfaceAirFlaps_get_ventRightSet(ModeCoordinator* handle);
/*! Sets the value of the variable 'ventRightSet' that is defined in the interface scope 'AirFlaps'. */ 
extern void modeCoordinatorIfaceAirFlaps_set_ventRightSet(ModeCoordinator* handle, sc_integer value);
/*! Gets the value of the variable 'floorLeftSet' that is defined in the interface scope 'AirFlaps'. */ 
extern sc_integer modeCoordinatorIfaceAirFlaps_get_floorLeftSet(ModeCoordinator* handle);
/*! Sets the value of the variable 'floorLeftSet' that is defined in the interface scope 'AirFlaps'. */ 
extern void modeCoordinatorIfaceAirFlaps_set_floorLeftSet(ModeCoordinator* handle, sc_integer value);
/*! Gets the value of the variable 'floorRightSet' that is defined in the interface scope 'AirFlaps'. */ 
extern sc_integer modeCoordinatorIfaceAirFlaps_get_floorRightSet(ModeCoordinator* handle);
/*! Sets the value of the variable 'floorRightSet' that is defined in the interface scope 'AirFlaps'. */ 
extern void modeCoordinatorIfaceAirFlaps_set_floorRightSet(ModeCoordinator* handle, sc_integer value);
/*! Gets the value of the variable 'recircSet' that is defined in the interface scope 'AirFlaps'. */ 
extern sc_integer modeCoordinatorIfaceAirFlaps_get_recircSet(ModeCoordinator* handle);
/*! Sets the value of the variable 'recircSet' that is defined in the interface scope 'AirFlaps'. */ 
extern void modeCoordinatorIfaceAirFlaps_set_recircSet(ModeCoordinator* handle, sc_integer value);


/*! Checks if the specified state is active. */
extern sc_boolean modeCoordinator_isActive(ModeCoordinator* handle, ModeCoordinatorStates state);

#ifdef __cplusplus
}
#endif 

#endif /* MODECOORDINATOR_H_ */
