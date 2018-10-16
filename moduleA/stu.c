/*************************************************************************
	> File Name: stu.c
	> Author: 
	> Mail: 
	> Created Time: 2018年10月16日 星期二 10时05分49秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include"main.h"

void addcredit(stu *stuhead,cose *cosehead)
{

    stu *p;
    cose *q;
    int i,j=0;
    int sum=0;
    p=stuhead->next;
    q=cosehead->next;
    while(p!=NULL&&p->name[0]!=0)
    {
        sum=0;
        for(i=0;i<10;i++)
        {
            q=cosehead->next;
            while(q!=NULL)
            {
                if(strcmp(p->classlist[i],q->classname)==0)
                {
                    sum=sum+q->classcredit;
                }
                q=q->next;
            }
        }
        p->credit=sum;
        p=p->next;
    }
}

stu* readfile()
{
    FILE *fp;
    char *fname="student.txt";
    stu *head;
    stu *new;
    stu *end;
    char ch;
    if((fp=fopen(fname,"rb+"))==NULL)
    {
        printf("打开文件%s错误\n",fname);
        exit(0);
    }
    rewind(fp);
    head=(stu *)malloc(sizeof(stu));
    head->next=NULL;
    end=head;
    if(!fread(&ch,sizeof(char),1,fp))
    {
        return head;
    }
    else
    {
        rewind(fp);
        while(feof(fp)==0)
        {
            new=(stu*)malloc(sizeof(stu));
            fread(new,sizeof(stu),1,fp);
            new->next=NULL;
            end->next=new;
            end=new;
        }
    }
    fclose(fp);
    return head;
}
/*将链表中内容写入文件，入参为链表头指针，无返回值*/
void writefile(stu *head)
{
    stu *p;
    p=head->next;
    char *fname="student.txt";
    FILE *fp;
    if((fp=fopen(fname,"wb+"))==NULL)
    {
        printf("打开文件%s错误\n",fname);
        exit(0);
    }
    while(p!=NULL&&p->name[0]!=0)
    {
        fwrite(p,sizeof(stu),1,fp);
        p=p->next;
    }
    fclose(fp);
    printf("写入学生信息成功！\n");
}
/*打印链表中所有学生的信息，入参为链表头指针，无返回值*/
void printall(stu *head)
{
    stu *p;
    int i;
    char cla[20]={0};
    char *str="****";
    p=head->next;
    while(p!=NULL&&p->name[0]!=0)
    {
        printf("学号:");
        puts(p->num);
        printf("姓名:");
        puts(p->name);
        printf("选课情况如下:\n");
        for(i=0;i<10;i++)
        {
            strcpy(cla,p->classlist[i]);
            if(strcmp(cla,str)==0)
            {
                break;
            }
            puts(p->classlist[i]);
        }
        printf("总学分为:%d\n\n\n",p->credit);
        p=p->next;
    }
}
/*增加学生信息，从键盘输入学生信息，之后调用写入函数写入文件，入参为链表头指针，无返回值*/
void addstu(stu *head,cose *cosehead)
{
    char *fname="log.log";
    char *log="add a student";
    FILE *fp;
    stu *p;
    stu *new;
    cose *q;
    q=cosehead;
    p=head;
    int i=0;
    int sum;
    int x=0;
    int flag;
    char str[5]="****";
    new=(stu *)malloc(sizeof(stu));
    printf("请输入学号:\n");
    scanf("%s",new->num);
    while (getchar() != '\n');
    printf("请输入姓名:\n");
    scanf("%s",new->name);
    memset(new->classlist,0,210*sizeof(char));
    printf("请输入课程名选课(输入'****'表示选课完毕，每人最多选10门):\n");
    while(i<10)
    {
        printf("请选第%d门课:\n",i+1);
        scanf("%s",new->classlist[i]);
        if(strcmp(new->classlist[i],str)==0)
        {
            break;
        }
        x=0;
        q=cosehead;
        while(q!=NULL)
        {
            if(strcmp(new->classlist[i],q->classname)==0)
            {
                x=1;
                if(q->selnum < q->maxsize)
                flag=1;
                else flag=0;
            }
            q=q->next;
        }
        if(x==1&&flag==1)
        {
            i++;
        }
        else if(x==1&&flag==0)
        {
            printf("该课程人数已达上限！\n");
        }
        else printf("没有这门课！\n");
    }
    if((fp=fopen(fname,"a"))==NULL)
    {
        printf("打开文件%s错误\n",fname);
        exit(0);
    }
    system("date >> log.log");
    fputs(log,fp);
    fprintf(fp,"\n");
    fprintf(fp,"学号为:");
    fputs(new->num,fp);
    fprintf(fp,"\n");
    fclose(fp);
    new->credit=0;
    new->next=p->next;
    p->next=new;
}

