#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"main.h"

int main()
{
    int n;
    stu *stuhead;
    cose *cosehead;
    printf("\n\n");
    printf("\t---------------欢迎使用选课管理系统！---------------\n");
    printf("\n\n");
    printf("\t---------------菜单如下，请输入选项！---------------\n");
    printf("\t[1]:查看所有学生信息\n");
    printf("\t[2]:新增学生信息\n");
    printf("\t[3]:修改学生信息\n");
    printf("\t[4]:删除学生信息\n");
    printf("\t[5]:按学号查看学生详细信息\n");
    printf("\t[6]:按姓名查看学生详细信息\n");
    printf("\t[7]:查看所有课程信息\n");
    printf("\t[8]:新增课程\n");
    printf("\t[9]:删除课程\n");
    printf("\t[10]:按编号查看课程详细信息\n");
    printf("\t[11]:按编号修改课程信息\n");
    printf("\t[12]:退出！\n");
    printf("\t----------------------------------------------------\n");
    printf("\t----------------------------------------------------\n\n");
    stuhead=readfile();
    cosehead=clreadfile();
    while(1)
    {
        printf("请输入选项：");
        scanf("%d",&n);
        printf("\n");
        switch(n)
        {
            case 1: printall(stuhead);break;
            case 2: addstu(stuhead,cosehead);addselnum(stuhead,cosehead);addcredit(stuhead,cosehead);writefile(stuhead);break;
            case 3: changestu(stuhead,cosehead);addcredit(stuhead,cosehead);addselnum(stuhead,cosehead);writefile(stuhead);break;
            case 4: delnum(stuhead);addselnum(stuhead,cosehead);writefile(stuhead);break;
            case 5: printnum(stuhead);break;
            case 6: printname(stuhead);break;
            case 7: clprintall(cosehead);break;
            case 8: addcourse(cosehead);clwritefile(cosehead);break;
            case 9: delclassnum(stuhead,cosehead);addcredit(stuhead,cosehead);clwritefile(cosehead);break;
            case 10: printclassnum(cosehead);break;
            case 11: changecose(cosehead);addcredit(stuhead,cosehead);clwritefile(cosehead);break;
            case 12: writefile(stuhead);clwritefile(cosehead);exit(0);break;
            default: printf("输入错误，请重试!");break;
        }
    }
}
