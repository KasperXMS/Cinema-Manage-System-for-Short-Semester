#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <direct.h>
#include <windows.h>
//电影院卖票 
typedef struct Order{ 		//用户个人信息及订单信息
    char ID[11];            //用户ID 
    int del;                //是否删除订单
	int num;                //订单编号 
    char MovName[32];       //影片名称 
    char CinName[32];       //影院名称 
    int seat[15][2];         //订单座位信息 
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
		fgets(id,12,stdin);    //输入用户ID 
		for (j = 0;find != 1;j++)//找到了就退出 
		{
			if ((fptr = fopen("C:/Users/DELL/Desktop/IOCS/accounts/user/Users.acc","r")) == NULL)//在用户名文件里找人 
			{
				printf("Fail to read!\n");
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
				}
     		}
     		if (fgets(Id,12,fptr) == NULL && find != 1 )//遍历完并且没有找到 
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
		int *Occupied;  //用于读取场次文件里的各项数据/字符
		
		int seat1,remain1;//占的座位的添加 
		int k=0,k1=0,k2=0,k3=0;
		char temp[18],temp1[18],temp2[18],temp3[18],temp4[18],path[255];
		int PosOfSes[20][20]={0};//the position of the seats in this session
		int SW,GW;
		//char filename[12]="ABCDEFG";  
		
		//假设这里场次信息已经完全确定 
		//char Ses[18];
		//strcpy(SerialNum, Ses);
		
		
		
		fgets(SerialNum,18,stdin);
		for (k = 0;SerialNum[k] != '\n';k++);
		SerialNum[k] = '\0';
		strcpy(iD,".ses"); 
		strcat(SerialNum,iD);//SerialNum即为该场次的文件名    
		
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
			temp4[k - k1 - 6] = SerialNum[k]; //截取字符串 
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
		
		if((fptr = fopen(path,"r+")) == NULL)//寻找名字叫该场次的场次文件 (该目录下） 
		{
        	printf("Open the file failure...\n");
        	l = 0;
        	return l;
    	}
    		else
			{
				fptr = fopen(path,"r+");
				//每行读入该场次文件中的对应数据，放在变量里 
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
					remain -= orders.SeatNum;//该票购买，剩余票数-1 
					fclose(fptr);//关闭文件 
					if((fptr1 = fopen(path,"w+")) == NULL)//寻找名字叫该场次的场次文件 (该目录下） 
					{
        				printf("Open the file failure...\n");
        				l = 0;
        				return l;
    				}
    					else
    					{
							fptr1 = fopen(path,"w+");//把存在各个变量里的场次信息文件里的各项数据弄回该文件，方便修改票余数 
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
					if((fptr2 = fopen(path,"a")) == NULL)//寻找名字叫该影厅的影厅文件 (该目录下） 
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
								fprintf(fptr2,"%d\n",seat1);//在影厅文件中最后每行每行添加已占座位数 
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
				//寻找对应的影厅的该电影的该播出时间段的对应文件，添加一个已占座位 (目前暂定文件为filename) 
				//strcpy(filename,orders[i].cinema);
				//strcat(filename,orders[i].hall);
				strcat(filename,".txt");				
				
				
				if((fptr3 = fopen(filename,"w+")) == NULL)//寻找名字叫该影厅的影厅文件 (该目录下） 
				{
        			printf("Open the file failure...\n");
        			return l;
    			}
    			else 
    			{
					fptr3 = fopen(filename,"w+");
					char cinema2[5],Type[4];
					int session1, Totalseat,Occupiedseats,*Occuseat;// 分离影片文件里的各项不同数据 
					Occuseat = (int *) malloc(remain * sizeof(int));//动态数组 
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
						
						if((fptr3 = fopen(filename,"w+")) == NULL)//寻找名字叫该影厅的影厅文件 (该目录下） 
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
							fprintf(fptr3,"%d\n",Occuseat[i]);//把数据重新输回去，同时票余数已更改 
						}
					}
				}						
	}
}*/ 


