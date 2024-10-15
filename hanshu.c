#include"lianbiao.h"
#include"hanshu.h"
#include"bianliang.h"
#include "font.h"



/* ����ṹ ���*/
typedef struct node
{
    char data[100];
    struct node *next;
    int num;
}node;
//��ѡ�е��ļ���Ϣ��������
int fuzhisuzhu(char *new,char *initial_data)
{
// ����ṩ�˳�ʼ���ݣ��͸��Ƶ� data ��Ա��
    strncpy(new, initial_data, strlen(initial_data)+1);
    new[strlen(initial_data)] = '\0'; // ȷ���ַ����� '\0' ��β
    printf("initial_data:%s\n",initial_data);
    printf("new:%s\n",new);
}


//��ʼ���ļ����ƺ��ļ�·��
void setup_nodes(void)
{
    p_video_name = init_node(NULL);
    q_file_bath = init_node(NULL);
    T_video_name = init_node(NULL);
    T_file_bath = init_node(NULL);
    video_name = p_video_name;
    file_bath = q_file_bath;//�ļ�·��

    t_video_name = T_video_name;
    t_file_bath = T_file_bath;
}



//#region
int lcd_init(void)
{
    lcd_fd = open(FB_FILE, O_RDWR);
    if (lcd_fd == -1)
    {
        printf("lcd open fail!\n");
        return -1;
    }

    // ��Ļӳ��
    mem_p = (unsigned int *)mmap(NULL, 800 * 480 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, lcd_fd, 0);
    if (mem_p == MAP_FAILED)
    {
        printf("mmap fail\n");
    }

    return 0;
}
//#endregion

// ���ӳ��
int lcd_uninit(void)
{

    munmap(mem_p, 800 * 480 * 4);
    close(lcd_fd);
}

//��ʼ��Lcd
struct LcdDevice *init_lcd(const char *device)
{
	//����ռ�
	struct LcdDevice* lcd = malloc(sizeof(struct LcdDevice));
	if(lcd == NULL)
	{
		return NULL;
	} 

	//1���豸
	lcd->fd = open(device, O_RDWR);
	if(lcd->fd < 0)
	{
		perror("open lcd fail");
		free(lcd);
		return NULL;
	}
	//ӳ��
	lcd->mp = mmap(NULL,800*480*4,PROT_READ|PROT_WRITE,MAP_SHARED,lcd->fd,0);

	return lcd;
}

//��ʾbmpͼƬ
int show_bmp(const char *path, int w, int h)
{
    int bmp_fd, i, j;
    unsigned char bmp_buf[w * h * 3];
    unsigned int buf[w * h];
    unsigned int tmp;

    bmp_fd = open(path, O_RDWR);
    if (bmp_fd == -1)
    {
        printf("open fail!\n");
        return -1;
    }

    // ����54�ֽ�
    lseek(bmp_fd, 54, SEEK_SET);

    // ��ͼƬRGB����������
    read(bmp_fd, bmp_buf, sizeof(bmp_buf));
    // תΪ���ֽڻ�����
    for (i = 0; i < w * h; i++)
    {
        buf[i] = bmp_buf[3 * i + 0] | bmp_buf[3 * i + 1] << 8 | bmp_buf[3 * i + 2] << 16;
    }
    // if (x + w >= 800 || y + w >= 480)
    // {
    //     printf("����Խ��\n");
    //     close(bmp_fd);
    //     return 0;
    // }
    // ���ص����
    for (i = 0; i < h; i++)
    {
        for (j = 0; j < w; j++)
        {
            mem_p[(800 * (i + y)) + j + x] = buf[(h - i) * w + j];
        }
    }
    close(bmp_fd);
    return 0;
}

// #define DIR_PATH_1   "/file/morning"
// #define DIR_PATH_2   "/file/noon"
// #define DIR_PATH_3   "/file/night"


int panduanshijian()
{
    if (0<Time_hour && Time_hour<=8)
    {
        get_picture_path1(DIR_PATH_1,".mp4");
        // printf("t_file_bath->next->data:%s\n",t_file_bath->next->data);
        // fuzhisuzhu(file_name,t_file_bath->next->data);
    }
    if (8<Time_hour && Time_hour<=16)
    {
        get_picture_path1(DIR_PATH_2,".mp4");
        // printf("t_file_bath->next->data:%s\n",t_file_bath->next->data);
        // fuzhisuzhu(file_name,t_file_bath->next->data);
    }
    if (16<Time_hour && Time_hour<=23  ||  Time_hour ==0 )
    {
        get_picture_path1(DIR_PATH_3,".mp4");
        // printf("t_file_bath->next->data:%s\n",t_file_bath->next->data);
        // fuzhisuzhu(file_name,t_file_bath->next->data);
    }
    

}

