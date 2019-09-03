#ifndef _STRUCT_H
#define _STRUCT_H

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

#endif
