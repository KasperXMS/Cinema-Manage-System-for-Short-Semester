#ifndef _ADMINFUNCTION_H
#define _ADMINFUNCTION_H

//#include judge.h"
#include <direct.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#define MAX 101

void Changeinfo(char path[], char username[]);
void find_session_info(char path[]);
void find_studio_info(char path[]);
void studio_info(char path[]);
void add_session_info(char path[]);

void Changeinfo(char path[], char username[])
{
    FILE *in, *out;
    char buff[255];
    char password[MAX] = {'\0'};
    char NAME[MAX] = {'\0'}, cinema[MAX] = {'\0'}, email[MAX] = {'\0'};
    double remain = 0.00;
    char filename[MAX] = {'\0'};
    int choice = 0, flag = 1;
    char newPassword1[MAX], newPassword2[MAX], newEmail[MAX];

    strncpy(filename, path, strlen(path) - 8); //copy, 14是程序名位数加上.exe的位数
    strcat(filename, "accounts\\admin\\");
    strcat(filename, username); //拼接
    strcat(filename, ".acc");
    in = fopen(filename, "r");

    fscanf(in, "%s", username);
    fscanf(in, "%s", cinema);
    fscanf(in, "%s", NAME);
    fscanf(in, "%s", email);
    fscanf(in, "%s", password);

    while (flag)
    {
        printf("请选择：\n");
        printf("1. 修改密码\n");
        printf("2. 修改邮箱\n");
        printf("3. 返回\n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            flag = 1;
            while (flag)
            {
                printf("请输入新密码：\n");
                scanf("%s", newPassword1);
                printf("请再次确认新密码：\n");
                scanf("%s", newPassword2);
                if (strcmp(newPassword1, newPassword2) == 0)
                {
                    if (judgeUsername(newPassword1) == 1)
                    {
                        if (strcmp(newPassword1, password) != 0)
                        {
                            strcpy(password, newPassword1);
                            printf("修改成功！\n");
                            flag = 0;
                        }
                        else
                        {
                            printf("不能与原密码相同\n");
                        }
                    }
                    else
                    {
                        printf("非法输入！\n");
                    }
                }
                else
                {
                    printf("两次密码不一致请重新输入\n");
                }
            }
            flag = 1;
            break;
        case 2:
            flag = 1;
            while (flag)
            {
                printf("请输入新的邮箱：\n");
                scanf("%s", newEmail);
                if (judgeEmail(newEmail) == 1)
                {
                    if (strcmp(email, newEmail) != 0)
                    {
                        strcpy(email, newEmail);
                        printf("修改成功！\n");
                        flag = 0;
                    }
                    else
                    {
                        printf("不能与原邮箱相同\n");
                    }
                }
                else
                {
                    printf("非法输入！\n");
                }
            }
            flag = 1;
            break;
        case 3:
            flag = 0;
            break;
        default:
            printf("非法输入！\n");
        }
        fclose(in);
        if ((out = fopen(filename, "w+")) != NULL)
        {
            fprintf(out, "%s\n", username);
            fprintf(out, "%s\n", cinema);
            fprintf(out, "%s\n", NAME);
            fprintf(out, "%s\n", email);
            fprintf(out, "%s\n", password);
            fclose(out);
        }
        else
        {
            fprintf(stderr, "Cannot open the file!\n");
        }
    }
}

void find_session_info(char path[])
{
    getchar();
    char session[20];
    printf("请输入你要查找的场次ID：");
    gets(session);
    char to_search[101] = {'\0'};
    strncpy(to_search, path, strlen(path) - 8);
    strcpy(to_search, "session_info\\*.txt");
    long handle;                               //用于查找的句柄
    struct _finddata_t fileinfo;               //文件信息的结构体
    handle = _findfirst(to_search, &fileinfo); //第一次查找
    //printf("%s\n", fileinfo.name);        //打印出找到的文件的文件名
    char pathA[255] = {'\0'};
    strncpy(pathA, path, strlen(path) - 9);
    char filename[255] = {'\0'};
    int temp = 0;
    strcat(session, ".txt");
    if (strcmp(session, fileinfo.name) == 0)
    {
        temp = 1;
        wsprintf(filename, "\\session_info\\%s", fileinfo.name);
        strcat(pathA, filename);
        FILE *fp = NULL;
        fp = fopen(pathA, "r");
        char str[255];
        printf("此场次的具体信息如下：\n");
        fgets(str, 255, (FILE *)fp);
        while (!feof(fp))
        {
            printf("%s", str);
            fgets(str, 255, (FILE *)fp);
        }
    }
    while (!_findnext(handle, &fileinfo)) //循环查找其他符合的文件，知道找不到其他的为止
    {
        //printf("%s\n", fileinfo.name);
        if (strcmp(session, fileinfo.name) == 0)
        {
            temp = 1;
            memset(pathA, '\0', sizeof(pathA));
            strncpy(pathA, path, strlen(path) - 9);
            wsprintf(filename, "\\session_info\\%s", fileinfo.name);
            strcat(pathA, filename);
            FILE *fp = NULL;
            fp = fopen(pathA, "r");
            char str[255];
            int i;
            printf("此场次的具体信息如下：\n");
            fgets(str, 255, (FILE *)fp);
            while (!feof(fp))
            {
                printf("%s", str);
                fgets(str, 255, (FILE *)fp);
            }
        }
    }
    if (temp == 0)
    {
        printf("你输入的场次不存在");
    }
    _findclose(handle); //别忘了关闭句柄
}