//���ҵ�ǰʱ��Ҫ���ŵ���Ƶ��ͼƬ
int get_picture_path1(char *path_buff , char *buff)
{

    // struct node *q1,*p;
    // q1=video_name->next;
    // p = p_video_name->next;
    DIR *pdir;

    struct dirent *pdirent;
    char lujing[200] = {'\0'};
    int len , i =0;
    char ppath_buff[520] = {0};
    pdir = opendir(path_buff);
    if (pdir == NULL)
    {
        printf("opendir fail\n");
        return -1;
    }

    while ((pdirent = readdir(pdir)) != NULL)
    {
        //�ж��Ƿ�Ϊ��ͨ�ļ�
        if(8 == pdirent->d_type )
        {
            //�����ļ����ֵĳ���
            len = strlen(pdirent->d_name);

            if(len > 4)
            {
                if(strcmp(&pdirent->d_name[len-4], buff) == 0)
                {
                    printf("pdirent->d_name:%s\n", pdirent->d_name);
                    // sprintf(video_name, "%d:%s",cnt,  pdirent->d_name);

                    // insert_tail(t_video_name->next,pdirent->d_name);
                    // if (zaowuwan == 1 && video_name->num%2==0)
                    // {
                    //     video_name->num = video_name->num+1;

                    // }
                    



                    sprintf(file_name, "%s/%s",path_buff,  pdirent->d_name);

                    printf("file_name%s\n", file_name);

                    // insert_tail(t_file_bath->next,lujing);
                    // if ( zaowuwan == 1 && file_bath->num%2==0)
                    // {
                    //     file_bath->num = file_bath->num+1;
                    // }
                    // printf("t_file_bath->data:%s\n", t_file_bath->data);
                    // t_video_name = t_video_name->next;
                    // t_file_bath = t_file_bath->next;
                    cnt++;
                }                 
            } 
        }
    }
    closedir(pdir);
}

//�ж��Ƿ񴥷���½
int guanliyuan(void)
{
    int X, Y;
    int ts_fd;
    struct input_event ts;
    ts_fd = open(TS_PATH, O_RDWR);
    if(ts_fd == -1)
    {
        printf("open ts failure\n");
        return -1;
    }
    while(1)
    {
        //�ɿ��������ٴ�ӡ
            read(ts_fd, &ts, sizeof(struct input_event));

            //�ж�����
            if(ts.type == EV_ABS && ts.code == ABS_X)
            {
                X = ts.value;
            }

            if(ts.type == EV_ABS && ts.code == ABS_Y)
            {
                Y = ts.value;
            }

            //�жϰ���
            if(ts.type == EV_KEY && ts.code ==  BTN_TOUCH && ts.value == 1)
            {
         

            }
            //�ж��Ƿ��ɿ�
            if(ts.type == EV_KEY && ts.code ==  BTN_TOUCH && ts.value == 0)
            {
                X = X*(800.0/1024.0);      
                Y = Y*(480.0/600.0);
            }
        if(500<X && X<800 && 380<Y && Y<480)
        {
            close(ts_fd);            
            denglu = 1;
            system("killall -SIGKILL mplayer");
            mima();
            return 0;
        }
    }

}

