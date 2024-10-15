#ifndef __BIANLIANG_H
#define __BIANLIANG_H 


#define TS_PATH  "/dev/input/event0"
#define LCD_DEV_PATH "/dev/fb0"
#define FONT_PATH "/usr/share/fonts/DroidSansFallback.ttf"
#define LCD_DEV_TOUCH_PATH "/dev/input/event0"
#define LCD_W 800
#define LCD_H 480

//屏幕文件
#define FB_FILE  "/dev/fb0"

//遍历u盘文件路径
#define DIR_PATH   "/mnt/udisk/file"
#define DIR_PATH_1   "/file/morning"
#define DIR_PATH_2   "/file/noon"
#define DIR_PATH_3   "/file/night"

/* 链表结构 设计*/
typedef struct node
{
    char data[100];
    struct node *next;
    int num;
}node;


char mplayer_shell[100];
//关于遍历后的文件路径和名称
int cnt;

//定义结构体指针
struct node *p_video_name,*q_file_bath , *T_video_name , *T_file_bath;
struct node *video_name,*file_bath , *t_video_name, *t_file_bath;
unsigned int *mem_p;
int ts_fd;
int j;
unsigned int *mem_p;
int lcd_fd;
int denglu;
int x , y;
int fanhui;
int in_guanli;
int Time_hour;
int zaowuwan;
int tihuan;
int yulan;
//图片的声明
char picture[20];
char picture_1[20];
char picture_2[20];
char picture_3[20];
char picture_4[20];
char picture_5[20];
char picture_6[20];
char picture_7[20];
char picture_8[20];
char picture_9[20];
char picture_10[20];
char picture_11[20];
char picture_12[20];
char picture_13[20];
char picture_14[20];
char picture_15[20];
char picture_16[20];
//定义的用来存选中的文件数据的数组
char dianji8_name[50];
char dianji8_bath[200];

char file_name[50];
//用来存储要替换的文件数据
char huan_name[50];
char huan_bath[200];






#endif
