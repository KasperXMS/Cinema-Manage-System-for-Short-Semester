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
    printf("��������Ҫ���ҵĳ���ID��");
    gets(session);
    char *to_search = "D:\\workplace\\session_info\\*.txt";
    long handle;                               //���ڲ��ҵľ��
    struct _finddata_t fileinfo;               //�ļ���Ϣ�Ľṹ��
    handle = _findfirst(to_search, &fileinfo); //��һ�β���
    //printf("%s\n", fileinfo.name);        //��ӡ���ҵ����ļ����ļ���
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
        printf("�˳��εľ�����Ϣ���£�\n");
        while (!feof(fp))
        {
            fgets(str, 255, (FILE *)fp);
            printf("%s", str);
        }
    }
    while (!_findnext(handle, &fileinfo)) //ѭ�������������ϵ��ļ���֪���Ҳ���������Ϊֹ
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
            printf("�˳��εľ�����Ϣ���£�\n");
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