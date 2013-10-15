
/* Values for 'state'   */
#define INACTIVE        0
#define READY           1
#define RUNNING         2
#define WAIT_DLY        3
#define WAIT_ITV        4
#define WAIT_OR         5
#define WAIT_AND        6
#define WAIT_SEM        7
#define WAIT_MBX        8
#define WAIT_MUT        9
#define WAIT_MEM				10

typedef struct rl_task_info
{
	U8 state; /* Task state */
	U8 prio; /* Execution priority */
	U8 task_id; /* Task ID value for optimized TCB access */
	U8 stack_usage; /* Stack usage percent value. eg.=58 if 58%*/
	void (*ptask)(); /* Task entry address */
} RL_TASK_INFO;

/*----------------------------------------------------------------------------
 * User Defined API
 *---------------------------------------------------------------------------*/
#define __SVC_0					__svc_indirect(0)

/* Wrapper for os_tsk_count_get */
extern int rt_tsk_count_get(void);
#define os_tsk_count_get(void) _os_tsk_count_get((U32)rt_tsk_count_get)
extern int _os_tsk_count_get (U32 p) __SVC_0;

extern OS_RESULT rt_tsk_get (OS_TID task_id, RL_TASK_INFO *buffer);
#define os_tsk_get(task_id, buffer) _os_task_get((U32) rt_tsk_get, task_id, buffer)
extern OS_RESULT os_task_get(U32 p, OS_TID task_id, RL_TASK_INFO * buffer) __SVC_0;


