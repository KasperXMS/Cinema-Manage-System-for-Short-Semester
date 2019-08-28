#include <stdio.h>
#include <string.h>
#include <windows.h>
void add_session_info();
int main()
{
    add_session_info();
}
//将电影信息存入表中
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
    printf("请输入你要添加的场次ID：");
    gets(session);
    printf("请输入你要添加的影片名称：");
    gets(mov);
    printf("请输入你所在的影院：");
    gets(cma);
    printf("请输入你要添加到的影厅号：");
    scanf("%d", &studio);
    //影片类型
    strcpy(kind, "待定");
    //打折率
    rate = 1;
    char path[255] = "D:/workplace";
    char filename[255];
    wsprintf(filename, "/session_info/%s.txt", session);
    strcat(path, filename);
    FILE *fp = NULL;
    fp = fopen(path, "a+");
    //将传入信息和自定义信息依次录入表中
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