//��������
int mima()
{
    int X, Y;
    char a_bu[10]={0};
    char b_bu[10] = {"1234"};
    int password_num = 0;
    struct input_event ts;
    ts_fd = open(TS_PATH, O_RDWR);
    if(ts_fd == -1)
    {
        printf("open ts failure\n");
        return -1;
    }
    
    
    int w = 0, h = 0;
    unsigned char buf[54] = {0};
    int x_zanshi = 194;
    // printf("�������ӡ������:x-y\n");
    // scanf("%d", &x);
    // scanf("%d", &y);
    x = 500;
    y = 0;
    // ��ͼƬ�ļ�
    int fd = open("keyb.bmp", O_RDONLY);

    read(fd, buf, sizeof(buf));

    // �ϳ�ͼƬ�ĸ߶�  20  03 ==��0320
    w = buf[19] << 8 | buf[18];

    // �ϳ�ͼƬ�Ŀ��
    h = buf[23] << 8 | buf[22];

    lcd_init();
    show_bmp("keyb.bmp", w, h);
    lcd_uninit();

    close(fd);
        picture_xianshi(0,0,picture_8);
        picture_xianshi(104,220,picture_15);//shurukuang
        sleep(1);
        picture_xianshi(500,0,picture_16);

    while(1)
    {
        //�ɿ��������ٴ�ӡ
        while (1)
        {
            read(ts_fd, &ts, sizeof(struct input_event));

            //�ж�����
            if(ts.type == EV_ABS && ts.code == ABS_X)
            {
                X = ts.value;
            }

            if(ts.type == EV_ABS && ts.code == ABS_Y)
            {
                Y = ts.value;
            }

            //�жϰ���
            if(ts.type == EV_KEY && ts.code ==  BTN_TOUCH && ts.value == 1)
            {
         

            }
            //�ж��Ƿ��ɿ�
            if(ts.type == EV_KEY && ts.code ==  BTN_TOUCH && ts.value == 0)
            {
            
                                                                   	             	
                X = X*(800.0/1024.0);      
                Y = Y*(480.0/600.0);
                break;
            }           

            
        }

        printf("X:%d, Y:%d\n", X, Y);


        if(500<X && X<600 && 0<Y && Y<85)
        {
            printf("1\n");
            // lcd_init();
            // show_bmp("du.bmp");
            // lcd_uninit();
            password_num = 0;
            password_num = 1;

            sprintf(a_bu, "%s%d", a_bu, password_num);

            file_zhifu("1",x_zanshi,224);
            x_zanshi=x_zanshi+10;
        }
        if(600<X && X<700 && 0<Y && Y<85)
        {
            printf("2\n");
            password_num = 0;
            password_num = 2;
            sprintf(a_bu, "%s%d", a_bu, password_num);
            file_zhifu("2",x_zanshi,224);
            x_zanshi=x_zanshi+10;
        }
        if(700<X && X<800 && 0<Y && Y<85)
        {
            printf("3\n");
            password_num = 0;
            password_num = 3;
            sprintf(a_bu, "%s%d", a_bu, password_num);
            file_zhifu("3",x_zanshi,224);
            x_zanshi=x_zanshi+10;
        }
        if(500<X && X<600 && 85<Y && Y<170)
        {
            printf("4\n");
            password_num = 0;
            password_num = 4;
            sprintf(a_bu, "%s%d", a_bu, password_num);
            file_zhifu("4",x_zanshi,224);
            x_zanshi=x_zanshi+10;
        }
        if(600<X && X<700 && 85<Y && Y<170)
        {
            printf("5\n");
            password_num = 0;
            password_num = 5;
            sprintf(a_bu, "%s%d", a_bu, password_num);
            file_zhifu("5",x_zanshi,224);
            x_zanshi=x_zanshi+10;
        }
        if(700<X && X<800 && 85<Y && Y<170)
        {
            printf("6\n");
            password_num = 0;
            password_num = 6;
            sprintf(a_bu, "%s%d", a_bu, password_num);
            file_zhifu("6",x_zanshi,224);
            x_zanshi=x_zanshi+10;
        }
        if(500<X && X<600 && 170<Y && Y<265)
        {
            printf("7\n");
            password_num = 0;
            password_num = 7;
            sprintf(a_bu, "%s%d", a_bu, password_num);
            file_zhifu("7",x_zanshi,224);
            x_zanshi=x_zanshi+10;
        }
        if(600<X && X<700 && 170<Y && Y<265)
        {
            printf("8\n");
            password_num = 0;
            password_num = 8;
            sprintf(a_bu, "%s%d", a_bu, password_num);
            file_zhifu("8",x_zanshi,224);
            x_zanshi=x_zanshi+10;
        }
        if(700<X && X<800 && 170<Y && Y<265)
        {
            printf("9\n");
            password_num = 0;
            password_num = 9;
            sprintf(a_bu, "%s%d", a_bu, password_num);
            file_zhifu("9",x_zanshi,224);
            x_zanshi=x_zanshi+10;
        }
        if(600<X && X<700 && 265<Y && Y<380)
        {
            printf("0\n");
            password_num = 0;
            password_num = 0;
            sprintf(a_bu, "%s%d", a_bu, password_num);
            file_zhifu("0",x_zanshi,224);
            x_zanshi=x_zanshi+10;
        }
        if(700<X && X<800 && 265<Y && Y<380)
        {
            printf("����\n");
            fanhui = 1;
            close(ts_fd);
            return 0;
        }
        if(500<X && X<600 && 265<Y && Y<380)
        {
            printf("ȷ��\n");

            if (strcmp (a_bu , b_bu) == 0)
            {
                printf("a_bu �� b_bu ���: %s\n", a_bu);
                in_guanli = 1;
                close(ts_fd);
                // guanliyuan_mode();
                return 0;
            } else {
                for (int i = 0; i < 10; i++)
                {
                    file_zhifu("������󣡣���",194,224);//�������
                    a_bu[i]='\0';
                    x_zanshi = 194;
                }
                
                printf("a_bu �� b_bu �����: a=%s, b=%s\n", a_bu, b_bu);
            }

        }


    }
    close(ts_fd);
}

