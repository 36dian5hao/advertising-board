#ifndef __HANSHU_H
#define __HANSHU_H 


//将选中的文件信息赋予数组
int fuzhisuzhu(char *new,char *initial_data);
//初始化文件名称和文件路径
void setup_nodes(void);

//初始化;
int lcd_init(void);
// 解除映射
int lcd_uninit(void);
//初始化Lcd
struct LcdDevice *init_lcd(const char *device);
//显示bmp图片
int show_bmp(const char *path, int w, int h);
//判断时间
int panduanshijian();
//查找当前时间要播放的视频或图片
int get_picture_path1(char *path_buff , char *buff);
//判断是否触发登陆
int guanliyuan(void);
//输入密码
int mima();
//显示图片的接口
int picture_xianshi(int x_z,int y_z,char *picture);
//显示管理员的界面
int guanliyuan_picture();
//首页显示
int shouye();
//管理员界面控制按钮
int guanliyuan_kongzhi();
//字符的显示
//#region
int file_zhifu(char *file__name,int x,int y);
//时间显示模块
void show_font_time(struct LcdDevice *lcd, char *buf_time);
// 获取时间
char *get_time();
//遍历文件buff为要寻找的是图片还是视频，path_buff为路径
int get_picture_path(char *path_buff , char *buff);
//在固定位子显示被遍历的文件名
int display_upan(char *buff,char *PATH);
//在固定位子显示被遍历的广告文件名
int display_upan_guanggao(char *buff,char *PATH,char *PATH1,char *PATH2, int y);
//裁减字符串
void trim_string_end(char *str, const char *suffix);
//裁减字符串的函数
int chaijian(char *suffix,char *str);
//替换文件
int tihuan_file();

#endif
