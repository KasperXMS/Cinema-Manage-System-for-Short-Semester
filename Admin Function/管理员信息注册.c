#include <stdio.h>
#include <string.h>
#include <windows.h>
void input_info();
void add_session_info();
void change_info();
int main()
{
    // input_info();
    // change_info();
}
void input_info() //����Ա����Ϣ¼��,num�����num������Ա
{
    char ID[20], cma[20];
    char name[20];
    char addr[40], pwd[30];
    // ��ID��password��������
    printf("����Ա�����������ID��\n");
    gets(ID);
    printf("�������������ӰԺ��\n");
    gets(cma);
    printf("���������������\n");
    gets(name);
    printf("��������������ַ��\n");
    gets(addr);
    printf("������������룺\n");
    gets(pwd);
    //printf( ID);
    //��ʼ��д�ļ�
    char path[255] = "D:/workplace";
    char filename[255];
    wsprintf(filename, "/%s.txt", ID);
    strcat(path, filename);
    FILE *fp = NULL;
    fp = fopen(path, "a+");
    //���ν�¼����Ϣ�������
    fputs(ID, fp);
    fputs("\n", fp);
    fputs(cma, fp);
    fputs("\n", fp);
    fputs(name, fp);
    fputs("\n", fp);
    fputs(addr, fp);
    fputs("\n", fp);
    fputs(pwd, fp);
    fputs("\n", fp);
    fclose(fp);
}
void change_info() //���Ĺ���Ա��Ϣ
{
    char ID[20];
    printf("��������Ĺ���ԱID��\n");
    //����ID���ҹ���Ա
    gets(ID);
    char path[255] = "D:/workplace";
    char filename[255];
    wsprintf(filename, "/%s.txt", ID);
    strcat(path, filename);
    FILE *fp = NULL;
    fp = fopen(path, "r");
    //��ȡԭ���ݲ��洢
    char str[5][255];
    char cma[20];
    char name[20];
    char addr[40], pwd[30];
    int i = 0;
    while (!feof(fp))
    {
        fgets(str[i], 255, (FILE *)fp);
        i++;
    }
    strcpy(ID, str[0]);
    strcpy(cma, str[1]);
    strcpy(name, str[2]);
    strcpy(addr, str[3]);
    printf("�������µ����룺\n");
    //��������
    gets(pwd);
    //¼���ļ�
    fp = fopen(path, "w");
    fputs(ID, fp);
    fputs(cma, fp);
    fputs(name, fp);
    fputs(addr, fp);
    fputs(pwd, fp);
    fclose(fp);
}