/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2017,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��179029047
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		KEA128_adc
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		v2.0
 * @Software 		IAR 7.7 or MDK 5.23
 * @Target core		S9KEA128AMLK
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2017-11-6
 ********************************************************************************************************************/


#include "KEA128_adc.h"


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ADC��ʼ��
//  @param      adcn_ch         ѡ��ADCͨ��
//  @return     void
//  @since      v2.0
//  Sample usage:               adc_init(ADC0_SE8);
//-------------------------------------------------------------------------------------------------------------------
void adc_init(ADCn_Ch adcn_ch)
{
    SIM->SCGC |= SIM_SCGC_ADC_MASK;         //����ADCʱ��
    
    ADC->APCTL1 |= 1<<adcn_ch;              //ʹ��ADC����
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ADC�ɼ�
//  @param      adcn_ch         ѡ��ADCͨ��
//  @param      bit             ѡ�񾫶�ADC_8bit��ADC_10bit��ADC_12bit
//  @return     void
//  @since      v2.0
//  Sample usage:               uint16 dat = adc_once(ADC0_SE8,ADC_12bit);//�ɼ�ADC0_SE8��ѹ������12λ
//-------------------------------------------------------------------------------------------------------------------
uint16 adc_once(ADCn_Ch adcn_ch, ADC_nbit bit)
{
    uint16 result;
    ADC->SC3 = (0
                | ADC_SC3_ADIV(0)           //��Ƶϵ��
                | ADC_SC3_MODE(bit)         //�ֱ���
                | ADC_SC3_ADICLK(0)         //ʹ������ʱ����ΪADC��ʱ��Դ
                );
        
    
    ADC->SC2 = ADC_SC2_REFSEL(0);           //��׼��ѹѡ��

    ADC->SC1 = ADC_SC1_ADCH(adcn_ch);       //����ת��
    
    while(!(ADC->SC1 & ADC_SC1_COCO_MASK)); //�ȴ�ת�����
    result = ADC->R;
    return (result & ADC_R_ADR_MASK);       //���ؽ��    
}
  /*************************************************************************
*  �������ƣ�ad_ave
*  ����˵������β�����ȡƽ��ֵ
*  ����˵���� adcn_ch ͨ����
*            bit     ���ȣ� ADC_8bit,ADC_12bit, ADC_10bit, ADC_16bit ��
*            N       ��ֵ�˲�����(��Χ:0~255)
*  for example       adc_once(ADC_CHANNEL_AD4,ADC_12BIT,10);
*************************************************************************/
uint32  adc_get(ADCn_Ch adcn_ch, ADC_nbit bit) //��ֵ�˲�
{
    uint32 ad_collect[5];
    for(int i=0;i<5;i++)
      ad_collect[i]=adc_once(adcn_ch, bit);
    uint32 temp=0;
        for(int i=0;i<5;i++)   
        {   
            for(int j=i+1;j<5;j++)
            {
                if(ad_collect[i]>ad_collect[j])   
                {   
                    temp=ad_collect[i];   
                    ad_collect[i]=ad_collect[j];   
                    ad_collect[j]=temp;   
                }
            }
        } 
        uint32  sum=0;
        for(int i=1;i<3;i++)
        {
            sum+=ad_collect[i];
        }
        sum/=3;
    return sum;
}
   /*************************************************************************
*  �������ƣ�ad_ave
*  ����˵������β�����ȡƽ��ֵ
*  ����˵���� adcn_ch ͨ����
*            bit     ���ȣ� ADC_8bit,ADC_12bit, ADC_10bit, ADC_16bit ��
*            N       ��ֵ�˲�����(��Χ:0~255)
*  for example       adc_once(ADC_CHANNEL_AD4,ADC_12BIT,10);
*************************************************************************/
char coe[7] = {1,2,3,4,3,2,1};
int8 sum_coe1 = 1+2+3+4+3+2+1;

uint32  adc_get1(ADCn_Ch adcn_ch, ADC_nbit bit)//��Ȩ����ƽ���˲��� 
{
   int32 value_buf[7];
   int32  sum=0;
   for (int8 count=0;count<7;count++)
   {
      value_buf[count] = adc_once(adcn_ch, bit);
   }
   for (int8 count=0;count<7;count++)
   {
      sum += value_buf[count]*coe[count];
   }
      sum /= sum_coe1;
   return (5000*sum)/((1<<8)-1);   
}




//-------------------------------------------------------------------------------------------------------------------
//  @brief      ADCֹͣ�ɼ�
//  @param      adcn_ch         ѡ��ADCͨ��
//  @param      bit             ѡ�񾫶�ADC_8bit��ADC_10bit��ADC_12bit
//  @return     void
//  @since      v2.0
//  Sample usage:               adc_stop(adc0);
//-------------------------------------------------------------------------------------------------------------------
void adc_stop(void)
{
    ADC->SC1 = ADC_SC1_ADCH(0xFF); 
}
