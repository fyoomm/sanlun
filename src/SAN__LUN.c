
#include "SAN__LUN.h"

/*----------------------��г�ʼ��-------------------------------------*/
void AD_Init(void)           
{
    adc_init(ADC0_SE8);        //ADC��ʼ��  ��һ
    adc_init(ADC0_SE9);        //ADC��ʼ��   ���
    adc_init(ADC0_SE10);       //ADC��ʼ��   ��һ
    adc_init(ADC0_SE11);       //ADC��ʼ��   �Ҷ�
}
/*-----------------------�����ĳ�ʼ��----------------------------------*/
void ELSE_Init(void)     
{
    uart_init(uart2,38400);  //������ʼ��
    OLED_Init();             //OLED��ʼ��
    gpio_init(E5,GPO,1);     //������
    gpio_init(I5,GPI,1);     //ͣ����־
    FLASH_Init();            //flash��ʼ��    
}
/*------------------------����·�ε��PD����---------------------------*/
int16   PID_Dir_error(float Now_Error)   
{
     int16   Cha_Uk;
     NowError=Now_Error;
     Inductance_Error=NowError-LastError;
     KP_Fuzzy(NowError,Inductance_Error);
     CHA_P =Inductance_Kp * (fuzzy_kp);
     CHA_D =Inductance_Kd * (fuzzy_kd);
     Cha_Uk=(int)(CHA_P*NowError+CHA_D*Inductance_Error);
     LastError=NowError;//���ϴεı������
     if(Cha_Uk>930)
       Cha_Uk=930;
     if(Cha_Uk<-930)
      Cha_Uk=(-930);
     return Cha_Uk;
}
/*------------------------����·�ε��PD����----------------------------*/
int16  PID_Dir_error1(float Now_Error)
{
     int16   Cha_Uk;
     NowError1=Now_Error;
     Inductance_Error1=NowError1-LastError1;
     KP_Fuzzy(NowError1,Inductance_Error1);
     CHA_P = Inductance_Kp1 * (fuzzy_kp);
     CHA_D = Inductance_Kd1 * (fuzzy_kd);
     Cha_Uk=(int)(CHA_P*NowError1+CHA_D*Inductance_Error1);
     LastError1=NowError1;//���ϴεı������
     if(Cha_Uk>930)
       Cha_Uk=930;
     if(Cha_Uk<-930)
      Cha_Uk=(-930);
     return Cha_Uk;
}
/*----------------------ȡ����ֵ------------------------------------------*/
int16    Abs(int16 value)           
{
    int16    F_value;
    if(value>=0)
       F_value=value;
    else if(value<0)
       F_value=(-1)*value;
    return  F_value;
}
/*----------------------������ȡ����ֵ------------------------------------*/
float   Float_Abs(float value)           
{
    float    F_value;
    if(value>=0)
       F_value=value;
    else if(value<0)
       F_value=(-1)*value;
    return  F_value;
}
/*------------------------��ȡ���������Сֵ------ ------------------------*/
void  AD_GET_MAX_MIN(void)
{
      uint8 COLLECT_SIGN = 0;       //д�����ݱ�־λ
      uint8 sector  = FLASH_SECTOR_NUM - 1;
      uint8 sector1 = FLASH_SECTOR_NUM - 2;
      while(KEY_ONE==0)
       {
         static  uint8  fan=0;
         COLLECT_SIGN = 1;
         AD_Value_Now[0] = ad_L2_gain;
         AD_Value_Now[1] = ad_L1_gain;   
         AD_Value_Now[2] = ad_R1_gain;
         AD_Value_Now[3] = ad_R2_gain;
         for(uint8 i=0;i<4;i++)
          {
             if(AD_Value_Max[i]<MAX(AD_Value_Now[i],AD_Value_Last[i]))
               {
                 AD_Value_Max[i]=MAX(AD_Value_Now[i],AD_Value_Last[i]);
               }
          }
      if(fan==0)
         {
           for(uint8 i=0;i<4;i++)
            {
              AD_Value_Last[i]=AD_Value_Now[i];
            }
           fan++;
         }
      for(uint8 i=0;i<4;i++)
       {
         if(AD_Value_Min[i]>MIN(AD_Value_Now[i],AD_Value_Last[i]))
          {
            AD_Value_Min[i]=MIN(AD_Value_Now[i],AD_Value_Last[i]);
          }
       }
       for(uint8 i=0;i<2;i++)
       {
         AD_Value_Last[i]=AD_Value_Now[i];
       }
       OLED_P8x16Str(0,0,"L2");
       OLED_Print_Num(30,0,AD_Value_Max[0]);
       OLED_Print_Num(80,0,AD_Value_Min[0]);
       OLED_P8x16Str(0,2,"L1");
       OLED_Print_Num(30,2,AD_Value_Max[1]);
       OLED_Print_Num(80,2,AD_Value_Min[1]);
       OLED_P8x16Str(0,4,"R1");
       OLED_Print_Num(30,4,AD_Value_Max[2]);
       OLED_Print_Num(80,4,AD_Value_Min[2]); 
       OLED_P8x16Str(0,6,"R2");
       OLED_Print_Num(30,6,AD_Value_Max[3]);
       OLED_Print_Num(80,6,AD_Value_Min[3]); 
      }
  if(COLLECT_SIGN==1)             //д������
    {
     FLASH_EraseSector(sector );   //������������
     FLASH_EraseSector(sector1);   //������������
     for(uint8 i=0;i<4;i++)
     {
       FLASH_WriteSector(sector ,(const uint8 *)&AD_Value_Max[i],4,4*i);
       FLASH_WriteSector(sector1,(const uint8 *)&AD_Value_Min[i],4,4*i);
     }
     }
  for(uint8 i=0;i<4;i++)     //��ȡ����
  {
    AD_Value_Max[i]=flash_read(sector ,4*i,uint16);
    AD_Value_Min[i]=flash_read(sector1,4*i,uint16);
  }
    Oled_Clr();  
}
/*-----------------------��вɼ����һ��------------------------------*/
void Get_AD(void)
{
        Adc_Value[0] = ad_L2_gain;
        Adc_Value[1] = ad_L1_gain;   
        Adc_Value[2] = ad_R1_gain;
        Adc_Value[3] = ad_R2_gain;
        for(int8 i=0;i<4;i++)
        {
          Adc_Value_guiyi[i]=(1000*(Adc_Value[i]-AD_Value_Min[i])/(AD_Value_Max[i]-AD_Value_Min[i]));
          if(Adc_Value_guiyi[i]>1000)
          Adc_Value_guiyi[i]=1000;
          else if(Adc_Value_guiyi[i]<=0)
          Adc_Value_guiyi[i]=1;     
        }
}
/*-------------------------ת��---------------------------------------*/
void TURN_OUT_DIR(void)
{
     static   int16   flag2=0;
       if(huandao_A==0)
       {
          if(((Adc_Value_guiyi[0]+Adc_Value_guiyi[3])>1700))
           {
            huandao_A=1;
            if(KEY_THREE==0)       fuck++;
           }
       }
        if((huandao_A==1)&&(huandao_B==0))
        {
          if((Adc_Value_guiyi[0]+Adc_Value_guiyi[3])<1200)
          {
            huandao_B=1;
          }   
        }
        if(huandao_B==1)
        {
          if(((Adc_Value_guiyi[0]+Adc_Value_guiyi[3]))>1600)
           {
             huandao_B=2;
           }
        }
        if(huandao_B==2)
        {
          if(((Adc_Value_guiyi[0]+Adc_Value_guiyi[3])<1200))
          {
            huandao_B=0;
            huandao_A=0;
            if(KEY_THREE==0)       fuck++;
          }
        }
       if(huandao_B==1)     flag2++;
       if(flag2>450&&KEY_FOUR==1)     Speed_Flag=4;
       if(huandao_B==2)     flag2=0;
        switch(huandao_A)
        {
          case 0:
            Cha2_error=(((sqrt(Adc_Value_guiyi[0])-sqrt(Adc_Value_guiyi[3]))*1.0/(Adc_Value_guiyi[0]+Adc_Value_guiyi[3]))*5000);
            //Cha1_error=(((sqrt(Adc_Value_guiyi[1])-sqrt(Adc_Value_guiyi[2]))*1.0/(Adc_Value_guiyi[1]+Adc_Value_guiyi[2]))*5000);
            Cha_error=position_filter(Cha2_error);
            TURN_OUT=PID_Dir_error(Cha_error);
            Turn_Out_Filter();
            break;
          case 1:
            if(huandao_B==0)
            {
              Cha1_error=(((sqrt(Adc_Value_guiyi[1])-sqrt(Adc_Value_guiyi[2]))*1.0/(Adc_Value_guiyi[1]+Adc_Value_guiyi[2]))*5000);
              Cha_error=Cha1_error;
              TURN_OUT=PID_Dir_error1(Cha_error);
            }
            else if(huandao_B==1)
            {
              Cha2_error=(((sqrt(Adc_Value_guiyi[0])-sqrt(Adc_Value_guiyi[3]))*1.0/(Adc_Value_guiyi[0]+Adc_Value_guiyi[3]))*5000);
              Cha_error=Cha2_error;
              TURN_OUT=PID_Dir_error(Cha_error);
              Turn_Out_Filter(); 
            }
            else if(huandao_B==2)
            {
              int8 b;
              if(Adc_Value_guiyi[0]>Adc_Value_guiyi[3])  b=-2;
              if(Adc_Value_guiyi[0]<Adc_Value_guiyi[3])  b=2;
              Cha2_error=(((b+sqrt(Adc_Value_guiyi[0])-sqrt(Adc_Value_guiyi[3]))*1.0/(Adc_Value_guiyi[0]+Adc_Value_guiyi[3]))*5000);
              Cha_error=Cha2_error;
              TURN_OUT=PID_Dir_error(Cha_error);
              Turn_Out_Filter();
            }
            break;
         default : 
              break;
          
        }
     if(Speed_Flag!=4)
     {
       switch(huandao_A)
        {
          case 0:
            Speed_Flag=0;
            break;
          case 1:
            if(huandao_B==0)
            {
              Speed_Flag=1;
            }
            else if(huandao_B==1)
            {
              Speed_Flag=2; 
            }
            else if(huandao_B==2)
            {
              Speed_Flag=3;
            }
            break;
         default : 
              break;
          
        }
     }
}
/*------------------ת���������˲�---------------------------------*/
void  Turn_Out_Filter(void)        
{
  static float Pre1_Error[4]; 
  Pre1_Error[3]=Pre1_Error[2];
  Pre1_Error[2]=Pre1_Error[1];
  Pre1_Error[1]=Pre1_Error[0];
  Pre1_Error[0]=TURN_OUT;
  TURN_OUT=Pre1_Error[0]*0.4+Pre1_Error[1]*0.3+Pre1_Error[2]*0.2+Pre1_Error[3]*0.1;
}
/*--------------------���ֵ�˲�--------------------------------------*/
float position_filter(float position)  
{
        static float position_add[5]={0,0,0,0,0};
        float position_add_copy[5];
        int32 position_total = 0;
        float position_average;
        float temp = 0.0;
        uint8 i = 0;
        uint8 j = 0;
        
        for( i = 4 ; i>0 ; i--)
        {
            position_add[i] = position_add[i-1];              //����ѭ������
        }
        position_add[0] = position;                           //�����ε�ƫ��ŵ�����ͷ�� 
        
        for(i=0;i<5;i++)
        {
            position_add_copy[i] = position_add[i];
        }  
        
        for( i=0;i<5;i++)                   //ð������
        {
            for( j=i+1;j<5;j++)
            {
                    if(position_add_copy[i] > position_add_copy[j])
                    {
                            temp = position_add_copy[i];
                            position_add_copy[i] = position_add_copy[j];
                            position_add_copy[j] = temp;
                    }
            }
        }
        
        for( i=1 ; i<4 ;i++) 
        {
            position_total += position_add_copy[i];                        //ȥ����С��3��������3��������ֵ���
        } 
        position_average = position_total / 3.0f;
        
        if(position_average > 0.0f)                              //������ƫ����е�ƽ
        {
          position_average *= LEFT_PISITION_GAIN;
        }
        if(position_average < 0.0f)
        {
          position_average *= RIGHT_PISITION_GAIN;
        }
        
        if(position_average > POSITION_BOUND)                              //��ƫ������޷�
        {
          position_average = POSITION_BOUND;
        }
        if(position_average < (-(POSITION_BOUND)))
        {
          position_average = (-(POSITION_BOUND));
        }
        return position_average;
}




