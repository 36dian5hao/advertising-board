#ifndef __LIANBIAO_H
#define __LIANBIAO_H 

/*�����ʼ�� */
struct node *init_node(char *initial_data);
/*�����������*/
int play_node(struct node *head,int num,char *fuyuduixiang);
/*�������*/
void display_node(struct node *head);
/*����β����*/
int insert_tail(struct node *head, char *data);
/*��������*/
int destroy_node(struct node *head);




#endif
