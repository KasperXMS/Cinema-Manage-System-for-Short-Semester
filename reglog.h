/*
登录与注册接口 
请调用WelcomeUI()函数作为接口 
注意：启动时一定确保当前目录下有\accounts\admin和\accounts\user目录，否则无法写入用户信息文件！
最后编辑于2019-08-27 17:18 

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

//-----功能函数声明区----- 
int regisUI(char path[]);
int regis(int choice, char path[]);
int loginUI(char path[]);
int login(int choice, char path[]);

//-----辅助函数声明区-----
char *randspawner(); 

int regisUI(char path[])
{
	int choice=0, flag=1;
	while(flag)
	{
		printf("**********新用户注册**********\n");
		printf("注册为:\n");
		printf("1. 影院管理员\n");
		printf("2. 普通用户\n");
		printf("3. 返回\n");
		printf("请输入选项:\n");
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
				printf("非法输入！\n");
				
		}
	}
	return 1;
}

int loginUI(char path[])
{
	int choice=0, flag=1;
	while(flag)
	{
		printf("**********登录**********\n");
		printf("请选择登录角色:\n");
		printf("1. 影院管理员\n");
		printf("2. 普通用户\n");
		printf("3. 返回\n");
		printf("请输入选项:\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				flag=login(choice, path);
				if(flag)
				{
					printf("Login successfully!\n");
					return 2;							//回传值为2则触发欢迎界面函数结束，进入登录后界面 
				}
				else
				{
					printf("Login failed!\n");
				}
				break;
			case 2:
				flag=login(choice, path);
				if(flag)
				{
					printf("Login successfully!\n");
					return 2;							//回传值为2则触发欢迎界面函数结束，进入登录后界面 
				}
				else
				{
					printf("Login failed!\n");
				}
				break;
			default:
				printf("非法输入！\n");	
		}		
	}
	return 1;
}

//-----注册机制的具体实现------ 
int regis(int choice, char path[])
{
	FILE *out;                                                           //设立文件指针 
	char username[MAX], password1[MAX]={'\0'}, password2[MAX]={'\0'};    //初始化用户名密码字符串 
	char NAME[MAX]={'\0'}, gender[10]={'\0'}, tel[MAX]={'\0'}, email[MAX]={'\0'}; 
	char filename[MAX]={'\0'};  										 //初始化文件名字符串 
	int flag=1;                                                          //控制循环 
	printf("所有的输入不应超过20字符\n");               //“所有的输入不应超过20字符” 
	while(flag)
	{
		printf("输入用户名:");
		scanf("%s", username);
		printf("\n输入密码:");
		scanf("%s", password1);
		printf("\n再次确认密码:");
		scanf("%s", password2);
		printf("\n输入姓名:");
		scanf("%s", NAME);
		printf("\n输入性别:");
		scanf("%s", gender);
		printf("\n输入电话号码:");
		scanf("%s", tel);
		printf("\n输入电子邮箱:");
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
					printf("邮箱格式不正确\n");
				}
			}
			else
			{
				printf("电话格式不正确\n");
			}
		}
		else
		{
			printf("用户名格式不正确\n"); 
		}
		 
	}                 												 //步骤均无问题方可跳出循环 
	
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
			strcat(filename, ".acc");                                    //文件路径名拼接 
		}
		if(access(filename, 0)!=0)										 //检查用户名是否已存在 
		{
			if((out=fopen(filename, "w"))!=NULL)						 //新建以用户名为名称的文件并以写入模式打开 
			{
				fprintf(out, "%s\n", username);							  
				fprintf(out, "%s\n", NAME);
				fprintf(out, "%s\n", gender);
				fprintf(out, "%s\n", tel);
				fprintf(out, "%s\n", password2);
				fprintf(out, "%s\n", email);
				fprintf(out, "%lf\n", 0.00);
				if(fclose(out)!=0)										 //防止错误关闭 
				{
					fprintf(stderr, "system Error!\n");
					return 0;
				}
				return 1;												 //注册成功则返回1 
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

//-------登录机制的具体实现--------- 
int login(int choice, char path[])
{
	
	char username[MAX], password1[MAX]={'\0'}, password2[MAX]={'\0'};   //作用同上	  
	char NAME[MAX]={'\0'}, gender[10]={'\0'}, tel[MAX]={'\0'}, email[MAX]={'\0'};
	char filename[MAX]={'\0'};
	char verify[7]={'\0'}, veryfin[MAX]={'\0'};
	double remain=0.00;
	int flag=0, value=1;
	while(flag<4 && value)
	{
		FILE *in;
		flag=4;
		printf("所有的输入不应超过20字符\n");
		printf("输入用户名:");
		scanf("%s",username);
		printf("\n输入密码:");
		scanf("%s",password1);
		printf("\n输入验证码:");
		strcpy(verify, randspawner());   								//验证码机制 
		printf("%s\n", verify);
		scanf("%s", veryfin);
		if(strcmp(verify, veryfin)!=0)
		{
			printf("验证未通过!\n");
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
				strcat(filename, ".acc");										//拼接文件路径 
			}
		
			if((in=fopen(filename, "r"))!=NULL)									//试图读取用户名所指文件 
			{
				fscanf(in, "%s", username);							  
				fscanf(in, "%s", NAME);
				fscanf(in, "%s", gender);
				fscanf(in, "%s", tel);
				fscanf(in, "%s", password2);
				fscanf(in, "%s", email);
				fscanf(in, "%lf", &remain);
				if(strcmp(password1, password2)==0)								//密码验证 
				{
					if(fclose(in)!=0)
					{
						fprintf(stderr, "system Error!\n");
						return 0;
					}							 
					return 1;													//登陆成功，返回1			
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

//------随机数生成器--------
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
		printf("*********欢迎**********\n");
		printf("1. 登录已有账号\n");
		printf("2. 注册新账号\n");
		printf("3. 退出系统\n");
		printf("请输入选项:");
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
				printf("非法输入!\n");
		}
		
	}
	return value;							//0-推出  2-登录已成功，进入登陆后界面 
}

#endif