//��ʾͼƬ�Ľӿ�
int picture_xianshi(int x_z,int y_z,char *picture)
{
    //����ͼƬ��x���y��/
    x = x_z;
    y = y_z;

    int h,w;
    int t;
    unsigned char buf[54] = {0};
    // ��ͼƬ�ļ�
    int fd = open(picture, O_RDONLY);
    read(fd, buf, sizeof(buf));
    // �ϳ�ͼƬ�ĸ߶�  20  03 ==��0320
    w = buf[19] << 8 | buf[18];
    // �ϳ�ͼƬ�Ŀ��
    h = buf[23] << 8 | buf[22];

    lcd_init();
    show_bmp(picture, w, h);
    lcd_uninit();

    close(fd);
    return 0;
}

//��ʾ����Ա�Ľ���
int guanliyuan_picture()
{

    picture_xianshi(0,0,picture_3);
    picture_xianshi(0,0,picture_2);
    picture_xianshi(480,0,picture_4);
    picture_xianshi(480,80,picture_7);
    picture_xianshi(640,80,picture_9);
    picture_xianshi(480,180,picture_10);
    picture_xianshi(640,180,picture_11);
    picture_xianshi(480,280,picture_12);
    picture_xianshi(640,280,picture_13);
    picture_xianshi(480,380,picture_14);
    picture_xianshi(640,380,picture_6);
    
}

//��ҳ��ʾ
int shouye()
{
    picture_xianshi(0,0,picture_3);
    picture_xianshi(500,380,picture);
    picture_xianshi(500,0,picture_1);
}

