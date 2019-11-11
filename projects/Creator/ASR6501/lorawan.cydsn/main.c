#include "project.h"
#include <stdio.h>
#ifdef AOS_KV
#include "kvmgr.h"
#endif
#include <uart_port.h>
#include "hw.h"
#include "hw_conf.h"
#include "spi.h"
#include "rtc-board.h"
#include "asr_timer.h"

extern int application_start();
extern void GpioIsrEntry (void);
extern void board_init(void);
static void sys_start(void)
{
    //board_init();
    SpiInit(); //SPI初始化
    default_UART_Init();//默认串口初始化
   
    global_irq_StartEx(GpioIsrEntry);
    /* set wco */
    Asr_Timer_Init();//ASR timer初始化
    RtcInit();//RTC初始化

    application_start();//应用启动
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
	  
    sys_start();
    
    while(1){
    }
    return 0;
}