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
    // printf("请输入你要整理的影院：");
    // gets(cma);
    system("del D:\\workplace\\mov_info\\*txt");
    char *to_search = "D:\\workplace\\session_info\\*txt"; //欲查找的文件，支持通配符
    long handle;                                           //用于查找的句柄
    struct _finddata_t fileinfo;                           //文件信息的结构体
    handle = _findfirst(to_search, &fileinfo);
    //printf("%s\n", fileinfo.name);
    //打开所遍历到的文件
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
    //查找文件中所属的影院
    for (i = 0; i < 4; i++)
    {
        fgets(str[i], 255, (FILE *)fp);
    }
    //对比文件所属影院与待查找影院，符合则录入
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
    while (!_findnext(handle, &fileinfo)) //继续遍历文件夹的文件
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
        //继续对比所属影院，符合则录入
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