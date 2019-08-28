#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <direct.h>
#include <windows.h>
#include <time.h>
#define MAXSIZE 32
typedef struct Order{  //������Ϣ
    char ID[11];                //�û�ID
    int del;                    //�Ƿ�ɾ������
    int num;                    //�������
    char MovName[MAXSIZE];      //ӰƬ����
    char CinName[MAXSIZE];      //ӰԺ����
    int seat[3][2];             //������λ��Ϣ
    int SeatNum;                //������λ����
    int Hour;                   //�µ�ʱ��
    int Min;
    int date_year;              //�µ�����
    int date_month;
    int date_day;
    int MovieNum;               //Ԥ���ĳ�����
    int MoneyAccount;           //�˻����
}Order;

int FindOrder(char id[]);                            //��ѯ�˻�����
int ReadOrder(char id[],Order temp[],int OrderNum);  //��ȡ������Ϣ
bool _is_Time_Conflict(char moviename[]);
void SerchMovie(char Movname[],char Cinname[]);      //��ѯӰƬ����
void OrderTicket(Order tp,int OrderNum);             //������д���ļ�
int DeleteOrder(char id[],Order temp[],int OrderNum);//ɾ������
int DealOrder(Order orders);
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

int ReadOrder(char id[],Order temp[],int OrderNum){  //���ļ��еĶ�����Ϣд��temp������
    int i=OrderNum;
    char FileName[MAXSIZE];
    strcpy(FileName,id);
    strcat(FileName,".txt");
    
    FILE* fp;
    if((fp=fopen(FileName,"r"))){
        while(!feof(fp)){
            temp[i].del=0;
            fscanf(fp,"%s%d%s%d",temp[i].ID,&temp[i].num,temp[i].MovName,
                   &temp[i].SeatNum);                                //д���û���,�������,ӰƬ����
            fscanf(fp,"%s%02d%02d",temp[i].CinName,&temp[i].Hour,
                   &temp[i].Min);                                    //д��ӰԺ���ƣ��µ�ʱ��
            fscanf(fp,"%d%d%d%d",&temp[i].date_year,&temp[i].date_month,
                   &temp[i].date_day,&temp[i].MovieNum);             //д���µ����ںͳ�����
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

void OrderTicket(Order tp,int OrderNum){               //��������Ϣд���ļ���
    int i,j,flag=1;
    char FileName[MAXSIZE];
    Order temp[100];
    Order NewOrder;
    //��ʼ��������Ϣ
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
    NewOrder.num++;                                     //���µ�˳���Ŷ������
    if(tp.SeatNum<=3&&NewOrder.MovieNum<=5){            //ÿ�������Ԥ��������λ������������
        for(i=0;i<tp.SeatNum;i++){
            for(j=0;j<2;j++){
                if(tp.seat[i][j]>=1&&tp.seat[i][j]<=10) //��λ����1-10֮��˵��Ԥ����λ�ɹ�
                    NewOrder.seat[i][j]=tp.seat[i][j];
                else
                    flag=0;
            }
            if(flag)                    //Ԥ���ɹ�����λ����Ӧ�ĵ���
                NewOrder.SeatNum++;
        }
        NewOrder.MovieNum++;            //���μ�һ
    }
    else{                               //����������λ����ۿ�������������λ��Ŷ���Ϊ-1����ʾԤ��ʧ��
        for(i=0;i<tp.SeatNum;i++){
            for(j=0;j<2;j++)
                NewOrder.seat[i][j]=-1;
        }
    }
    temp[OrderNum]=NewOrder;            //temp�����м����µĶ���
    
    FILE *fp;
    if(FindOrder(tp.ID)){               //�˻��ж�����¼,��Ԥ�����μ�һ��ͬʱ��֮ǰ������׷���¶���
        temp[OrderNum].MovieNum++;
        fp=fopen(FileName,"a");
    }
    else
        fp=fopen(FileName,"w");
    
    if(fp==NULL)
        exit(0);
    if(NewOrder.MoneyAccount>=(50*NewOrder.SeatNum)){                 //�˻����ۿ���н������д���ļ�
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
        for(int j=0;j<temp[OrderNum].SeatNum;j++)     //¼����λ��Ϣ
            fprintf(fp,"%d%d\n",temp[OrderNum].seat[j][0],
                    temp[OrderNum].seat[j][1]);
        fprintf(fp,"%d\n",temp[OrderNum].MoneyAccount);
    }
    else
        printf("���ȳ�ֵ\n");
    fclose(fp);
}

void SerchMovie(char Movname[],char Cinname[]){
    char moviename[MAXSIZE];
    char str[MAXSIZE];
    strcpy(moviename,Movname);
    strcat(moviename,".txt");
    
    FILE *fp;
    if((fp=fopen(moviename,"r"))==NULL){
        printf("���ļ�ʧ��\n");
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

Order OrderInfo(void){       //���������ṹ��
    Order orders;
    int i;
    printf("�������û�ID:");
    gets(orders.ID);
    printf("������ӰԺ����:");
    gets(orders.CinName);
    printf("������ӰƬ����:");
    gets(orders.MovName);
    printf("������Ԥ������λ��:");
    scanf("%d",&orders.SeatNum);
    printf("��������λ��:");
    for(i=0;i<orders.SeatNum;i++){
        scanf("%d%d",&orders.seat[i][0],&orders.seat[i][1]);
    }
    getchar();
    return orders;
}

int DealOrder(Order orders)
{
	FILE *fptr=NULL,*fptr1=NULL,*fptr2=NULL,*fptr3=NULL;
	
	char id[11]="\0",Id[11]="\0",iD[5]=".ses";
	int i=0,j=0,find=0,find1=0,l=0;
	
	
	/*strcpy(orders.ID , "Zenglingxi");
	orders.del = 0;
	orders.num = 1;
	strcpy(orders.MovName,"Avengers4");
	strcpy(orders.CinName,"DDYYY");
	orders.seat[0][0] = 1;
	orders.seat[0][1] = 1;
	orders.seat[1][0] = 2;
	orders.seat[1][1] = 2;
	orders.seat[2][0] = 6;
	orders.seat[2][1] = 8;
	orders.Hour = 21;
	orders.Min = 33;
	orders.SeatNum = 3;*/
		//strcpy(id,orders.ID);
		//fgets(id,12,stdin);    //�����û�ID 
		strcpy(id,orders.ID);
		strcat(id,"\n");
		for (j = 0;find != 1;j++)//�ҵ��˾��˳� 
		{
			if ((fptr = fopen("C:/Users/DELL/Desktop/IOCS/accounts/user/Users.acc","r")) == NULL)//���û����ļ������� 
			{
				printf("Fail to read!\n");
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
				}
     		}
     		if (fgets(Id,12,fptr) == NULL && find != 1 )//�����겢��û���ҵ� 
			{
				printf("Can't Find The User!\n");
			} 
		}
		char SerialNum[18]="\0";
		char moviename1[18] = "\0";
		char cinema1[5]="\0";
		int  hall1;
		int  starttime,endtime,length;
		int  totalseat,remain;
		double price;
		char lang[4]="\0";  
		int *Occupied;  //���ڶ�ȡ�����ļ���ĸ�������/�ַ�
		
		int seat1,remain1;//ռ����λ����� 
		int k=0,k1=0,k2=0,k3=0;
		char temp[18]="\0",temp1[18]="\0",temp2[18]="\0",temp3[18]="\0",temp4[18]="\0",path[255]="\0";
		int PosOfSes[20][20]={0};//the position of the seats in this session
		int SW,GW;
		//char filename[12]="ABCDEFG";  
		
		//�������ﳡ����Ϣ�Ѿ���ȫȷ�� 
		//char Ses[18];
		//strcpy(SerialNum, Ses);
		
		
		
		fgets(SerialNum,18,stdin);
		for (k = 0;SerialNum[k] != '\n';k++);
		SerialNum[k] = '\0';
		strcpy(iD,".ses"); 
		strcat(SerialNum,iD);//SerialNum��Ϊ�ó��ε��ļ���    
		
		for (k = 0;SerialNum[k] > 57;k++)
			temp1[k] = SerialNum[k];
		temp1[k] = '\0';
		k1 = k;
		for (k = k1;k < k1 + 4;k++)
			temp2[k - k1] = SerialNum[k];
		temp2[k - k1] = '\0';
		for (k = k1 + 4;k < k1 + 6;k++)
			temp3[k - k1 - 4] = SerialNum[k];
		temp3[k - k1 - 4]  = '\0';
		for (k = k1 + 6;k < k1 + 8;k++)
			temp4[k - k1 - 6] = SerialNum[k]; //��ȡ�ַ��� 
		temp4[k - k1 - 6] = '\0';
		strcpy(path,"C:/Users/DELL/Desktop/IOCS/sessions/");
		strcat(path,temp1);
		strcat(path,"/");
		strcat(path,temp3);
		strcat(path,"/");
		strcat(path,temp2);
		strcat(path,"/");
		strcat(path,SerialNum);
		for (k = 0;path[k] != '\0';k++);
		path[k] = '\0';
		
		if((fptr = fopen(path,"r+")) == NULL)//Ѱ�����ֽиó��εĳ����ļ� (��Ŀ¼�£� 
		{
        	printf("Open the file failure...\n");
        	l = 0;
        	return l;
    	}
    		else
			{
				fptr = fopen(path,"r+");
				//ÿ�ж���ó����ļ��еĶ�Ӧ���ݣ����ڱ����� 
				fscanf(fptr,"%s",temp);
			    fscanf(fptr,"%s",moviename1);
			    fscanf(fptr,"%s",cinema1);
				fscanf(fptr,"%d",&hall1);
				fscanf(fptr,"%d",&starttime);
				fscanf(fptr,"%d",&endtime);
				fscanf(fptr,"%d",&length);
				fscanf(fptr,"%d",&totalseat);
				fscanf(fptr,"%d",&remain);
				fscanf(fptr,"%lf",&price);
				fscanf(fptr,"%s",lang);
				Occupied = (int *)malloc((totalseat - remain) * sizeof(int));
				if (!Occupied)
				{
					printf("Can't create the array!\n");
					l = 0;
					fclose(fptr);
					return l;
				}
				else
				{
					for (k = 0;k < totalseat - remain;k++)
						fscanf(fptr,"%d",&Occupied[k]);
					remain1 = remain;
					remain -= orders.SeatNum;//��Ʊ����ʣ��Ʊ��-1 
					fclose(fptr);//�ر��ļ� 
					if((fptr1 = fopen(path,"w+")) == NULL)//Ѱ�����ֽиó��εĳ����ļ� (��Ŀ¼�£� 
					{
        				printf("Open the file failure...\n");
        				l = 0;
        				return l;
    				}
    					else
    					{
							fptr1 = fopen(path,"w+");//�Ѵ��ڸ���������ĳ�����Ϣ�ļ���ĸ�������Ū�ظ��ļ��������޸�Ʊ���� 
							fprintf(fptr1,"%s\n",temp);
							fprintf(fptr1,"%s\n",moviename1);
			    			fprintf(fptr1,"%s\n",cinema1);
							fprintf(fptr1,"%d\n",hall1);
							fprintf(fptr1,"%d\n",starttime);
							fprintf(fptr1,"%d\n",endtime);
							fprintf(fptr1,"%d\n",length);
							fprintf(fptr1,"%d\n",totalseat);
							fprintf(fptr1,"%d\n",remain);
							fprintf(fptr1,"%lf\n",price);
							fprintf(fptr1,"%s\n",lang);
							for (k = 0;k < totalseat - remain1;k++)
								fprintf(fptr1,"%d\n",Occupied[k]);
							fclose(fptr1);
							for (k2 = 0;k2 < totalseat - remain1;k2++)
							{
								SW = Occupied[k2] / 100;
								GW = Occupied[k2] - SW * 100;
								if (PosOfSes[SW - 1][GW - 1] == 0)
									PosOfSes[SW - 1][GW - 1] = 1;
							}
						}
					if((fptr2 = fopen(path,"a")) == NULL)//Ѱ�����ֽи�Ӱ����Ӱ���ļ� (��Ŀ¼�£� 
					{
        				printf("Open the file failure...\n");
        				l = 0;
						return l;
    				}
    					else
    					{
							fptr2 = fopen(path,"a");
							for (k = 0;k < orders.SeatNum;k++)
							{
								SW = orders.seat[k][0] * 100;
								GW = orders.seat[k][1];
								seat1 = SW + GW;
								fprintf(fptr2,"%d\n",seat1);//��Ӱ���ļ������ÿ��ÿ�������ռ��λ�� 
							}
							fclose(fptr2);
						}
					for (k = 0;k < orders.SeatNum;k++)
					{
						PosOfSes[orders.seat[k][0] - 1][orders.seat[k][1] - 1] = 1;
					}
						for (k2 = 0;k2 < 10;k2++)
						{
							for (k3 = 0;k3 < 10;k3++)
							{
								if (k3 != 9)
									printf("%d ",PosOfSes[k2][k3]);
								else 
									printf("%d\n",PosOfSes[k2][k3]);
							}
						}
				} 
			}
}

int main(int argc, const char * argv[]) {
    int i,j,k;
    Order orders;
    orders = OrderInfo();
    /*
    int OrderNum=0,schedule;
    Order temp[100],tp[100];
    printf("������Ҫ��ӵĶ�����:");
    scanf("%d",&schedule);
    getchar();
    for(j=0;j<schedule;j++){
        tp[j]=OrderInfo();
        OrderTicket(tp[j],OrderNum);
        OrderNum=ReadOrder(tp[j].ID,temp,OrderNum);
        
        for(i=0;i<OrderNum;i++){
            printf("�û���Ϊ:%s\n",temp[i].ID);
            printf("�������Ϊ:%d\n",temp[i].num);
            printf("ӰƬ����Ϊ:%s\n",temp[i].MovName);
            printf("ӰԺ����Ϊ:%s\n",temp[i].CinName);
            printf("�µ�ʱ��Ϊ:%02d:%02d\n",temp[i].Hour,temp[i].Min);
            printf("�µ�����Ϊ:%d��%d��%d��\n",temp[i].date_year,temp[i].date_month,
                   temp[i].date_day);
            printf("Ԥ����λ��:%d\n",temp[i].SeatNum);
        }*/
    	k = DealOrder(orders);
    return 0;
}
