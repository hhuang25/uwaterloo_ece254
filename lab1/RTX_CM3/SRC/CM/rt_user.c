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

struct OS_XCB WaitingForMem = {
	HCB,
	NULL,
	NULL,
	NULL,
	NULL,
	0
};
   
/*------------------------ os_tsk_count_get ---------------------------------*/
int rt_tsk_count_get (void)
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
OS_RESULT rt_tsk_get (OS_TID task_id, RL_TASK_INFO *buffer)
{
    //get top of stack
    P_TCB p_TCB;
    U32 stk, initial;
    U16 total;
      
    //we do not need to loop because we know the index that has relationship with task_id. Reference to lab 0B (n-1)
  
    if(os_active_TCB[task_id-1] != NULL && ((P_TCB)os_active_TCB[task_id-1])->task_id == task_id)
    {
        //Assume Success
        buffer->state = ((P_TCB)os_active_TCB[task_id-1])->state;
        buffer->prio = ((P_TCB)os_active_TCB[task_id-1])->prio;
        buffer->task_id = task_id;
        p_TCB = os_active_TCB[task_id-1];
  
        /* total stack size */
        total = (U16)os_stackinfo;
  
        /* Write to the top of stack. */
        stk = (U32)&p_TCB->stack[total/4];
			
				/* bottom of stack*/
        if(p_TCB->state == RUNNING)
				{
            initial = (U32)rt_get_PSP();
        }
        else {
            initial = (U32)p_TCB->tsk_stack;
        }
        /* (final - initial) / total size * 100% */
        buffer->stack_usage = (stk - initial)/(double)total*100;
        buffer->ptask = ((P_TCB)os_active_TCB[task_id-1])->ptask;
        return(OS_R_OK);
    }
          
    //Assume Failure
    return(OS_R_NOK);
}
  
void *rt_mem_alloc (void *box_mem)
{
	
    OS_TID CurrentTask;
    void *mem_avail;
		
    CurrentTask = rt_tsk_self();
		
    //idle task should not call this
    if(CurrentTask != 0xFF)
    {
      
				mem_avail = rt_alloc_box(box_mem);  
				//no memory available
        if(mem_avail == NULL)
        {
						//queue and block
            rt_put_prio(&WaitingForMem, os_active_TCB[CurrentTask-1]);
            rt_block (0xFF, WAIT_MEM);
        }
        return(mem_avail);
    }
    return(NULL);
}
  
OS_RESULT rt_mem_free (void *box_mem, void *box)
{
    int OK;
    P_TCB unblocked;
    //valid range of memory of box
    if(box > box_mem && box <= ((P_BM) box_mem)->end)
    {
			//something is waiting in the box
			if(WaitingForMem.p_lnk != NULL){
				//get first item in queue
				unblocked = rt_get_first(&WaitingForMem);
				unblocked->ret_val = (U32)box;
			}
			//free the memory
			OK = rt_free_box(box_mem, box);
			if(OK != 0){
				// dequeue
				rt_dispatch(unblocked);
				return(OS_R_OK);
			}else{
				return(OS_R_NOK);
			}
		}
		return(OS_R_NOK);
		
} 
