/* ### OSEK MAIN ### */
/*
 * Author: 2013 Sebastian Pietrowski
 */
 
#include "shared.h"
#include "runnable.h"
#include "mpc5668Glib.h"

/* The compare value for PIT3
 * 100000000 = 1   sec
 * 10000000  = 100 mSec
 */
#define COMPARE_VALUE 1000000

/* OSEK declerations */
%%

int main(void)
{
	/* Enable PIT3 or PIT4 (Programmable interval timer 3)to
	 * get the value of the potentiometer on the MPC5668G
	 * Value of the PIT3-Level = 151
	 * Value of the PIT4-Level = 152
	 * The first 16 level of the dynamic table are reserved,
	 * therefore we have to add 16 to the Interruptnumber:
	 * 16+151 = 167 and 16+152 = 168
	 * In General the EE_e200z7_register_ISR is used to enable
	 * dynamic ISR table support
	 */
%ISR

	/* Enable the Interrupt Requests */
	EE_e200z7_enableIRQ();

	/* ODFRGSULTAPPMODE is the default Application Mode, which is
	 * always a valid Mode that can be passed to StartOS
	 *
	 * Applications Modes are startup configurations that are used
	 * to configure the running application for a certain mode of
	 * operation. Other examples: "Normal execution", "Flash Programming",
	 * "Debug Mode"
	 *
	 * Application modes are listed inside the OIL configuration file. There
	 * exist always at least on application mode called OSDEFAULTMODE. Once set at
	 * startup into StartOS the Applications mode cannot be changed
	 * */
	StartOS(OSDEFAULTAPPMODE);
}//EOF