void find_studio_info(char path[]) //管理员影厅查询
{
    getchar();
    char studio[5];
    printf("请输入你要查找的影厅完整编号：");
    gets(studio);
    char to_search[101] = {'\0'};
    strncpy(to_search, path, strlen(path) - 8);
    strcat(to_search, "studio_info\\*.txt");
    long handle;                               //用于查找的句柄
    struct _finddata_t fileinfo;               //文件信息的结构体
    handle = _findfirst(to_search, &fileinfo); //第一次查找
    //printf("%s\n", fileinfo.name);        //打印出找到的文件的文件名
    char pathA[255] = {'\0'};
    strncpy(pathA, path, strlen(path) - 9);
    char filename[255] = {'\0'};
    int temp = 0;
    strcat(studio, ".txt");
    if (strcmp(studio, fileinfo.name) == 0)
    {
        temp = 1;
        wsprintf(filename, "\\studio_info\\%s", fileinfo.name);
        strcat(pathA, filename);
        FILE *fp = NULL;
        fp = fopen(pathA, "r");
        char str[255];
        printf("此影厅的具体信息如下：\n");
        fgets(str, 255, (FILE *)fp);
        while (!feof(fp))
        {
            printf("%s", str);
            fgets(str, 255, (FILE *)fp);
        }
    }
    while (!_findnext(handle, &fileinfo)) //循环查找其他符合的文件，知道找不到其他的为止
    {
        //printf("%s\n", fileinfo.name);
        if (strcmp(studio, fileinfo.name) == 0)
        {
            temp = 1;
            memset(pathA, '\0', sizeof(path));
            strncpy(pathA, path, strlen(path) - 9);
            wsprintf(filename, "\\studio_info\\%s", fileinfo.name);
            strcat(pathA, filename);
            FILE *fp = NULL;
            fp = fopen(pathA, "r");
            char str[255];
            printf("此影厅的具体信息如下：\n");
            fgets(str, 255, (FILE *)fp);
            while (!feof(fp))
            {
                printf("%s", str);
                fgets(str, 255, (FILE *)fp);
            }
        }
    }
    if (temp == 0)
    {
        printf("你输入的场次不存在");
    }
    _findclose(handle); //别忘了关闭句柄
}

void studio_info(char path[]) //添加影厅
{
    //将所属影院、编号、座位数和类型存入表中
    char cma[20];
    int num;
    int seats;
    char kind[10];
    getchar();
    printf("请输入你所在的影院：");
    gets(cma);
    printf("请输入你要添加的影厅号：");
    scanf("%d", &num);
    printf("请输入此影厅总座位数：");
    scanf("%d", &seats);
    printf("请输入此影厅的类型；");
    scanf("%s", kind);
    char pathA[255] = {'\0'};
    strncpy(pathA, path, strlen(path) - 9);
    char filename[255] = {'\0'};
    wsprintf(filename, "\\studio_info\\%s%d.txt", cma, num);
    strcat(pathA, filename);
    FILE *fp = NULL;
    fp = fopen(pathA, "a+");
    //依次录入
    fprintf(fp, "%s", cma);
    fputs("\n", fp);
    fprintf(fp, "%d", num);
    fputs("\n", fp);
    fprintf(fp, "%d", seats);
    fputs("\n", fp);
    fprintf(fp, "%s", kind);
    fputs("\n", fp);
    fclose(fp);
}

void add_session_info(char path[]) //添加场次
{
    char session[20];
    char mov[20];
    char cma[20];
    int studio;
    int star = 1210;
    int end = 1340;
    int time = 90;
    int pri = 60;
    char kind[5];
    double rate = 1;
    getchar();
    printf("请输入你要添加的场次ID：");
    gets(session);
    printf("请输入你要添加的影片名称：");
    gets(mov);
    printf("请输入你所在的影院：");
    gets(cma);
    printf("请输入你要添加到的影厅号：");
    scanf("%d", &studio);
    //影片类型
    strcpy(kind, "待定");
    //打折率
    rate = 1;
    char pathA[255] = {'\0'};
    strncpy(pathA, path, strlen(path) - 9);
    char filename[255] = {'\0'};
    wsprintf(filename, "\\session_info\\%s.txt", session);
    strcat(pathA, filename);
    FILE *fp = NULL;
    printf("%s\n", pathA);
    fp = fopen(pathA, "a+");
    //将传入信息和自定义信息依次录入表中
    fputs(session, fp);
    fputs("\n", fp);
    fputs(mov, fp);
    fputs("\n", fp);
    fputs(cma, fp);
    fputs("\n", fp);
    fprintf(fp, "%d", studio);
    fputs("\n", fp);
    fprintf(fp, "%d", star);
    fputs("\n", fp);
    fprintf(fp, "%d", end);
    fputs("\n", fp);
    fprintf(fp, "%d", time);
    fputs("\n", fp);
    fprintf(fp, "%d", pri);
    fputs("\n", fp);
    fputs(kind, fp);
    fputs("\n", fp);
    fprintf(fp, "%lf", rate);
    fputs("\n", fp);
    fclose(fp);
}
