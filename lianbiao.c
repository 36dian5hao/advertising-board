#include"lianbiao.h"
#include"hanshu.h"
#include"bianliang.h"
#include "font.h"

/*链表初始化 */
struct node *init_node(char *initial_data)
{
    node *new = (node *)malloc(sizeof(node));
    if (new == NULL)
    {
        printf("malloc fail\n");
        return NULL;
    }

    // 初始化数据成员
    if (initial_data != NULL)
    {
        // 如果提供了初始数据，就复制到 data 成员中
        strncpy(new->data, initial_data, sizeof(new->data) - 1);
        new->data[sizeof(new->data) - 1] = '\0'; // 确保字符串以 '\0' 结尾
        
    }
    else
    {
        // 如果没有提供初始数据，将 data 成员初始化为空字符串
        new->data[0] = '\0';
    }

    // 设置 next 成员为 NULL
    new->next = NULL;
    new->num = 0;
    // 返回新创建的节点的地址
    return new;
}

/*链表遍历查找*/
int play_node(struct node *head,int num,char *fuyuduixiang)
{
    struct node *p;
    p = head->next;

    printf("head->next->data:%s",head->next->data);
    while (p!= NULL)
    {

        if(p->num == num)
        {

            fuzhisuzhu(fuyuduixiang,p->data);
            return 1;
        }
        p = p->next;
    }

    return 0;
}

/*链表遍历*/
void display_node(struct node *head)
{
    struct node *p;
    p = head->next;
    while (p!= NULL)
    {
        printf("%s", p->data);
        p = p->next;
    }
    printf("\n");
}

/*链表尾插入*/
int insert_tail(struct node *head, char *data)
{
    struct node *new;
    new = init_node(data);
    if(new == NULL)
    {
        printf("malloc fail\n");
        return -1;
    }
    struct node *p;
    p = head;
    while (p->next!= NULL)
    {
        p = p->next;
    }
    if(zaowuwan == 1 && (p->num+1)%2 == 0)
    {
        new->num = p->num + 2;
        
    }else{
        new->num = p->num+1;
    }
    p->next = new;  
    return true;
}

/*链表销毁*/
int destroy_node(struct node *head)
{
    if(head == NULL)
    {
        return 0;
    }
    struct node *q1, *p1;
    p1 = head->next;
    if (p1 == NULL)
    {
        return 0;
    }
    
    while (p1->next!= NULL)
    {
        q1 = p1;
        if(p1->next != NULL)
        {
            p1 = p1->next;
        }
        q1->num = 0;
        free(q1);
        if(p1->next == NULL)
        {
            break;
        }
    }
    return true;
}