#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
//��ӰԺ��Ʊ 
typedef struct order{  						
							//�û�������Ϣ��������Ϣ
    char ID[11];          //�û�ID
    char changci[12];       //���εı�� 
    char moviename[12];     //��Ӱ���� 
    char cinema[10];        //ӰԺ���� 
    char hall[10];          //Ӱ������ 
    int Start;              //��Ӱ��ʼʱ�� 
	int End;                //��Ӱ����ʱ�� 
    int seat[3][2];            //������λ��Ϣ
    int SeatNum;               //������λ����
}Order;
Order orders[10000];



int DealOrder(Order orders[]);


int main (int argc, const char * argv[])
{
	DealOrder(orders);
	printf("");//���κ� 
	printf("");//���º��Ʊ���� 
	printf("");//���º����λ�ֲ�
	printf("");//���û�ѡ�����λ
	 
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
		fgets(id,12,stdin);    //�����û�ID 
		for (j = 0;find != 1;j++)//�ҵ��˾��˳� 
		{
			if ((fptr = fopen("Users.txt","r")) == NULL)//���û����ļ������� 
			{
				printf("Fail to read!\n");
				return l;
			}
			else
				fptr = fopen("Users.txt","r");
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
		char id2[18]="\0";
		char filename[12]="ABCDEFG"; 
		char id1[13], cinema1[5], lang[4]; 
		int session, starttime, endtime, length, remain;
		double price;//���ڶ�ȡ�����ļ���ĸ�������/�ַ� 
		int seat1;//ռ����λ����� 
		
		//�������ﳡ����Ϣ�Ѿ���ȫȷ�� 
			//strcpy(id2,orders[0].changci);
		fgets(id2,18,stdin);
		for (k = 0;id2[k] != '\n';k++);
		id2[k] = '\0';
		strcpy(iD,".txt"); 
		//strcpy(id2,orders[j].changci);//��ȡ������Ϣ��ĳ�����Ϣ 
		strcat(id2,iD);//id2��Ϊ�ó��ε��ļ���    ???
		if((fptr = fopen(id2,"r+")) == NULL)//Ѱ�����ֽиó��εĳ����ļ� (��Ŀ¼�£� 
		{
        	printf("Open the file failure...\n");
        	return l;
    	}
    		else
			{
				fptr = fopen(id2,"r+");
				//ÿ�ж���ó����ļ��еĶ�Ӧ���ݣ����ڱ����� 
				fscanf(fptr, "%s", id1);
			    fscanf(fptr,"%s",cinema1);
				fscanf(fptr,"%d",&session);
				fscanf(fptr,"%d",&starttime);
				fscanf(fptr,"%d",&endtime);
				fscanf(fptr,"%d",&length);
				fscanf(fptr,"%d",&remain);
				fscanf(fptr,"%lf",&price);
				fscanf(fptr,"%s",lang);
				remain -= orders[i].SeatNum;//��Ʊ����ʣ��Ʊ��-1 
				fclose(fptr);//�ر��ļ� 
				if((fptr1 = fopen(id2,"w+")) == NULL)//Ѱ�����ֽиó��εĳ����ļ� (��Ŀ¼�£� 
				{
        			printf("Open the file failure...\n");
        			return l;
    			}
    				else
    				{
						fptr1 = fopen(id2,"w+");//�Ѵ��ڸ���������ĳ�����Ϣ�ļ���ĸ�������Ū�ظ��ļ��������޸�Ʊ���� 
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
				//Ѱ�Ҷ�Ӧ��Ӱ���ĸõ�Ӱ�ĸò���ʱ��εĶ�Ӧ�ļ������һ����ռ��λ (Ŀǰ�ݶ��ļ�Ϊfilename) 
				//strcpy(filename,orders[i].cinema);
				//strcat(filename,orders[i].hall);
				strcat(filename,".txt");				if((fptr2 = fopen(filename,"a")) == NULL)//Ѱ�����ֽи�Ӱ����Ӱ���ļ� (��Ŀ¼�£� 
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
						fprintf(fptr2,"\n");//��Ӱ���ļ������ÿ��ÿ�������ռ��λ�� 
					}
					fclose(fptr2);
				}
				
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
}


