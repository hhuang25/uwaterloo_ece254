/**
 * @brief: ECE254 lab1 starter file that calls os_tsk_get()
 * @file: lab1_main.c
 * @author: Yiqing Huang
 * @date: 2013/05/28
 */
   
#include <LPC17xx.h>
#include "uart_polling.h"
#include "../../RTX_CM3/INC/RTL.h" /* modified RTL.h file. NOT the default one! */
#include <stdio.h>
#include <string.h>
  
struct func_info {
  void (*p)();      /* function pointer */
  char name[16];    /* name of the function */
};
  
extern void os_idle_demon(void);
__task void task1(void);
__task void task2(void);
__task void taskAllocate(void);
__task void taskBlocked(void);
__task void taskHigherPriority(void);
__task void init (void);
   
char *state2str(unsigned char state, char *str);
char *fp2name(void (*p)(), char *str);
  
OS_MUT g_mut_uart;
OS_TID g_tid = 255;
  
int  g_counter = 0;  // a global counter
char g_str[16];
char g_tsk_name[16];
  
void * allocated;
_declare_box(memoryPool,4,4);
  
struct func_info g_task_map[] = \
{
  /* os_idle_demon function ptr to be initialized in main */
  {NULL,  "os_idle_demon"}, \
  {task1, "task1"},   \
  {task2, "task2"},   \
	{taskAllocate, "allocate memory"},   \
	{taskBlocked, "blocked task"},   \
	{taskHigherPriority, "high prio task"},   \
  {init,  "init" }
};
  
/* no local variables defined, use one global var */
__task void task1(void)
{
    for (;;) {
        g_counter++;
    }
}
  
  
/*--------------------------- task2 -----------------------------------*/
/* checking states of all tasks in the system                          */
/*---------------------------------------------------------------------*/
__task void task2(void)
{
		os_mut_wait(g_mut_uart, 0xFFFF);
		printf("going into task2\n");
		os_mut_release(g_mut_uart);
  while(1){
		
		U8 i=1;
		RL_TASK_INFO task_info;

		os_dly_wait(2);
		
		os_mut_wait(g_mut_uart, 0xFFFF);
		printf("TID\tNAME\t\tPRIO\tSTATE   \t%%STACK\n");
		os_mut_release(g_mut_uart);
					
		for(i = 0; i <6; i++) { // this is a lazy way of doing loop.
				if (os_tsk_get(i+1, &task_info) == OS_R_OK) {
						os_mut_wait(g_mut_uart, 0xFFFF);  
						printf("%d\t%s\t\t%d\t%s\t%d%%\n", \
												 task_info.task_id, \
												 fp2name(task_info.ptask, g_tsk_name), \
												 task_info.prio, \
												 state2str(task_info.state, g_str),  \
												 task_info.stack_usage);
						os_mut_release(g_mut_uart);
				} 
		}
					
		if (os_tsk_get(0xFF, &task_info) == OS_R_OK) {
				os_mut_wait(g_mut_uart, 0xFFFF);  
				printf("%d\t%s\t%d\t%s\t%d%%\n", \
										 task_info.task_id, \
										 fp2name(task_info.ptask, g_tsk_name), \
										 task_info.prio, \
										 state2str(task_info.state, g_str),  \
										 task_info.stack_usage);
				os_mut_release(g_mut_uart);
		} 
	}
	//os_tsk_delete_self();
	
}
  
/*----------------------- taskAllocate --------------------------------*/
/* task to allocate memory                                             */
/*---------------------------------------------------------------------*/
__task void taskAllocate(void)
{

	
	allocated = os_mem_alloc(memoryPool);

	os_dly_wait(10);

	os_mem_free(memoryPool, allocated);
	
	os_dly_wait(10);
	os_tsk_delete_self();
}
  
/*----------------------- taskAllocate --------------------------------*/
/* task to get its memory blocked                                      */
/*---------------------------------------------------------------------*/
__task void taskBlocked(void)
{

		allocated = os_mem_alloc(memoryPool);
		os_dly_wait(10);
    os_mem_free(memoryPool, allocated);

		os_tsk_delete_self();
}
  
/*----------------------- taskAllocate --------------------------------*/
/* task with higher priority                                           */
/*---------------------------------------------------------------------*/
__task void taskHigherPriority(void)
{

		allocated = os_mem_alloc(memoryPool);
		os_dly_wait(10);
    os_mem_free(memoryPool, allocated);

		os_tsk_delete_self();
}
  
/*----------------------- taskAllocateOnly-----------------------------*/
/* task that only allocates                                            */
/*---------------------------------------------------------------------*/
__task void taskAllocateOnly(void)
{

		allocated = os_mem_alloc(memoryPool);
		os_dly_wait(10);
    //os_mem_free(memoryPool, allocated);

	  os_tsk_delete_self();
}
  