//����Ա������ư�ť
int guanliyuan_kongzhi()
{
    int X, Y;
    struct input_event ts;
    ts_fd = open(TS_PATH, O_RDWR);
    if(ts_fd == -1)
    {
        printf("open ts failure\n");
        return -1;
    }
    while(1)
    {
        //�ɿ��������ٴ�ӡ
        while (1)
        {
            read(ts_fd, &ts, sizeof(struct input_event));

            //�ж�����
            if(ts.type == EV_ABS && ts.code == ABS_X)
            {
                X = ts.value;
            }

            if(ts.type == EV_ABS && ts.code == ABS_Y)
            {
                Y = ts.value;
            }

            //�жϰ���
            if(ts.type == EV_KEY && ts.code ==  BTN_TOUCH && ts.value == 1)
            {
         

            }
            //�ж��Ƿ��ɿ�
            if(ts.type == EV_KEY && ts.code ==  BTN_TOUCH && ts.value == 0)
            {
            
                                                                   	             	
                X = X*(800.0/1024.0);      
                Y = Y*(480.0/600.0);
                break;
            }           
        }

        printf("X:%d, Y:%d\n", X, Y);
        //u���ļ���ʾ
        if(480<X && X<608 && 80<Y && Y<180)
        {
            picture_xianshi(0,0,picture_8);
            file_zhifu("��ѡ��:",80,410);
            file_zhifu(huan_name,150,410);
            file_zhifu("u����Ƶ",80,20);
            destroy_node(p_video_name);      
            char buff[10] = {".mp4"};
            setup_nodes();
            //��ʾ�ļ��ĺ���
            display_upan(buff,DIR_PATH);
            video_name = p_video_name->next;
            while (video_name != NULL)
            {
                printf("p_video_name:%s\n",video_name->data);
                printf("num:%d\n",video_name->num);
                video_name = video_name->next;
            }
            

        }
        if(640<X && X<768 && 80<Y && Y<180)
        {

            picture_xianshi(0,0,picture_8);
            file_zhifu("��ѡ��:",80,410);
            file_zhifu(huan_name,150,410);
            file_zhifu("u����Ƭ",80,20);
            destroy_node(p_video_name);            
            char buff_1[10] = {".bmp"};
            setup_nodes();
            //��ʾ�ļ��ĺ���
            display_upan(buff_1,DIR_PATH);
            video_name = p_video_name->next;
            while (video_name != NULL)
            {
                printf("p_video_name:%s\n",video_name->data);
                printf("num:%d\n",video_name->num);
                video_name = video_name->next;
            }
        }
        //�����Ƶ�͹����Ƭ
        if(480<X && X<608 && 180<Y && Y<280)
        {
            zaowuwan = 1;
            picture_xianshi(0,0,picture_2);

            file_zhifu("�����Ƶ",80,20);
            file_zhifu("��ѡ��:",80,410);
            file_zhifu(huan_name,150,410);
            destroy_node(p_video_name);            
            char buff[10] = {".mp4"};

            //��ʾ�����Ƶ���
            setup_nodes();
            //��ʾ�ļ��ĺ���

            display_upan_guanggao(buff,DIR_PATH_1,DIR_PATH_2,DIR_PATH_3,75);

            // while (p_video_name->next!= NULL )
            // {
            //     printf("p_video_name:%s\n",p_video_name->next->data);
            //     p_video_name->next = p_video_name->next->next;
            // }


            // destroy_node(p_video_name);
            // //��ʾ�����Ƶ���
            // setup_nodes();
            // //��ʾ�ļ��ĺ���
            // display_upan_guanggao(buff,DIR_PATH_2,175);

            // destroy_node(p_video_name);
            // //��ʾ�����Ƶ���
            // setup_nodes();
            // //��ʾ�ļ��ĺ���
            // display_upan_guanggao(buff,DIR_PATH_2,275);
            zaowuwan = 0;


        }
        if(640<X && X<768 &&  180<Y && Y<280)
        {
            
            picture_xianshi(0,0,picture_2);
            file_zhifu("�����Ƭ",80,20);
            file_zhifu("��ѡ��:",80,410);
            file_zhifu(huan_name,150,410);
            char buff[10] = {".bmp"};
            destroy_node(p_video_name);
            // //��ʾ���ͼƬ���            
            setup_nodes();
            // //��ʾ�ļ��ĺ���
            display_upan(buff,DIR_PATH_1);
            display_upan(buff,DIR_PATH_2);
            display_upan(buff,DIR_PATH_3);

            // destroy_node(p_video_name);
            // //��ʾ���ͼƬ���
            // setup_nodes();
            // //��ʾ�ļ��ĺ���
            // display_upan_guanggao(buff,DIR_PATH_2,175);
 
            // destroy_node(p_video_name);
            // //��ʾ���ͼƬ���
            // setup_nodes();
            // //��ʾ�ļ��ĺ���
            // display_upan_guanggao(buff,DIR_PATH_3,275);

        }
        //Ԥ����ȡ��Ԥ��
        if(480<X && X<608 && 280<Y && Y<380)
        {
            file_zhifu("Ԥ��",80,20);
            int len = strlen(dianji8_bath);
            if(strcmp(&dianji8_bath[len-4], ".mp4") == 0)
            {
                yulan = 1;
            }
            if(strcmp(&dianji8_bath[len-4], ".bmp") == 0)
            {
            
                picture_xianshi(80,80,dianji8_bath);
                
            }


            printf("Ԥ��\n");
        }
        if(640<X && X<768 && 280<Y && Y<380)
        {
            file_zhifu("ȡ��Ԥ��",80,20);
            int len = strlen(dianji8_bath);
            if(strcmp(&dianji8_bath[len-4], ".mp4") == 0)
            {
                system("killall -SIGkill mplayer");
                yulan = 0;
                picture_xianshi(0,0,picture_8);
            }
            if(strcmp(&dianji8_bath[len-4], ".bmp") == 0)
            {
                picture_xianshi(0,0,picture_8);
                
            }

            printf("ȡ��Ԥ��\n");
        }
        //�滻���˳�
        if(480<X && X<608 && 380<Y && Y<480)
        {
            if(tihuan == 0)
            {
                file_zhifu("�滻",80,20);
                fuzhisuzhu(huan_name,dianji8_name);
                fuzhisuzhu(huan_bath,dianji8_bath);
                file_zhifu(dianji8_name,550,10);
                file_zhifu("��ѡ��:",80,410);
                file_zhifu(huan_name,150,410);
                printf("huan_name:%s\n",huan_name);
                printf("huan_bath:%s\n",huan_bath);

                printf("�滻\n");
                tihuan = 1;
            }else if (tihuan == 1)
            {
                file_zhifu("�滻�ɹ�",80,20);
                file_zhifu("��ˢ��",250,20);
                tihuan_file();

                for (int i = 0; i < 50; i++)
                {
                    huan_name[i] = '\0';
                }
                for (int i = 0; i <100; i++)
                {
                    huan_bath[i] = '\0';
                }

                tihuan = 0;
            }
            

        }
        if(640<X && X<800 && 380<Y && Y<480)
        {
            printf("�˳�\n");
            fanhui = 1;
            close(ts_fd);
            return 0;
            // guanliyuan_mode();
        }

        //�������ѡ��
        if(80<X && X<255 && 75<Y && Y<175)
        {
            printf("1\n");
            //����
            printf("p_video_name->data:%s\n",p_video_name->next->data);
            if((play_node(p_video_name,1,dianji8_name)) == 1)
            {
                file_zhifu(dianji8_name,550,10);
                printf("dianji8_name:%s\n",dianji8_name);
            }
            //·��
            if((play_node(q_file_bath,1,dianji8_bath)) == 1)
            {
                // file_zhifu(dianji8_name,550,10);
                printf("dianji8_bath:%s\n",dianji8_bath);
            }
        }
        if(265<X && X<445 && 75<Y && Y<175)
        {
            printf("2\n");
            if((play_node(p_video_name,2,dianji8_name)) == 1)
            {
                file_zhifu(dianji8_name,550,10);
                printf("dianji8_name:%s\n",dianji8_name);
            }
            //·��
            if((play_node(q_file_bath,2,dianji8_bath)) == 1)
            {
                // file_zhifu(dianji8_name,550,10);
                printf("dianji8_bath:%s\n",dianji8_bath);
            }
            
        }
        if(80<X && X<255 && 175<Y && Y<275)
        {
            printf("3\n");
            if((play_node(p_video_name,3,dianji8_name)) == 1)
            {
                file_zhifu(dianji8_name,550,10);
                printf("dianji8_name:%s\n",dianji8_name);
            }
            //·��
            if((play_node(q_file_bath,3,dianji8_bath)) == 1)
            {
                // file_zhifu(dianji8_name,550,10);
                printf("dianji8_bath:%s\n",dianji8_bath);
            }
        }
        if(265<X && X<445 && 175<Y && Y<275)
        {
            printf("4\n");
            if((play_node(p_video_name,4,dianji8_name)) == 1)
            {
                file_zhifu(dianji8_name,550,10);
                printf("dianji8_name:%s\n",dianji8_name);
            }
            //·��
            if((play_node(q_file_bath,4,dianji8_bath)) == 1)
            {
                // file_zhifu(dianji8_name,550,10);
                printf("dianji8_bath:%s\n",dianji8_bath);
            }
        }
        if(80<X && X<255 && 270<Y && Y<365)
        {
            printf("5\n");
            if((play_node(p_video_name,5,dianji8_name)) == 1)
            {
                file_zhifu(dianji8_name,550,10);
                printf("dianji8_name:%s\n",dianji8_name);
            }
            //·��
            if((play_node(q_file_bath,5,dianji8_bath)) == 1)
            {
                // file_zhifu(dianji8_name,550,10);
                printf("dianji8_bath:%s\n",dianji8_bath);
            }
        }
        if(265<X && X<445 && 270<Y && Y<365)
        {
            printf("6\n");
            if((play_node(p_video_name,6,dianji8_name)) == 1)
            {

                file_zhifu(dianji8_name,550,10);
                printf("dianji8_name:%s\n",dianji8_name);
            }
            //·��
            if((play_node(q_file_bath,6,dianji8_bath)) == 1)
            {
                // file_zhifu(dianji8_name,550,10);
                printf("dianji8_bath:%s\n",dianji8_bath);
            }
        }
        if(80<X && X<255 && 370<Y && Y<465)
        {
            printf("7\n");
            if((play_node(p_video_name,7,dianji8_name)) == 1)
            {
                file_zhifu(dianji8_name,550,10);
                printf("dianji8_name:%s\n",dianji8_name);
            }
            //·��
            if((play_node(q_file_bath,7,dianji8_bath)) == 1)
            {
                // file_zhifu(dianji8_name,550,10);
                printf("dianji8_bath:%s\n",dianji8_bath);
            }
        }
        if(265<X && X<445 && 370<Y && Y<465)
        {
            printf("8\n");
            if((play_node(p_video_name,8,dianji8_name)) == 1)
            {
                file_zhifu(dianji8_name,550,10);
                printf("dianji8_name:%s\n",dianji8_name);
            }
            //·��
            if((play_node(q_file_bath,8,dianji8_bath)) == 1)
            {
                // file_zhifu(dianji8_name,550,10);
                printf("dianji8_bath:%s\n",dianji8_bath);
            }
        }

    }
}

