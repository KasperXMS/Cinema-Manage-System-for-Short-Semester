/*
��¼��ע��ӿ� 
�����WelcomeUI()������Ϊ�ӿ� 
ע�⣺����ʱһ��ȷ����ǰĿ¼����\accounts\admin��\accounts\userĿ¼�������޷�д���û���Ϣ�ļ���
���༭��2019-08-27 17:18 

*/

#ifndef _REGLOG_H
#define _REGLOG_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<io.h>
#include<time.h>
#include"judge.h"

#define MAX 101

//-----���ܺ���������----- 
int regisUI(char path[]);
int regis(int choice, char path[]);
int loginUI(char path[]);
int login(int choice, char path[]);

//-----��������������-----
char *randspawner(); 

int regisUI(char path[])
{
	int choice=0, flag=1;
	while(flag)
	{
		printf("**********���û�ע��**********\n");
		printf("ע��Ϊ:\n");
		printf("1. ӰԺ����Ա\n");
		printf("2. ��ͨ�û�\n");
		printf("3. ����\n");
		printf("������ѡ��:\n");
		scanf("%d", &choice);
		switch(choice)
		{
			case 1:
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
				break;
			case 2:
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
				break;
			default:
				printf("�Ƿ����룡\n");
				
		}
	}
	return 1;
}

int loginUI(char path[])
{
	int choice=0, flag=1;
	while(flag)
	{
		printf("**********��¼**********\n");
		printf("��ѡ���¼��ɫ:\n");
		printf("1. ӰԺ����Ա\n");
		printf("2. ��ͨ�û�\n");
		printf("3. ����\n");
		printf("������ѡ��:\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				flag=login(choice, path);
				if(flag)
				{
					printf("Login successfully!\n");
					return 2;							//�ش�ֵΪ2�򴥷���ӭ���溯�������������¼����� 
				}
				else
				{
					printf("Login failed!\n");
				}
			case 2:
				flag=login(choice, path);
				if(flag)
				{
					printf("Login successfully!\n");
					return 2;							//�ش�ֵΪ2�򴥷���ӭ���溯�������������¼����� 
				}
				else
				{
					printf("Login failed!\n");
				}
			default:
				printf("�Ƿ����룡\n");	
		}		
	}
	return 1;
}

//-----ע����Ƶľ���ʵ��------ 
int regis(int choice, char path[])
{
	FILE *out;                                                           //�����ļ�ָ�� 
	char username[MAX], password1[MAX]={'\0'}, password2[MAX]={'\0'};    //��ʼ���û��������ַ��� 
	char NAME[MAX]={'\0'}, gender[10]={'\0'}, tel[MAX]={'\0'}, email[MAX]={'\0'}; 
	char filename[MAX]={'\0'};  										 //��ʼ���ļ����ַ��� 
	int flag=1;                                                          //����ѭ�� 
	printf("���е����벻Ӧ����20�ַ�\n");               //�����е����벻Ӧ����20�ַ��� 
	while(flag)
	{
		printf("�����û���:");
		scanf("%s", username);
		printf("\n��������:");
		scanf("%s", password1);
		printf("\n�ٴ�ȷ������:");
		scanf("%s", password2);
		printf("\n��������:");
		scanf("%s", NAME);
		printf("\n�����Ա�:");
		scanf("%s", gender);
		printf("\n����绰����:");
		scanf("%s", tel);
		printf("\n�����������:");
		scanf("%s", email);
		if(judgeUsername(username))
		{
			if(judgeTel(tel))
			{
				if(judgeEmail(email))
				{
					flag=0;
				}
				else
				{
					printf("�����ʽ����ȷ\n");
				}
			}
			else
			{
				printf("�绰��ʽ����ȷ\n");
			}
		}
		else
		{
			printf("�û�����ʽ����ȷ\n"); 
		}
		 
	}                 												 //����������ⷽ������ѭ�� 
	
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
				fprintf(out, "%s\n", username);							  
				fprintf(out, "%s\n", NAME);
				fprintf(out, "%s\n", gender);
				fprintf(out, "%s\n", tel);
				fprintf(out, "%s\n", password2);
				fprintf(out, "%s\n", email);
				fprintf(out, "%lf\n", 0.00);
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
	
	char username[MAX], password1[MAX]={'\0'}, password2[MAX]={'\0'};   //����ͬ��	  
	char NAME[MAX]={'\0'}, gender[10]={'\0'}, tel[MAX]={'\0'}, email[MAX]={'\0'};
	char filename[MAX]={'\0'};
	char verify[7]={'\0'}, veryfin[MAX]={'\0'};
	double remain=0.00;
	int flag=0, value=1;
	while(flag<4 && value)
	{
		FILE *in;
		flag=4;
		printf("���е����벻Ӧ����20�ַ�\n");
		printf("�����û���:");
		scanf("%s",username);
		printf("\n��������:");
		scanf("%s",password1);
		printf("\n������֤��:");
		strcpy(verify, randspawner());   								//��֤����� 
		printf("%s\n", verify);
		scanf("%s", veryfin);
		if(strcmp(verify, veryfin)!=0)
		{
			printf("��֤δͨ��!\n");
			flag--;
		}
		else
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
				strcat(filename, ".acc");										//ƴ���ļ�·�� 
			}
		
			if((in=fopen(filename, "r"))!=NULL)									//��ͼ��ȡ�û�����ָ�ļ� 
			{
				fscanf(in, "%s", username);							  
				fscanf(in, "%s", NAME);
				fscanf(in, "%s", gender);
				fscanf(in, "%s", tel);
				fscanf(in, "%s", password2);
				fscanf(in, "%s", email);
				fscanf(in, "%lf", &remain);
				if(strcmp(password1, password2)==0)								//������֤ 
				{
					if(fclose(in)!=0)
					{
						fprintf(stderr, "system Error!\n");
						return 0;
					}							 
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
		if(value)
		{
			flag=0;
		}
	
	}
	
	return 0;		
}

//------�����������--------
char *randspawner()
{
	int min=1, max=36, a, i;
	static char code[7];
	srand(time(0));
	for(i=0;i<6;i++)  
	{
		a=(max-min)*rand()/(RAND_MAX+1)+min;
		if(a<=10)
		{
			code[i]=a+47;
		}
		else
		{
			code[i]=a+54;
		}
	}
	return code;
}

int WelcomeUI(char path[])
{
	int value=1;
	int choice=0;
	while(value==1)
	{
		printf("*********��ӭ**********\n");
		printf("1. ��¼�����˺�\n");
		printf("2. ע�����˺�\n");
		printf("3. �˳�ϵͳ\n");
		printf("������ѡ��:");
		scanf("%d", &choice);
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
				printf("�Ƿ�����!\n");
		}
		
	}
	return value;							//0-�Ƴ�  2-��¼�ѳɹ��������½����� 
}

#endif
