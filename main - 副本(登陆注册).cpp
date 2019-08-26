/*
初版登录界面 
最后编辑于2019-08-26 23:24 
目前未发现文件读写的问题，注册登录模块容错性足矣 
菜单非法输入仍会导致死循环bug 
下一步将改成长字符串输入形式以缓冲非法输入的破坏性 
未完成用户完整信息的录入功能 
 
 注意：启动时一定确保当前目录下有\accounts\admin和\accounts\user目录，否则无法写入用户信息文件！ 

*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<io.h>
#include<time.h>

#define MAX 101

//-----功能函数声明区----- 
int regisUI(char path[]);
int regis(int choice, char path[]);
int loginUI(char path[]);
int login(int choice, char path[]);

//-----辅助函数声明区-----
char *randspawner(); 

//-----主登录界面入口------ 
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
			printf("Input error!\n");				//已知此处有非法输入死循环bug 
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
	return value;							//0-推出  2-登录已成功，进入登陆后界面 
};

//-----主函数-----
int main(int argc, char *argv[])			//argv[0]包含了文件路径信息 
{
	switch(WelcomeUI(argv[0]))
	{
		case 0:
			printf("Exit\n");
			break;
		case 2:
			printf("Experimental Page. Login action passed successfully!\n");
			printf("Later functons are under development. Coming soon.\n");			//接口预留处 
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
		if(!scanf("%d",&choice))								//此处鲁棒性良好 
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
		printf("**********Login**********\n");
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

//-----注册机制的具体实现------ 
int regis(int choice, char path[])
{
	FILE *out;                                                           //设立文件指针 
	char username[MAX], password1[MAX]={'\0'}, password2[MAX]={'\0'};    //初始化用户名密码字符串 
	char filename[MAX]={'\0'};  										 //初始化文件名字符串 
	int flag=0;                                                          //控制循环 
	printf("All inputs shall not beyond 20 characters\n");               //“所有的输入不应超过20字符” 
	printf("Enter username:");
	while(flag<3)
	{
		flag=3;
		if(!scanf("%s",username))                                        //防出错 
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
	}                     												 //步骤均无问题方可跳出循环 
	
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
				fprintf(out, "%s", password2);							 //写入密码 
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
	char filename[MAX]={'\0'};
	char verify[7]={'\0'}, veryfin[MAX]={'\0'};
	int flag=0, value=1;
	while(flag<4 && value)
	{
		FILE *in;
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
		strcpy(verify, randspawner());   								//验证码机制 
		printf("%s\n", verify);
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
				fscanf(in,"%s",password2);
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
