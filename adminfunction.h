#ifndef _ADMINFUNCTION_H
#define _ADMINFUNCTION_H

#include "gadgets.h"
#include "judge.h"
#include "session.h"
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
void session_classified(char path[]);
int session_arrange(char path[], char cinema[], int newhall, int newstart, int newtime);
void manager_find_order(char path[]);
void Changeinfo(char path[], char username[])
{
    FILE *in, *out;
    char buff[255] = {'\0'};
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
    SessionDetail Session;
    getchar();
    char session[20] = {'\0'};
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
        Session = Read_session_to_struct(fp, Session);
        char str[255];
        printf("此场次的具体信息如下：\n");
        ShowSession(Session);
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
            memset(pathA, '\0', sizeof(pathA));
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
    int num = 0;
    int seats = 0;
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
    char session[20] = {'\0'};
    char mov[20] = {'\0'};
    char cma[20] = {'\0'};
    int studio = 0;
    char star[6] = {'\0'};
    char end[6] = {'\0'};
    int time = 90;
    double pri = 60;
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
    int judge = 0;
    while (judge == 0)
    {
        printf("请输入影片的开始时间：");
        scanf("%s", star);
        printf("请输入影片的结束时间：");
        scanf("%s", end);
        printf("请输入影片时长：");
        scanf("%d", &time);
        judge = session_arrange(path, cma, studio, hhmm2min(star), time);
        if (judge == 0)
        {
            printf("你输入的时间与其他场次有冲突，请重新输入");
        }
    }
    printf("请输入本场次票价：");
    scanf("%lf", &pri);
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
    fprintf(fp, "%s", star);
    fputs("\n", fp);
    fprintf(fp, "%s", end);
    fputs("\n", fp);
    fprintf(fp, "%d", time);
    fputs("\n", fp);
    fprintf(fp, "%lf", pri);
    fputs("\n", fp);
    fputs(kind, fp);
    fputs("\n", fp);
    fprintf(fp, "%lf", rate);
    fputs("\n", fp);
    fclose(fp);
}

