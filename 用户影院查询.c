#include <direct.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
void cst_find_cma();
int main()
{
    cst_find_cma();
}
void cst_find_cma()
{
    char cma[20];
    printf("请输入你想要查找的影院：");
    gets(cma);
    char *to_search = "D:\\workplace\\cma_info\\*txt"; //欲查找的文件，支持通配符
    long handle;                                       //用于查找的句柄
    struct _finddata_t fileinfo;                       //文件信息的结构体
    handle = _findfirst(to_search, &fileinfo);
    //printf("%s\n", fileinfo.name);
    //打开所遍历到的文件
    char pathA[255] = "D:/workplace";
    char filename[255] = {'\0'};
    char str[255] = {'\0'};
    strcat(cma, ".txt");
    int temp = 0;
    if (strcmp(fileinfo.name, cma) == 0)
    {
        temp = 1;
        wsprintf(filename, "/cma_info/%s", fileinfo.name);
        strcat(pathA, filename);
        FILE *fp = NULL;
        fp = fopen(pathA, "r");
        printf("此电影院的影片场次如下：\n");
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
        if (strcmp(cma, fileinfo.name) == 0)
        {
            temp = 1;
            memset(pathA, '\0', sizeof(pathA));
            strcpy(pathA, "D:/workplace");
            wsprintf(filename, "/cma_info/%s", fileinfo.name);
            strcat(pathA, filename);
            FILE *fp = NULL;
            fp = fopen(pathA, "r");
            char str[255];
            printf("此电影院的影片场次如下：\n");
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
        printf("你输入的影院不存在");
    }
    _findclose(handle); //别忘了关闭句柄
}