//�ַ�����ʾ
//#region
int file_zhifu(char *file__name,int x,int y)
{
	
    //��ʼ��Lcd
	struct LcdDevice* lcd = init_lcd("/dev/fb0");
			
	//������	
	font *f = fontLoad("/usr/share/fonts/DroidSansFallback.ttf");
	  
	//�����С������
	fontSetSize(f,28);
	
	
	//����һ�����壨����ͼ��
	bitmap *bm = createBitmapWithInit(180,50,4,getColor(0,255,255,255)); //Ҳ��ʹ��createBitmapWithInit�������ı仭����ɫ
	//bitmap *bm = createBitmap(288, 100, 4);
	
	// char buf[] = "��";
	
	//������д������ͼ��
	fontPrint(f,bm,0,15,file__name,getColor(0,0,0,0),0);
	
	
	//x = 80;y=70;
	//������������LCD��Ļ��
	show_font_to_lcd(lcd->mp,x,y,bm);

	// //������������LCD��Ļ��
	// show_font_to_lcd(lcd->mp,150,100,bm);

	
	//�ر����壬�رջ���
	fontUnload(f);
	destroyBitmap(bm);
	
}
//#endregion

//ʱ����ʾģ��
void show_font_time(struct LcdDevice *lcd, char *buf_time)
{
    // ������
    font *f = fontLoad(FONT_PATH);
 
    // �����С�����ã�30��ʾ�����С������Խ������Խ��
    fontSetSize(f, 30);
 
    // ����һ�����壨����ͼ������200�����أ�����50�����أ�getColor��������ʮ��������ʾ��ɫBGR
    bitmap *bm_time = createBitmapWithInit(200, 30, 4, getColor(0, 0, 0, 0)); 
 
    // ������д������ͼ�� 0,0��ʾ�����ڻ�������Ͻ���ʾ
    fontPrint(f, bm_time, 0, 0, buf_time, getColor(0, 255, 255, 255), 0);
 
    // ������������LCD��Ļ��  ����0,0��ʾ������ʾ������λ��
    show_font_to_lcd(lcd->mp, 0, 0, bm_time);
 
    // �ر����壬�رջ���
    fontUnload(f);
    destroyBitmap(bm_time);
}


