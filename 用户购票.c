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
#define FALSE 0
#define TRUE 1
#define MAXSIZE 101
#define MAX_LENGTH_OF_LINE 1024

typedef struct Order{   //订单结构体
    char ID[MAXSIZE];       //用户ID
    char MovName[MAXSIZE];  //影片名
    char Startime[6]; //影片开始时间
    char Stoptime[6]; //影片结束时间
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
    int  cost;               //总花费金额
    int MoneyAccount;       //账户余额
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
    float discount;         //优惠政策
    int row;                //总排数
    int colum;              //总列数
    int seat[MAXSIZE][MAXSIZE];//座位信息
}SessionDetail;

void SetPositionByLine(FILE *fp,int line);
Order CreateOrder(void);
bool Order_Is_Legal(Order order,SessionDetail session);
bool Time_Is_Conflict(char id[],SessionDetail session);
bool Money_Is_Enough(Order order);
bool Moive_Is_Repeat(char id[],SessionDetail session);
Order CompleteOrder(Order order,SessionDetail session);
void ReadOrder(Order order);
int SearchOrder(char id[]);
SessionDetail ReadSession(char sessionum[]);
void CurrentSeat(SessionDetail session);
Order SelectSeat(Order order,SessionDetail session);
Order Pay(Order order);
int time_to_min(char time[]);



void SetPositionByLine(FILE *fp,int line){   //将文件指针定位到指定行
    int i=0;
    char buffer[MAX_LENGTH_OF_LINE+1]={'\0'};
    fpos_t pos;
    rewind(fp);
    for(i=1;i<line;i++)
        fgets(buffer,MAX_LENGTH_OF_LINE,fp);
    fgetpos(fp,&pos);
}


Order CreateOrder(void){
    Order temp;
    temp.MoneyAccount=10000;
    printf("请输入用户ID:");
    scanf("%s",temp.ID);
    printf("请输入想要观看的影片:");
    scanf("%s",temp.MovName);
    
    return temp;
}

Order CompleteOrder(Order order,SessionDetail session){ //完善订单信息
    strcpy(order.CinName,session.CinName);
    strcpy(order.MovName,session.MovName);
    strcpy(order.Sessions,session.SessioNum);
    strcpy(order.Startime,session.Startime);
    strcpy(order.Stoptime,session.Stoptime);
    order.MovieRoom=session.MovieRoom;
    order.cost=order.SeatNum*session.price*session.discount;
    order.del=0;
    time_t t;
    time(&t);
    struct tm* p;
    p=localtime(&t);
    order.date.year=p->tm_year+1900;
    order.date.month=p->tm_mon+1;
    order.date.day=p->tm_mday;
    order.date.hour=p->tm_hour;
    order.date.min=p->tm_min;
    return order;
    
}

void ReadOrder(Order order){         //将订单信息写入文件
    int i=0;
    char name[MAXSIZE]={'\0'};
    strcpy(name,order.ID);
    strcat(name,".txt");
    
    FILE *fp;
    if(SearchOrder(order.ID))
        fp=fopen(name,"a+");
    else
        fp=fopen(name,"w");
    if(fp==NULL){
        printf("写入文件失败!\n");
        exit(0);
    }
    fprintf(fp,"%s\n",order.ID);
    fprintf(fp,"%d\n",order.del);
    fprintf(fp,"%s\n",order.MovName);
    fprintf(fp,"%s\n",order.Startime);
    fprintf(fp,"%s\n",order.Stoptime);
    fprintf(fp,"%s\n",order.CinName);
    fprintf(fp,"%d\n",order.MovieRoom);
    fprintf(fp,"%s\n",order.Sessions);
    fprintf(fp,"%d\n",order.SeatNum);
    for(i=0;i<order.SeatNum;i++)
        fprintf(fp,"%d %d\n",order.seat[i][0],order.seat[i][1]);
    fprintf(fp,"%d\n",order.date.year);
    fprintf(fp,"%d\n",order.date.month);
    fprintf(fp,"%d\n",order.date.day);
    fprintf(fp,"%d\n",order.date.hour);
    fprintf(fp,"%d\n",order.date.min);
    fprintf(fp,"%d\n",order.cost);
}

int SearchOrder(char id[]){         //查询订单
    char temp[MAXSIZE]={'\0'};
    strcpy(temp,id);
    strcat(temp,".txt");

    FILE *fp;
    if((fp=fopen(temp,"r"))==NULL)
        return 0;
    return 1;
}

int time_to_min(char time[]){
    char hour[3]={'\0'};
    char min[3]={'\0'};
    int h=0;
    int m=0;
    strncpy(hour,time,2);
    strncpy(min,time+3,2);
    h=atoi(hour);
    m=atoi(min);
    return h*60+m;
}

Order Pay(Order order){
    order.MoneyAccount=order.MoneyAccount-order.cost;
    return order;
}

