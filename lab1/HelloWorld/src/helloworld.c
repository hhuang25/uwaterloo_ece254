#include <LPC17xx.h>
#include "uart_polling.h"
#include "../../RTX_CM3/INC/RTL.h"
#include <stdio.h>

__task void task1()
{
	unsigned int i = 0;
	for(;; i++)
	{
		printf("Task1: %d\n", i);
		os_dly_wait(100);
	}
}

__task void task2()
{
	while(1)
	{
		printf("Task2: HelloWorld!\n");
		os_dly_wait(300);
	}
}

__task void task3()
{
	int g = 1;
	while(1)
	{
		g = g + g;
		os_dly_wait(300);
	}
}

__task void task4()
{
	int p = 1;
	while(1)
	{
		p = p + p;
		os_dly_wait(300);
	}
}

__task void SysMon()
{
	while(1)
	{
		int num = os_tsk_count_get();
		printf("Number of tasks running: %i\n", num);
		os_dly_wait(100);
	}
}

__task void lab1()
{
	
	
}

__task void init(void)
{
	os_tsk_create(task1, 1); // task1 at priority 1
	os_tsk_create(task2, 1); // task2 at priority 1
	os_tsk_create(task3, 1); // task1 at priority 1
	os_tsk_create(task4, 1); // task2 at priority 1
	os_tsk_create(lab1, 1);
	os_tsk_delete_self(); // must delete itself before exiting
}
/*
int main()
{
  SystemInit();
  uart0_init();
  os_sys_init(init);
}
*/
