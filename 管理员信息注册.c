#include <stdio.h>
#include <string.h>
void input_info();
void mov_info(char *series, char *cma, int studio, int star, int end, int time);
void studio_info(int num, int seats, char *type);
int main()
{
    //input_info();

    // char series[20];
    // char cma[20];
    // int studio;
    // int star;
    // int end;
    // int time;
    // strcpy( series, "DDYY08270407");
    // strcpy( cma, "���ӰԺ");
    // studio = 60;
    // star = 1210;
    // end = 1330;
    // time = 130;
    // mov_info(series, cma, studio, star, end, time);
    int num = 7;
    int seats = 120;
    char type[2];
    strcpy(type, "4D");
    studio_info(num, seats, type);
}
void input_info()
{
    char cont = 'y';
    while (cont == 'y')
    {
        char ID[20], cma[20];
        char name[20];
        char addr[40], pwd[30];
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
        printf("����������y���˳�������n");
        scanf("%s", &cont);
        getchar();
        //��ʼ��д�ļ�
        FILE *fp = NULL;
        fp = fopen("D:/workplace/manager_info.acc", "a+");
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
}
void mov_info(char *series, char *cma, int studio, int star, int end, int time)
{
    int pri;
    char kind[5];
    double rate;
    pri = 60;
    strcpy(kind, "����");
    rate = 1;
    FILE *fp = NULL;
    fp = fopen("D:/workplace/mov_info.ses", "a+");
    fputs(series, fp);
    fputs("\n", fp);
    fputs(cma, fp);
    fputs("\n", fp);
    fprintf(fp,"%d",studio);
    fputs("\n", fp);
    fprintf(fp,"%d",star);
    fputs("\n", fp);
    fprintf(fp,"%d",end);
    fputs("\n", fp);
    fprintf(fp,"%d",time);
    fputs("\n", fp);
    fprintf(fp,"%d",pri);
    fputs("\n", fp);
    fputs(kind, fp);
    fputs("\n", fp);
    fprintf(fp,"%lf",rate);
    fputs("\n", fp);
    fclose(fp);
}
void studio_info(int num, int seats, char *type)
{
    FILE *fp = NULL;
    fp = fopen("D:/workplace/studio_info.txt", "a+");
    fprintf(fp,"%d",num);
    fputs("\n", fp);
    fprintf(fp,"%d",seats);
    fputs("\n", fp);
    fprintf(fp,"%s",type);
    fputs("\n", fp);
    fclose(fp);
}