bool Order_Is_Legal(Order order,SessionDetail session){
    int i,flag=1;
    for(i=0;i<order.SeatNum&&flag;i++){
        if(order.seat[i][1]==2){
            if(session.seat[order.seat[i][0]][order.seat[i][1]-1]||
               session.seat[order.seat[i][0]][order.seat[i][0]+2])
                flag=0;
        }
        else if(order.seat[i][1]==session.colum-1){
            if(session.seat[order.seat[i][0]][order.seat[i][1]+1]||
               session.seat[order.seat[i][0]][order.seat[i][0]-2])
                flag=0;
        }
        else if(order.seat[i][1]==1){
            if(session.seat[order.seat[i][0]][order.seat[i][1]+2])
                flag=0;
        }
        else if(order.seat[i][1]==session.colum){
            if(session.seat[order.seat[i][0]][order.seat[i][1]-2])
                flag=0;
        }
        else{
            if(session.seat[order.seat[i][0]][order.seat[i][1]-2]||
               session.seat[order.seat[i][0]][order.seat[i][0]+2]||
               session.seat[order.seat[i][0]][order.seat[i][0]]||
               order.seat[i][0]>session.row||order.seat[i][1]>session.colum)
                flag=0;
        }
    }
    return flag;
}

bool Money_Is_Enough(Order order){
    if(order.MoneyAccount<order.cost)
        return FALSE;
    return TRUE;
}

bool Moive_Is_Repeat(char id[],SessionDetail session){
    int flag=1;
    int i=3;
    char movie[MAXSIZE]={'\0'},temp[MAXSIZE]={'\0'};
    if(SearchOrder(id)==0)
        return TRUE;
    strcpy(temp,id);
    strcat(temp,".txt");
    FILE *fp;
    if((fp=fopen(temp,"r"))==NULL){
        printf("打开文件失败!\n");
        exit(0);
    }
    SetPositionByLine(fp, i);
    while(!feof(fp)&&flag){
        fscanf(fp,"%s",movie);
        if(strcmp(movie,session.MovName)==0)
            flag=0;
        i=i+17;
        SetPositionByLine(fp, i);
    }
    return flag;
}

bool Time_Is_Conflict(char id[],SessionDetail session){
    char time1[MAXSIZE]={'\0'},time2[MAXSIZE]={'\0'},temp[MAXSIZE]={'\0'};
    int Startmin1=time_to_min(session.Startime);
    int Startmin2=0,Stopmin2=0;
    int i=4,flag=1;
    if(SearchOrder(id)==0)
        return TRUE;
    strcpy(temp,id);
    strcat(temp,".txt");
    FILE *fp;
    if((fp=fopen(temp,"r"))==NULL){
        printf("文件打开失败\n");
        exit(0);
    }
    SetPositionByLine(fp, i);
    while(!feof(fp)&&flag){
        fscanf(fp,"%s",time1);
        fscanf(fp,"%s",time2);
        Startmin2=time_to_min(time1);
        Stopmin2=time_to_min(time2);
        if(Startmin1>=Startmin2&&Startmin1<=Stopmin2)
            flag=0;
        i=i+17;
        SetPositionByLine(fp, i);
    }
    return flag;
}

SessionDetail ReadSession(char sessionum[]){   //将场次信息文件写入结构体中
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
    SetPositionByLine(fp,2);
    fscanf(fp,"%s%s%d",temp.MovName,temp.CinName,&temp.MovieRoom);
    fscanf(fp,"%s%s%d",temp.Startime,temp.Stoptime,&temp.time);
    fscanf(fp,"%d%d%lf",&temp.AllticketNum,&temp.remainTicket,&temp.price);
    fscanf(fp,"%s%s%f%d%d",temp.language,temp.MovType,&temp.discount,&temp.row,&temp.colum);
    for(i=1;i<=temp.row;i++)
        for(j=1;j<=temp.colum;j++)
            temp.seat[i][j]=0;
    SetPositionByLine(fp,16);
    while(!feof(fp)){
        fscanf(fp,"%s",str);
        seat=atoi(str);
        seatx=seat/100;
        seaty=seat%100;
        temp.seat[seatx][seaty]=1;
    }
    fclose(fp);
    return temp;
}

void CurrentSeat(SessionDetail session){
    int i,j;
    printf("当前选座情况如图:(0代表可以选，1代表不可选)\n");
    for(i=1;i<=session.row;i++){
        for(j=1;j<=session.colum;j++){
            if(j==session.colum)
                printf("%d\n",session.seat[i][j]);
            else
                printf("%d ",session.seat[i][j]);
        }
    }
}

Order SelectSeat(Order order,SessionDetail session){
    int i=0,flag;
    int money;
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
    order.cost=order.SeatNum*session.price*session.discount;
    if(Money_Is_Enough(order)==0){
        printf("您的账户余额为%d元,当前账单为%d元,您最少需要充值%d元\n",
               order.MoneyAccount,order.cost,order.MoneyAccount-order.cost);
        printf("请输入要充值的金额:");
        scanf("%d",&money);
        order.MoneyAccount=order.MoneyAccount+money;
    }
    order=CompleteOrder(order, session);
    
    return order;
}

int main(int argc,const char * argv[]){
    //char str[MAXSIZE]={'\0'};
    SessionDetail session;
    Order order;
    order=CreateOrder();
    session=ReadSession("DDYY08021431");
    /*
    FILE *fp;
    if((fp=fopen("DDYY08021430.txt","r"))==NULL)
        exit(0);
    SetPositionByLine(fp, 4);
    fscanf(fp,"%s",str);
    printf("%s",str);
    */
    if(Time_Is_Conflict(order.ID, session)==0)
        //printf("您预订的电影:%s和您已购买的电影:%s时间上冲突\n",order.MovName,session.MovName);
    if(Moive_Is_Repeat(order.ID, session)==0)
        printf("您之前已经预定过该电影，您确定要再次预订吗？\n");
    order=SelectSeat(order,session);
    ReadOrder(order);
}

