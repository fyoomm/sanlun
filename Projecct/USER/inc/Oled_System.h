#ifndef _OLED__SYSTEM_C
#define _OLED__SYSTEM_C

#include "headfile.h"


/*****--------------��������ֽ���-------------*****/
#define    KEY_YES             0               //��������
#define    KEY_NO              1               //����������
#define    KEY_LEFT            gpio_get(F3)    //���
#define    KEY_RIGHT           gpio_get(A7)    //�ұ�
#define    KEY_UP              gpio_get(F2)    //�ϱ�
#define    KEY_DOWN            gpio_get(E4)    //�±�
#define    KEY_MIDDLE          gpio_get(A6)    //�м�
/*---------------���뿪�غ궨��------------------*/
#define    KEY_ONE             gpio_get(F1)
#define    KEY_TWO             gpio_get(F0)
#define    KEY_THREE           gpio_get(A3)
#define    KEY_FOUR            gpio_get(A2)
#define    KEY_FIVE            gpio_get(A1)
#define    KEY_SIX             gpio_get(C7)
#define    KEY_SEVEN           gpio_get(I3)
#define    KEY_EIGHT           gpio_get(G3)
extern   uint8     Key_Check;



/*****-------------���庯���ֽ���---------------*****/
void Work_choice(void);                            //ͨ�����뿪��ѡ��С���Ĺ���״̬
void boma_open();                                  //���뿪��ѡ����ʾ
void WU_XIANG_Init(void);                          //���򿪹س�ʼ��
void Check_Key(void);                             //���򿪹ذ������
void Switch_init(void);                           //���뿪�س�ʼ��
void Oled_WrDat_1(unsigned char data);
void OLED_ShowCN(unsigned char x, unsigned char y, char str, char polarity);
void Oled_Set_Pos_1(unsigned char x, unsigned char y);
void Oled_WrCmd_1(unsigned char cmd);
void  Primary_Menu(void);  
void  Show_Menu(void);
void  Alter_Menu(void);
void Oled_Clr(void);







#endif