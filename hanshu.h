#ifndef __HANSHU_H
#define __HANSHU_H 


//��ѡ�е��ļ���Ϣ��������
int fuzhisuzhu(char *new,char *initial_data);
//��ʼ���ļ����ƺ��ļ�·��
void setup_nodes(void);

//��ʼ��;
int lcd_init(void);
// ���ӳ��
int lcd_uninit(void);
//��ʼ��Lcd
struct LcdDevice *init_lcd(const char *device);
//��ʾbmpͼƬ
int show_bmp(const char *path, int w, int h);
//�ж�ʱ��
int panduanshijian();
//���ҵ�ǰʱ��Ҫ���ŵ���Ƶ��ͼƬ
int get_picture_path1(char *path_buff , char *buff);
//�ж��Ƿ񴥷���½
int guanliyuan(void);
//��������
int mima();
//��ʾͼƬ�Ľӿ�
int picture_xianshi(int x_z,int y_z,char *picture);
//��ʾ����Ա�Ľ���
int guanliyuan_picture();
//��ҳ��ʾ
int shouye();
//����Ա������ư�ť
int guanliyuan_kongzhi();
//�ַ�����ʾ
//#region
int file_zhifu(char *file__name,int x,int y);
//ʱ����ʾģ��
void show_font_time(struct LcdDevice *lcd, char *buf_time);
// ��ȡʱ��
char *get_time();
//�����ļ�buffΪҪѰ�ҵ���ͼƬ������Ƶ��path_buffΪ·��
int get_picture_path(char *path_buff , char *buff);
//�ڹ̶�λ����ʾ���������ļ���
int display_upan(char *buff,char *PATH);
//�ڹ̶�λ����ʾ�������Ĺ���ļ���
int display_upan_guanggao(char *buff,char *PATH,char *PATH1,char *PATH2, int y);
//�ü��ַ���
void trim_string_end(char *str, const char *suffix);
//�ü��ַ����ĺ���
int chaijian(char *suffix,char *str);
//�滻�ļ�
int tihuan_file();

#endif
