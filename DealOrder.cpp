#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <direct.h>
#include <windows.h>
//��ӰԺ��Ʊ 
typedef struct Order{ 		//�û�������Ϣ��������Ϣ
    char ID[11];            //�û�ID 
    int del;                //�Ƿ�ɾ������
	int num;                //������� 
    char MovName[32];       //ӰƬ���� 
    char CinName[32];       //ӰԺ���� 
    int seat[15][2];         //������λ��Ϣ 
    int Hour;               //time of order
	int Min;				
	int SeatNum;            //amount of seats in the order
	int data_year;			//date of order
	int data_month;			   
	int MovieNum; 			//sessions of orders of this user today
	int MoneyAccount;       //the money remaining in the account
}Order;
Order orders;



int DealOrder(Order orders);


int main (int argc, const char * argv[])
{
	int OrderResult; 
	OrderResult = DealOrder(orders);
	if (OrderResult == 0)
		printf("Fail To Order The Tickets!\n");
		else if (OrderResult == 1)
			printf("Order Tickets Successfully!\n");
	return 0;
}
int DealOrder(Order orders)
{
	FILE *fptr=NULL,*fptr1=NULL,*fptr2=NULL,*fptr3=NULL;
	
	char id[18]={'\0'},Id[12]={'\0'},iD[5]=".ses";
	int i=0,j=0,find=0,find1=0,l=0;
	
	
	strcpy(orders.ID , "Zenglingxi");
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
	orders.SeatNum = 3;
		//strcpy(id,orders.ID);
		fgets(id,12,stdin);    //�����û�ID 
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
		char cinema1[5];
		int  hall1;
		int  starttime,endtime,length;
		int  totalseat,remain;
		double price;
		char lang[4];  
		int *Occupied;  //���ڶ�ȡ�����ļ���ĸ�������/�ַ�
		
		int seat1,remain1;//ռ����λ����� 
		int k=0,k1=0,k2=0,k3=0;
		char temp[18],temp1[18],temp2[18],temp3[18],temp4[18],path[255];
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
		strcat(path,"C:/Users/DELL/Desktop/IOCS/sessions/");
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
	
			
			
			/* 
				//Ѱ�Ҷ�Ӧ��Ӱ���ĸõ�Ӱ�ĸò���ʱ��εĶ�Ӧ�ļ������һ����ռ��λ (Ŀǰ�ݶ��ļ�Ϊfilename) 
				//strcpy(filename,orders[i].cinema);
				//strcat(filename,orders[i].hall);
				strcat(filename,".txt");				
				
				
				if((fptr3 = fopen(filename,"w+")) == NULL)//Ѱ�����ֽи�Ӱ����Ӱ���ļ� (��Ŀ¼�£� 
				{
        			printf("Open the file failure...\n");
        			return l;
    			}
    			else 
    			{
					fptr3 = fopen(filename,"w+");
					char cinema2[5],Type[4];
					int session1, Totalseat,Occupiedseats,*Occuseat;// ����ӰƬ�ļ���ĸ��ͬ���� 
					Occuseat = (int *) malloc(remain * sizeof(int));//��̬���� 
					if (!Occuseat)
					{
						printf("Fail to create the array!\n");
						return l;
					}
					else
					{
						fscanf(fptr3,"%s",cinema2);
						fscanf(fptr3,"%d",&session1);
						fscanf(fptr3,"%d",&Totalseat);
						fscanf(fptr3,"%d",&Occupiedseats);
						fscanf(fptr3,"%s",Type);
						
						for (k = 0;k < Totalseat - remain;k++)
							fscanf(fptr3,"%d",Occuseat[i]);
						fclose(fptr3);
						
						if((fptr3 = fopen(filename,"w+")) == NULL)//Ѱ�����ֽи�Ӱ����Ӱ���ļ� (��Ŀ¼�£� 
						{
        					printf("Open the file failure...\n");
        					return l;
    					}
    					else
    					{
							fptr3 = fopen(filename,"w+");
							fprintf(fptr3,"%s\n",cinema2);
							fprintf(fptr3,"%d\n",session1);
							fprintf(fptr3,"%d\n",Totalseat);
							fprintf(fptr3,"%d\n",Occupiedseats);
							fprintf(fptr3,"%s\n",Type);
						for (k = 0;k < Totalseat - remain;k++)
							fprintf(fptr3,"%d\n",Occuseat[i]);//�������������ȥ��ͬʱƱ�����Ѹ��� 
						}
					}
				}						
	}
}*/ 


