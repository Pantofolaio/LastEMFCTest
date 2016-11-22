
#ifndef TEMPERATUREFLAPCTRL_H_
#define TEMPERATUREFLAPCTRL_H_

#include "sc_types.h"

#ifdef __cplusplus
extern "C" { 
#endif 

/*! \file Header of the state machine 'TemperatureFlapCtrl'.
*/

//! enumeration of all states 
typedef enum {
	TemperatureFlapCtrl_main_region_Set_Temp_Flap,
	TemperatureFlapCtrl_last_state
} TemperatureFlapCtrlStates;

//! Type definition of the data structure for the TemperatureFlapCtrlIface interface scope.
typedef struct {
	sc_integer interiorTemp;
	sc_integer setTemp;
	sc_integer tempFlapSet;
} TemperatureFlapCtrlIface;

//! Type definition of the data structure for the TemperatureFlapCtrlInternal interface scope.
typedef struct {
	sc_integer counter;
	sc_integer max;
	sc_integer min;
} TemperatureFlapCtrlInternal;


//! the maximum number of orthogonal states defines the dimension of the state configuration vector.
#define TEMPERATUREFLAPCTRL_MAX_ORTHOGONAL_STATES 1

/*! Type definition of the data structure for the TemperatureFlapCtrl state machine.
This data structure has to be allocated by the client code. */
typedef struct {
	TemperatureFlapCtrlStates stateConfVector[TEMPERATUREFLAPCTRL_MAX_ORTHOGONAL_STATES];
	sc_ushort stateConfVectorPosition; 
	
	TemperatureFlapCtrlIface iface;
	TemperatureFlapCtrlInternal internal;
} TemperatureFlapCtrl;

/*! Initializes the TemperatureFlapCtrl state machine data structures. Must be called before first usage.*/
extern void temperatureFlapCtrl_init(TemperatureFlapCtrl* handle);

/*! Activates the state machine */
extern void temperatureFlapCtrl_enter(TemperatureFlapCtrl* handle);

/*! Deactivates the state machine */
extern void temperatureFlapCtrl_exit(TemperatureFlapCtrl* handle);

/*! Performs a 'run to completion' step. */
extern void temperatureFlapCtrl_runCycle(TemperatureFlapCtrl* handle);


/*! Gets the value of the variable 'interiorTemp' that is defined in the default interface scope. */ 
extern sc_integer temperatureFlapCtrlIface_get_interiorTemp(TemperatureFlapCtrl* handle);
/*! Sets the value of the variable 'interiorTemp' that is defined in the default interface scope. */ 
extern void temperatureFlapCtrlIface_set_interiorTemp(TemperatureFlapCtrl* handle, sc_integer value);
/*! Gets the value of the variable 'setTemp' that is defined in the default interface scope. */ 
extern sc_integer temperatureFlapCtrlIface_get_setTemp(TemperatureFlapCtrl* handle);
/*! Sets the value of the variable 'setTemp' that is defined in the default interface scope. */ 
extern void temperatureFlapCtrlIface_set_setTemp(TemperatureFlapCtrl* handle, sc_integer value);
/*! Gets the value of the variable 'tempFlapSet' that is defined in the default interface scope. */ 
extern sc_integer temperatureFlapCtrlIface_get_tempFlapSet(TemperatureFlapCtrl* handle);
/*! Sets the value of the variable 'tempFlapSet' that is defined in the default interface scope. */ 
extern void temperatureFlapCtrlIface_set_tempFlapSet(TemperatureFlapCtrl* handle, sc_integer value);


/*! Checks if the specified state is active. */
extern sc_boolean temperatureFlapCtrl_isActive(TemperatureFlapCtrl* handle, TemperatureFlapCtrlStates state);

#ifdef __cplusplus
}
#endif 

#endif /* TEMPERATUREFLAPCTRL_H_ */
