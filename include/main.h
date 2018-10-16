

#ifndef _MAIN_H
#define _MAIN_H
typedef struct student
{
    char num[12]; //学号
    char name[20];//姓名
    char classlist[11][20];//选课列表
    int credit;//总学分
    struct student* next;//指针域
}stu;
typedef struct course
{
    char sernum[4]; //课程编号
    char classname[20];//课程名称
    char nature[20];//课程性质
    int time;//授课学时
    int classcredit;//学分
    int selnum;//已选人数
    int maxsize;//课程人数上限
    struct course* next;
}cose;
cose *clreadfile();//读取文件，将内容写入链表
void clwritefile(cose *);//读取链表内容，将其写入文件
void clprintall(cose *);//打印所有课程信息
void addcourse(cose *);//增加课程信息
void delclassnum(stu *,cose *);//按编号删除课程
void printclassnum(cose *);//按编号打印课程信息
int changecose(cose *);//按编号修改课程信息
stu* readfile();
void writefile(stu*);
void printall(stu*);
void addstu(stu*,cose *);
void delnum(stu*);
void printnum(stu*);
void printname(stu*);
int changestu(stu*,cose *);
void addselnum(stu *,cose *);
void addcredit(stu *, cose *);
#endif
