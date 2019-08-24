#ifndef _SAN__LUN_c
#define _SAN__LUN_c

#include "headfile.h"

#define RANK     7

#define LEFT_PISITION_GAIN           1.0        //������ƫ���ƽֵ
#define RIGHT_PISITION_GAIN          1.0       //������ƫ���ƽֵ
#define POSITION_BOUND               350        //����ƫ���޷�ֵ
#define BEEP_ON         gpio_set(E5,0)
#define BEEP_OFF        gpio_set(E5,1)
#define MAX( x, y ) ( ((x) > (y)) ? (x) : (y) )
#define MIN( x, y ) ( ((x) < (y)) ? (x) : (y) )
#define ad_L1_gain    adc_get(ADC0_SE9,ADC_12bit)
#define ad_L2_gain    adc_get(ADC0_SE8,ADC_12bit)
#define ad_R1_gain    adc_get(ADC0_SE11,ADC_12bit)
#define ad_R2_gain    adc_get(ADC0_SE10,ADC_12bit)
/*****--------------��������ֽ���-------------*****/

extern int8       Inductance_Kp;
extern int8       Inductance_Kd;
extern int8       Inductance_Kp1;
extern int8       Inductance_Kd1;
extern int8       huandao_A;
extern int8       huandao_B;
extern int8       fuck;
extern int16      Adc_Value[4];                   //�����ҵĵ��
extern int16      Adc_Value_guiyi[4];             //�����ҵĵ�й�һ����ֵ
extern uint16     AD_Value_Now[4];
extern uint16     AD_Value_Last[4];
extern uint16     AD_Value_Max[4];
extern uint16     AD_Value_Min[4];


extern float     NowError;                  //��һ�����
extern float     LastError;                 //��һ�ε�����
extern float     Inductance_Error;          //��������ϴ����Ĳ�
extern float     NowError1;                  //��һ�����
extern float     LastError1;                 //��һ�ε�����
extern float     Inductance_Error1;          //��������ϴ����Ĳ�
extern float     Cha1_error;                //�м�Ե�в�Ⱥ����
extern float     Cha2_error;                //�Ա߶Ե�в�Ⱥ����
extern float     Cha_error;                 //�ܵ�в�Ⱥ����
extern float     fuzzy_kp;                  //ģ����õ�kpֵ
extern float     fuzzy_kd;                  //ģ����õ�kdֵ
extern float     TURN_OUT;                  //ת�����
extern float     CHA_P;                     //ת��P
extern float     CHA_D;                     //ת��D


/*****-------------���庯���ֽ���---------------*****/

void     AD_Init(void);                                     //��г�ʼ��
void     ELSE_Init(void);                                   //�����ĳ�ʼ��
void     Get_AD(void);                                      //��ȡADֵ
void     TURN_OUT_DIR(void);
void     KP_Fuzzy(float position , float position_error);   //ģ��PD
void     Turn_Out_Filter(void);                               //ת���������˲�      
float    position_filter(float position);                     //���ֵ�˲�
int16    PID_Dir_error(float Now_Error);                      //���PD���� 
int16    PID_Dir_error1(float Now_Error);                      //���PD���� 
int16    Abs(int16 value);                                    //����ֵ����
float   Float_Abs(float value);
int32    diangan_gui_yi(int32 diangan_temp);                    //��й�һ��
void    AD_GET_MAX_MIN(void);
void    Reed_End(void);
void    Start_Car();


#endif