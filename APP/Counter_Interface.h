#ifndef COUNTER_INTERFACE_FILE
#define COUNTER_INTERFACE_FILE

#include "../LIB/STD.h"
#include "../LIB/ErrorStates.h"


//APIs' prototypes 
extern ErrorState_t Counter_enu_Initialization(void);

extern ErrorState_t Counter_enu_Operation(void);

void Counter_vid_IncrementCounter(void* Copy_pvid_Parameters);

void Counter_vid_DecrementCounter(void* Copy_pvid_Parameters);


//Local functions' prototypes

#endif