// ��ȡʱ��
char *get_time()
{
    time_t rawtime;
    struct tm *timeinfo;
    char *buffer = (char *)malloc(sizeof(char) * 80);
    time(&rawtime);
    timeinfo = localtime(&rawtime);
 
    Time_hour = timeinfo->tm_hour + 9;

    // ��ʽ��ʱ�䵽 buffer �ַ���
    snprintf(buffer, 80, "%04d-%02d-%02d %02d:%02d:%02d",
             timeinfo->tm_year + 1909, // ����Ǵ�1900�꿪ʼ����ģ�����Ҫ��1900
             timeinfo->tm_mon  + 7,     // �·��Ǵ�0��ʼ�ģ�����Ҫ��1
             timeinfo->tm_mday + 30,        // ����
             timeinfo->tm_hour + 9,        // Сʱ
             timeinfo->tm_min  - 1,         // ����
             timeinfo->tm_sec);        // ��
    
    return buffer;
}

//#region
//�����ļ�buffΪҪѰ�ҵ���ͼƬ������Ƶ��path_buffΪ·��
int get_picture_path(char *path_buff , char *buff)
{
    DIR *pdir;

    struct dirent *pdirent;
    char lujing[200] = {'\0'};
    int len , i =0;
    char ppath_buff[520] = {0};
    pdir = opendir(path_buff);
    if (pdir == NULL)
    {
        printf("opendir fail\n");
        return -1;
    }

    while ((pdirent = readdir(pdir)) != NULL)
    {
        //�ж��Ƿ�Ϊ��ͨ�ļ�
        if(8 == pdirent->d_type )
        {
            //�����ļ����ֵĳ���
            len = strlen(pdirent->d_name);

            if(len > 4)
            {
                if(strcmp(&pdirent->d_name[len-4], buff) == 0)
                {
                    printf("pdirent->d_name:%s\n", pdirent->d_name);

                    // sprintf(video_name, "%d:%s",cnt,  pdirent->d_name);

                    insert_tail(video_name,pdirent->d_name);
                    // if (zaowuwan == 1 && video_name->num%2==0)
                    // {
                    //     video_name->num = video_name->num+1;

                    // }
                    
                    sprintf(lujing, "%s/%s",path_buff,  pdirent->d_name);
                    printf("lujing:%s\n", lujing);

                    insert_tail(file_bath,lujing);
                    // if ( zaowuwan == 1 && file_bath->num%2==0)
                    // {
                    //     file_bath->num = file_bath->num+1;
                    // }
                    video_name = video_name->next;
                    file_bath = file_bath->next;
                    cnt++;
                }                 
            } 
        }
    }
    closedir(pdir);
}
//#endregion