void delnum(stu *head)
{
    char *fname="log.log";
    char *log="delete a student";
    FILE *fp;
    char str[12]={0};
    printf("请输入所需删除学生的学号:\n");
    scanf("%s",str);
    stu *p;
    stu *r;
    p=head->next;
    r=head;
    while(p!=NULL&&p->name[0]!=0)
    {
        if(strcmp(str,p->num)==0)
        {
            r->next=p->next;
            free(p);
            p=r->next;
        }
        else
        {
            p=p->next;
            r=r->next;
        }
    }
    if((fp=fopen(fname,"a"))==NULL)
    {
        printf("打开文件%s错误\n",fname);
        exit(0);
    }
    system("date >> log.log");
    fputs(log,fp);
    fprintf(fp,"\n");
    fprintf(fp,"学号为:");
    fputs(str,fp);
    fprintf(fp,"\n");
    fclose(fp);
}
void printnum(stu *head)
{
    stu *p;
    int i;
    char ch[12]={0};
    char cla[20]={0};
    char *str="****";
    printf("请输入所查看的学生的学号:\n");
    scanf("%s",ch);
    p=head->next;
    while(p!=NULL&&p->name[0]!=0)
    {
        if(strcmp(ch,p->num)==0)
        {
            printf("学号:");
            puts(p->num);
            printf("姓名:");
            puts(p->name);
            printf("选课情况如下:\n");
            for(i=0;i<10;i++)
            {
                strcpy(cla,p->classlist[i]);
                if(strcmp(cla,str)==0)
                {
                    break;
                }
                puts(p->classlist[i]);
            }
            printf("总学分为:%d\n\n",p->credit);
        }
        p=p->next;
    }
}
void printname(stu *head)
{
    stu *p;
    int i;
    char ch[20]={0};
    char cla[20]={0};
    char *str="****";
    printf("请输入所查看的学生的姓名:\n");
    scanf("%s",ch);
    p=head->next;
    while(p!=NULL&&p->name[0]!=0)
    {
        if(strcmp(ch,p->name)==0)
        {
            printf("学号:");
            puts(p->num);
            printf("姓名:");
            puts(p->name);
            printf("选课情况如下:\n");
            for(i=0;i<10;i++)
            {
                strcpy(cla,p->classlist[i]);
                if(strcmp(cla,str)==0)
                {
                    break;
                }
                puts(p->classlist[i]);
            }
            printf("总学分为:%d\n\n",p->credit);
        }
        p=p->next;
    }
}
int changestu(stu *head,cose *cosehead)
{
    char *fname="log.log";
    FILE *fp;
    stu *p;
    cose *q;
    q=cosehead;
    int flag=0,x=0;
    p=head->next;
    int i=0;
    char str[5]="****";
    int pos;
    char *log="change a student";
    char *cg1="change name";
    char *cg2="change classlist";
    char *cg3="no changes";
    char ch[12]={0};
    printf("请输入所修改的学生的学号:\n");
    scanf("%s",ch);
    printf("\n\n\t修改菜单如下，请选择:\n");
    printf("\t学号为固定属性，无法修改.若无任何提示，则未找到学生\n");
    printf("\t[1]:修改姓名\n");
    printf("\t[2]:修改选课情况\n");
    printf("\t[3]:返回上一级\n\n");
    do
    {
        printf("\t请输入选项:");
        scanf("%d",&pos);
        getchar();
        if(pos>3||pos<1)
        {
            printf("error! please retry!\n");
        }
    }while(pos>3||pos<1); 
    if((fp=fopen(fname,"a"))==NULL)
    {
        printf("打开文件%s错误\n",fname);
        exit(0);
    }
    system("date >> log.log");
    fputs(log,fp);
    fprintf(fp,"\n");
    fprintf(fp,"学号为:");
    fputs(ch,fp);
    if(pos==1)
    {
        fputs(cg1,fp);
    }
    if(pos==2)
    {
        fputs(cg2,fp);
    }
    if(pos==3)
    {
        fputs(cg3,fp);
    }
    fprintf(fp,"\n");
    fclose(fp);
    while(p!=NULL)
    {
        if(strcmp(ch,p->num)==0)
        {
            if(pos==1)
            {
                printf("请修改姓名:\n");
                scanf("%s",p->name);
            }
            if(pos==2)
            {
                memset(p->classlist,0,210*sizeof(char));
                printf("请输入课程名重新选课(输入'****'表示选课完毕，每人最多选10门):\n");
                while(i<10)
                {
                    printf("请选第%d门课:\n",i+1);
                    scanf("%s",p->classlist[i]);
                    if(strcmp(p->classlist[i],str)==0)
                    {
                        break;
                    }
                    x=0;
                    q=cosehead;
                    while(q!=NULL)
                    {
                        if(strcmp(p->classlist[i],q->classname)==0)
                        {
                            x=1;
                            if(q->selnum < q->maxsize)
                            flag=1;
                            else flag=0;
                        }
                        q=q->next;
                    }
                    if(x==1&&flag==1)
                    {
                        i++;
                    }
                    else if(x==1&&flag==0)
                    {
                        printf("该课程人数已达上限！\n");
                    }
                    else printf("没有这门课！\n");
                }
            }
            if(pos==3)
            {
                return 0;
            }
        }
        p=p->next;
    }
    return 0;
}
