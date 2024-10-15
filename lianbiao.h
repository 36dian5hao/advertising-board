#ifndef __LIANBIAO_H
#define __LIANBIAO_H 

/*链表初始化 */
struct node *init_node(char *initial_data);
/*链表遍历查找*/
int play_node(struct node *head,int num,char *fuyuduixiang);
/*链表遍历*/
void display_node(struct node *head);
/*链表尾插入*/
int insert_tail(struct node *head, char *data);
/*链表销毁*/
int destroy_node(struct node *head);




#endif
