#include <stdio.h>
#include <string.h>
#include <windows.h>
void studio_info();
int main()
{
    studio_info();
}
void studio_info() 
{
    //������ӰԺ����š���λ�������ʹ������
    char cma[20];
    int num;
    int seats;
    char kind[10];
    printf("�����������ڵ�ӰԺ��");
    gets(cma);
    printf("��������Ҫ��ӵ�Ӱ���ţ�");
    scanf("%d", &num);
    printf("�������Ӱ������λ����");
    scanf("%d", &seats);
    printf("�������Ӱ�������ͣ�");
    scanf("%s", kind);
    char path[255] = "D:/workplace";
    char filename[255];
    wsprintf(filename, "/studio_info/%s%d.txt", cma,num);
    strcat(path, filename);
    FILE *fp = NULL;
    fp = fopen(path, "a+");
    //����¼��
    fprintf(fp, "%s", cma);
    fputs("\n", fp);
    fprintf(fp, "%d", num);
    fputs("\n", fp);
    fprintf(fp, "%d", seats);
    fputs("\n", fp);
    fprintf(fp, "%s", kind);
    fputs("\n", fp);
    fclose(fp);
}