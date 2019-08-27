#include <stdio.h>
#include <string.h>
#include <windows.h>
void input_info(int num);
void mov_info(char *series, char *cma, int studio, int star, int end, int time);
void studio_info(int num, int seats, char *type);
int main()
{
    input_info(1);
    // char series[20];
    // char cma[20];
    // int studio;
    // int star;
    // int end;
    // int time;
    // strcpy( series, "DDYY08270407");
    // strcpy( cma, "大地影院");
    // studio = 60;
    // star = 1210;
    // end = 1330;
    // time = 130;
    // mov_info(series, cma, studio, star, end, time);
    // int num = 7;
    // int seats = 120;
    // char type[2];
    // strcpy(type, "4D");
    // studio_info(num, seats, type);
}
void input_info(int num) //管理员的信息录入,num代表第num个管理员
{
    char cont = 'y';
    char ID[20], cma[20];
    char name[20];
    char addr[40], pwd[30];
    // 从ID到password依次输入
    printf("管理员，请输入你的ID：\n");
    gets(ID);
    printf("请输入你的所属影院：\n");
    gets(cma);
    printf("请输入你的姓名：\n");
    gets(name);
    printf("请输入你的邮箱地址：\n");
    gets(addr);
    printf("请输入你的密码：\n");
    gets(pwd);
    //printf( ID);
    printf("继续请输入y，退出请输入n");
    scanf("%s", &cont);
    getchar();
    //开始读写文件
    char path[255] = "D:/workplace";
    char filename[255];
    wsprintf(filename, "/manager_%d.txt", num);
    strcat(path, filename);
    FILE *fp = NULL;
    fp = fopen(path, "a+");
    //依次将录入信息存入表中
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
void mov_info(char *series, char *cma, int studio, int star, int end, int time)
{
    int pri;
    char kind[5];
    double rate;
    pri = 60;
    //影片类型
    strcpy(kind, "待定");
    //打折率
    rate = 1;
    FILE *fp = NULL;
    fp = fopen("D:/workplace/mov_info.ses", "a+");
    //将传入信息和自定义信息录入表中
    fputs(series, fp);
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
void studio_info(int num, int seats, char *type) //将编号、座位数和类型存入表中
{
    FILE *fp = NULL;
    fp = fopen("D:/workplace/studio_info.txt", "a+");
    fprintf(fp, "%d", num);
    fputs("\n", fp);
    fprintf(fp, "%d", seats);
    fputs("\n", fp);
    fprintf(fp, "%s", type);
    fputs("\n", fp);
    fclose(fp);
}