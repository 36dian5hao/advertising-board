#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <linux/input.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <pthread.h> //跟线程有关的头文件
#include <time.h>
#include <dirent.h>
#include"lianbiao.h"
#include"hanshu.h"
#include"bianliang.h"
#include "font.h"
pthread_t id1,id2,id3,id4; //存放线程的ID号

//线程1111111111111111111111111111111111111111
void *fun1(void *arg)
{
    panduanshijian();
    //char mplayer_shell[100] = "mplayer -slave -quiet -input  file=/pipe -geometry 400:50  -zoom -x 240 -y 200 ";
    // char file_name[50]="/myproject/guanggao/morning/f.mp4";
	while(1)
	{
        if(denglu==1)
        {pthread_exit(NULL);}        // if(t==0)
        char mplayer_shell_totl[150] = {'\0'};
        sprintf(mplayer_shell_totl, "%s%s", mplayer_shell, file_name);
        // printf("mplayer_shell_totl:%s\n",mplayer_shell_totl);
        system(mplayer_shell_totl);
        sleep(2);
	}
}
//线程2222222222222222222222222222222222222222
void *fun2(void *arg)
{
    // 初始化Lcd
    struct LcdDevice *lcd = init_lcd(LCD_DEV_PATH);
    if (lcd == (struct LcdDevice *)NULL)
    {
        printf("初始化LCD失败！\n");
        return 0;
    }
    while (1)
    {
        if(denglu==1)
        {pthread_exit(NULL);}
        char *buf_time = get_time();
        show_font_time(lcd, buf_time);
    }
 
    return 0;
}
void *fun3(void *arg)
{
    while(1)
	{
        if (yulan == 1)
        {
            char mplayer_shell_totl[150] = {'\0'};
            sprintf(mplayer_shell_totl, "%s%s", mplayer_shell, dianji8_bath);
            // printf("mplayer_shell_totl:%s\n",mplayer_shell_totl);
            system(mplayer_shell_totl);
            sleep(2);
        }
	}
}

void *fun4(void *arg)
{
    char a_pitruce[50]={'\0'};
    char b_pitruce[50]={'\0'};
    char buu[10]={".bmp"};
    while (1)
    {
        if(denglu==1)
        {pthread_exit(NULL);} 

        if(0<Time_hour && Time_hour<=8)
        {
            get_picture_path(DIR_PATH_1,buu);
            printf("q_file_bath:%s\n",q_file_bath->data);
            fuzhisuzhu(a_pitruce,q_file_bath->next->data);
            q_file_bath->next = q_file_bath->next->next;
            fuzhisuzhu(b_pitruce,q_file_bath->next->data);
            picture_xianshi(500,0,a_pitruce);
            sleep(2);
            if(denglu==1)
            {pthread_exit(NULL);} 
            picture_xianshi(500,0,b_pitruce);
            sleep(2);
            
        }
        if(8<Time_hour && Time_hour<=16)
        {

            get_picture_path(DIR_PATH_2,buu);
            printf("q_file_bath:%s\n",q_file_bath->data);
            fuzhisuzhu(a_pitruce,q_file_bath->next->data);
            q_file_bath->next = q_file_bath->next->next;
            fuzhisuzhu(b_pitruce,q_file_bath->next->data);
            picture_xianshi(500,0,a_pitruce);
            sleep(2);
            if(denglu==1)
            {pthread_exit(NULL);} 
            picture_xianshi(500,0,b_pitruce);
            sleep(2);
            
        }
        if(16<Time_hour && Time_hour<=23 ||  Time_hour ==0 )
        {

            get_picture_path(DIR_PATH_3,buu);
            printf("q_file_bath:%s\n",q_file_bath->data);
            fuzhisuzhu(a_pitruce,q_file_bath->next->data);
            q_file_bath->next = q_file_bath->next->next;
            fuzhisuzhu(b_pitruce,q_file_bath->next->data);
            picture_xianshi(500,0,a_pitruce);
            sleep(2);
            if(denglu==1)
            {pthread_exit(NULL);} 
            picture_xianshi(500,0,b_pitruce);
            sleep(2);
            
        }
        for (int i = 0; i < 50; i++)
        {
            a_pitruce[i]='\0';
        }
        for (int i = 0; i < 50; i++)
        {
            b_pitruce[i]='\0';
        }
        
        
    }
    
    
}


int main(void)
{
    setup_nodes();
    while (1)
    {   

        fanhui = 0;
        in_guanli =0;
        denglu = 0;

        //首页的视频
        shouye();

        pthread_create(&id1,NULL,fun1,NULL);
        pthread_create(&id2,NULL,fun2,NULL);
        pthread_create(&id3,NULL,fun3,NULL);
        pthread_create(&id4,NULL,fun4,NULL);

        // void *status;
        while(1)
        {
            guanliyuan();
            if (fanhui == 1)
            {
                break;
            }

            //判断进入管理员界面
            if(in_guanli == 1)
            {
                fanhui = 0;
                guanliyuan_picture();
                // zhifu();

                //管理员界面控制
                guanliyuan_kongzhi();
                if (fanhui == 1)
                {
                    break;
                }
            }
            
        }      
    }
    
}