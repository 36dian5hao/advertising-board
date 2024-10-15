#include"lianbiao.h"
#include"hanshu.h"
#include"bianliang.h"
#include "font.h"



char mplayer_shell[100] = "mplayer -slave -quiet -input  file=/pipe -geometry 400:25  -zoom -x 480 -y 450 ";
//关于遍历后的文件路径和名称
int cnt=1;

//定义结构体指针
struct node *p_video_name,*q_file_bath , *T_video_name , *T_file_bath;
struct node *video_name,*file_bath , *t_video_name, *t_file_bath;
unsigned int *mem_p;
int ts_fd;
int j = 0;
unsigned int *mem_p;
int lcd_fd;
int denglu=0;
int x = 0, y = 0;
int fanhui=0;
int in_guanli =0;
int Time_hour = 0;
int zaowuwan = 0;
int tihuan =0;
int yulan =0;
//图片的声明
char picture[20]={"login.bmp"};
char picture_1[20]={"guanggao.bmp"};
char picture_2[20]={"wenjian_1.bmp"};
char picture_3[20]={"back.bmp"};
char picture_4[20]={"xianshikuang.bmp"};
char picture_5[20]={"anjian.bmp"};
char picture_6[20]={"anjian_1.bmp"};
char picture_7[20]={"anjian_2.bmp"};
char picture_8[20]={"upanwj.bmp"};
char picture_9[20]={"anjian_3.bmp"};
char picture_10[20]={"anjian_4.bmp"};
char picture_11[20]={"anjian_5.bmp"};
char picture_12[20]={"anjian_6.bmp"};
char picture_13[20]={"anjian_7.bmp"};
char picture_14[20]={"anjian_8.bmp"};
char picture_15[20]={"shurukuang.bmp"};
char picture_16[20]={"keyb.bmp"};
//定义的用来存选中的文件数据的数组
char dianji8_name[50] = {'\0'};
char dianji8_bath[200] = {'\0'};

char file_name[50]={'\0'};
//用来存储要替换的文件数据
char huan_name[50] = {'\0'};
char huan_bath[200] = {'\0'};