//**************************************************************
/***************------   ģ��  PID  -------********************/
//**************************************************************
void KP_Fuzzy(float position , float position_error)
{
    int fe = 0,fec = 0;//���뵽ģ�����ƫ��
    int pe = 0,pec = 0;//���뵽ģ�����ƫ��仯��
    int num=0;
    float eRule[7]={5,10,20,30,40,50,60};                             //ƫ��ķֶε�                        
    float ecRule[7]={0,1.5,2.5,3.5,4.5,5.5,6.5};                 //ƫ��仯���ķֶε�
						
	//ƫ��仯������
    /*�ٶ�ģ������*/
              /*ԭֵ*/
    float Rule_kp[7]={0.7,0.8,0.9,1,1.1,1.3,1.4};          //kp������������ֵ
//    float Rule_kd[7]={6,6.5,7,7.5,8,8.5,9};                 //kp������������ֵ
//	float Rule_speed[7]={2.5,2.6,2.7,2.8,2.85,2.9,2.95};
          /*���ں� �ٶȵȼ�15*/
//    float Rule_kp[7]={0.58,0.60,0.62,0.64,0.66,0.68,0.7};          //kp������������ֵ
//    float Rule_kd[7]={5,5.5,6.0,6.5,7.0,7.5,8.0};                 //kp������������ֵ
//	  float Rule_speed[7]={2.4,2.53,2.55,2.57,2.59,2.61,2.63};
             /*�ٶȵȼ�16*/
 //   float Rule_kp[7]={0.62,0.64,0.66,0.68,0.70,0.72,0.72};          //kp������������ֵ
 //   float Rule_kd[7]={6,6.5,7,7.5,8,9,10};                 //kp������������ֵ
//    float Rule_speed[7]={2.5,2.65,2.68,2.7,2.72,2.75,2.78};
            /*�ٶȵȼ�17*/
  //   float Rule_kp[7]={0.63,0.65,0.8,1.0,1.5,1.8,2};          //kp������������ֵ
      float Rule_kd[7]={10,11,13,15,17,19,21};                 //kp������������ֵ
//      float Rule_speed[7]={2.58,2.80,2.82,2.85,2.87,2.89,2.91};
            /*�ٶȵȼ�18*/
//    float Rule_kp[7]={0.64,0.66,0.68,0.73,0.76,0.79,0.83};          //kp������������ֵ
//    float Rule_kd[7]={16,17.5,20,21,22,23,24};                 //kp������������ֵ
//	  float Rule_speed[7]={2.7,2.95,2.98,3,3.03,3.08,3.1};
            /*�ٶȵȼ�19*/
//    float Rule_kp[7]={0.64,0.66,0.68,0.73,0.76,0.79,0.83};          //kp������������ֵ
//    float Rule_kd[7]={20,21,22,23,24,25,26};                 //kp������������ֵ
//	  float Rule_speed[7]={2.7,2.95,3.03,3.08,3.1,3.13,3.2};
            /*�ٶȵȼ�20*/
//    float Rule_kp[7]={0.62,0.66,0.68,0.73,0.76,0.79,0.86};          //kp������������ֵ
//    float Rule_kd[7]={12,16,18,20,22,25,28};                 //kp������������ֵ
//      float Rule_speed[7]={2.7,2.9,3.25,3.28,3.33,3.36,3.4};
    
    
    float eFuzzy[2]={0.0,0.0};                              //ƫ��������
    float ecFuzzy[2]={0.0, 0.0};                                //ƫ��仯������
    float U1Fuzzy_kp[7]={0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    float U1Fuzzy_kd[7]={0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    int rule_kp[7][7]=
    {
  //ec 0 1 2 3 4 5 6  //e
      {2,2,1,1,1,0,0},//0    3,2,2,1,1,1,0
      {3,3,2,1,1,1,0},//1    2,2,1,1,1,0,0 
      {4,4,3,2,2,1,1},//2    2,2,1,1,1,0,0 
      {5,4,4,3,2,1,1},//3    4,3,2,1,1,1,0 
      {5,5,4,4,2,2,1},//4
      {6,5,5,4,4,3,2},//5
      {6,6,5,5,5,4,3} //6
    };

    int rule_kd[7][7]=
    {
  //ec 0 1 2 3 4 5 6  //e
      {3,3,4,5,5,6,6},//0
      {3,3,4,4,5,5,6},//1
      {2,3,3,4,5,5,5},//2
      {1,2,2,3,3,4,5},//3
      {1,1,2,2,3,3,3},//4
      {0,1,1,1,2,2,3},//5
      {0,0,1,1,1,2,2} //6
    };

    /*-------------------------------------------*/
    /*----------------ȷ��������-----------------*/
    /*-------------------------------------------*/
    
//    fe = Float_Abs(position);          //ƫ���ƫ��ı仯����ȡ����ֵ������
//    fec = Float_Abs(position_error);
    fe = (int)(Abs(position));          //ƫ���ƫ��ı仯����ȡ����ֵ������
    fec = (int)(Abs(position_error));
    fuzzy_kp = 0.0;
    fuzzy_kd = 0.0;
    /*-------------------------------------------*/
    /*---------------ȷ��kp������----------------*/
    /*-------------------------------------------*/
    if(fe < eRule[0])     		       
    {
        eFuzzy[0] =1.0; 
        pe= 0;         
    }
    else if(fe < eRule[1])	        
    {       
        eFuzzy[0] = (eRule[1]-fe)/(eRule[1]-eRule[0]);
        pe = 0;
    }
    else if(fe < eRule[2])	       
    {
        eFuzzy[0] = (eRule[2] -fe)/(eRule[2]-eRule[1]);
        pe =1;
    }
    else if(fe < eRule[3])	       
    {
        eFuzzy[0] = (eRule[3] -fe)/(eRule[3]-eRule[2]);
        pe =2;
    }
    else if(fe < eRule[4])		       
    {   
        eFuzzy[0] = (eRule[4]-fe)/(eRule[4]-eRule[3]);
        pe=3;
    }
    else if(fe < eRule[5])		       
    {
        eFuzzy[0] = (eRule[5]-fe)/(eRule[5]-eRule[4]);
        pe=4;
    }
    else if(fe < eRule[6])		        
    {
        eFuzzy[0] = (eRule[6]-fe)/(eRule[6]-eRule[5]);
        pe=5;
    }		
    else						        
    {
        eFuzzy[0] =1.0;
        pe=6;
    }
    eFuzzy[1] = 1.0 - eFuzzy[0];                    //eFuzzy[0]+eFuzzy[1]=1;

    
    /*-------------------------------------------*/
    /*---------------ȷ��kd������----------------*/
    /*-------------------------------------------*/
    if(fec <= ecRule[0])
    {
        ecFuzzy[0] =1.0;
        pec = 0;
    }
    else if(fec < ecRule[1])
    {
        ecFuzzy[0] = (ecRule[1] - fec)/(ecRule[1]-ecRule[0]);
        pec = 0 ;
    }
    else if(fec < ecRule[2])
    {
        ecFuzzy[0] = (ecRule[2] - fec)/(ecRule[2]-ecRule[1]);
        pec = 1;
    }
    else if(fec < ecRule[3])
    {
        ecFuzzy[0] = (ecRule[3] - fec)/(ecRule[3]-ecRule[2]);
        pec = 2 ;
    }
    else if(fec < ecRule[4])
    { 
        ecFuzzy[0] = (ecRule[4] - fec)/(ecRule[4]-ecRule[3]);
        pec=3;
    }
    else if(fec < ecRule[5])		
    {
        ecFuzzy[0] = (ecRule[5]-fec)/(ecRule[5]-ecRule[4]);
        pec=4;
    }
    else if(fec<ecRule[6])		
    {
        ecFuzzy[0] = (ecRule[6]-fec)/(ecRule[6]-ecRule[5]);
        pec=5;
    }		
    else										
    {
        ecFuzzy[0] =1.0;
        pec=6;
    }
    ecFuzzy[1] = 1.0 - ecFuzzy[0];
 
    /*-------------------------------------------*/
    /*---------------��ѯkp�����----------------*/
    /*-------------------------------------------*/  
    if(pe<(RANK-1) && pec<(RANK-1))        // e��e'��û�дﵽ��Ե
    {
        num = rule_kp[pec][pe];
        U1Fuzzy_kp[num] += eFuzzy[0]*ecFuzzy[0];

        num = rule_kp[pec][pe+1];
        U1Fuzzy_kp[num] += eFuzzy[1]*ecFuzzy[0];	
    
        num = rule_kp[pec+1][pe];
        U1Fuzzy_kp[num] += eFuzzy[0]*ecFuzzy[1];
    
        num = rule_kp[pec+1][pe+1];
        U1Fuzzy_kp[num] += eFuzzy[1]*ecFuzzy[1];
    }
    else if(pe==(RANK-1) && pec<(RANK-1))  // e�ﵽ��Ե
    {
        num = rule_kp[pec][pe];
        U1Fuzzy_kp[num] += eFuzzy[0]*ecFuzzy[0];                
        num = rule_kp[pec+1][pe];
        U1Fuzzy_kp[num] += eFuzzy[0]*ecFuzzy[1];
    }
    else if(pe<(RANK-1) && pec==(RANK-1))  // e'�ﵽ��Ե
    {
        num = rule_kp[pec][pe];
        U1Fuzzy_kp[num] += eFuzzy[0]*ecFuzzy[0];	
        num = rule_kp[pec][pe+1];
        U1Fuzzy_kp[num] += eFuzzy[1]*ecFuzzy[0];
    }
    else				       // e��e'ͬʱ�ﵽ��Ե
    {     
        num = rule_kp[pec][pe];
        U1Fuzzy_kp[num] += eFuzzy[0]*ecFuzzy[0];		
    }
    
    
    /*-------------------------------------------*/
    /*---------------��ѯkd�����----------------*/
    /*-------------------------------------------*/
    if(pe<(RANK-1) && pec<(RANK-1))        // e��e'��û�дﵽ��Ե
    {
        num = rule_kd[pec][pe];
        U1Fuzzy_kd[num] += eFuzzy[0]*ecFuzzy[0];
    
        num = rule_kd[pec][pe+1];
        U1Fuzzy_kd[num] += eFuzzy[1]*ecFuzzy[0];	
    
        num = rule_kd[pec+1][pe];
        U1Fuzzy_kd[num] += eFuzzy[0]*ecFuzzy[1];
    
        num = rule_kd[pec+1][pe+1];
        U1Fuzzy_kd[num] += eFuzzy[1]*ecFuzzy[1];
    }
    else if(pe==(RANK-1) && pec<(RANK-1))  // e�ﵽ��Ե9
    {
        num = rule_kd[pec][pe];
        U1Fuzzy_kd[num] += eFuzzy[0]*ecFuzzy[0];                
        num = rule_kd[pec+1][pe];
        U1Fuzzy_kd[num] += eFuzzy[0]*ecFuzzy[1];
    }
    else if(pe<(RANK-1) && pec==(RANK-1))  // e'�ﵽ��Ե
    {
        num = rule_kd[pec][pe];
        U1Fuzzy_kd[num] += eFuzzy[0]*ecFuzzy[0];	
        num = rule_kd[pec][pe+1];
        U1Fuzzy_kd[num] += eFuzzy[1]*ecFuzzy[0];
    }
    else				       // e��e'ͬʱ�ﵽ��Ե
    {
        num = rule_kd[pec][pe];
        U1Fuzzy_kd[num] += eFuzzy[0]*ecFuzzy[0];		
    }
    
    /*-------------------------------------------*/
    /*-----------------��ģ��--------------------*/
    /*-------------------------------------------*/
    for(int l=0;l<RANK;l++)
    {     
        fuzzy_kp += U1Fuzzy_kp[l] * Rule_kp[l];
        fuzzy_kd += U1Fuzzy_kd[l] * Rule_kd[l];
    }
}
/*--------------------ͣ�����--------------------------------------*/
void  Reed_End(void)
{
static   uint16  Stop_Count=0;
static   uint8   Stop_Count_flag=0;
  if(Stop_Count_flag==0)
  {
    Stop_Count++;
  }
  if(Stop_Count>=1000)
  {
    Stop_Count_flag=1;
  }
  if(Stop_Count_flag==1)
  {
    if((gpio_get(I5)==0))
        {
         Speed_Flag=4;
        }
    if(Speed_Flag==4&&Car_Actual_Speed<5)
      {
        ftm_pwm_duty(ftm2,ftm_ch1,0);
        ftm_pwm_duty(ftm2,ftm_ch0,0);
        ftm_pwm_duty(ftm2,ftm_ch3,0);
        ftm_pwm_duty(ftm2,ftm_ch2,0);
        OLED_P8x16Str(0,0,"ok");
       }
  }
}
/*--------------------�����ӳٿ��ж�--------------------------------------*/
void Start_Car()
{
  Oled_Clr();
  systick_delay_ms(2000);                       //�����ӳ�ʱ��
  pit_init_ms(pit0,2);	                        //��ʼ��pit0 				
  set_irq_priority(PIT_CH0_IRQn,1);	        //����pit0���ȼ�
  enable_irq(PIT_CH0_IRQn);			//����pit0�ж�
  EnableInterrupts;
}



