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
    printf("����������Ҫ���ҵ�ӰԺ��");
    gets(cma);
    char *to_search = "D:\\workplace\\cma_info\\*txt"; //�����ҵ��ļ���֧��ͨ���
    long handle;                                       //���ڲ��ҵľ��
    struct _finddata_t fileinfo;                       //�ļ���Ϣ�Ľṹ��
    handle = _findfirst(to_search, &fileinfo);
    //printf("%s\n", fileinfo.name);
    //�������������ļ�
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
        printf("�˵�ӰԺ��ӰƬ�������£�\n");
        fgets(str, 255, (FILE *)fp);
        while (!feof(fp))
        {
            printf("%s", str);
            fgets(str, 255, (FILE *)fp);
        }
    }
    while (!_findnext(handle, &fileinfo)) //ѭ�������������ϵ��ļ���֪���Ҳ���������Ϊֹ
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
            printf("�˵�ӰԺ��ӰƬ�������£�\n");
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
        printf("�������ӰԺ������");
    }
    _findclose(handle); //�����˹رվ��
}