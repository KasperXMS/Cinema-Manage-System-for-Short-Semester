#include <stdio.h>
#include <string.h>
#include <windows.h>
void add_session_info();
int main()
{
    add_session_info();
}
//����Ӱ��Ϣ�������
void add_session_info()
{
    char session[20];
    char mov[20];
    char cma[20];
    int studio;
    int star = 1210;
    int end = 1340;
    int time = 90;
    int pri = 60;
    char kind[5];
    double rate = 1;
    printf("��������Ҫ��ӵĳ���ID��");
    gets(session);
    printf("��������Ҫ��ӵ�ӰƬ���ƣ�");
    gets(mov);
    printf("�����������ڵ�ӰԺ��");
    gets(cma);
    printf("��������Ҫ��ӵ���Ӱ���ţ�");
    scanf("%d", &studio);
    //ӰƬ����
    strcpy(kind, "����");
    //������
    rate = 1;
    char path[255] = "D:/workplace";
    char filename[255];
    wsprintf(filename, "/session_info/%s.txt", session);
    strcat(path, filename);
    FILE *fp = NULL;
    fp = fopen(path, "a+");
    //��������Ϣ���Զ�����Ϣ����¼�����
    fputs(session, fp);
    fputs("\n", fp);
    fputs(mov, fp);
    fputs("\n", fp);
    fputs(cma, fp);
    fputs("\n", fp);
    fprintf(fp, "%d", studio);
    fputs("\n", fp);
    fprintf(fp, "%d", star);
    fputs("\n", fp);
    fprintf(fp, "%d", end);
    fputs("\n", fp);
    fprintf(fp, "%d", time);
    fputs("\n", fp);
    fprintf(fp, "%d", pri);
    fputs("\n", fp);
    fputs(kind, fp);
    fputs("\n", fp);
    fprintf(fp, "%lf", rate);
    fputs("\n", fp);
    fclose(fp);
}