#include <direct.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
void studio_classified(char *cma);
int main()
{
    char cma[20];
    printf("请你输入要归类的影院：");
    gets(cma);
    studio_classified(cma);
}
void studio_classified(char *cma)
{
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
    char *p;
    int i;
    for (i = 0; i < 4; i++)
    {
        fgets(str[i], 255, (FILE *)fp);
    }
    //对比文件所属影院与待查找影院，符合则录入
    p = strtok(str[2], "\n");
    if (strcmp(str[2], cma) == 0)
    {
        memset(pathA, '\0', sizeof(pathA));
        strcpy(pathA, "D:/workplace");
        FILE *files = NULL;
        strtok(str[3], "\n");
        wsprintf(filename, "/studio_info/%s%s.txt", cma, str[3]);
        strcat(pathA, filename);
        files = fopen(pathA, "a+");
        fprintf(files, "%s", str[0]);
        fputs("\n", fp);
    }
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
        p = strtok(str[2], "\n");
        //继续对比所属影院，符合则录入
        if (strcmp(str[2], cma) == 0)
        {
            memset(pathA, '\0', sizeof(pathA));
            strcpy(pathA, "D:/workplace");
            FILE *files = NULL;
            strtok(str[3], "\n");
            wsprintf(filename, "/studio_info/%s%s.txt", cma, str[3]);
            strcat(pathA, filename);
            files = fopen(pathA, "a+");
            fprintf(files, "%s", str[0]);
            fputs("\n", fp);
        }
    }
    _findclose(handle);

    //查找文件中所属的影院
}