//
//  main.c
//  小学期
//
//  Created by 想去南极的北极熊 on 2019/8/26.
//  Copyright © 2019 想去南极的北极熊. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#define FALSE 0
#define TRUE 1
#define MAXSIZE 32

typedef struct Order{  //订单信息
    char ID[11];                //用户ID
    int del;                    //是否删除订单
    int num;                    //订单编号
    char MovName[MAXSIZE];      //影片名称
    char CinName[MAXSIZE];      //影院名称
    int seat[3][2];             //订单座位信息
    int SeatNum;                //订单座位个数
    int Hour;                   //下单时间
    int Min;
    int date_year;              //下单日期
    int date_month;
    int date_day;
    int MovieNum;               //预订的场次数
    int MoneyAccount;           //账户余额
}Order;

int FindOrder(char id[]);                            //查询账户订单
int ReadOrder(char id[],Order temp[],int OrderNum);  //读取订单信息
bool _is_Time_Conflict(char moviename[]);
void SerchMovie(char Movname[],char Cinname[]);      //查询影片场次
void OrderTicket(Order tp,int OrderNum);             //将订单写入文件
int DeleteOrder(char id[],Order temp[],int OrderNum);//删除订单
Order OrderInfo(void);

int FindOrder(char id[]){
    char filename[MAXSIZE];
    strcpy(filename,id);
    strcat(filename,".txt");
    
    FILE *fp;
    if((fp=fopen(filename,"r"))==NULL)
        return 0;
    return 1;
}

int ReadOrder(char id[],Order temp[],int OrderNum){  //将文件中的订单信息写入temp数组中
    int i=OrderNum;
    char FileName[MAXSIZE];
    strcpy(FileName,id);
    strcat(FileName,".txt");
    
    FILE* fp;
    if((fp=fopen(FileName,"r"))){
        while(!feof(fp)){
            temp[i].del=0;
            fscanf(fp,"%s%d%s%d",temp[i].ID,&temp[i].num,temp[i].MovName,
                   &temp[i].SeatNum);                                //写入用户名,订单编号,影片名称
            fscanf(fp,"%s%02d%02d",temp[i].CinName,&temp[i].Hour,
                   &temp[i].Min);                                    //写入影院名称，下单时间
            fscanf(fp,"%d%d%d%d",&temp[i].date_year,&temp[i].date_month,
                   &temp[i].date_day,&temp[i].MovieNum);             //写入下单日期和场次数
            for(int j=0;j<temp[i].SeatNum;j++){
                fscanf(fp,"%d%d",&temp[i].seat[j][0],&temp[i].seat[j][1]);
            }
            fscanf(fp,"%d",&temp[i].MoneyAccount);
            fgetc(fp);
            i++;
        }
    }
    fclose(fp);
    
    return i;
}

