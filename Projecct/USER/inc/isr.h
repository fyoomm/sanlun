#ifndef _isr_h
#define _isr_h

#include "headfile.h"
   
/*****--------------��������ֽ���-------------*****/
   
extern  int8     AD_Time_Flag;    //��ʱ6ms��Ҫ�ı���

/*****-------------���庯���ֽ���---------------*****/

void PIT_CH0_IRQHandler(void);  
   
   
   
#endif
