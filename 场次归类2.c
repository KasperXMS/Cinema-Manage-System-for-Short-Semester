#include <direct.h>
#include <io.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
void session_classified();
int main()
{
    session_classified();
}
void session_classified()
{
    // printf("请输入你要整理的影院：");
    // gets(cma);
    system("del D:\\workplace\\cma_info\\*txt");
    char *to_search = "D:\\workplace\\session_info\\*txt"; //欲查找的文件，支持通配符
    long handle;                                           //用于查找的句柄
    struct _finddata_t fileinfo;                           //文件信息的结构体
    handle = _findfirst(to_search, &fileinfo);
    //printf("%s\n", fileinfo.name);
    //打开所遍历到的文件
    char path[255] = "D:/workplace";
    char filename[255] = {'\0'};
    wsprintf(filename, "/session_info/%s", fileinfo.name);
    strcat(path, filename);
    FILE *fp = NULL;
    fp = fopen(path, "r");
    char str[3][255];
    memset(str, 0, sizeof(str));
    char *p;
    int i;
    //int num = 0;
    //查找文件中所属的影院
    for (i = 0; i < 3; i++)
    {
        fgets(str[i], 255, (FILE *)fp);
    }
    //对比文件所属影院与待查找影院，符合则录入
    p = strtok(str[2], "\n");
    // if (strcmp(str[2], cma) == 0)
    // {
    // num++;
    memset(path, '\0', sizeof(path));
    strcpy(path, "D:/workplace");
    FILE *files = NULL;
    wsprintf(filename, "/cma_info/%s.txt", str[2]);
    strcat(path, filename);
    if (access(path, 0))
    {
        files = fopen(path, "w+");
    }
    else
    {
        files = fopen(path, "a+");
    }
    fprintf(files, "%s", str[0]);
    fputs("\n", fp);
    // }
    while (!_findnext(handle, &fileinfo)) //继续遍历文件夹的文件
    {
        //printf("%s\n", fileinfo.name);
        memset(path, '\0', sizeof(path));
        strcpy(path, "D:/workplace");
        wsprintf(filename, "/session_info/%s", fileinfo.name);
        strcat(path, filename);
        FILE *fp = NULL;
        fp = fopen(path, "r");
        for (i = 0; i < 3; i++)
        {
            fgets(str[i], 255, (FILE *)fp);
        }
        p = strtok(str[2], "\n");
        //继续对比所属影院，符合则录入
        // if (strcmp(str[2], cma) == 0)
        // {
        memset(path, '\0', sizeof(path));
        strcpy(path, "D:/workplace");
        FILE *files = NULL;
        wsprintf(filename, "/cma_info/%s.txt", str[2]);
        strcat(path, filename);
        if (access(path, 0))
        {
            files = fopen(path, "w+");
        }
        else
        {
            files = fopen(path, "a+");
        }
        fprintf(files, "%s", str[0]);
        fputs("\n", fp);
        //}
    }
    _findclose(handle);
}