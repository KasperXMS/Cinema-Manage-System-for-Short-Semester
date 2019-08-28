#include <direct.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
void find_session_info();
int main()
{
    find_session_info();
}
void find_session_info()
{
    char session[20];
    printf("请输入你要查找的场次ID：");
    gets(session);
    char *to_search = "D:\\workplace\\session_info\\*.txt";
    long handle;                               //用于查找的句柄
    struct _finddata_t fileinfo;               //文件信息的结构体
    handle = _findfirst(to_search, &fileinfo); //第一次查找
    //printf("%s\n", fileinfo.name);        //打印出找到的文件的文件名
    char path[255] = "D:/workplace";
    char filename[255];
    int temp = 0;
    strcat(session, ".txt");
    if (strcmp(session, fileinfo.name) == 0)
    {
        temp = 1;
        wsprintf(filename, "/session_info/%s", fileinfo.name);
        strcat(path, filename);
        FILE *fp = NULL;
        fp = fopen(path, "r");
        char str[255];
        printf("此场次的具体信息如下：\n");
        while (!feof(fp))
        {
            fgets(str, 255, (FILE *)fp);
            printf("%s", str);
        }
    }
    while (!_findnext(handle, &fileinfo)) //循环查找其他符合的文件，知道找不到其他的为止
    {
        //printf("%s\n", fileinfo.name);
        if (strcmp(session, fileinfo.name) == 0)
        {
            temp = 1;
            memset(path, '\0', sizeof(path));
            strcpy(path, "D:/workplace");
            wsprintf(filename, "/session_info/%s", fileinfo.name);
            strcat(path, filename);
            FILE *fp = NULL;
            fp = fopen(path, "r");
            char str[255];
            int i;
            printf("此场次的具体信息如下：\n");
            while (!feof(fp))
            {
                fgets(str, 255, (FILE *)fp);
                printf("%s", str);
            }
        }
    }
    if(temp==0)
    {
        printf("你输入的场次不存在");
    }
    _findclose(handle); //别忘了关闭句柄
}