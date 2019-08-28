#include <stdio.h>
#include <string.h>
#include <windows.h>
void input_info();
void add_session_info();
void change_info();
int main()
{
    // input_info();
    // change_info();
}
void input_info() //管理员的信息录入,num代表第num个管理员
{
    char ID[20], cma[20];
    char name[20];
    char addr[40], pwd[30];
    // 从ID到password依次输入
    printf("管理员，请输入你的ID：\n");
    gets(ID);
    printf("请输入你的所属影院：\n");
    gets(cma);
    printf("请输入你的姓名：\n");
    gets(name);
    printf("请输入你的邮箱地址：\n");
    gets(addr);
    printf("请输入你的密码：\n");
    gets(pwd);
    //printf( ID);
    //开始读写文件
    char path[255] = "D:/workplace";
    char filename[255];
    wsprintf(filename, "/%s.txt", ID);
    strcat(path, filename);
    FILE *fp = NULL;
    fp = fopen(path, "a+");
    //依次将录入信息存入表中
    fputs(ID, fp);
    fputs("\n", fp);
    fputs(cma, fp);
    fputs("\n", fp);
    fputs(name, fp);
    fputs("\n", fp);
    fputs(addr, fp);
    fputs("\n", fp);
    fputs(pwd, fp);
    fputs("\n", fp);
    fclose(fp);
}
void change_info() //更改管理员信息
{
    char ID[20];
    printf("请输入你的管理员ID：\n");
    //根据ID查找管理员
    gets(ID);
    char path[255] = "D:/workplace";
    char filename[255];
    wsprintf(filename, "/%s.txt", ID);
    strcat(path, filename);
    FILE *fp = NULL;
    fp = fopen(path, "r");
    //读取原数据并存储
    char str[5][255];
    char cma[20];
    char name[20];
    char addr[40], pwd[30];
    int i = 0;
    while (!feof(fp))
    {
        fgets(str[i], 255, (FILE *)fp);
        i++;
    }
    strcpy(ID, str[0]);
    strcpy(cma, str[1]);
    strcpy(name, str[2]);
    strcpy(addr, str[3]);
    printf("请输入新的密码：\n");
    //更改密码
    gets(pwd);
    //录入文件
    fp = fopen(path, "w");
    fputs(ID, fp);
    fputs(cma, fp);
    fputs(name, fp);
    fputs(addr, fp);
    fputs(pwd, fp);
    fclose(fp);
}