void session_classified(char path[])
{
    getchar();
    char cma[20] = {'\0'};
    printf("请输入你要整理的影院：");
    gets(cma);
    char to_search[101] = {'\0'};
    strncpy(to_search, path, strlen(path) - 8);
    strcat(to_search, "session_info\\*.txt");
    long handle;                               //用于查找的句柄
    struct _finddata_t fileinfo;               //文件信息的结构体
    handle = _findfirst(to_search, &fileinfo); //第一次查找
    //printf("%s\n", fileinfo.name);        //打印出找到的文件的文件名
    char pathA[255] = {'\0'};
    strncpy(pathA, path, strlen(path) - 9);
    char filename[255] = {'\0'};
    wsprintf(filename, "\\session_info\\%s", fileinfo.name);
    strcat(pathA, filename);
    FILE *fp = NULL;
    fp = fopen(pathA, "r");
    char str[3][255];
    memset(str, 0, sizeof(str));
    char *p;
    int i;
    int num = 0;
    //查找文件中所属的影院
    for (i = 0; i < 3; i++)
    {
        fgets(str[i], 255, (FILE *)fp);
    }
    //对比文件所属影院与待查找影院，符合则录入
    p = strtok(str[2], "\n");
    if (strcmp(str[2], cma) == 0)
    {
        num++;
        memset(pathA, '\0', sizeof(pathA));
        strncpy(pathA, path, strlen(path) - 9);
        FILE *files = NULL;
        wsprintf(filename, "\\cma_info\\%s.txt", cma);
        strcat(pathA, filename);
        if (num == 1)
        {
            files = fopen(pathA, "w+");
        }
        else
        {
            files = fopen(pathA, "a+");
        }
        fprintf(files, "%s", str[0]);
        fputs("\n", fp);
    }
    while (!_findnext(handle, &fileinfo)) //继续遍历文件夹的文件
    {
        //printf("%s\n", fileinfo.name);
        memset(str, 0, sizeof(str));
        memset(pathA, '\0', sizeof(pathA));
        strncpy(pathA, path, strlen(path) - 9);
        wsprintf(filename, "\\session_info\\%s", fileinfo.name);
        strcat(pathA, filename);
        FILE *fp = NULL;
        if ((fp = fopen(pathA, "r")) != NULL)
        {
            //printf("Successfully found!\n");
        }
        else
        {
            printf("Open failed!\n");
        }
        for (i = 0; i < 3; i++)
        {
            fgets(str[i], 255, (FILE *)fp);
        }
        p = strtok(str[2], "\n");
        //继续对比所属影院，符合则录入
        if (strcmp(str[2], cma) == 0)
        {
            num++;
            memset(pathA, '\0', sizeof(pathA));
            strncpy(pathA, path, strlen(path) - 9);
            FILE *files = NULL;
            wsprintf(filename, "\\cma_info\\%s.txt", cma);
            strcat(pathA, filename);
            if (num == 1)
            {
                files = fopen(pathA, "w+");
            }
            else
            {
                files = fopen(pathA, "a+");
            }
            fprintf(files, "%s", str[0]);
            fputs("\n", fp);
        }
    }
    _findclose(handle);
}
int session_arrange(char path[], char cinema[], int newhall, int newstart, int newtime)
{
    typedef struct
    {
        int hall;
        int start;
        int end;
        int time;
        char starts[20];
        char ends[20];
    } Sessiontime; //数据读出后存在结构体
    int value = 0;
    char filename[MAX] = {'\0'}, buffering[MAX] = {'\0'};
    FILE *fp1, *fp2;
    int i = 0, n = 0, newend = newstart + newtime, IOTime = 10, sweeptime = 10;
    strncpy(filename, path, strlen(path) - 19);
    strcat(filename, "cma_info\\");
    strcat(filename, cinema);
    strcat(filename, ".txt");
    printf("%s\n", filename);
    if ((fp1 = fopen(filename, "r")) != NULL)
    {
        for (n = 0; !feof(fp1); n++)
        {
            fscanf(fp1, "%s", buffering); //获取影院文件中场次数量(实际操作中这个数是+1的，但不影响程序正常功能)
        }
        n--;
        fclose(fp1);
        char **session_ID = (char **)malloc(n * sizeof(char *));
        for (i = 0; i < n; i++)
        {
            session_ID[i] = (char *)malloc(20 * sizeof(char)); //二维场次名数组
        }
        fp1 = fopen(filename, "r");
        Sessiontime *sessions = (Sessiontime *)malloc(n * sizeof(Sessiontime)); //动态结构体数组
        for (i = 0; i < n; i++)
        {
            fp2 = NULL;
            fscanf(fp1, "%s", session_ID[i]);
            memset(filename, 0, MAX * sizeof(char));
            strncpy(filename, path, strlen(path) - 19);
            strcat(filename, "session_info\\");
            strcat(filename, session_ID[i]);
            strcat(filename, ".txt");
            if ((fp2 = fopen(filename, "r")) != NULL)
            {
                for (int j = 0; j < 3; j++)
                {
                    fscanf(fp2, "%s", buffering);
                }
                fscanf(fp2, "%d", &sessions[i].hall);
                fscanf(fp2, "%s", sessions[i].starts);
                fscanf(fp2, "%s", sessions[i].ends);
                fscanf(fp2, "%d", &sessions[i].time);
                sessions[i].start = hhmm2min(sessions[i].starts);
                sessions[i].end = hhmm2min(sessions[i].ends); //依列表打开场次文件读取信息
            }
            else
            {
                fprintf(stderr, "File open error_2!\n");
            }
            fclose(fp2);
            if (sessions[i].hall == newhall)
            {
                if (newend < sessions[i].start)
                {
                    if ((sessions[i].start - newend) < (2 * IOTime + sweeptime))
                    {
                        return 0;
                    }
                    else
                    {
                        value = 1;
                    }
                }
                else
                {
                    if (newstart > sessions[i].end)
                    {
                        if ((newstart - sessions[i].end) > (2 * IOTime + sweeptime))
                        {
                            value = 1;
                        }
                        else
                        {
                            return 0;
                        }
                    }
                    else
                    {
                        return 0;
                    }
                }
            }
            else
            {
                value = 1;
                if (abs(newend - sessions[i].end) < (IOTime + sweeptime))
                    return 0;
                if ((sessions[i].start - newend) < IOTime && (sessions[i].start - newend) > 0)
                    return 0;
                if (abs(newstart - sessions[i].start) < IOTime)
                    return 0;
                if ((newstart - sessions[i].end) < IOTime && (newstart - sessions[i].end) > 0)
                    return 0;
            }
        } //这些稍微绕脑的逻辑，画个图就明白了
    }
    else
    {
        fprintf(stderr, "File open error_1!\n");
    }
    return value;
}
void manager_find_order(char path[])
{
    getchar();
    char cma[20];
    printf("请输入你要所在的影院：");
    gets(cma);
    char to_search[101] = {'\0'};
    strncpy(to_search, path, strlen(path) - 8);
    strcat(to_search, "order_info\\*.txt");
    long handle;                               //用于查找的句柄
    struct _finddata_t fileinfo;               //文件信息的结构体
    handle = _findfirst(to_search, &fileinfo); //第一次查找
    //printf("%s\n", fileinfo.name);
    //打开所遍历到的文件
    char pathA[255] = {'\0'};
    strncpy(pathA, path, strlen(path) - 9);
    char filename[255] = {'\0'};
    wsprintf(filename, "\\order_info\\%s", fileinfo.name);
    strcat(pathA, filename);
    FILE *fp = NULL;
    fp = fopen(pathA, "r");
    char str[6][255];
    memset(str, '\0', sizeof(str));
    char *p;
    int i;
    int num = 0;
    //查找文件中所属的影院
    for (i = 0; i < 6; i++)
    {
        fgets(str[i], 255, (FILE *)fp);
    }
    //对比文件所属影院与待查找影院，符合则录入
    strtok(str[5], "\n");
    if (strcmp(str[5], cma) == 0)
    {
        num++;
        printf("你所在的影院有以下几个用户订单：\n");
        printf("%s", str[0]);
    }
    while (!_findnext(handle, &fileinfo)) //继续遍历文件夹的文件
    {
        //printf("%s\n", fileinfo.name);
        memset(pathA, '\0', sizeof(pathA));
        strncpy(pathA, path, strlen(path) - 9);
        wsprintf(filename, "/order_info/%s", fileinfo.name);
        strcat(pathA, filename);
        FILE *fp = NULL;
        fp = fopen(pathA, "r");
        for (i = 0; i < 6; i++)
        {
            fgets(str[i], 255, (FILE *)fp);
        }
        p = strtok(str[5], "\n");
        if (strcmp(str[5], cma) == 0)
        {
            num++;
            if (num == 1)
            {
                printf("你所在的影院有以下几个用户订单：\n");
            }
            printf("%s", str[0]);
        }
    }
    char cont = 'y';
    while (cont == 'y')
    {
        char order[20];
        printf("请选择你要查询的订单：");
        gets(order);
        memset(pathA, '\0', sizeof(pathA));
        strncpy(pathA, path, strlen(path) - 9);
        strcat(order, ".txt");
        wsprintf(filename, "/order_info/%s", order);
        strcat(pathA, filename);
        fp = fopen(pathA, "r");
        char info[255];
        if (fp != NULL)
        {
            fgets(info, 255, (FILE *)fp);
            while (!feof(fp))
            {
                printf("%s", info);
                fgets(info, 255, (FILE *)fp);
            }
            fclose(fp);
            printf("你是否需要继续查询？\n继续请输入y，退出请输入任意字符\n");
            scanf("%c", &cont);
            getchar();
        }
        else
        {
            printf("请重新输入\n");
        }
    }

    _findclose(handle);
}
#endif
