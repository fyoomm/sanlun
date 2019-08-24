#include "headfile.h"
   
/*-----------------------------------
          *��вɼ�����*
-----------------------------------*/
int16  Adc_Value[4];                   //�����ҵĵ��
int16  Adc_Value_guiyi[4];             //�����ҵĵ�й�һ����ֵ
/*-------------------------------------
          *��вɼ����ֵ��Сֵ*
---------------------------------------*/
uint16   AD_Value_Now[4] ={0,0,0,0};
uint16   AD_Value_Last[4]={0,0,0,0};
uint16   AD_Value_Max[4] ={0,0,0,0};
uint16   AD_Value_Min[4] ={10000,10000,10000,10000};
/*------------------------------------
         *���PD���Ʊ���*
--------------------------------------*/
float     Cha1_error;                  //�м�Ե�в�Ⱥ����
float     Cha2_error;                  //�Ա߶Ե�в�Ⱥ����
float     Cha_error;                   //�ܵ�в�Ⱥ����
float     NowError=0.0;                //��һ�����
float     LastError=0.0;               //��һ�����
float     Inductance_Error;            //��������ϴ����Ĳ�
float     NowError1=0.0;                //��һ�����
float     LastError1=0.0;               //��һ�����
float     Inductance_Error1;            //��������ϴ����Ĳ�
float     fuzzy_kp = 0.0;              //ģ����õ�kpֵ
float     fuzzy_kd = 0.0;              //ģ����õ�kdֵ
float     CHA_P;                       //ת��P
float     CHA_D;                       //ת��D
/*-------------------------------------
        *ת���ٶȿ��Ʊ���*
---------------------------------------*/
int16 sudu_turn_L=0;              //����ת���ٶ�
int16 sudu_turn_R=0;              //����ת���ٶ�
/*--------------------------------------
        *���������Ʊ���*
----------------------------------------*/
int16 ActualSpeed_L;                //����������
int16 ActualSpeed_R;                //����������
int8  temp1_Dir;                    //���ַ���  1��0��
int8  temp2_Dir;                    //���ַ���  0��1��
/*---------------------------------------
        *���������Ʊ���*
----------------------------------------*/
//�ٶȻ�
float   SpeedControlOutOld=0;          //�ɵ��ٶ�
float   SpeedControlOutNew=0;          //�µ��ٶ�
float   Speed_Error;                   //�µ��ٶ���ɵ��ٶȲ�
float   SPEED_OUT=0;                     //�ٶȻ����
float   TURN_OUT;                      //ת�����
float   PID_SPEED_P=10;                //�ٶȻ�P
float   PID_SPEED_I=0.1;             //�ٶȻ�I
float   SpeedControlIntegral=0;
float   SpeedError;
int8     SpeedCount=0;                 //�ٶ�һ��һ����ı���
int16    motor_L_out;                  //��ߵ�����
int16    motor_R_out;                  //�ұߵ�����
int16    Car_Actual_Speed;             //������ʵ�ٶ�
int16    Car_Set_Speed;               //���������ٶ�
int16    Car_Set_Speed_1=95;             //���������ٶ�
uint8    Limit_Speed=180;
uint8    Po_Dao_Speed=110;
/*--------------------------------------
        *С����״̬*
---------------------------------------*/
uint8    WorkMode;                   //�ж�С������״̬
/*--------------------------------------
        *��ʱ���任��Ҫ�ı���*
---------------------------------------*/
int8     AD_Time_Flag=0;            //AD�ɼ�ʱ����Ƶı�־λ
int8     Speed_Flag=0;               //�ٶ�ѡ���־λ
int8     huandao_A=0;               //�жϻ���������
int8     huandao_B=0;               //������������
int8     fuck=0;

uint8    Key_Check=0;               //������򿪹ذ���
/*--------------------------------------
        *ģ���Ŵ���*
---------------------------------------*/
int8    Inductance_Kp=20;//41
int8    Inductance_Kd=19;//45
int8    Inductance_Kp1=41;
int8    Inductance_Kd1=10;

/*-------------------һ�������ķָ���--------------------------*/

   int main(void)
{
    get_clk();                      //��ȡʱ��Ƶ�� ����ִ��
    AD_Init();                      //��г�ʼ��
    ELSE_Init();                    //�����ĳ�ʼ��
    FTM_Init();                     //���pwm�ͱ�������ʼ��
    Switch_init();                 //���뿪�س�ʼ�� 
    Work_choice();                 //ͨ�����뿪��ѡ��С���Ĺ���״̬
    WU_XIANG_Init();               //���򿪹س�ʼ��
    AD_GET_MAX_MIN();              //��������������Сֵ
    if(KEY_TWO==0)                 //���븴λ����
    Start_Car();
    Primary_Menu();
    while(1)
    {
      //boma_open();
     //  Uart1_Send_AF(Cha_error,Inductance_Error,CHA_P,CHA_D,0,0,0,0);
      // Uart1_Send_AF(ActualSpeed_L,ActualSpeed_R,Car_Actual_Speed,SpeedControlIntegral,motor_L_out,SpeedError,Car_Set_Speed,0);
  //    Uart1_Send_AF(Adc_Value_guiyi[0],Adc_Value_guiyi[1],Adc_Value_guiyi[2],Adc_Value_guiyi[3],0,0,0,0);
       Check_Key();
       if(Key_Check!=0)
       Primary_Menu(); 
    }
}
