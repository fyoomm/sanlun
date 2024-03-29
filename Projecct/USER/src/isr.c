/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2017,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：179029047
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		中断文件
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		v2.0
 * @Software 		IAR 7.7 or MDK 5.23
 * @Target core		S9KEA128AMLK
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2017-11-6
 ********************************************************************************************************************/



#include "isr.h"

void PIT_CH0_IRQHandler(void)
{
    PIT_FLAG_CLR(pit0);//清除标志
    static  uint8  SPEED_TIME_FLAG=0;
 //4ms循环一次
    if(AD_Time_Flag==0)
      {
       Get_AD();
       TURN_OUT_DIR();
       Speed_chioce();
      }
    AD_Time_Flag++;
    if(AD_Time_Flag>1)  
       AD_Time_Flag=0;
    //4ms循环一次到此为止
      /*--速度平缓控制--*/ 
        SPEED_TIME_FLAG++;
        if(SPEED_TIME_FLAG>=4)
        {
          get_speed();
          Speed_Control();
          SpeedCount=0;
          SPEED_TIME_FLAG=0;
        }
        Speed_Control_out();
        SpeedCount++;        
        motor_shuchu();
        Reed_End();   //检测停车
        if(KEY_SEVEN==1)
        {
           if((Adc_Value_guiyi[0]<25)&&(Adc_Value_guiyi[3]<25))
            {       
              ftm_pwm_duty(ftm2,ftm_ch1,0);
              ftm_pwm_duty(ftm2,ftm_ch0,0);
              ftm_pwm_duty(ftm2,ftm_ch3,0);
              ftm_pwm_duty(ftm2,ftm_ch2,0);
              DisableInterrupts;
            }
        }
        
}       

void PIT_CH1_IRQHandler(void)
{
}

void IRQ_IRQHandler(void)
{
    CLEAR_IRQ_FLAG;
    
}


void KBI0_IRQHandler(void)
{
    CLEAN_KBI0_FLAG;
    
}





/*
中断函数名称，用于设置对应功能的中断函数
Sample usage:当前启用了周期定时器 通道0得中断
void PIT_CH0_IRQHandler(void)
{
    ;
}
记得进入中断后清除标志位

FTMRE_IRQHandler      
PMC_IRQHandler        
IRQ_IRQHandler        
I2C0_IRQHandler       
I2C1_IRQHandler       
SPI0_IRQHandler       
SPI1_IRQHandler       
UART0_IRQHandler 
UART1_IRQHandler 
UART2_IRQHandler 
ADC0_IRQHandler       
ACMP0_IRQHandler      
FTM0_IRQHandler       
FTM1_IRQHandler       
FTM2_IRQHandler       
RTC_IRQHandler        
ACMP1_IRQHandler      
PIT_CH0_IRQHandler    
PIT_CH1_IRQHandler    
KBI0_IRQHandler       
KBI1_IRQHandler       
Reserved26_IRQHandler 
ICS_IRQHandler        
WDG_IRQHandler        
PWT_IRQHandler        
MSCAN_Rx_IRQHandler   
MSCAN_Tx_IRQHandler   
*/




