#ifndef _SPEED__CONCTOL_C
#define _SPEED__CONCTOL_C

#include "headfile.h"
 

#define Speed_Filter_Times   6                           //���ٶȷ�Ϊ�ķݣ���ݼ��ٶ�

/*----------------��������ֽ���--------------------*/
extern   float  SpeedError;
extern   int8     Speed_Flag;                   //�ٶ�ѡ���־λ
extern   int8     temp1_Dir;                   //���ַ���  1��0��
extern   int8     temp2_Dir;                   //���ַ���  0��1��
extern   int16    Car_Actual_Speed;            //������ʵ�ٶ�
extern   int16    Car_Set_Speed;               //���������ٶ�
extern   int16    Car_Set_Speed_1;               //���������ٶ�
extern   int16    motor_L_out;                 //��ߵ�����
extern   int16    motor_R_out;                 //�ұߵ�����
extern   uint8    WorkMode;                    //�ж�С������״̬
extern   int8     SpeedCount;                  //�ٶ�һ��һ����ı�
extern   int16    ActualSpeed_L;               //����������
extern   int16    ActualSpeed_R;               //����������
extern   float   SPEED_OUT;                   //�ٶȻ����
extern   float   PID_SPEED_P;                  //�ٶȻ�P
extern   float   PID_SPEED_I;                  //�ٶȻ�I
extern   float   SpeedControlOutOld;          //�ɵ��ٶ�
extern   float   SpeedControlOutNew;          //�µ��ٶ�
extern   float   Speed_Error;                 //�µ��ٶ���ɵ��ٶȲ�
extern   float   SpeedControlIntegral;        //�ٶȻ�����
extern   uint8    Limit_Speed;                 //�ٶȱ仯��Χ
extern   uint8    Po_Dao_Speed;                

/*-----------------���庯���ֽ���-------------------*/
int16       speed_collect_L();                                //��߱������������з���
int16       speed_collect_R();                                //�ұ߱������������з���
void        get_speed();                                     //��ȡ���������ٶȺ�����м��ٶ�
void        Speed_Control_out(void);                         //�ٶȻ��Ŀ���
void        motor_shuchu(void);                              //����������
void        Speed_Control(void);                              //�ٶȻ����Ʊ���
void        FTM_Init(void);                                    //���pwm�ͱ�������ʼ��
void        Speed_chioce(void);

#endif