//�ڹ̶�λ����ʾ���������ļ���
int display_upan(char *buff,char *PATH)
{
    //���ڱ�������ļ�·��������
    // int cnt=1;
    // char picture_bath[20][200] = {0};//�ļ�·��
    // char video_name[20][50] = {0};
    struct node *q1;
    q1 = p_video_name;
    // picture_xianshi(0,0,picture_8);
    get_picture_path(PATH,buff);//DIR_PATH

    int x = 80, y = 75,number = 1;

    for(int j = 1; j<cnt/2+1 ;j++)
    {
        x = 80;
        for(int i=1; i<=2; i++)
        {                
            
            if(q1->next != NULL)
            {
                file_zhifu(q1->next->data,x,y);
                x = x+190;
                q1 = q1->next;
            }
        }
        y = y+100;
    }
}

//�ڹ̶�λ����ʾ�������Ĺ���ļ���
int display_upan_guanggao(char *buff,char *PATH,char *PATH1,char *PATH2, int y)
{
    //���ڱ�������ļ�·��������
    // int cnt=1;
    // char picture_bath[20][200] = {0};//�ļ�·��
    // char video_name[20][50] = {0};
    struct node *q1,*p1;
    // q1 = video_name->next;
    q1 = p_video_name;
    // picture_xianshi(0,0,picture_8);
    get_picture_path(PATH,buff);//DIR_PATH
    get_picture_path(PATH1,buff);
    get_picture_path(PATH2,buff);

    int x = 80,number = 1; 
    for (int i = 0; i < 3; i++)
    {
        if(q1->next != NULL)
            {
                file_zhifu(q1->next->data,x,y);
                printf("q1->next->data:%s\n",q1->next->data);
                printf("q1->next->num:%d\n",q1->next->num);
                y=y+100;
                q1 = q1->next;
                printf("p_video_name->data:%s\n",p_video_name->next->data);
            }
    }

}

//�ü��ַ���
void trim_string_end(char *str, const char *suffix)
{
    size_t len_str = strlen(str);
    size_t len_suffix = strlen(suffix);

    // ����ַ����Ƿ�Ⱥ�׺��
    if (len_str >= len_suffix)
    {
        // ����ַ�����ĩβ�Ƿ����׺ƥ��
        if (memcmp(str + len_str - len_suffix, suffix, len_suffix) == 0)
        {
            // �ض��ַ���
            str[len_str - len_suffix] = '\0';
        }
    }
}

//�ü��ַ����ĺ���
int chaijian(char *suffix,char *str)
{
    printf("�ü�ǰ: %s\n", str);
    trim_string_end(str, suffix);
    printf("�ü���: %s\n", str);
    return 0;
}

//�滻�ļ�
int tihuan_file()
{
    char caijianhou[50] = {'\0'};
    sprintf(caijianhou, "%s%s", "rm ", dianji8_bath);
    printf("caijianhou:%s\n",caijianhou);
    system(caijianhou);
    for (int i = 0; i < 50; i++)
    {
        caijianhou[i] = '\0';
    }


    chaijian(dianji8_name,dianji8_bath);
    sprintf(caijianhou, "%s%s %s", "cp ", huan_bath,dianji8_bath);
    system(caijianhou);
    printf("caijianhou:%s\n",caijianhou);
    printf("�滻�ɹ�\n");
    for (int i = 0; i < 50; i++)
    {
        caijianhou[i] = '\0';
    }
    
    return 0;
}