#include <direct.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
void find_studio_info();
int main()
{
    find_studio_info();
}
void find_studio_info()
{
    char studio[5];
    printf("��������Ҫ���ҵ�Ӱ��������ţ�");
    gets(studio);
    char *to_search = "D:\\workplace\\studio_info\\*.txt";
    long handle;                               //���ڲ��ҵľ��
    struct _finddata_t fileinfo;               //�ļ���Ϣ�Ľṹ��
    handle = _findfirst(to_search, &fileinfo); //��һ�β���
    //printf("%s\n", fileinfo.name);        //��ӡ���ҵ����ļ����ļ���
    char path[255] = "D:/workplace";
    char filename[255];
    int temp = 0;
    strcat(studio, ".txt");
    if (strcmp(studio, fileinfo.name) == 0)
    {
        temp = 1;
        wsprintf(filename, "/studio_info/%s", fileinfo.name);
        strcat(path, filename);
        FILE *fp = NULL;
        fp = fopen(path, "r");
        char str[255];
        printf("��Ӱ���ľ�����Ϣ���£�\n");
        while (!feof(fp))
        {
            fgets(str, 255, (FILE *)fp);
            printf("%s", str);
        }
    }
    while (!_findnext(handle, &fileinfo)) //ѭ�������������ϵ��ļ���֪���Ҳ���������Ϊֹ
    {
        //printf("%s\n", fileinfo.name);
        if (strcmp(studio, fileinfo.name) == 0)
        {
            temp = 1;
            memset(path, '\0', sizeof(path));
            strcpy(path, "D:/workplace");
            wsprintf(filename, "/studio_info/%s", fileinfo.name);
            strcat(path, filename);
            FILE *fp = NULL;
            fp = fopen(path, "r");
            char str[255];
            printf("��Ӱ���ľ�����Ϣ���£�\n");
            while (!feof(fp))
            {
                fgets(str, 255, (FILE *)fp);
                printf("%s", str);
            }
        }
    }
    if(temp==0)
    {
        printf("������ĳ��β�����");
    }
    _findclose(handle); //�����˹رվ��
}