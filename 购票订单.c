//
//  main.c
//  小学期2
//
//  Created by 想去南极的北极熊 on 2019/8/27.
//  Copyright © 2019 想去南极的北极熊. All rights reserved.
//

//
//  main.c
//  小学期2
//
//  Created by 想去南极的北极熊 on 2019/8/27.
//  Copyright © 2019 想去南极的北极熊. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#define MAXSIZE 101
#define MAX_LENGTH_OF_LINE 1024

typedef struct Order{   //订单结构体
    char ID[MAXSIZE];       //用户ID
    char MovName[MAXSIZE];  //影片名
    char CinName[MAXSIZE];  //影院名
    char Sessions[MAXSIZE]; //场次
    int MovieRoom;          //影厅
    int SeatNum;            //座位数
    int seat[3][2];         //座位信息
    int del;                //是否删除订单
    int legal;              //订单是否合法
    struct{                 //下单时间
        int year;
        int month;
        int day;
        int hour;
        int min;
    }date;
    int cost;               //总花费金额
}Order;

typedef struct movie{//场次信息结构体
    char SessioNum[13];     //场次号
    char MovName[MAXSIZE];  //影片名
    char CinName[MAXSIZE];  //影院名
    int MovieRoom;          //影厅
    char Startime[6];           //开始时间
    char Stoptime[6];           //结束时间
    int time;               //总时长
    int AllticketNum;       //总票数
    int remainTicket;       //余票数
    double price;           //票价
    char language[20];      //语言类型
    char MovType[6];        //影片类型
    int row;                //总排数
    int colum;              //总列数
    int seat[MAXSIZE][MAXSIZE];//座位信息
}SessionDetail;


SessionDetail ReadSession(char moviename[]);
Order CreateOrder(void);
void CurrentSeat(SessionDetail session);
Order SelectSeat(Order order,SessionDetail session);
void SetPositionByLine(FILE *fp,int line);
bool Order_Is_Legal(Order order,SessionDetail session);
Order CompleteOrder(Order order,SessionDetail session);

Order CreateOrder(void){
    Order temp;
    temp.del=0;
    time_t t;
    time(&t);
    struct tm* p;
    p=localtime(&t);
    temp.date.year=p->tm_year+1900;
    temp.date.month=p->tm_mon+1;
    temp.date.day=p->tm_mday;
    temp.date.hour=p->tm_hour;
    temp.date.min=p->tm_min;
    printf("请输入用户ID:");
    scanf("%s",temp.ID);
    printf("请输入想要观看的影片:");
    scanf("%s",temp.MovName);
    
    return temp;
}

Order CompleteOrder(Order order,SessionDetail session){
    strcpy(order.CinName,session.CinName);
    strcpy(order.MovName,session.MovName);
    strcpy(order.Sessions,session.SessioNum);
    order.MovieRoom=session.MovieRoom;
    order.cost=order.SeatNum*session.price;
    return order;
}

void SetPositionByLine(FILE *fp,int line){   //将文件指针定位到指定行
    int i=0;
    char buffer[MAX_LENGTH_OF_LINE+1]={'\0'};
    fpos_t pos;
    rewind(fp);
    for(i=0;i<=line;i++)
        fgets(buffer,MAX_LENGTH_OF_LINE,fp);
    fgetpos(fp,&pos);
}

bool Order_Is_Legal(Order order,SessionDetail session){
    int i,j,flag=1;
    for(i=0;i<order.SeatNum&&flag;i++)
        for(j=0;j<order.SeatNum&&flag;j++)
            if(session.seat[order.seat[i][j]-1][order.seat[i][j]-1]||
               session.seat[order.seat[i][j]+1][order.seat[i][j]+1])
                flag=0;
    return flag;
}

SessionDetail ReadSession(char sessionum[]){//将场次信息文件写入结构体中
    SessionDetail temp;
    int i,j,seat=0,seatx=0,seaty=0;
    char str[5]={'\0'};
    char str1[MAXSIZE]={'\0'};
    strcpy(temp.SessioNum,sessionum);
    strcpy(str1,sessionum);
    strcat(str1,".txt");
    FILE *fp;
    if((fp=fopen(str1,"r"))==NULL)
        exit(0);
    SetPositionByLine(fp,0);
    fscanf(fp,"%s%s%d",temp.MovName,temp.CinName,&temp.MovieRoom);
    fscanf(fp,"%s%s%d",temp.Startime,temp.Stoptime,&temp.time);
    fscanf(fp,"%d%d%lf",&temp.AllticketNum,&temp.remainTicket,&temp.price);
    fscanf(fp,"%s%s%d%d",temp.language,temp.MovType,&temp.row,&temp.colum);
    for(i=0;i<temp.row;i++)
        for(j=0;j<temp.colum;j++)
            temp.seat[i][j]=0;
    SetPositionByLine(fp,13);
    while(!feof(fp)){
        fscanf(fp,"%s",str);
        seat=atoi(str);
        seatx=seat/100;
        seaty=seat%100;
        temp.seat[seatx-1][seaty-1]=1;
    }
    fclose(fp);
    return temp;
}

void CurrentSeat(SessionDetail session){
    int i,j;
    printf("当前选座情况如图：\n");
    for(i=0;i<session.row;i++){
        for(j=0;j<session.colum;j++){
            if(j==session.colum-1)
                printf("%d\n",session.seat[i][j]);
            else
                printf("%d ",session.seat[i][j]);
        }
    }
}

Order SelectSeat(Order order,SessionDetail session){
    int i=0,flag;
    
    printf("请输入预订座位数:");
    scanf("%d",&order.SeatNum);
    if(order.SeatNum>3){//购票数大于余票数或者购票数大于3都表示订单失败
        printf("一个场次最多只允许订三个座位!请重新输入购买座位数:");
        scanf("%d",&order.SeatNum);
    }
    if(session.remainTicket<order.SeatNum){
        printf("剩余票数为%d张,您是否要继续购买?\n",session.remainTicket);
        scanf("%d",&flag);
        if(flag){
            printf("请输入购买座位数:");
            scanf("%d",&order.SeatNum);
        }
    }
    CurrentSeat(session);                      //向客户显示当前座位信息
    printf("请输入座位信息:");
    for(i=0;i<order.SeatNum;i++)
        scanf("%d%d",&order.seat[i][0],&order.seat[i][1]);
    if(Order_Is_Legal(order, session)==0){
        printf("请重新选座!\n");
        for(i=0;i<order.SeatNum;i++)
            scanf("%d%d",&order.seat[i][0],&order.seat[i][1]);
    }
    else
        order=CompleteOrder(order, session);
    
    return order;
}

int main(int argc,const char * argv[]){
    /*
     SessionDetail session;
     Order order;
     order=CreateOrder();
     session=ReadSession("DDYY08021430");
     order=SelectSeat(order,session);
     */
}

