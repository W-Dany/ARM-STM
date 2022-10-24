#include "includes.h"

//define task control block
static OS_TCB		AppTaskStartTCB;
static OS_TCB		Led1TaskTCB;
static OS_TCB		Led2TaskTCB;
static OS_TCB		Led3TaskTCB;


//define task stack
static CPU_STK		AppTaskStartStk[APP_TASK_START_STK_SIZE];
static CPU_STK		Led1TaskStk[APP_TASK_LED1_STK_SIZE];
static CPU_STK		Led2TaskStk[APP_TASK_LED2_STK_SIZE];
static CPU_STK		Led3TaskStk[APP_TASK_LED3_STK_SIZE];


static void AppStart_Task(void *p_arg);
static void Led1_Task(void *p_arg);
static void Led2_Task(void *p_arg);
static void Led3_Task(void *p_arg);


void systick_init(void)
{
	uint32_t rcc_clocks;
	uint32_t cnt;

	rcc_clocks = HAL_RCC_GetSysClockFreq();
	cnt = rcc_clocks / 1000;
	
	CPU_REG_NVIC_ST_CTRL |= SysTick_CTRL_TICKINT_Msk;//开启SYSTICK中断
	CPU_REG_NVIC_ST_RELOAD = cnt; 					//每1/OS_TICKS_PER_SEC秒中断一次	
	CPU_REG_NVIC_ST_CTRL |= SysTick_CTRL_ENABLE_Msk; //开启SYSTICK
}

void my_delay(u32 cnt)
{
	while(cnt--);
}

int main(void)
{
	OS_ERR  err;
	
	Stm32_Clock_Init(360,25,2,7);
	
//	BSP_Init();
//	systick_init();
//	
//	while(1)
//	{
//		LED0 = ~LED0;
//		my_delay(0xfffff);
//	}
	
//	OS_ERR  err;
	
	OSInit(&err);
	
	OSTaskCreate((OS_TCB	 		*)	&AppTaskStartTCB,
							 (CPU_CHAR 		*)	"APP_TASK_START",
							 (OS_TASK_PTR	 )	AppStart_Task,
							 (void 				*)  0,
							 (OS_PRIO			 )  APP_TASK_START_PRIO,
							 (CPU_STK			*)	&AppTaskStartStk[0],
							 (CPU_STK_SIZE )	APP_TASK_START_STK_SIZE/10,
							 (CPU_STK_SIZE )  APP_TASK_START_STK_SIZE,
							 (OS_MSG_QTY	 )	5u,
							 (OS_TICK			 ) 	0u,
							 (void 				*)	0,
							 (OS_OPT			 )	(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
							 (OS_ERR			*) 	&err);
							 
	OSStart(&err);
}

static void AppStart_Task(void *p_arg)
{
	CPU_INT32U	cpu_clk_freq;
	CPU_INT32U	cnts;
	OS_ERR			err;
	
	(void)p_arg;
	CPU_Init();
	BSP_Init();
#if 0	
	cpu_clk_freq = BSP_CPU_ClkFreq();
	cnts = cpu_clk_freq / (CPU_INT32U)(OSCfg_TickRate_Hz);
	OS_CPU_SysTickInit(cnts);
#endif
	systick_init();
	
	Mem_Init();
	
#if OS_CFG_STAT_TASK_EN > 0u
    OSStatTaskCPUUsageInit(&err);                               /* Compute CPU capacity with no task running            */
#endif

#ifdef CPU_CFG_INT_DIS_MEAS_EN
    CPU_IntDisMeasMaxCurReset();
#endif


    OSTaskCreate((OS_TCB     *)&Led1TaskTCB,                /* Create the Led1 task                                */
                 (CPU_CHAR   *)"Task Led1",
                 (OS_TASK_PTR ) Led1_Task,
                 (void       *) 0,
                 (OS_PRIO     ) APP_TASK_LED1_PRIO,
                 (CPU_STK    *)&Led1TaskStk[0],
                 (CPU_STK_SIZE) APP_TASK_LED1_STK_SIZE / 10,
                 (CPU_STK_SIZE) APP_TASK_LED1_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);
	#if 0							 
    OSTaskCreate((OS_TCB     *)&Led2TaskTCB,                /* Create the Led2 task                                */
                 (CPU_CHAR   *)"Task Led2",
                 (OS_TASK_PTR ) Led2_Task,
                 (void       *) 0,
                 (OS_PRIO     ) APP_TASK_LED2_PRIO,
                 (CPU_STK    *)&Led2TaskStk[0],
                 (CPU_STK_SIZE) APP_TASK_LED2_STK_SIZE / 10,
                 (CPU_STK_SIZE) APP_TASK_LED2_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);

    OSTaskCreate((OS_TCB     *)&Led3TaskTCB,                /* Create the Led3 task                                */
                 (CPU_CHAR   *)"Task Led3",
                 (OS_TASK_PTR ) Led3_Task,
                 (void       *) 0,
                 (OS_PRIO     ) APP_TASK_LED3_PRIO,
                 (CPU_STK    *)&Led3TaskStk[0],
                 (CPU_STK_SIZE) APP_TASK_LED3_STK_SIZE / 10,
                 (CPU_STK_SIZE) APP_TASK_LED3_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);
		
	#endif
		OSTaskDel ( &AppTaskStartTCB, & err );
}

static void Led1_Task(void *p_arg)
{
	
	OS_ERR      err;

 (void)p_arg;


	while (DEF_TRUE) {                                          /* Task body, always written as an infinite loop.       */
		LED0 = ~LED0;
		OSTimeDly ( 300, OS_OPT_TIME_DLY, & err );
	}
}

static void Led2_Task(void *p_arg)
{
	
	OS_ERR      err;

 (void)p_arg;


	while (DEF_TRUE) {                                          /* Task body, always written as an infinite loop.       */
		LED1 = ~LED1;
		OSTimeDly ( 600, OS_OPT_TIME_DLY, & err );
	}
}

static void Led3_Task(void *p_arg)
{
	
	OS_ERR      err;

 (void)p_arg;

	while (DEF_TRUE) {                                          /* Task body, always written as an infinite loop.       */
		LED2 = ~LED2;
		OSTimeDly ( 1000, OS_OPT_TIME_DLY, & err );
	}
}

