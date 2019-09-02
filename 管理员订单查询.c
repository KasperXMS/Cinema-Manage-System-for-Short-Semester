#include <direct.h>
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
    char cma[20];
    printf("请输入你要所在的影院：");
    gets(cma);
    char *to_search = "D:\\workplace\\order_info\\*txt"; //欲查找的文件，支持通配符
    long handle;                                         //用于查找的句柄
    struct _finddata_t fileinfo;                         //文件信息的结构体
    handle = _findfirst(to_search, &fileinfo);
    //printf("%s\n", fileinfo.name);
    //打开所遍历到的文件
    char path[255] = "D:/workplace";
    char filename[255] = {'\0'};
    wsprintf(filename, "/order_info/%s", fileinfo.name);
    strcat(path, filename);
    FILE *fp = NULL;
    fp = fopen(path, "r");
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
        memset(path, '\0', sizeof(path));
        strcpy(path, "D:/workplace");
        wsprintf(filename, "/order_info/%s", fileinfo.name);
        strcat(path, filename);
        FILE *fp = NULL;
        fp = fopen(path, "r");
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
        memset(path, '\0', sizeof(path));
        strcpy(path, "D:/workplace");
        strcat(order, ".txt");
        wsprintf(filename, "/order_info/%s", order);
        strcat(path, filename);
        fp = fopen(path, "r");
        char info[255];
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
    
    _findclose(handle);
}