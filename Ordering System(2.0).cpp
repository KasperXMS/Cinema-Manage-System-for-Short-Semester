#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <direct.h>
#include <windows.h>
#include <time.h>
#define MAXSIZE 101
#define MAX_LENGTH_OF_LINE 1024

typedef struct Basic{
	char IdOfUser[11];
	char MovieOrCinema[MAXSIZE];
}Basic;
typedef struct Order{  			//information of order
    char ID[MAXSIZE];           //ID of the user
    char MovName[MAXSIZE];      //name of the movie
    char CinName[MAXSIZE];      //name of the cinema
    char Sessions[MAXSIZE];		//session of the movie
    int MovieRoom; 				//number of the hall in the cinema
	int SeatNum;                //numbers of the seats that the user want to order
	int seat[3][2];             //positions of seats that the user want to order
    int del;                    //whether to delete the order
    int legal;					//judge whether the order is legal
	struct {
    	int year;
    	int month;
    	int day;
    	int hour;
    	int min;				//time when the order begins 
	}date;
	int cost;					//total cost of these seats
}Order;
typedef struct movie{			//场次信息结构体
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
void SetPositionByLine(FILE *fp,int line);
Basic InfoOfUser();				//store the information that the user prints
int JudgeID(Basic basics);		//judge if the ID is legal and the type of the string that the user prints
Order CreateOrder(Basic basics);
char *MovieSearch(Basic basics);	//search sessions concerning this movie
char *CinemaSearch(Basic basics);	//search sessions concering this cinema
SessionDetail ReadSession(char sessionum[]);
void CurrentSeat(SessionDetail session);
bool Order_Is_Legal(Order order,SessionDetail session);
Order SelectSeat(Order order,SessionDetail session);
Order CompleteOrder(Order order,SessionDetail session);
char *GetPath(Order order);			//get the path of the file of the session
void DealOrder(Order order); 		//deal with the order and change information in the files of session
void Pay(Order order);
void Recover(Order order);
void OrderSystem();

	Basic basics;
	Order order;
	SessionDetail Detail;
int main ()
{
	OrderSystem();
	return 0;
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
Basic InfoOfUser()
{
	Basic basic;
	printf("Please enter your ID: ");
	scanf("%s",basic.IdOfUser);
	printf("Please enter the name of movie/cinema you want to search: ");
	scanf("%s",basic.MovieOrCinema);
	return basic;
}
int JudgeID(Basic basics)
{
	char id[11]="\0",Id[11]="\0";
	int i=0,j=0,find=0,find1=0,l=0;
	FILE *fptr=NULL;
	strcpy(id,basics.IdOfUser);
	strcat(id,"\n");
	for (j = 0;find != 1;j++)//找到了就退出 
	{
		if ((fptr = fopen("C:/Users/DELL/Desktop/IOCS/accounts/user/Users.acc","r")) == NULL)//在用户名文件里找人 
			{
				printf("Fail to read!\n");
				l = 0;
				return l;
			}
			else
				fptr = fopen("C:/Users/DELL/Desktop/IOCS/accounts/user/Users.acc","r");
			while(fgets(Id,12,fptr) != NULL && find != 1)//遍历每行的id，直至找到或者全部搜完 
     		{
     			if (strcmp(id,Id) == 0)//找到对应的用户id 
     			{
					find = 1;
					printf("Successfully Find The User!\n");//寻找到了用户的ID 
					if (strlen(basics.MovieOrCinema) == 4)
						l = 2;
					else
						l = 1;
					return l;
				}
     		}
     		if (fgets(Id,12,fptr) == NULL && find != 1 )//遍历完并且没有找到 
			{
				printf("Can't Find The User!\n");
				l = 0;
				return l;
			} 
		}
	
}
Order CreateOrder(Basic basics){
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
    if(strlen(basics.MovieOrCinema) == 4)
		strcpy(temp.CinName,basics.MovieOrCinema);
	else
		strcpy(temp.MovName,basics.MovieOrCinema);
    return temp;
}

char *MovieSearch(Basic basics)
{
	int i=0,j=0,k=0;
	char movie[MAXSIZE]="\0";
	char path[255]="\0";
	static char Changci[MAXSIZE]="\0";
	char path1[255]="\0";
	FILE *fptr=NULL,*fptr1=NULL;
	strcpy(path,"C:/Users/DELL/Desktop/IOCS/cma_info");
	strcat(path,basics.MovieOrCinema);
	strcat(path,".txt");//打开对应的写着影片名的文件，读取所有该影片的场次编号 
	if ((fptr = fopen(path,"r")) == NULL)
	{
		printf("Open Fail Failure...\n");
		return NULL;
	}
	else 
	{
		fptr = fopen(path,"r");//打开影片名文件 
		if(fgets(Changci,MAXSIZE,fptr) == NULL)
			printf("No Session Now For This Movie.\n");
		else
		{ 
			for (i = 0;fgets(Changci,MAXSIZE,fptr) != NULL;i++)//读取每行的场次编号 
			{
				fscanf(fptr,"%s",Changci);
				strcpy(path1,"C:/Users/DELL/Desktop/IOCS/sessions/");
				strcat(path1,Changci);
				strcat(path1,".ses");//读取场次编号文件 
				if ((fptr1 = fopen(path1,"r")) == NULL)
				{
					printf("Open Fail Failure...\n");
					return NULL;
				}
					else
					{
						printf("      Cinema            Movie            Date      Hall      Session      Price\n");
						char CC[MAXSIZE]="\0";
						int line=0,column=0;
						char MOVIENAME[MAXSIZE]="\0",CINEMA[MAXSIZE]="\0",DATE[4]="\0",START[6]="\0",END[6]="\0";
						char LANG[6]="\0",TYPE[6]="\0",COUPON[MAXSIZE]="\0";
						int HALL=0,LENGTH=0,TOTAL=0,REMAIN=0;
						double PRICE=0.0;
						fptr1 = fopen(path1,"r");
						fscanf(fptr1,"%s",CC);
						fscanf(fptr1,"%s",MOVIENAME);
						fscanf(fptr1,"%s",CINEMA);
						fscanf(fptr1,"%d",&HALL);
						fscanf(fptr1,"%s",START);
						fscanf(fptr1,"%s",END);
						fscanf(fptr1,"%d",&LENGTH);
						fscanf(fptr1,"%d",&TOTAL);
						fscanf(fptr1,"%d",&REMAIN);
						fscanf(fptr1,"%lf",&PRICE);//按每行顺序读取所需数据 
						fscanf(fptr1,"%s",LANG);
						fscanf(fptr1,"%s",TYPE);
						fscanf(fptr1,"%s",COUPON);
						fscanf(fptr1,"%d",&line);
						fscanf(fptr1,"%d",&column);
						for (i = 4;i < 8;i++)
							DATE[i] = CC[i];//日期信息从场次编号中获取 
						printf("%10s%24s%13d%10d%16s%9.2lf\n",CINEMA,MOVIENAME,DATE,HALL,CC,PRICE);//打印所有的该影片场次具体信息 
						printf("Please Enter The Session You Want To Order:");
						scanf("%s",Changci);//用户输入想要的场次 
					}
			}
		}
	}
	return Changci;
}
char *CinemaSearch(Basic basics)
{
	FILE *fp=NULL;
	char cma[20]="\0";
	static char seSSion[MAXSIZE]="\0";
	strcpy(cma,basics.MovieOrCinema);
	char to_search[MAXSIZE] = "D:/workplace/cma_info/*txt"; //欲查找的文件，支持通配符
    long handle;                                       //用于查找的句柄
    struct _finddata_t fileinfo;                       //文件信息的结构体
    handle = _findfirst(to_search, &fileinfo);
    //printf("%s\n", fileinfo.name);
    //打开所遍历到的文件
    char pathA[255] = "D:/workplace";
    char path3[MAXSIZE] ="\0";
    char filename[255] = {'\0'};
    char str[255] = {'\0'};
    strcat(cma, ".txt");
    int temp = 0;
    if (strcmp(fileinfo.name, cma) == 0)
    {
        temp = 1;
        wsprintf(filename, "/cma_info/%s", fileinfo.name);
        strcat(pathA, filename);
        FILE *fp = NULL;
        fp = fopen(pathA, "r");
        printf("此电影院的影片场次如下：\n");
        fgets(str, 255, (FILE *)fp);
        while (!feof(fp))
        {
            printf("%s", str);
            fgets(str, 255, (FILE *)fp);
        }
    }
    while (!_findnext(handle, &fileinfo)) //循环查找其他符合的文件，知道找不到其他的为止
    {
        //printf("%s\n", fileinfo.name);
        if (strcmp(cma, fileinfo.name) == 0)
        {
            temp = 1;
            memset(pathA, '\0', sizeof(pathA));
            strcpy(pathA, "D:/workplace");
            wsprintf(filename, "/cma_info/%s", fileinfo.name);
            strcat(pathA, filename);
            FILE *fp = NULL;
            fp = fopen(pathA, "r");
            char str[255];
            printf("Current Sessions For This Cinema ：\n");
            fgets(str, 255, (FILE *)fp);
            while (!feof(fp))
            {
                printf("%s", str);
                fgets(str, 255, (FILE *)fp);
            }
        }
    }
    if (temp == 0)
    {
        printf("No Such Cinema Or This Cinema Has No Session Now！");
        return NULL;
    }
    _findclose(handle); //别忘了关闭句柄
    printf("Please Enter The Session You Want To Order: ");
    scanf("%s",seSSion);
    strcpy(path3,"C:/Users/DELL/Desktop/IOCS/sessions/");
	strcat(path3,seSSion);
	strcat(path3,".ses");//读取场次编号文件 
	if ((fp = fopen(path3,"r")) == NULL)
	{
		printf("Open Fail Failure...\n");
		return NULL;
	}
    return seSSion;
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
bool Order_Is_Legal(Order order,SessionDetail session){//此处有所修改 
    int i,j,flag=1;
    for(i=0;i<order.SeatNum&&flag;i++)
    {   // for(j=0;j<order.SeatNum&&flag;j++)
            if(session.seat[order.seat[i][0]-1][order.seat[i][1]-1]||
               session.seat[order.seat[i][0]+1][order.seat[i][1]+1]||
			   order.seat[i][0] > session.row||order.seat[i][1] > session.colum)
                flag=0;
	}
	return flag;
}
void CurrentSeat(SessionDetail session){
    int i,j;
    printf("当前选座情况如图。其中1代表该位置已被占用，0代表该位置可以选择。\n");
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
        order = CompleteOrder(order, session);
    
    return order;
}
Order CompleteOrder(Order order,SessionDetail session){
    strcpy(order.CinName,session.CinName);
    strcpy(order.MovName,session.MovName);
    strcpy(order.Sessions,session.SessioNum);
    order.MovieRoom=session.MovieRoom;
    order.cost=order.SeatNum*session.price;
    return order;
}
char *GetPath(Order order)
{
	int k=0; 
	char cc[MAXSIZE]="\0",iD[5]=".ses";
	static char path[255]="\0";
	strcpy(cc, order.Sessions);
	for (k = 0;cc[k] != '\n';k++);
		cc[k] = '\0';
	strcat(cc,iD);//SerialNum即为该场次的文件名    
	strcpy(path,"C:/Users/DELL/Desktop/IOCS/sessions/");
	strcat(path,cc);
	for (k = 0;path[k] != '\0';k++);
		path[k] = '\0'; //截取出正确的文件路径，放入path 
	return path;
}

void DealOrder(Order order)
{
	FILE *fptr=NULL,*fptr1=NULL,*fptr2=NULL;
	char path[255]="\0",SerialNum[MAXSIZE] = "\0",moviename1[MAXSIZE] = "\0",starttime[6]="\0";
	char cinema1[5]="\0",lang[4]="\0",type[4]="\0",coupon[MAXSIZE]="\0",endtime[6]="\0";
	int  line=0,column=0,hall=0,totalseat=0,remain=0,length=0;
	double price=0.0;
	int *Occupied=NULL;  //用于读取场次文件里的各项数据/字符
	int seat1=0,remain1=0,k=0,k1=0,k2=0,k3=0,l=0;//占的座位的添加 
	int SW=0,GW=0;
	strcpy(path,GetPath(order));		
		if((fptr = fopen(path,"r+")) == NULL)//寻找名字叫该场次的场次文件 (该目录下） 
		{
        	printf("Open the file failure...\n");
        	order.legal = 0;
    	}
    		else
			{
				fptr = fopen(path,"r+");//每行读入该场次文件中的对应数据，放在变量里 
				fscanf(fptr,"%s",SerialNum);
			    fscanf(fptr,"%s",moviename1);
			    fscanf(fptr,"%s",cinema1);
				fscanf(fptr,"%d",&hall);
				fscanf(fptr,"%s",starttime);
				fscanf(fptr,"%s",endtime);
				fscanf(fptr,"%d",&length);
				fscanf(fptr,"%d",&totalseat);
				fscanf(fptr,"%d",&remain);
				fscanf(fptr,"%lf",&price);
				fscanf(fptr,"%s",lang);
				fscanf(fptr,"%s",type);
				fscanf(fptr,"%s",coupon);
				fscanf(fptr,"%d",&line);
				fscanf(fptr,"%d",&column);
				Occupied = (int *)malloc((totalseat - remain) * sizeof(int));
				if (!Occupied)
				{
					printf("Can't create the array!\n");
					fclose(fptr);
					order.legal = 0;
				}
				else
				{
					for (k = 0;k < totalseat - remain;k++)
						fscanf(fptr,"%d",&Occupied[k]);
					remain1 = remain;
					remain -= order.SeatNum;//该票购买，剩余票数-1 
					fclose(fptr);//关闭文件 
					if((fptr1 = fopen(path,"w+")) == NULL)//寻找名字叫该场次的场次文件 (该目录下） 
					{
        				printf("Open the file failure...\n");
        				order.legal = 0; 
    				}
    					else
    					{
							fptr1 = fopen(path,"w+");//把存在各个变量里的场次信息文件里的各项数据弄回该文件，方便修改票余数 
							fprintf(fptr1,"%s\n",SerialNum);
							fprintf(fptr1,"%s\n",moviename1);
			    			fprintf(fptr1,"%s\n",cinema1);
							fprintf(fptr1,"%d\n",hall);
							fprintf(fptr1,"%s\n",starttime);
							fprintf(fptr1,"%s\n",endtime);
							fprintf(fptr1,"%d\n",length);
							fprintf(fptr1,"%d\n",totalseat);
							fprintf(fptr1,"%d\n",remain);
							fprintf(fptr1,"%lf\n",price);
							fprintf(fptr1,"%s\n",lang);
							fprintf(fptr1,"%s\n",type);
							fprintf(fptr1,"%s\n",coupon);
							fprintf(fptr1,"%d\n",line);
							fprintf(fptr1,"%d\n",column);
							for (k = 0;k < totalseat - remain1;k++)
								fprintf(fptr1,"%d\n",Occupied[k]);
							fclose(fptr1);
						}
					if((fptr2 = fopen(path,"a")) == NULL)//寻找名字叫该影厅的影厅文件 (该目录下） 
					{
        				remain += order.SeatNum;
						printf("Open the file failure...\n");
        				order.legal = 0;
    				}
    					else
    					{
							fptr2 = fopen(path,"a");
							for (k = 0;k < order.SeatNum;k++)
							{
								SW = order.seat[k][0] * 100;
								GW = order.seat[k][1];
								seat1 = SW + GW;
								fprintf(fptr2,"%d\n",seat1);//在影厅文件中最后每行每行添加已占座位数 
							}
							fclose(fptr2);
							order.legal = 1;
						}
				}
			}
}
int TIME(Order order)
{
	int timeexceed=0;
	long long int totaltime=0,ordertime=0;
	time_t It;
	time(&It);
	struct tm* ptr;
	ptr = localtime(&It);
	return timeexceed;
}
void Pay(Order order)
{

}
void Recover(Order order)
{
	FILE *fpt=NULL,*fpt1=NULL;
	int k=0;
	char path4[255]="\0",SerialNum[MAXSIZE] = "\0",moviename1[MAXSIZE] = "\0",starttime[6]="\0";
	char cinema1[5]="\0",lang[4]="\0",type[4]="\0",coupon[MAXSIZE]="\0",endtime[6]="\0";
	int  line=0,column=0,hall=0,totalseat=0,remain=0,length=0;
	double price=0.0;
	int *Occupied1=NULL;  //用于读取场次文件里的各项数据/字符
	strcpy(path4,GetPath(order));		
		if((fpt = fopen(path4,"w+")) == NULL)//寻找名字叫该场次的场次文件 (该目录下） 
        printf("Open the file failure.Fail to recover.\n");
    	else
		{
			fpt = fopen(path4,"w+");//每行读入该场次文件中的对应数据，放在变量里 
			fscanf(fpt,"%s",SerialNum);
		    fscanf(fpt,"%s",moviename1);
		    fscanf(fpt,"%s",cinema1);
			fscanf(fpt,"%d",&hall);
			fscanf(fpt,"%s",starttime);
			fscanf(fpt,"%s",endtime);
			fscanf(fpt,"%d",&length);
			fscanf(fpt,"%d",&totalseat);
			fscanf(fpt,"%d",&remain);
			fscanf(fpt,"%lf",&price);
			fscanf(fpt,"%s",lang);
			fscanf(fpt,"%s",type);
			fscanf(fpt,"%s",coupon);
			fscanf(fpt,"%d",&line);
			fscanf(fpt,"%d",&column);
			Occupied1 = (int *)malloc((totalseat - remain) * sizeof(int));
			if (!Occupied1)
			{
				printf("Can't create the array!Fail to recover.\n");
				fclose(fpt);
			}
			else
			{
				for (k = 0;k < totalseat - remain;k++)
					fscanf(fpt,"%d",&Occupied1[k]);
				remain += order.SeatNum;//
				fclose(fpt);//关闭文件 
				if((fpt1 = fopen(path4,"w+")) == NULL)//寻找名字叫该场次的场次文件 (该目录下） 
				{
        			printf("Open the file failure...\n");
        			order.legal = 0; 
    			}
    				else
    				{
						fpt1 = fopen(path4,"w+");//把存在各个变量里的场次信息文件里的各项数据弄回该文件，方便修改票余数 
						fprintf(fpt1,"%s\n",SerialNum);
						fprintf(fpt1,"%s\n",moviename1);
			   			fprintf(fpt1,"%s\n",cinema1);
						fprintf(fpt1,"%d\n",hall);
						fprintf(fpt1,"%s\n",starttime);
						fprintf(fpt1,"%s\n",endtime);
						fprintf(fpt1,"%d\n",length);
						fprintf(fpt1,"%d\n",totalseat);
						fprintf(fpt1,"%d\n",remain);
						fprintf(fpt1,"%lf\n",price);
						fprintf(fpt1,"%s\n",lang);
						fprintf(fpt1,"%s\n",type);
						fprintf(fpt1,"%s\n",coupon);
						fprintf(fpt1,"%d\n",line);
						fprintf(fpt1,"%d\n",column);
						for (k = 0;k < totalseat - remain;k++)
						fprintf(fpt1,"%d\n",Occupied1[k]);
						fclose(fpt1);
					} 
			} 
		} 
}
void OrderSystem()
{
	int result=0,judge,legal1,i=0,XZ=0,i1=0,SRHF=0,TimeExceed=0;
	char Session[MAXSIZE];
	basics = InfoOfUser();			//用户输入ID 与影片/影院名 
	result = JudgeID(basics);		//判断ID是否合法 并且判断其输入的是影片还是影院 
	SRHF = 0;
	TimeExceed = 0;
	time_t It;
	if (result != 0)
	{
		for (i1 = 0;SRHF != 1;i1++)
		{		
			order = CreateOrder(basics);	
			if (result == 1 && MovieSearch(basics) != NULL)
			{
				strcpy(Session,MovieSearch(basics));    
				SRHF = 1;
			}
			else if (result == 2 && CinemaSearch(basics) != NULL)
			{
				strcpy(Session,CinemaSearch(basics));  //利用函数获得用户想订购的场次 
				SRHF = 1;
			}
			else 
				SRHF = 0;
			if (SRHF == 1)
			{
				Detail = ReadSession(Session); //通过用户选择的场次返还更具体的信息 
				XZ = 0;     	   
				for (i = 0;XZ != 1;i++)
				{
					order = SelectSeat(order,Detail);		   //用户开始选座 
					order = CompleteOrder(order,Detail);	   //用户最后确认订单 传过来的订单一定是合法的 
					DealOrder(order);
					if (order.legal == 1) 
					{
						printf("Do you want to delete your order ? If you want to delete, please print 1;if not, please print 0.");
						scanf("%d",&order.del);
						if (order.del == 0)//如果订单有效 
						{
							TimeExceed = TIME(order);
							if (TimeExceed == 0)//未超时 
							{
								Pay(order);
								printf("Order Tickets Successfully!\n");
							}
							else
								printf("Time Out For The Order! Please Try Again!\n");
						}
						else if (order.del == 1)
						{
							Recover(order);
							printf("Delete The Order Successfully!\n");
						}
					}
					else if (order.legal == 0)
						printf("Fail To Order Tickets!\n");
				}
			} 
		}
	}
}
