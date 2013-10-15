#include "rt_TypeDef.h"
#include "RTX_Config.h"
#include "rt_System.h"
#include "rt_Task.h"
#include "rt_List.h"
#include "rt_MemBox.h"
#include "rt_Robin.h"
#include "rt_HAL_CM.h"
#include "rt_user.h"


/*----------------------------------------------------------------------------
 * User Implemented Function
 *---------------------------------------------------------------------------*/
 
/*------------------------ os_tsk_count_get ---------------------------------*/
int os_tsk_count_get (void)
{
	int p_new = 0;
	int i;
	if(os_idle_TCB.state != 0)
	{
		p_new++;
	}
	for (i = 0; i < os_maxtaskrun; i++)
	{
    if (os_active_TCB[i] != NULL &&((P_TCB)os_active_TCB[i])->state != 0)
		{
			p_new++;
		}
	}
	return p_new;
}

/*--------------------------- os_tsk_get ------------------------------------*/
OS_RESULT os_tsk_get (OS_TID task_id, RL_TASK_INFO *buffer)
{

	//we do not need to loop because we know the index that has relationship with task_id. Reference to lab 0B (n-1)

	if(os_active_TCB[task_id-1] != NULL && ((P_TCB)os_active_TCB[task_id-1])->task_id == task_id)
	{
		//Assume Success
		buffer->state = ((P_TCB)os_active_TCB[task_id-1])->state;
		buffer->prio = ((P_TCB)os_active_TCB[task_id-1])->prio;
		buffer->task_id = task_id;
		//os_stackinfo
		//buffer->stack_usage = sizeof(buffer)/(sizeof(buffer)*os_maxtaskrun)
		buffer->ptask = os_active_TCB[task_id-1]->ptask;
		return(OS_R_OK);
	}
		
	//Assume Failure
	return(OS_R_NOK);
}
