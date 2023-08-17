/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2017,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��179029047
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		�ж��ļ�
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		v2.0
 * @Software 		IAR 7.7 or MDK 5.23
 * @Target core		S9KEA128AMLK
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2017-11-6
 ********************************************************************************************************************/



#include "isr.h"

void PIT_CH0_IRQHandler(void)
{
    PIT_FLAG_CLR(pit0);//�����־
    static  uint8  SPEED_TIME_FLAG=0;
 //4msѭ��һ��
    if(AD_Time_Flag==0)
      {
       Get_AD();
       TURN_OUT_DIR();
       Speed_chioce();
      }
    AD_Time_Flag++;
    if(AD_Time_Flag>1)  
       AD_Time_Flag=0;
    //4msѭ��һ�ε���Ϊֹ
      /*--�ٶ�ƽ������--*/ 
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
        Reed_End();   //���ͣ��
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
�жϺ������ƣ��������ö�Ӧ���ܵ��жϺ���
Sample usage:��ǰ���������ڶ�ʱ�� ͨ��0���ж�
void PIT_CH0_IRQHandler(void)
{
    ;
}
�ǵý����жϺ������־λ

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




