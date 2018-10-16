/*************************************************************************
	> File Name: course.c
	> Author: 
	> Mail: 
	> Created Time: 2018年10月16日 星期二 10时06分00秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"main.h"

void addselnum(stu* stuhead,cose* cosehead)
{
    stu *p;
    cose *q;
    int i,j=0;
    int sum=0;
    char cla[20]={0};
    char *str="****";
    p=stuhead->next;
    q=cosehead->next;
    while(q!=NULL&&q->classname[0]!=0)
    {
        sum=0;
        while(p!=NULL)
        {
            for(i=0;i<10;i++)
            {
                if(strcmp(p->classlist[i],q->classname)==0)
                sum=sum+1;
            }
            p=p->next;
        }
        q->selnum=sum;
        q=q->next;
    }
}

cose* clreadfile()
{
    FILE *fp;
    char *fname="course.txt";
    cose *head;
    cose *new;
    cose *end;
    char ch;
    if((fp=fopen(fname,"rb+"))==NULL)
    {
        printf("打开文件%s错误\n",fname);
        exit(0);
    }
    rewind(fp);
    head=(cose *)malloc(sizeof(cose));
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
            new=(cose*)malloc(sizeof(cose));
            fread(new,sizeof(cose),1,fp);
            new->next=NULL;
            end->next=new;
            end=new;
        }
    }
    fclose(fp);
    return head;
}
void clwritefile(cose *head)
{
    cose *p;
    char *fname="course.txt";
    p=head->next;
    FILE *fp;
    if((fp=fopen(fname,"wb+"))==NULL)
    {
        printf("打开文件%s错误\n",fname);
        exit(0);
    }
    while(p!=NULL&&p->classname[0]!=0)
    {
        fwrite(p,sizeof(cose),1,fp);
        p=p->next;
    }
    fclose(fp);
    printf("写入课程信息成功！\n");
}
void clprintall(cose *head)
{
    cose *p;
    p=head->next;
    while(p!=NULL&&p->classname[0]!=0)
    {
        printf("课程编号:");
        puts(p->sernum);
        printf("课程名称:");
        puts(p->classname);
        printf("课程性质:");
        puts(p->nature);
        printf("授课学时:%d学时\n",p->time);
        printf("课程学分:%d分\n",p->classcredit);
        printf("已选人数:%d人\n",p->selnum);
        printf("课程人数上限:%d人\n\n\n",p->maxsize);
        p=p->next;
    }
}
void addcourse(cose *head)
{
    FILE *fp;
    cose *p;
    cose *new;
    char *fname="log.log";
    char *log="add a course";
    p=head;
    new=(cose *)malloc(sizeof(cose));
    printf("请输入课程编号:\n");
    scanf("%s",new->sernum);
    while (getchar() != '\n');
    printf("请输入课程名称:\n");
    scanf("%s",new->classname);
    printf("请输入课程性质:\n");
    scanf("%s",new->nature);
    while (getchar() != '\n');
    printf("请输入授课学时:\n");
    scanf("%d",&(new->time));
    printf("请输入课程学分:\n");
    scanf("%d",&(new->classcredit));
    new->selnum=0;
    printf("请输入课程人数上限:\n");
    scanf("%d",&(new->maxsize));
    if((fp=fopen(fname,"a"))==NULL)
    {
        printf("打开文件%s错误\n",fname);
        exit(0);
    }
    system("date >> log.log");
    fputs(log,fp);
    fprintf(fp,"\n");
    fprintf(fp,"名称为:");
    fputs(new->classname,fp);
    fprintf(fp,"\n");
    fclose(fp);
    new->next=p->next;
    p->next=new;
}
void delclassnum(stu *stuhead,cose *head)
{
    char *fname="log.log";
    char *log="delete a course";
    FILE *fp;
    char str[4]={0};
    char ch[20]={0};
    printf("请输入所需删除课程的编号:\n");
    scanf("%s",str);
    cose *p;
    cose *r;
    stu *q;
    int i=0;
    int j=0;
    q=stuhead->next;
    p=head->next;
    r=head;
    if((fp=fopen(fname,"a"))==NULL)
    {
        printf("打开文件%s错误\n",fname);
        exit(0);
    }
    system("date >> log.log");
    fputs(log,fp);
    fprintf(fp,"\n");
    fprintf(fp,"编号为:");
    fputs(str,fp);
    fprintf(fp,"\n");
    fclose(fp);
    while(p!=NULL&&p->classname[0]!=0)
    {
        if(strcmp(str,p->sernum)==0)
        {
            strcpy(ch,p->classname);
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
    while(q!=NULL)
    {
        for(i=0;i<10;i++)
        {
            if(strcmp(ch,q->classlist[i])==0)
            {
                for(j=i;j<9;j++)
                {
                    strcpy(q->classlist[j],q->classlist[j+1]);
                }
            }
        }
        q=q->next;
    }
}

void printclassnum(cose *head)
{
    cose *p;
    char ch[4]={0};
    printf("请输入所查看课程的编号:\n");
    scanf("%s",ch);
    p=head->next;
    while(p!=NULL&&p->classname[0]!=0)
    {
        if(strcmp(ch,p->sernum)==0)
        {
            printf("课程编号:");
            puts(p->sernum);
            printf("课程名称:");
            puts(p->classname);
            printf("课程性质:");
            puts(p->nature);
            printf("授课学时:%d学时\n",p->time);
            printf("授课学分:%d分\n",p->classcredit);
            printf("已选人数:%d人\n",p->selnum);
            printf("课程人数上限:%d人\n\n\n",p->maxsize);            
        }
        p=p->next;
    }
}
int changecose(cose *head)
{
    char *fname="log.log";
    char *log="change a course";
    char *cg1="change classname";
    char *cg2="change classnature";
    char *cg3="change period";
    char *cg4="change credit";
    char *cg5="change maxsize";
    char *cg6="no changes";
    FILE *fp;
    cose *p;
    p=head;
    int pos;
    char ch[4]={0};
    printf("请输入所修改的课程的编号:\n");
    scanf("%s",ch);
    printf("\n\n\t修改菜单如下，请选择:\n");
    printf("\t编号为固定属性，无法修改,若无任何提示，则未找到课程\n");
    printf("\t[1]:修改课程名称\n");
    printf("\t[2]:修改课程性质\n");
    printf("\t[3]:修改授课学时\n");
    printf("\t[4]:修改学分\n");
    printf("\t[5]:修改课程人数上限\n");
    printf("\t[6]:返回上一级\n");
    do
    {
        printf("\t请输入选项:");
        scanf("%d",&pos);
        getchar();
        if(pos>6||pos<1)
        {
            printf("error! please retry!\n");
        }
    }while(pos>6||pos<1);
    if((fp=fopen(fname,"a"))==NULL)
    {
        printf("打开文件%s错误\n",fname);
        exit(0);
    }
    system("date >> log.log");
    fputs(log,fp);
    fprintf(fp,"\n");
    fprintf(fp,"编号为:");
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
    if(pos==4)
    {
        fputs(cg4,fp);
    }
    if(pos==5)
    {
        fputs(cg5,fp);
    }
    if(pos==6)
    {
        fputs(cg6,fp);
    }
    fprintf(fp,"\n");
    fclose(fp);
    while(p!=NULL)
    {
        if(strcmp(ch,p->sernum)==0)
        {
            if(pos==1)
            {
                printf("请修改课程名称:");
                scanf("%s",p->classname);
            }
            if(pos==2)
            {
                printf("请修改课程性质:");
                scanf("%s",p->nature);
            }
            if(pos==3)
            {
                printf("请输入授课学时:");
                scanf("%d",&(p->time));
            }
            if(pos==4)
            {
                printf("请输入课程学分:");
                scanf("%d",&(p->classcredit));
            }
            if(pos==5)
            {
                printf("请输入课程人数上限:");
                scanf("%d",&(p->maxsize));
            }
            if(pos==6)
            {
                return 0;
            }
        }
        p=p->next;
    }
    return 0;
}
