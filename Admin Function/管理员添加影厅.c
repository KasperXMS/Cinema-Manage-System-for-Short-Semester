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
    //将所属影院、编号、座位数和类型存入表中
    char cma[20];
    int num;
    int seats;
    char kind[10];
    printf("请输入你所在的影院：");
    gets(cma);
    printf("请输入你要添加的影厅号：");
    scanf("%d", &num);
    printf("请输入此影厅总座位数：");
    scanf("%d", &seats);
    printf("请输入此影厅的类型；");
    scanf("%s", kind);
    char path[255] = "D:/workplace";
    char filename[255];
    wsprintf(filename, "/studio_info/%s%d.txt", cma,num);
    strcat(path, filename);
    FILE *fp = NULL;
    fp = fopen(path, "a+");
    //依次录入
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