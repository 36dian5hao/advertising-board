#include"lianbiao.h"
#include"hanshu.h"
#include"bianliang.h"
#include "font.h"

/*�����ʼ�� */
struct node *init_node(char *initial_data)
{
    node *new = (node *)malloc(sizeof(node));
    if (new == NULL)
    {
        printf("malloc fail\n");
        return NULL;
    }

    // ��ʼ�����ݳ�Ա
    if (initial_data != NULL)
    {
        // ����ṩ�˳�ʼ���ݣ��͸��Ƶ� data ��Ա��
        strncpy(new->data, initial_data, sizeof(new->data) - 1);
        new->data[sizeof(new->data) - 1] = '\0'; // ȷ���ַ����� '\0' ��β
        
    }
    else
    {
        // ���û���ṩ��ʼ���ݣ��� data ��Ա��ʼ��Ϊ���ַ���
        new->data[0] = '\0';
    }

    // ���� next ��ԱΪ NULL
    new->next = NULL;
    new->num = 0;
    // �����´����Ľڵ�ĵ�ַ
    return new;
}

/*�����������*/
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

/*�������*/
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

/*����β����*/
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

/*��������*/
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