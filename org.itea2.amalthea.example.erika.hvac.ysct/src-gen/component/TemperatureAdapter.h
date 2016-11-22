
#ifndef TEMPERATUREADAPTER_H_
#define TEMPERATUREADAPTER_H_

#include "sc_types.h"

#ifdef __cplusplus
extern "C" { 
#endif 

/*! \file Header of the state machine 'TemperatureAdapter'.
*/

//! enumeration of all states 
typedef enum {
	TemperatureAdapter__region0_off,
	TemperatureAdapter__region0_on,
	TemperatureAdapter__region0_on__region0_Calculate_Driver_Temperature,
	TemperatureAdapter_last_state
} TemperatureAdapterStates;

//! Type definition of the data structure for the TemperatureAdapterIface interface scope.
typedef struct {
	sc_boolean temperatureSet_raised;
	sc_boolean off_raised;
	sc_boolean on_raised;
	sc_integer plusTicks;
	sc_integer minusTicks;
	sc_integer temp;
} TemperatureAdapterIface;

//! Type definition of the data structure for the TemperatureAdapterInternal interface scope.
typedef struct {
	sc_integer low;
	sc_integer high;
	sc_integer step;
} TemperatureAdapterInternal;


//! the maximum number of orthogonal states defines the dimension of the state configuration vector.
#define TEMPERATUREADAPTER_MAX_ORTHOGONAL_STATES 1

/*! Type definition of the data structure for the TemperatureAdapter state machine.
This data structure has to be allocated by the client code. */
typedef struct {
	TemperatureAdapterStates stateConfVector[TEMPERATUREADAPTER_MAX_ORTHOGONAL_STATES];
	sc_ushort stateConfVectorPosition; 
	
	TemperatureAdapterIface iface;
	TemperatureAdapterInternal internal;
} TemperatureAdapter;

/*! Initializes the TemperatureAdapter state machine data structures. Must be called before first usage.*/
extern void temperatureAdapter_init(TemperatureAdapter* handle);

/*! Activates the state machine */
extern void temperatureAdapter_enter(TemperatureAdapter* handle);

/*! Deactivates the state machine */
extern void temperatureAdapter_exit(TemperatureAdapter* handle);

/*! Performs a 'run to completion' step. */
extern void temperatureAdapter_runCycle(TemperatureAdapter* handle);


/*! Raises the in event 'temperatureSet' that is defined in the default interface scope. */ 
extern void temperatureAdapterIface_raise_temperatureSet(TemperatureAdapter* handle);

/*! Raises the in event 'off' that is defined in the default interface scope. */ 
extern void temperatureAdapterIface_raise_off(TemperatureAdapter* handle);

/*! Raises the in event 'on' that is defined in the default interface scope. */ 
extern void temperatureAdapterIface_raise_on(TemperatureAdapter* handle);

/*! Gets the value of the variable 'plusTicks' that is defined in the default interface scope. */ 
extern sc_integer temperatureAdapterIface_get_plusTicks(TemperatureAdapter* handle);
/*! Sets the value of the variable 'plusTicks' that is defined in the default interface scope. */ 
extern void temperatureAdapterIface_set_plusTicks(TemperatureAdapter* handle, sc_integer value);
/*! Gets the value of the variable 'minusTicks' that is defined in the default interface scope. */ 
extern sc_integer temperatureAdapterIface_get_minusTicks(TemperatureAdapter* handle);
/*! Sets the value of the variable 'minusTicks' that is defined in the default interface scope. */ 
extern void temperatureAdapterIface_set_minusTicks(TemperatureAdapter* handle, sc_integer value);
/*! Gets the value of the variable 'temp' that is defined in the default interface scope. */ 
extern sc_integer temperatureAdapterIface_get_temp(TemperatureAdapter* handle);
/*! Sets the value of the variable 'temp' that is defined in the default interface scope. */ 
extern void temperatureAdapterIface_set_temp(TemperatureAdapter* handle, sc_integer value);


/*! Checks if the specified state is active. */
extern sc_boolean temperatureAdapter_isActive(TemperatureAdapter* handle, TemperatureAdapterStates state);

#ifdef __cplusplus
}
#endif 

#endif /* TEMPERATUREADAPTER_H_ */
