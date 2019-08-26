/*
�����¼���� 
���༭��2019-08-26 23:24 
Ŀǰδ�����ļ���д�����⣬ע���¼ģ���ݴ������� 
�˵��Ƿ������Իᵼ����ѭ��bug 
��һ�����ĳɳ��ַ���������ʽ�Ի���Ƿ�������ƻ��� 
δ����û�������Ϣ��¼�빦�� 
 
 ע�⣺����ʱһ��ȷ����ǰĿ¼����\accounts\admin��\accounts\userĿ¼�������޷�д���û���Ϣ�ļ��� 

*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<io.h>
#include<time.h>

#define MAX 101

//-----���ܺ���������----- 
int regisUI(char path[]);
int regis(int choice, char path[]);
int loginUI(char path[]);
int login(int choice, char path[]);

//-----��������������-----
char *randspawner(); 

//-----����¼�������------ 
int WelcomeUI(char path[])
{
	int value=1;
	int choice=0;
	while(value==1)
	{
		printf("*********Welcome**********\n");
		printf("1. Login\n");
		printf("2. Register\n");
		printf("3. Exit\n");
		printf("enter option:");
		if(!scanf("%d",&choice))
		{
			printf("Input error!\n");				//��֪�˴��зǷ�������ѭ��bug 
		}
		else
		{
			switch(choice)
			{
				case 1:
					value=loginUI(path);
					break;
				case 2:
					value=regisUI(path);
					break;
				case 3:
					value=0;
					break;
				default:
					printf("Illegal input!\n");
			}
		}
	}
	return value;							//0-�Ƴ�  2-��¼�ѳɹ��������½����� 
};

//-----������-----
int main(int argc, char *argv[])			//argv[0]�������ļ�·����Ϣ 
{
	switch(WelcomeUI(argv[0]))
	{
		case 0:
			printf("Exit\n");
			break;
		case 2:
			printf("Experimental Page. Login action passed successfully!\n");
			printf("Later functons are under development. Coming soon.\n");			//�ӿ�Ԥ���� 
			break;
		default:
			printf("Something wrong occured.\n");
	}
	return 0;
}

int regisUI(char path[])
{
	int choice=0, flag=1;
	while(flag)
	{
		printf("**********Register**********\n");
		printf("Register as:\n");
		printf("1. Administrator\n");
		printf("2. User\n");
		printf("3. Back\n");
		printf("Enter option:\n");
		if(!scanf("%d",&choice))								//�˴�³�������� 
		{
			printf("Input error!\n");
			flag=0;
		}
		else
		{
			if(choice==1 || choice==2)
			{
				flag=regis(choice, path);
				if(flag)
				{
					printf("Register successfully!\n");
					return 1;
				}
				else
				{
					printf("Register failed!\n");
				}
			}
			else if(choice==3)
			{
				flag=0;
			}
			else
			{
				printf("Illegal input!\n");
			}
		}
		
	}
	return 1;
}

int loginUI(char path[])
{
	int choice=0, flag=1;
	while(flag)
	{
		printf("**********Register**********\n");
		printf("Login as:\n");
		printf("1. Administrator\n");
		printf("2. User\n");
		printf("3. Back\n");
		printf("Enter option:\n");
		if(!scanf("%d",&choice))
		{
			printf("Input error!\n");
			flag=0;
		}
		else
		{
			if(choice==1 || choice==2)
			{
				flag=regis(choice, path);
				if(flag)
				{
					printf("Login successfully!\n");
					return 2;							//�ش�ֵΪ2�򴥷���ӭ���溯�������������¼����� 
				}
				else
				{
					printf("Login failed!\n");
				}
			}
			else if(choice==3)
			{
				flag=0;
			}
			else
			{
				printf("Illegal input!\n");
			}
		}	
	}
	return 1;
}

//-----ע����Ƶľ���ʵ��------ 
int regis(int choice, char path[])
{
	FILE *out;                                                           //�����ļ�ָ�� 
	char username[MAX], password1[MAX]={'\0'}, password2[MAX]={'\0'};    //��ʼ���û��������ַ��� 
	char filename[MAX]={'\0'};  										 //��ʼ���ļ����ַ��� 
	int flag=0;                                                          //����ѭ�� 
	printf("All inputs shall not beyond 20 characters\n");               //�����е����벻Ӧ����20�ַ��� 
	printf("Enter username:");
	while(flag<3)
	{
		flag=3;
		if(!scanf("%s",username))                                        //������ 
		{
			printf("Illegal input!\n");
			flag--;
		}
		printf("\nEnter password:");
		if(!scanf("%s",password1))
		{
			printf("Illegal input!\n");
			flag--;
		}
		printf("\nConfirm password:");
		if(!scanf("%s",password2))
		{
			printf("Illlegal input!\n");
			flag--;
		}
	}                     												 //����������ⷽ������ѭ�� 
	
	if(strcmp(password1,password2)==0)
	{
		strncpy(filename, path, strlen(path)-8);
		if(choice==1)
		{
			strcat(filename, "accounts\\admin\\");
			strcat(filename, username);
			strcat(filename, ".acc");
		}
		else if(choice==2)
		{
			strcat(filename, "accounts\\user\\");
			strcat(filename, username);
			strcat(filename, ".acc");                                    //�ļ�·����ƴ�� 
		}
		if(access(filename, 0)!=0)										 //����û����Ƿ��Ѵ��� 
		{
			if((out=fopen(filename, "w"))!=NULL)						 //�½����û���Ϊ���Ƶ��ļ�����д��ģʽ�� 
			{
				fprintf(out, "%s", password2);							 //д������ 
				if(fclose(out)!=0)										 //��ֹ����ر� 
				{
					fprintf(stderr, "system Error!\n");
					return 0;
				}
				return 1;												 //ע��ɹ��򷵻�1 
			}
			else
			{
				fprintf(stderr, "System Error!\n");
			}
			
		}
		else
		{
			printf("Invalid USername!\n");
		}
		
		
	}
	else
	{
		printf("Wrong password!\n"); 
	}
	return 0;
}

//-------��¼���Ƶľ���ʵ��--------- 
int login(int choice, char path[])
{
	FILE *in;
	char username[MAX], password1[MAX]={'\0'}, password2[MAX]={'\0'};   //����ͬ��	  
	char filename[MAX]={'\0'};
	char verify[7]={'\0'}, veryfin[MAX]={'\0'};
	int flag=0, value=1;
	while(flag<4 && value)
	{
		flag=4;
		printf("All inputs shall not beyond 20 characters\n");
		printf("Enter username:");
		if(!scanf("%s",username))
		{
			printf("Illegal input!\n");
			flag--;
		}
		printf("\nEnter password:");
		if(!scanf("%s",password1))
		{
			printf("Illegal input!\n");
			flag--;
		}
		printf("\nEnter verify code:");
		strcpy(verify, randspawner());   								//��֤����� 
		printf("%s", verify);
		if(!scanf("%s", veryfin))
		{
			printf("Illegal input!\n");
			flag--;
		}
		if(strcmp(verify, veryfin)!=0)
		{
			printf("Cannot be verified!\n");
			flag--;
		}
	
		strncpy(filename, path, strlen(path)-8);
		if(choice==1)
		{
			strcat(filename, "accounts\\admin\\");
			strcat(filename, username);
			strcat(filename, ".acc");
		}
		else if(choice==2)
		{
			strcat(filename, "accounts\\user\\");
			strcat(filename, username);
			strcat(filename, ".acc");										//ƴ���ļ�·�� 
		}
	
		if((in=fopen(filename, "r"))!=NULL)									//��ͼ��ȡ�û�����ָ�ļ� 
		{
			fscanf(in,"%s",password2);
			if(strcmp(password1, password2)==0)								//������֤ 
			{
				if(fclose(in)!=0)
				{
					fprintf(stderr, "system Error!\n");
					return 0;
				}
				printf("Login successfully!\n");							 
				return 1;													//��½�ɹ�������1			
			}
			else
			{
			printf("Wrong password!\n");
			}
		}
		else
		{
			fprintf(stderr, "System Error!\n");
		}
		printf("Try again(1) or exit(0)?");
		scanf("%d",&value);
	
	}
	
	return 0;		
}

//------�����������--------
char *randspawner()
{
	int min=1, max=36, i;
	static char code[7];
	srand(time(0));
	for(i=0;i<6;i++)
	{
		code[i]=char((max-min)*rand()/(RAND_MAX+1)+min);
	}
	return code;
} 
