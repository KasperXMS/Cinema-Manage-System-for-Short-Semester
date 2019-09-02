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

    strncpy(filename, path, strlen(path) - 8); //copy, 14�ǳ�����λ������.exe��λ��
    strcat(filename, "accounts\\admin\\");
    strcat(filename, username); //ƴ��
    strcat(filename, ".acc");
    in = fopen(filename, "r");

    fscanf(in, "%s", username);
    fscanf(in, "%s", cinema);
    fscanf(in, "%s", NAME);
    fscanf(in, "%s", email);
    fscanf(in, "%s", password);

    while (flag)
    {
        printf("��ѡ��\n");
        printf("1. �޸�����\n");
        printf("2. �޸�����\n");
        printf("3. ����\n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            flag = 1;
            while (flag)
            {
                printf("�����������룺\n");
                scanf("%s", newPassword1);
                printf("���ٴ�ȷ�������룺\n");
                scanf("%s", newPassword2);
                if (strcmp(newPassword1, newPassword2) == 0)
                {
                    if (judgeUsername(newPassword1) == 1)
                    {
                        if (strcmp(newPassword1, password) != 0)
                        {
                            strcpy(password, newPassword1);
                            printf("�޸ĳɹ���\n");
                            flag = 0;
                        }
                        else
                        {
                            printf("������ԭ������ͬ\n");
                        }
                    }
                    else
                    {
                        printf("�Ƿ����룡\n");
                    }
                }
                else
                {
                    printf("�������벻һ������������\n");
                }
            }
            flag = 1;
            break;
        case 2:
            flag = 1;
            while (flag)
            {
                printf("�������µ����䣺\n");
                scanf("%s", newEmail);
                if (judgeEmail(newEmail) == 1)
                {
                    if (strcmp(email, newEmail) != 0)
                    {
                        strcpy(email, newEmail);
                        printf("�޸ĳɹ���\n");
                        flag = 0;
                    }
                    else
                    {
                        printf("������ԭ������ͬ\n");
                    }
                }
                else
                {
                    printf("�Ƿ����룡\n");
                }
            }
            flag = 1;
            break;
        case 3:
            flag = 0;
            break;
        default:
            printf("�Ƿ����룡\n");
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
    printf("��������Ҫ���ҵĳ���ID��");
    gets(session);
    char to_search[101] = {'\0'};
    strncpy(to_search, path, strlen(path) - 8);
    strcpy(to_search, "session_info\\*.txt");
    long handle;                               //���ڲ��ҵľ��
    struct _finddata_t fileinfo;               //�ļ���Ϣ�Ľṹ��
    handle = _findfirst(to_search, &fileinfo); //��һ�β���
    //printf("%s\n", fileinfo.name);        //��ӡ���ҵ����ļ����ļ���
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
        printf("�˳��εľ�����Ϣ���£�\n");
        ShowSession(Session);
    }
    while (!_findnext(handle, &fileinfo)) //ѭ�������������ϵ��ļ���֪���Ҳ���������Ϊֹ
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
            printf("�˳��εľ�����Ϣ���£�\n");
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
        printf("������ĳ��β�����");
    }
    _findclose(handle); //�����˹رվ��
}

void find_studio_info(char path[]) //����ԱӰ����ѯ
{
    getchar();
    char studio[5];
    printf("��������Ҫ���ҵ�Ӱ��������ţ�");
    gets(studio);
    char to_search[101] = {'\0'};
    strncpy(to_search, path, strlen(path) - 8);
    strcat(to_search, "studio_info\\*.txt");
    long handle;                               //���ڲ��ҵľ��
    struct _finddata_t fileinfo;               //�ļ���Ϣ�Ľṹ��
    handle = _findfirst(to_search, &fileinfo); //��һ�β���
    //printf("%s\n", fileinfo.name);        //��ӡ���ҵ����ļ����ļ���
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
        printf("��Ӱ���ľ�����Ϣ���£�\n");
        fgets(str, 255, (FILE *)fp);
        while (!feof(fp))
        {
            printf("%s", str);
            fgets(str, 255, (FILE *)fp);
        }
    }
    while (!_findnext(handle, &fileinfo)) //ѭ�������������ϵ��ļ���֪���Ҳ���������Ϊֹ
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
            printf("��Ӱ���ľ�����Ϣ���£�\n");
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
        printf("������ĳ��β�����");
    }
    _findclose(handle); //�����˹رվ��
}

