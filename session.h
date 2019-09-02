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
    printf("场次编号:%s\n", session.SessioNum);
    printf("影片名称:%s\n", session.MovName);
    printf("影院名称:%s\n", session.CinName);
    printf("影厅号:%d\n", session.MovieRoom);
    printf("影片开始时间:%s\n", session.Startime);
    printf("影片开始时间:%s\n", session.Stoptime);
    printf("总时长:%d\n", session.time);
    printf("总座位:%d\n", session.AllticketNum);
    printf("余票数:%d\n", session.remainTicket);
    printf("票价:%lf\n", session.price);
    printf("语言类型:%s\n", session.language);
    printf("电影类型:%s\n", session.MovType);
    printf("优惠政策:%f\n", session.discount);
    printf("总排数:%d\n", session.row);
    printf("总列数:%d\n", session.colum);
    printf("已占座位信息:\n");
    for (i = 0; i < session.AllticketNum - session.remainTicket; i++)
        printf("%d排%d座\n", session.Curseat[i][0], session.Curseat[i][1]);
}
