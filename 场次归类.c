#include <direct.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
void cma_info();
int main()
{
    cma_info();
}
void cma_info()
{
    char cma[20];
    printf("��������Ҫ�����ӰԺ��");
    gets(cma);
    char *to_search = "D:\\workplace\\session_info\\*txt";//�����ҵ��ļ���֧��ͨ��� 
    long handle;                                //���ڲ��ҵľ��
    struct _finddata_t fileinfo;              //�ļ���Ϣ�Ľṹ�� 
    handle = _findfirst(to_search, &fileinfo); 
    //printf("%s\n", fileinfo.name);        
    //�������������ļ�
    char path[255] = "D:/workplace";
    char filename[255];
    wsprintf(filename, "/session_info/%s", fileinfo.name);
    strcat(path, filename);
    FILE *fp = NULL;
    fp = fopen(path, "r");
    char str[2][255];
    char *p;
    int i;
    //�����ļ���������ӰԺ
    for (i = 0; i < 2; i++)
    {
        fgets(str[i], 255, (FILE *)fp);
    }
    //�Ա��ļ�����ӰԺ�������ӰԺ��������¼��
    p = strtok(str[1], "\n");
    if (strcmp(str[1], cma) == 0)
    {
        memset(path, '\0', sizeof(path));
        strcpy(path, "D:/workplace");
        FILE *files = NULL;
        wsprintf(filename, "/cma_info/%s.txt", cma);
        strcat(path, filename);
        files = fopen(path, "a+");
        fprintf(files, "%s", str[0]);
        fputs("\n", fp);
    }
    while (!_findnext(handle, &fileinfo)) //���������ļ��е��ļ�
    {
        //printf("%s\n", fileinfo.name);
        memset(path, '\0', sizeof(path));
        strcpy(path, "D:/workplace");
        wsprintf(filename, "/session_info/%s", fileinfo.name);
        strcat(path, filename);
        FILE *fp = NULL;
        fp = fopen(path, "r");
        for (i = 0; i < 2; i++)
        {
            fgets(str[i], 255, (FILE *)fp);
        }
        p = strtok(str[1], "\n");
        //�����Ա�����ӰԺ��������¼��
        if (strcmp(str[1], cma) == 0)
        {
            memset(path, '\0', sizeof(path));
            strcpy(path, "D:/workplace");
            FILE *files = NULL;
            wsprintf(filename, "/cma_info/%s.txt", cma);
            strcat(path, filename);
            files = fopen(path, "a+");
            fprintf(files, "%s", str[0]);
            fputs("\n", fp);
        }
    }
    _findclose(handle); 
}