void studio_info(char path[]) //���Ӱ��
{
    //������ӰԺ����š���λ�������ʹ������
    char cma[20];
    int num = 0;
    int seats = 0;
    char kind[10];
    getchar();
    printf("�����������ڵ�ӰԺ��");
    gets(cma);
    printf("��������Ҫ��ӵ�Ӱ���ţ�");
    scanf("%d", &num);
    printf("�������Ӱ������λ����");
    scanf("%d", &seats);
    printf("�������Ӱ�������ͣ�");
    scanf("%s", kind);
    char pathA[255] = {'\0'};
    strncpy(pathA, path, strlen(path) - 9);
    char filename[255] = {'\0'};
    wsprintf(filename, "\\studio_info\\%s%d.txt", cma, num);
    strcat(pathA, filename);
    FILE *fp = NULL;
    fp = fopen(pathA, "a+");
    //����¼��
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

void add_session_info(char path[]) //��ӳ���
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
    printf("��������Ҫ��ӵĳ���ID��");
    gets(session);
    printf("��������Ҫ��ӵ�ӰƬ���ƣ�");
    gets(mov);
    printf("�����������ڵ�ӰԺ��");
    gets(cma);
    printf("��������Ҫ��ӵ���Ӱ���ţ�");
    scanf("%d", &studio);
    int judge = 0;
    while (judge == 0)
    {
        printf("������ӰƬ�Ŀ�ʼʱ�䣺");
        scanf("%s", star);
        printf("������ӰƬ�Ľ���ʱ�䣺");
        scanf("%s", end);
        printf("������ӰƬʱ����");
        scanf("%d", &time);
        judge = session_arrange(path, cma, studio, hhmm2min(star), time);
        if (judge == 0)
        {
            printf("�������ʱ�������������г�ͻ������������");
        }
    }
    printf("�����뱾����Ʊ�ۣ�");
    scanf("%lf", &pri);
    //ӰƬ����
    strcpy(kind, "����");
    //������
    rate = 1;
    char pathA[255] = {'\0'};
    strncpy(pathA, path, strlen(path) - 9);
    char filename[255] = {'\0'};
    wsprintf(filename, "\\session_info\\%s.txt", session);
    strcat(pathA, filename);
    FILE *fp = NULL;
    printf("%s\n", pathA);
    fp = fopen(pathA, "a+");
    //��������Ϣ���Զ�����Ϣ����¼�����
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
    printf("��������Ҫ�����ӰԺ��");
    gets(cma);
    char to_search[101] = {'\0'};
    strncpy(to_search, path, strlen(path) - 8);
    strcat(to_search, "session_info\\*.txt");
    long handle;                               //���ڲ��ҵľ��
    struct _finddata_t fileinfo;               //�ļ���Ϣ�Ľṹ��
    handle = _findfirst(to_search, &fileinfo); //��һ�β���
    //printf("%s\n", fileinfo.name);        //��ӡ���ҵ����ļ����ļ���
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
    //�����ļ���������ӰԺ
    for (i = 0; i < 3; i++)
    {
        fgets(str[i], 255, (FILE *)fp);
    }
    //�Ա��ļ�����ӰԺ�������ӰԺ��������¼��
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
    while (!_findnext(handle, &fileinfo)) //���������ļ��е��ļ�
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
        //�����Ա�����ӰԺ��������¼��
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
    } Sessiontime; //���ݶ�������ڽṹ��
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
            fscanf(fp1, "%s", buffering); //��ȡӰԺ�ļ��г�������(ʵ�ʲ������������+1�ģ�����Ӱ�������������)
        }
        n--;
        fclose(fp1);
        char **session_ID = (char **)malloc(n * sizeof(char *));
        for (i = 0; i < n; i++)
        {
            session_ID[i] = (char *)malloc(20 * sizeof(char)); //��ά����������
        }
        fp1 = fopen(filename, "r");
        Sessiontime *sessions = (Sessiontime *)malloc(n * sizeof(Sessiontime)); //��̬�ṹ������
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
                sessions[i].end = hhmm2min(sessions[i].ends); //���б�򿪳����ļ���ȡ��Ϣ
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
        } //��Щ��΢���Ե��߼�������ͼ��������
    }
    else
    {
        fprintf(stderr, "File open error_1!\n");
    }
    return value;
}
#endif
