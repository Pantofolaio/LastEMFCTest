
#ifndef BLOWERCTRL_H_
#define BLOWERCTRL_H_

#include "sc_types.h"

#ifdef __cplusplus
extern "C" { 
#endif 

/*! \file Header of the state machine 'BlowerCtrl'.
*/

//! enumeration of all states 
typedef enum {
	BlowerCtrl_main_region_Auto_Mode,
	BlowerCtrl_main_region_Auto_Mode__region0_Calc_Power,
	BlowerCtrl_main_region_PassThroughMode,
	BlowerCtrl_last_state
} BlowerCtrlStates;

//! Type definition of the data structure for the BlowerCtrlIface interface scope.
typedef struct {
	sc_boolean autoMode_raised;
	sc_boolean passThroughMode_raised;
	sc_integer passThroughValue;
	sc_integer interiorTemp;
	sc_integer drvRefTemp;
	sc_integer passRefTemp;
	sc_integer power;
} BlowerCtrlIface;

//! Type definition of the data structure for the BlowerCtrlInternal interface scope.
typedef struct {
	sc_integer drvDelta;
	sc_integer passDelta;
	sc_integer tempPwr;
} BlowerCtrlInternal;


//! the maximum number of orthogonal states defines the dimension of the state configuration vector.
#define BLOWERCTRL_MAX_ORTHOGONAL_STATES 1

/*! Type definition of the data structure for the BlowerCtrl state machine.
This data structure has to be allocated by the client code. */
typedef struct {
	BlowerCtrlStates stateConfVector[BLOWERCTRL_MAX_ORTHOGONAL_STATES];
	sc_ushort stateConfVectorPosition; 
	
	BlowerCtrlIface iface;
	BlowerCtrlInternal internal;
} BlowerCtrl;

/*! Initializes the BlowerCtrl state machine data structures. Must be called before first usage.*/
extern void blowerCtrl_init(BlowerCtrl* handle);

/*! Activates the state machine */
extern void blowerCtrl_enter(BlowerCtrl* handle);

/*! Deactivates the state machine */
extern void blowerCtrl_exit(BlowerCtrl* handle);

/*! Performs a 'run to completion' step. */
extern void blowerCtrl_runCycle(BlowerCtrl* handle);


/*! Raises the in event 'autoMode' that is defined in the default interface scope. */ 
extern void blowerCtrlIface_raise_autoMode(BlowerCtrl* handle);

/*! Raises the in event 'passThroughMode' that is defined in the default interface scope. */ 
extern void blowerCtrlIface_raise_passThroughMode(BlowerCtrl* handle);

/*! Gets the value of the variable 'passThroughValue' that is defined in the default interface scope. */ 
extern sc_integer blowerCtrlIface_get_passThroughValue(BlowerCtrl* handle);
/*! Sets the value of the variable 'passThroughValue' that is defined in the default interface scope. */ 
extern void blowerCtrlIface_set_passThroughValue(BlowerCtrl* handle, sc_integer value);
/*! Gets the value of the variable 'interiorTemp' that is defined in the default interface scope. */ 
extern sc_integer blowerCtrlIface_get_interiorTemp(BlowerCtrl* handle);
/*! Sets the value of the variable 'interiorTemp' that is defined in the default interface scope. */ 
extern void blowerCtrlIface_set_interiorTemp(BlowerCtrl* handle, sc_integer value);
/*! Gets the value of the variable 'drvRefTemp' that is defined in the default interface scope. */ 
extern sc_integer blowerCtrlIface_get_drvRefTemp(BlowerCtrl* handle);
/*! Sets the value of the variable 'drvRefTemp' that is defined in the default interface scope. */ 
extern void blowerCtrlIface_set_drvRefTemp(BlowerCtrl* handle, sc_integer value);
/*! Gets the value of the variable 'passRefTemp' that is defined in the default interface scope. */ 
extern sc_integer blowerCtrlIface_get_passRefTemp(BlowerCtrl* handle);
/*! Sets the value of the variable 'passRefTemp' that is defined in the default interface scope. */ 
extern void blowerCtrlIface_set_passRefTemp(BlowerCtrl* handle, sc_integer value);
/*! Gets the value of the variable 'power' that is defined in the default interface scope. */ 
extern sc_integer blowerCtrlIface_get_power(BlowerCtrl* handle);
/*! Sets the value of the variable 'power' that is defined in the default interface scope. */ 
extern void blowerCtrlIface_set_power(BlowerCtrl* handle, sc_integer value);


/*! Checks if the specified state is active. */
extern sc_boolean blowerCtrl_isActive(BlowerCtrl* handle, BlowerCtrlStates state);

#ifdef __cplusplus
}
#endif 

#endif /* BLOWERCTRL_H_ */