void OrderTicket(Order tp,int OrderNum){               //将订单信息写入文件中
    int i,j,flag=1;
    char FileName[MAXSIZE];
    Order temp[100];
    Order NewOrder;
    //初始化订单信息
    strcpy(FileName,tp.ID);
    strcat(FileName,".txt");
    strcpy(NewOrder.ID,tp.ID);
    strcpy(NewOrder.MovName,tp.MovName);
    strcpy(NewOrder.CinName,tp.CinName);
    NewOrder.MovieNum=0;
    NewOrder.del=0;
    NewOrder.SeatNum=0;
    NewOrder.num=0;
    NewOrder.MoneyAccount=10000;
    time_t t;
    time(&t);
    struct tm* tp1;
    tp1=localtime(&t);
    NewOrder.Hour=tp1->tm_hour;
    NewOrder.Min=tp1->tm_min;
    NewOrder.date_year=tp1->tm_year+1900;
    NewOrder.date_month=tp1->tm_mon+1;
    NewOrder.date_day=tp1->tm_mday;
    for(int i=0;i<OrderNum;i++)
        if(temp[i].num>NewOrder.num)
            NewOrder.num=temp[i].num;
    NewOrder.num++;                                     //按下单顺序排订单编号
    if(tp.SeatNum<=3&&NewOrder.MovieNum<=5){            //每个人最多预订三个座位，最多五个场次
        for(i=0;i<tp.SeatNum;i++){
            for(j=0;j<2;j++){
                if(tp.seat[i][j]>=1&&tp.seat[i][j]<=10) //座位号在1-10之间说明预订座位成功
                    NewOrder.seat[i][j]=tp.seat[i][j];
                else
                    flag=0;
            }
            if(flag)                    //预订成功后座位数相应的调整
                NewOrder.SeatNum++;
        }
        NewOrder.MovieNum++;            //场次加一
    }
    else{                               //超过三个座位，或观看场次已满，座位编号都设为-1，表示预订失败
        for(i=0;i<tp.SeatNum;i++){
            for(j=0;j<2;j++)
                NewOrder.seat[i][j]=-1;
        }
    }
    temp[OrderNum]=NewOrder;            //temp数组中加入新的订单
    
    FILE *fp;
    if(FindOrder(tp.ID)){               //账户有订单记录,则预订场次加一，同时在之前订单后追加新订单
        temp[OrderNum].MovieNum++;
        fp=fopen(FileName,"a");
    }
    else
        fp=fopen(FileName,"w");
    
    if(fp==NULL)
        exit(0);
    if(NewOrder.MoneyAccount>=(50*NewOrder.SeatNum)){                 //账户余额扣款后还有结余才能写入文件
        fprintf(fp,"%s\n",temp[OrderNum].ID);
        fprintf(fp,"%d\n",temp[OrderNum].num);
        fprintf(fp,"%s\n",temp[OrderNum].MovName);
        fprintf(fp,"%d\n",temp[OrderNum].SeatNum);
        fprintf(fp,"%s\n",temp[OrderNum].CinName);
        fprintf(fp,"%02d\n",temp[OrderNum].Hour);
        fprintf(fp,"%02d\n",temp[OrderNum].Min);
        fprintf(fp,"%d\n",temp[OrderNum].date_year);
        fprintf(fp,"%d\n",temp[OrderNum].date_month);
        fprintf(fp,"%d\n",temp[OrderNum].date_day);
        fprintf(fp,"%d\n",temp[OrderNum].MovieNum);
        for(int j=0;j<temp[OrderNum].SeatNum;j++)     //录入座位信息
            fprintf(fp,"%d%d\n",temp[OrderNum].seat[j][0],
                    temp[OrderNum].seat[j][1]);
        fprintf(fp,"%d\n",temp[OrderNum].MoneyAccount);
    }
    else
        printf("请先充值\n");
    fclose(fp);
}

void SerchMovie(char Movname[],char Cinname[]){
    char moviename[MAXSIZE];
    char str[MAXSIZE];
    strcpy(moviename,Movname);
    strcat(moviename,".txt");
    
    FILE *fp;
    if((fp=fopen(moviename,"r"))==NULL){
        printf("打开文件失败\n");
        exit(0);
    }
    fgets(str,sizeof(str),fp);
    while(!feof(fp)){
        printf("%s",str);
        fgets(str,sizeof(str),fp);
    }
    fclose(fp);
}

int DeleteOrder(char id[],Order temp[],int OrderNum){
    int i,j;
    i=0;
    while(strcmp(id,temp[i].ID)&&i<OrderNum)
        i++;
    for(j=i;j<OrderNum-1;j++)
        temp[j]=temp[j+1];
    OrderNum--;
    return OrderNum;
}

Order OrderInfo(void){       //创建订单结构体
    Order tp;
    int i;
    printf("请输入用户ID:");
    gets(tp.ID);
    printf("请输入影院名称:");
    gets(tp.CinName);
    printf("请输入影片名称:");
    gets(tp.MovName);
    printf("请输入预订的座位数:");
    scanf("%d",&tp.SeatNum);
    printf("请输入座位号:");
    for(i=0;i<tp.SeatNum;i++){
        scanf("%d%d",&tp.seat[i][0],&tp.seat[i][1]);
    }
    getchar();
    return tp;
}



int main(int argc, const char * argv[]) {
    int i,j;
    int OrderNum=0,schedule;
    Order temp[100],tp[100];
    printf("请输入要添加的订单数:");
    scanf("%d",&schedule);
    getchar();
    for(j=0;j<schedule;j++){
        tp[j]=OrderInfo();
        OrderTicket(tp[j],OrderNum);
        OrderNum=ReadOrder(tp[j].ID,temp,OrderNum);
        
        for(i=0;i<OrderNum;i++){
            printf("用户名为:%s\n",temp[i].ID);
            printf("订单编号为:%d\n",temp[i].num);
            printf("影片名称为:%s\n",temp[i].MovName);
            printf("影院名称为:%s\n",temp[i].CinName);
            printf("下单时间为:%02d:%02d\n",temp[i].Hour,temp[i].Min);
            printf("下单日期为:%d年%d月%d日\n",temp[i].date_year,temp[i].date_month,
                   temp[i].date_day);
            printf("预订座位数:%d\n",temp[i].SeatNum);
        }
    }

    return 0;
}
