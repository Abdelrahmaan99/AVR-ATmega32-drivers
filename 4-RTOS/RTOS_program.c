/********************************************************************************************/
/********************************************************************************************/
/**************************		Author: Abdelrahman El_Gharbawy		            *************/
/**************************		Layer:  RTOS STACK								*************/
/**************************		SWC:	RTOS								    *************/
/**************************		Version:1.00 	             					*************/
/********************************************************************************************/
/********************************************************************************************/


#include "STD_TYPES.h"

#include "TIMER_interface.h"

#include "RTOS_interface.h"
#include "RTOS_private.h"
#include "RTOS_config.h"


Task_t SystemTasks [TASK_NUM] = {{NULL}};



u8 RTOS_u8CreateTask(u8 Copy_u8Priority , u16 Copy_u16Periodicity , void (*Copy_pvTaskFunc)(void) , u8 Copy_u8FirstDelay)
{
	u8 Local_u8ErrorState = OK;

	if(SystemTasks[Copy_u8Priority].TaskFunc == NULL)
	{
		SystemTasks[Copy_u8Priority].Periodicity = Copy_u16Periodicity;
		SystemTasks[Copy_u8Priority].TaskFunc    = Copy_pvTaskFunc;
		SystemTasks[Copy_u8Priority].State	     = TASK_RESUMED;
		SystemTasks[Copy_u8Priority].FirstDelay	 = Copy_u8FirstDelay ;
	}
	else
	{
		/* Required priority is reserved for another function */
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}

void RTOS_voidStart(void)
{
	TIMER0_u8SetCallBack(&Schedular);
	TIMER0_voidInit();
}

void RTOS_voidDeleteTask(u8 Copy_u8Priority)
{
	SystemTasks[Copy_u8Priority].TaskFunc = NULL;
}

void RTOS_voidSuspendTask(u8 Copy_u8Priority)
{
	SystemTasks[Copy_u8Priority].State = TASK_SUSPENDED;
}

void RTOS_voidResumeTask(u8 Copy_u8Priority)
{
	SystemTasks[Copy_u8Priority].State = TASK_RESUMED;
}


static void Schedular(void)
{
	u8 Local_u8TaskCounter;
	
	for(Local_u8TaskCounter = 0; Local_u8TaskCounter < TASK_NUM; Local_u8TaskCounter++)
	{
		/*Check if the task us resumed or suspended*/
		if(SystemTasks[Local_u8TaskCounter].State == TASK_RESUMED)
		{
			if(SystemTasks[Local_u8TaskCounter].FirstDelay == 0)
			{
				/* Invoke the task function */
				if(SystemTasks[Local_u8TaskCounter].TaskFunc != NULL)
				{
					SystemTasks[Local_u8TaskCounter].TaskFunc();
					SystemTasks[Local_u8TaskCounter].FirstDelay = SystemTasks[Local_u8TaskCounter].Periodicity - 1;
				}

			}
			else
			{
				/* Decrement The first delay */
				SystemTasks[Local_u8TaskCounter].FirstDelay--;
			}
		}
		else
		{
			/*Task is suspended , do nothing*/
		}

	}

}
