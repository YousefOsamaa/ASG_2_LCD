#include "../LIB/STD.h"
#include "../LIB/ErrorStates.h"



#include "../HAL/LCD/LCD_Interface.h"
#include "../MCAL/EXTI/EXTI_Interface.h"
#include "../MCAL/SREG/SREG_Interface.h"

#include "Counter_Private.h"
#include "Counter_Config.h"

//System Counter
static Counter_t str_SystemCounter = { 0 };


//APIs Implementaion 
void Counter_vid_IncrementCounter(void* Copy_pvid_Parameters)
{
    if(Copy_pvid_Parameters)
    {
        if( (((Counter_t*)Copy_pvid_Parameters)->Count) < COUNTER_MAX_NUMBER) 
        {
            (((Counter_t*)Copy_pvid_Parameters)->Count)++;
        }
    }
  
}

void Counter_vid_DecrementCounter(void* Copy_pvid_Parameters)
{
    if(Copy_pvid_Parameters)
    {
        if( (((Counter_t*)Copy_pvid_Parameters)->Count) > COUNTER_MIN_NUMBER) 
        {
            (((Counter_t*)Copy_pvid_Parameters)->Count)--;
        }
    }
}

extern ErrorState_t Counter_enu_Initialization(void)
{
    u8 Local_u8_ErrorFlag = ES_NOK;

    //Initializintg MCALs and HALs
    LCD_enu_Initialization();
    EXTI_enu_Initialization();



    //Setting Call back functions for INT0 and INT1
    EXTI_enu_SetCallBack(EXTI_INT0, Counter_vid_IncrementCounter, &str_SystemCounter);

    EXTI_enu_SetCallBack(EXTI_INT1, Counter_vid_DecrementCounter, &str_SystemCounter);
    
    //Clearing any set flags
    EXTI_enu_ClearINTFx(EXTI_INT0);
    EXTI_enu_ClearINTFx(EXTI_INT1);

    //Enabling Interrupts by setting GIE
    SREG_vid_EnableBitI();

    return Local_u8_ErrorFlag;
}

extern ErrorState_t Counter_enu_Operation(void)
{
    u8 Local_u8_ErrorFlag = ES_NOK;

    //Placing cursor to print main message
    LCD_enu_GoToPosition(LCD_ROW_1,LCD_COLUMN_1,LCD_PAGE_1);
    //Displaying main message
    LCD_enu_SendString("Counter = ");
    
    do
    {
        LCD_enu_WriteIntegerNum(str_SystemCounter.Count, LCD_ROW_1, LCD_COLUMN_11, LCD_PAGE_1);

    } while (1);
    

    return Local_u8_ErrorFlag;
}



//Local functions' implementation