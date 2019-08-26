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
#define FALSE 0
#define TRUE 1
#define MAXSIZE 32

typedef struct Order{  //用户个人信息及订单信息
    char ID[4];          //用户ID
    char Name[MAXSIZE];        //用户姓名
    int Tel[MAXSIZE];          //用户电话
    char gender;               //用户性别
    char Password[MAXSIZE];    //用户密码
    char Email[MAXSIZE];       //用户邮箱
    int del;                   //是否删除订单
    int num;                   //订单编号
    char moviename[MAXSIZE];   //影片名称
    int seat[2][2];            //订单座位信息
    int SeatNum;               //订单座位个数
    int MoneyAccount;          //账户余额
}Order;
Order temp[100];
void OrderTicket(char id[],int SeatNum,int seat[][2],char moviename[]);
int ReadOrder(Order temp[]);

int ReadOrder(Order temp[]){  //将Order_Ticket.txt文件中的订单信息写入temp数组中
    int i=0;
    FILE* fp;
    if((fp=fopen("Order_Ticket.txt","r"))==NULL)
        return i;
    
    while(!feof(fp)){
        temp[i].del=0;
        fscanf(fp,"%s",temp[i].ID);         //写入用户名
        fscanf(fp,"%d",&temp[i].num);       //写入订单编号
        fscanf(fp,"%s",temp[i].moviename);  //写入影片名称
        fscanf(fp,"%d",&temp[i].SeatNum);   //写入预订座位数
        
        for(int j=0;j<temp[i].SeatNum;j++){
            fscanf(fp,"%d%d",&temp[i].seat[j][0],&temp[i].seat[j][1]);
        }
        fscanf(fp,"%d",&temp[i].MoneyAccount);
        fgetc(fp);
        i++;
    }
    fclose(fp);
    
    return i-1;
}

void OrderTicket(char id[],int SeatNum,int seat[][2],char moviename[]){
    int OrderNum=ReadOrder(temp);
    Order NewOrder;
    //初始化订单信息
    strcpy(NewOrder.ID,id);
    strcpy(NewOrder.moviename,moviename);
    NewOrder.del=0;
    NewOrder.SeatNum=0;
    NewOrder.num=0;
    for(int i=0;i<OrderNum;i++)
        if(temp[i].num>NewOrder.num)
            NewOrder.num=temp[i].num;
    NewOrder.num++;
    for(int i=0;i<SeatNum;i++){
        for(int j=0;j<2;j++)
            if(seat[i][j]>=1&&seat[i][j]<=10)  //座位号在1-10之间说明预订座位成功
                NewOrder.seat[i][j]=seat[i][j];
        NewOrder.SeatNum++;
    }
    NewOrder.MoneyAccount=10000-(50*(NewOrder.SeatNum)); //账户余额实时扣费
    temp[OrderNum++]=NewOrder;   //temp数组中加入新的订单
    
    FILE *fp;
    if((fp=fopen("Order_Ticket.txt","w"))==NULL)    //将订单信息写入文件
        exit(0);
    for(int i=0;i<OrderNum;i++){
        fprintf(fp,"%s",temp[i].ID);
        fprintf(fp,"%d",temp[i].num);
        fprintf(fp,"%s",temp[i].moviename);
        fprintf(fp,"%d",temp[i].SeatNum);
        for(int j=0;j<temp[i].SeatNum;j++)     //录入座位信息
            fprintf(fp,"%d%d",temp[i].seat[j][0],temp[i].seat[j][1]);
        fprintf(fp,"%d",temp[i].MoneyAccount);
    }
    fclose(fp);
}

int main(int argc, const char * argv[]) {
    int seat[2][2]={{1,2},{3,4}};
    char moviename[]="复仇者联盟";
    char id[]="123";
    OrderTicket(id,2,seat,moviename);
    ReadOrder(temp);
    printf("用户名为:%s\n",temp[0].ID);
    printf("订单编号为：%d\n",temp[0].num);
    printf("影片名称为:%s\n",temp[0].moviename);
    printf("预订座位数:%d\n",temp[0].SeatNum);
    return 0;
}
