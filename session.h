#include <stdio.h>
#define MAXSIZE 101
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
    int Curseat[MAXSIZE][2];   //已占座位信息
}SessionDetail;

void ShowSession(SessionDetail session);
void ShowSession(SessionDetail session)
{
    int i = 0;
    printf("+--------------------------------------------------------------------------------------------------------------------------------------------------+\n");
    printf("|     场次编号     |      影片名称      | 影院名称 | 影厅号 | 开始时间 | 结束时间 | 总时长 | 总座位 | 余票数 |  票价  | 语言类型 |电影类型| 优惠政策 | 总排数 | 总列数 |\n");
    printf("+--------------------------------------------------------------------------------------------------------------------------------------------------+\n");
    printf("|  %s  |     %-9s     |  %s  |   %d   |  %s  |  %s  | ",session.SessioNum,session.MovName,session.CinName,
           session.MovieRoom,session.Startime,session.Stoptime);
    printf(" %d |  %d  |  %d  | %.2lf |   %s   |  %s  |  %.2f  |", session.time,session.AllticketNum,session.remainTicket,session.price,session.language,
           session.MovType,session.discount);
    printf("   %d   |  %d  |\n", session.row,session.colum);
    printf("+--------------------------------------------------------------------------------------------------------------------------------------------------+\n");
    printf("已占座位信息:\n");
    for (i = 0; i < session.AllticketNum - session.remainTicket; i++)
           printf("%d排%d座\n", session.Curseat[i][0], session.Curseat[i][1]);
}