/*----------------------- taskDeleteOnly-----------------------------*/
/* task that only allocates                                            */
/*---------------------------------------------------------------------*/
__task void taskDeleteOnly(void)
{

		//allocated = os_mem_alloc(memoryPool);
		os_dly_wait(10);
    os_mem_free(memoryPool, allocated);


	  os_tsk_delete_self();
}

/*--------------------------- init ------------------------------------*/
/* initialize system resources and create other tasks                  */
/*---------------------------------------------------------------------*/
__task void init(void)
{
	os_mut_init(&g_mut_uart);
	_init_box(memoryPool,sizeof(memoryPool),16);
	os_dly_wait(2);
	g_tid = os_tsk_create(taskAllocate, 2); /* task to allocate memory at priority 2*/	
	os_dly_wait(2);	
	g_tid = os_tsk_create(taskHigherPriority, 5);/* task at priority 3*/
	os_dly_wait(2);
	g_tid = os_tsk_create(taskBlocked, 4); /* task to allocate memory at priority 5*/  
	os_dly_wait(2);
	g_tid = os_tsk_create(taskBlocked, 3);  /* task 1 at priority 4 */
		 
	os_dly_wait(2);
		
	g_tid = os_tsk_create(task2, 3);  /* task 2 at priority 3 */
	os_mut_wait(g_mut_uart, 0xFFFF);
	printf("init: created task2 with TID %d\n", g_tid);
	os_mut_release(g_mut_uart);

	os_tsk_delete_self();
}
    
/*--------------------------- init2------------------------------------*/
/* tests critical code where the user may have non-ideal behaviour     */
/*---------------------------------------------------------------------*/
__task void init2(void)
{
	os_mut_init(&g_mut_uart);
	_init_box(memoryPool,sizeof(memoryPool),16);

	g_tid = os_tsk_create(task2, 3);  /* task 2 at priority 3 */
	os_dly_wait(2);
	os_tsk_create(taskAllocateOnly, 4);
	os_dly_wait(2);
	os_tsk_create(taskAllocateOnly, 4);
	os_dly_wait(2);
	os_tsk_create(taskAllocateOnly, 4);
	os_dly_wait(2);
	os_tsk_create(taskAllocateOnly, 4);
	os_dly_wait(2);
	os_tsk_create(taskAllocateOnly, 4);
	os_dly_wait(2);
	os_tsk_create(taskDeleteOnly, 3);
		
	g_tid = os_tsk_create(task2, 3);  /* task 2 at priority 3 */
	os_mut_wait(g_mut_uart, 0xFFFF);
	printf("init: created task2 with TID %d\n", g_tid);
	os_mut_release(g_mut_uart);

	os_tsk_delete_self();
}

/**
 * @brief: convert state numerical value to string represenation      
 * @param: state numerical value (macro) of the task state
 * @param: str   buffer to save the string representation, 
 *               buffer to be allocated by the caller
 * @return:the string starting address
 */
char *state2str(unsigned char state, char *str)
{
  switch (state) {
    case INACTIVE:
    strcpy(str, "INACTIVE");
    break;
  case READY:
    strcpy(str, "READY   ");
    break;
  case RUNNING:
    strcpy(str, "RUNNING ");
    break;
  case WAIT_DLY:
    strcpy(str, "WAIT_DLY");
    break;
  case WAIT_ITV:
    strcpy(str, "WAIT_ITV");
    break;
  case WAIT_OR:
    strcpy(str, "WAIT_OR");
    break;
  case WAIT_AND:
    strcpy(str, "WAIT_AND");
    break;
  case WAIT_SEM:
    strcpy(str, "WAIT_SEM");
    break;
  case WAIT_MBX:
    strcpy(str, "WAIT_MBX");
    break;
  case WAIT_MUT:
    strcpy(str, "WAIT_MUT");
    break;
	  case WAIT_MEM:
    strcpy(str, "WAIT_MEM");
    break;
  default:
    strcpy(str, "UNKNOWN");    
  }
  return str;
}
  
/** 
 * @brief: get function name by function pointer
 * @param: p the entry point of a function (i.e. function pointer)
 * @param: str the buffer to return the function name
 * @return: the function name string starting address
 */
char *fp2name(void (*p)(), char *str)
{
  int i;
  unsigned char is_found = 0;
    
  for ( i = 0; i < 7; i++) {
    if (g_task_map[i].p == p) {
      str = strcpy(str, g_task_map[i].name);  
      is_found = 1;
      break;
    }
  }
  if (is_found == 0) {
      strcpy(str, "ghost");
  }
  return str;
}
  
int main(void)
{
  SystemInit();         /* initialize the LPC17xx MCU */
  uart0_init();         /* initilize the first UART */
    
      
  /* fill the fname map with os_idle_demon entry point */
  g_task_map[0].p = os_idle_demon;
    
  printf("Calling os_sys_init()...\n");
	os_sys_init(init);    /* initilize the OS and start the first task */
	//os_sys_init(init2);    /* initilize the OS and start the first task */
} 
