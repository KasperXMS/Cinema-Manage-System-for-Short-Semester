#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
void session_classified();
int main()
{
    session_classified();
}
void session_classified()
{
    // printf("��������Ҫ�����ӰԺ��");
    // gets(cma);
    system("del D:\\workplace\\mov_info\\*txt");
    char *to_search = "D:\\workplace\\session_info\\*txt"; //�����ҵ��ļ���֧��ͨ���
    long handle;                                           //���ڲ��ҵľ��
    struct _finddata_t fileinfo;                           //�ļ���Ϣ�Ľṹ��
    handle = _findfirst(to_search, &fileinfo);
    //printf("%s\n", fileinfo.name);
    //�������������ļ�
    char pathA[255] = "D:/workplace";
    char filename[255] = {'\0'};
    wsprintf(filename, "/session_info/%s", fileinfo.name);
    strcat(pathA, filename);
    FILE *fp = NULL;
    fp = fopen(pathA, "r");
    char str[5][255];
    memset(str, 0, sizeof(str));
    int i;
    //int num = 0;
    //�����ļ���������ӰԺ
    for (i = 0; i < 4; i++)
    {
        fgets(str[i], 255, (FILE *)fp);
    }
    //�Ա��ļ�����ӰԺ�������ӰԺ��������¼��
    //p = strtok(str[2], "\n");
    // if (strcmp(str[2], cma) == 0)
    // {
    // num++;
    memset(pathA, '\0', sizeof(pathA));
    strcpy(pathA, "D:/workplace");
    FILE *files = NULL;
    strtok(str[1], "\n");
    wsprintf(filename, "/mov_info/%s.txt", str[1]);
    strcat(pathA, filename);
    files = fopen(pathA, "a+");
    fprintf(files, "%s", str[0]);
    fputs("\n", fp);
    // }
    while (!_findnext(handle, &fileinfo)) //���������ļ��е��ļ�
    {
        //printf("%s\n", fileinfo.name);
        memset(pathA, '\0', sizeof(pathA));
        strcpy(pathA, "D:/workplace");
        wsprintf(filename, "/session_info/%s", fileinfo.name);
        strcat(pathA, filename);
        FILE *fp = NULL;
        fp = fopen(pathA, "r");
        for (i = 0; i < 4; i++)
        {
            fgets(str[i], 255, (FILE *)fp);
        }
        strtok(str[1], "\n");
        //�����Ա�����ӰԺ��������¼��
        // if (strcmp(str[2], cma) == 0)
        // {
        memset(pathA, '\0', sizeof(pathA));
        strcpy(pathA, "D:/workplace");
        FILE *files = NULL;
        wsprintf(filename, "/mov_info/%s.txt", str[1]);
        strcat(pathA, filename);
        files = fopen(pathA, "a+");
        fprintf(files, "%s", str[0]);
        fputs("\n", fp);
        //}
    }
    _findclose(handle);
}