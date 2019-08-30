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
    	int min;
	}date;
	int cost;					//total cost of these seats
}Order;
typedef struct movie{			//������Ϣ�ṹ��
    char SessioNum[13];     //���κ�
    char MovName[MAXSIZE];  //ӰƬ��
    char CinName[MAXSIZE];  //ӰԺ��
    int MovieRoom;          //Ӱ��
    char Startime[6];           //��ʼʱ��
    char Stoptime[6];           //����ʱ��
    int time;               //��ʱ��
    int AllticketNum;       //��Ʊ��
    int remainTicket;       //��Ʊ��
    double price;           //Ʊ��
    char language[20];      //��������
    char MovType[6];        //ӰƬ����
    int row;                //������
    int colum;              //������
    int seat[MAXSIZE][MAXSIZE];//��λ��Ϣ
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
int main ()
{
	int result=0,judge,legal1;
	char Session[MAXSIZE];
	Basic basics;
	Order order;
	SessionDetail Detail;
	basics = InfoOfUser();			//�û�����ID ��ӰƬ/ӰԺ�� 
	result = JudgeID(basics);		//�ж�ID�Ƿ�Ϸ� �����ж����������ӰƬ����ӰԺ 
	if (result != 0)
	{
		order = CreateOrder(basics);	
		if (result == 1)
			strcpy(Session,MovieSearch(basics));    
		else 
			strcpy(Session,CinemaSearch(basics));  //���ú�������û��붩���ĳ��� 
		Detail = ReadSession(Session);      	   //ͨ���û�ѡ�񳡴εĳ��η������������Ϣ 
		order = SelectSeat(order,Detail);		   //�û���ʼѡ�� 
		order = CompleteOrder(order,Detail);	   //�û����ȷ�϶��� 
		if (order.del == 1)						   //���û���Ҫɾ������ 
			printf("Delete Order Successfully!\n");//ֱ��ɾ����������Ч 
			else
			{
				if (order.legal == 1)//���������Ч 
				{
					DealOrder(order);
					if (order.legal == 1)
						printf("Order Tickets Successfully!\n");
					else
						printf("There is something wrong with the system...\n");
				}
				else if (order.legal == 0)
					printf("Fail To Order Tickets!\n");
			}
	} 
	return 0;
} 

void SetPositionByLine(FILE *fp,int line){   //���ļ�ָ�붨λ��ָ����
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
	for (j = 0;find != 1;j++)//�ҵ��˾��˳� 
	{
		if ((fptr = fopen("C:/Users/DELL/Desktop/IOCS/accounts/user/Users.acc","r")) == NULL)//���û����ļ������� 
			{
				printf("Fail to read!\n");
				l = 0;
				return l;
			}
			else
				fptr = fopen("C:/Users/DELL/Desktop/IOCS/accounts/user/Users.acc","r");
			while(fgets(Id,12,fptr) != NULL && find != 1)//����ÿ�е�id��ֱ���ҵ�����ȫ������ 
     		{
     			if (strcmp(id,Id) == 0)//�ҵ���Ӧ���û�id 
     			{
					find = 1;
					printf("Successfully Find The User!\n");//Ѱ�ҵ����û���ID 
					if (strlen(basics.MovieOrCinema) == 4)
						l = 2;
					else
						l = 1;
					return l;
				}
     		}
     		if (fgets(Id,12,fptr) == NULL && find != 1 )//�����겢��û���ҵ� 
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
	strcat(path,".txt");//�򿪶�Ӧ��д��ӰƬ�����ļ�����ȡ���и�ӰƬ�ĳ��α�� 
	if ((fptr = fopen(path,"r")) == NULL)
	{
		printf("Open Fail Failure...\n");
		return NULL;
	}
	else 
	{
		fptr = fopen(path,"r");//��ӰƬ���ļ� 
		for (i = 0;fgets(Changci,MAXSIZE,fptr) != NULL;i++)//��ȡÿ�еĳ��α�� 
		{
			fscanf(fptr,"%s",Changci);
			strcpy(path1,"C:/Users/DELL/Desktop/IOCS/sessions/");
			strcat(path1,Changci);
			strcat(path1,".ses");//��ȡ���α���ļ� 
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
					fscanf(fptr1,"%lf",&PRICE);//��ÿ��˳���ȡ�������� 
					fscanf(fptr1,"%s",LANG);
					fscanf(fptr1,"%s",TYPE);
					fscanf(fptr1,"%s",COUPON);
					fscanf(fptr1,"%d",&line);
					fscanf(fptr1,"%d",&column);
					for (i = 4;i < 8;i++)
						DATE[i] = CC[i];//������Ϣ�ӳ��α���л�ȡ 
					printf("%10s%24s%13d%10d%16s%9.2lf\n",CINEMA,MOVIENAME,DATE,HALL,CC,PRICE);//��ӡ���еĸ�ӰƬ���ξ�����Ϣ 
					printf("Please Enter The Session You Want To Order:");
					scanf("%s",Changci);//�û�������Ҫ�ĳ��� 
				}
		}
	}
	return Changci;
}
char *CinemaSearch(Basic basics)
{
	char cma[20]="\0";
	static char seSSion[MAXSIZE]="\0";
	strcpy(cma,basics.MovieOrCinema);
	char to_search[MAXSIZE] = "D:/workplace/cma_info/*txt"; //�����ҵ��ļ���֧��ͨ���
    long handle;                                       //���ڲ��ҵľ��
    struct _finddata_t fileinfo;                       //�ļ���Ϣ�Ľṹ��
    handle = _findfirst(to_search, &fileinfo);
    //printf("%s\n", fileinfo.name);
    //�������������ļ�
    char pathA[255] = "D:/workplace";
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
        printf("�˵�ӰԺ��ӰƬ�������£�\n");
        fgets(str, 255, (FILE *)fp);
        while (!feof(fp))
        {
            printf("%s", str);
            fgets(str, 255, (FILE *)fp);
        }
    }
    while (!_findnext(handle, &fileinfo)) //ѭ�������������ϵ��ļ���֪���Ҳ���������Ϊֹ
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
            printf("�˵�ӰԺ��ӰƬ�������£�\n");
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
        printf("�������ӰԺ������");
    }
    printf("Please Enter The Session You Want To Order: ");
    scanf("%s",seSSion);
    _findclose(handle); //�����˹رվ��
    return seSSion;
}
SessionDetail ReadSession(char sessionum[]){//��������Ϣ�ļ�д��ṹ����
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
bool Order_Is_Legal(Order order,SessionDetail session){
    int i,j,flag=1;
    for(i=0;i<order.SeatNum&&flag;i++)
        for(j=0;j<order.SeatNum&&flag;j++)
            if(session.seat[order.seat[i][j]-1][order.seat[i][j]-1]||
               session.seat[order.seat[i][j]+1][order.seat[i][j]+1])
                flag=0;
    return flag;
}
void CurrentSeat(SessionDetail session){
    int i,j;
    printf("��ǰѡ�������ͼ��\n");
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
    
    printf("������Ԥ����λ��:");
    scanf("%d",&order.SeatNum);
    if(order.SeatNum>3){//��Ʊ��������Ʊ�����߹�Ʊ������3����ʾ����ʧ��
        printf("һ���������ֻ����������λ!���������빺����λ��:");
        scanf("%d",&order.SeatNum);
    }
    if(session.remainTicket<order.SeatNum){
        printf("ʣ��Ʊ��Ϊ%d��,���Ƿ�Ҫ��������?\n",session.remainTicket);
        scanf("%d",&flag);
        if(flag){
            printf("�����빺����λ��:");
            scanf("%d",&order.SeatNum);
        }
    }
    CurrentSeat(session);                      //��ͻ���ʾ��ǰ��λ��Ϣ
    printf("��������λ��Ϣ:");
    for(i=0;i<order.SeatNum;i++)
        scanf("%d%d",&order.seat[i][0],&order.seat[i][1]);
    if(Order_Is_Legal(order, session)==0){
        printf("������ѡ��!\n");
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
	strcat(cc,iD);//SerialNum��Ϊ�ó��ε��ļ���    
	strcpy(path,"C:/Users/DELL/Desktop/IOCS/sessions/");
	strcat(path,cc);
	for (k = 0;path[k] != '\0';k++);
		path[k] = '\0'; //��ȡ����ȷ���ļ�·��������path 
	return path;
} 
void DealOrder(Order order)
{
	FILE *fptr=NULL,*fptr1=NULL,*fptr2=NULL;
	char path[255]="\0",SerialNum[MAXSIZE] = "\0",moviename1[MAXSIZE] = "\0",starttime[6]="\0";
	char cinema1[5]="\0",lang[4]="\0",type[4]="\0",coupon[MAXSIZE]="\0",endtime[6]="\0";
	int  line=0,column=0,hall=0,totalseat=0,remain=0,length=0;
	double price=0.0;
	int *Occupied=NULL;  //���ڶ�ȡ�����ļ���ĸ�������/�ַ�
	int seat1=0,remain1=0,k=0,k1=0,k2=0,k3=0,l=0;//ռ����λ����� 
	int SW=0,GW=0;
	strcpy(path,GetPath(order));		
		if((fptr = fopen(path,"r+")) == NULL)//Ѱ�����ֽиó��εĳ����ļ� (��Ŀ¼�£� 
		{
        	printf("Open the file failure...\n");
        	order.legal = 0;
    	}
    		else
			{
				fptr = fopen(path,"r+");//ÿ�ж���ó����ļ��еĶ�Ӧ���ݣ����ڱ����� 
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
					remain -= order.SeatNum;//��Ʊ����ʣ��Ʊ��-1 
					fclose(fptr);//�ر��ļ� 
					if((fptr1 = fopen(path,"w+")) == NULL)//Ѱ�����ֽиó��εĳ����ļ� (��Ŀ¼�£� 
					{
        				printf("Open the file failure...\n");
        				order.legal = 0; 
    				}
    					else
    					{
							fptr1 = fopen(path,"w+");//�Ѵ��ڸ���������ĳ�����Ϣ�ļ���ĸ�������Ū�ظ��ļ��������޸�Ʊ���� 
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
							for (k2 = 0;k2 < totalseat - remain1;k2++)
							{
								SW = Occupied[k2] / 100;
								GW = Occupied[k2] - SW * 100;
							}
						}
					if((fptr2 = fopen(path,"a")) == NULL)//Ѱ�����ֽи�Ӱ����Ӱ���ļ� (��Ŀ¼�£� 
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
								fprintf(fptr2,"%d\n",seat1);//��Ӱ���ļ������ÿ��ÿ�������ռ��λ�� 
							}
							fclose(fptr2);
							order.legal = 1;
						}
				}
			}
}
