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
    printf("��������Ҫ���ڵ�ӰԺ��");
    gets(cma);
    char *to_search = "D:\\workplace\\order_info\\*txt"; //�����ҵ��ļ���֧��ͨ���
    long handle;                                         //���ڲ��ҵľ��
    struct _finddata_t fileinfo;                         //�ļ���Ϣ�Ľṹ��
    handle = _findfirst(to_search, &fileinfo);
    //printf("%s\n", fileinfo.name);
    //�������������ļ�
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
    //�����ļ���������ӰԺ
    for (i = 0; i < 6; i++)
    {
        fgets(str[i], 255, (FILE *)fp);
    }
    //�Ա��ļ�����ӰԺ�������ӰԺ��������¼��
    strtok(str[5], "\n");
    if (strcmp(str[5], cma) == 0)
    {
        num++;
        printf("�����ڵ�ӰԺ�����¼����û�������\n");
        printf("%s", str[0]);
    }
    while (!_findnext(handle, &fileinfo)) //���������ļ��е��ļ�
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
                printf("�����ڵ�ӰԺ�����¼����û�������\n");
            }
            printf("%s", str[0]);
        }
    }
    char cont = 'y';
    while (cont == 'y')
    {
        char order[20];
        printf("��ѡ����Ҫ��ѯ�Ķ�����");
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
        printf("���Ƿ���Ҫ������ѯ��\n����������y���˳������������ַ�\n");
        scanf("%c", &cont);
        getchar();
    }
    
    _findclose(handle);
}