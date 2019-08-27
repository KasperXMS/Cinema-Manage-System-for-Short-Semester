#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
//电影院卖票 
typedef struct order{  						
							//用户个人信息及订单信息
    char ID[11];          //用户ID
    char changci[12];       //场次的编号 
    char moviename[12];     //电影名字 
    char cinema[10];        //影院名称 
    char hall[10];          //影厅名称 
    int Start;              //电影开始时间 
	int End;                //电影结束时间 
    int seat[3][2];            //订单座位信息
    int SeatNum;               //订单座位个数
}Order;
Order orders[10000];



int DealOrder(Order orders[]);


int main (int argc, const char * argv[])
{
	DealOrder(orders);
	printf("");//场次号 
	printf("");//更新后的票余数 
	printf("");//更新后的座位分布
	printf("");//该用户选择的座位
	 
	return 0;
}
int DealOrder(Order orders[])
{
	FILE *fptr=NULL,*fptr1=NULL,*fptr2=NULL,*fptr3=NULL;
	char id[18]={'\0'},Id[12]={'\0'},iD[5]=".ses";
	int i=0,j=0,find=0,find1=0,k=0,l=0;
	strcpy(orders[0].ID , "Zenglingxi");
	strcpy(orders[0].changci , "DDYY08210407");
	strcpy(orders[0].moviename , "Avengers4");
	strcpy(orders[0].cinema , "DDYY");
	strcpy(orders[0].hall , "7");
	orders[0].Start = 1210;
	orders[0].End = 1340;
	orders[0].seat[0][0] = 1;
	orders[0].seat[0][1] = 1;
	orders[0].seat[1][0] = 2;
	orders[0].seat[1][1] = 2;
	orders[0].SeatNum = 2;
	for (i = 0;i < 10000;i++)
	{
		//strcpy(id,orders[i]->ID);
		fgets(id,12,stdin);    //输入用户ID 
		for (j = 0;find != 1;j++)//找到了就退出 
		{
			if ((fptr = fopen("Users.txt","r")) == NULL)//在用户名文件里找人 
			{
				printf("Fail to read!\n");
				return l;
			}
			else
				fptr = fopen("Users.txt","r");
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
		char id2[18]="\0";
		char filename[12]="ABCDEFG"; 
		char id1[13], cinema1[5], lang[4]; 
		int session, starttime, endtime, length, remain;
		double price;//用于读取场次文件里的各项数据/字符 
		int seat1;//占的座位的添加 
		
		//假设这里场次信息已经完全确定 
			//strcpy(id2,orders[0].changci);
		fgets(id2,18,stdin);
		for (k = 0;id2[k] != '\n';k++);
		id2[k] = '\0';
		strcpy(iD,".txt"); 
		//strcpy(id2,orders[j].changci);//获取订单信息里的场次信息 
		strcat(id2,iD);//id2即为该场次的文件名    ???
		if((fptr = fopen(id2,"r+")) == NULL)//寻找名字叫该场次的场次文件 (该目录下） 
		{
        	printf("Open the file failure...\n");
        	return l;
    	}
    		else
			{
				fptr = fopen(id2,"r+");
				//每行读入该场次文件中的对应数据，放在变量里 
				fscanf(fptr, "%s", id1);
			    fscanf(fptr,"%s",cinema1);
				fscanf(fptr,"%d",&session);
				fscanf(fptr,"%d",&starttime);
				fscanf(fptr,"%d",&endtime);
				fscanf(fptr,"%d",&length);
				fscanf(fptr,"%d",&remain);
				fscanf(fptr,"%lf",&price);
				fscanf(fptr,"%s",lang);
				remain -= orders[i].SeatNum;//该票购买，剩余票数-1 
				fclose(fptr);//关闭文件 
				if((fptr1 = fopen(id2,"w+")) == NULL)//寻找名字叫该场次的场次文件 (该目录下） 
				{
        			printf("Open the file failure...\n");
        			return l;
    			}
    				else
    				{
						fptr1 = fopen(id2,"w+");//把存在各个变量里的场次信息文件里的各项数据弄回该文件，方便修改票余数 
						fprintf(fptr1, "%s\n",id1);
			    		fprintf(fptr1,"%s\n",cinema1);
						fprintf(fptr1,"%d\n",session);
						fprintf(fptr1,"%d\n",starttime);
						fprintf(fptr1,"%d\n",endtime);
						fprintf(fptr1,"%d\n",length);
						fprintf(fptr1,"%d\n",remain);
						fprintf(fptr1,"%lf\n",price);
						fprintf(fptr1,"%s\n",lang);
						fclose(fptr1);
					}
			} 
				//寻找对应的影厅的该电影的该播出时间段的对应文件，添加一个已占座位 (目前暂定文件为filename) 
				//strcpy(filename,orders[i].cinema);
				//strcat(filename,orders[i].hall);
				strcat(filename,".txt");				if((fptr2 = fopen(filename,"a")) == NULL)//寻找名字叫该影厅的影厅文件 (该目录下） 
				{
        			printf("Open the file failure...\n");
        			return l;
    			}
    			else
    			{
					fptr2 = fopen(filename,"a");
					int SW;
					int GW;
					for (k = 0;k < orders[i].SeatNum;k++)
					{
						SW = orders[i].seat[k][0] * 100;
						GW = orders[i].seat[k][1];
						seat1 = SW + GW;
						fprintf(fptr2,"\n");
						fprintf(fptr2,"%d",seat1);
						fprintf(fptr2,"\n");//在影厅文件中最后每行每行添加已占座位数 
					}
					fclose(fptr2);
				}
				
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
}


