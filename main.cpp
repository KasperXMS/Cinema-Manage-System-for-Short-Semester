#include"reglog.h"
#include"userfunction.h"
#include"adminfunction.h"
#define MAX 101

void userUI(char path[], char username[]);
void adminUI(char path[], char username[]);

//-----主函数-----
int main(int argc, char *argv[])			//argv[0]包含了文件路径信息 
{
	int online=1;
	while(online)
	{
		char username[MAX]={'\0'};
		strcpy(username, WelcomeUI(argv[0]));
		int n=strlen(username);	
		if(strcmp(username, "FAIL")==0)
		{
			online=0;
			printf("退出中\n");
		}
		else
		{
			if(username[n-1]=='1')
			{
				username[n-1]='\0';
				adminUI(argv[0], username);                //管理员登陆后界面接口 
			}
			else if(username[n-1]=='2')
			{
				username[n-1]='\0';
				userUI(argv[0], username); 			 //用户登录后界面接口 
			} 
		}
	}
	
	return 0;
}

void adminUI(char path[], char username[])
{
	int flag=1;
	while(flag)
	{
		int choice=0;
		printf("欢迎，管理员%s!\n", username);
		printf("*************************\n");
		printf("1. 订单管理\n");
		printf("2. 影厅管理\n");
		printf("3. 场次管理\n");
		printf("4. 个人信息修改\n");
		printf("5. 登出\n");
		printf("请输入选项：");
		scanf("%d", &choice);
		switch(choice)
		{
			case 1:
				break;
			case 2:
				{
					int flaga2=1;
					while(flaga2)
					{
						int choicea2=0;
						printf("**********影厅管理**********\n");
						printf("1. 影厅查询\n");
						printf("2. 添加场次\n");
						printf("3. 返回;");
						printf("请输入选项：");
						scanf("%d",&choicea2);
						switch(choicea2)
						{
							case 1:
								find_studio_info(path);
								break;
							case 2:
								studio_info(path);
								break;
							case 3:
								flaga2=0;
								break;
							default:
								printf("非法输入！\n");
						} 
					}
				}
				
				break;
			case 3:
				{
					int flaga3=1;
					while(flaga3)
					{
						int choicea3=0;
						printf("**********场次管理**********\n");
						printf("1. 场次查询\n");
						printf("2. 添加场次\n");
						printf("3. 场次归类\n");
						printf("4. 返回\n");
						printf("请输入选项：");
						scanf("%d", &choicea3);
						switch(choicea3)
						{
							case 1:
								find_session_info(path);
								break;
							case 2:
								add_session_info(path);
								break;
							case 3:
								session_classified(path);
								break;
							case 4:
								flaga3=0;
								break;
							default:
								printf("非法输入！\n");
						}
					}
				}
				
				break;
			case 4:
				Changeinfo(path, username);
				break;
			case 5:
				flag=0;
				break;
			default:
				printf("非法输入！\n");
		}
	}
}

void userUI(char path[], char username[])
{
	int flag=1;
	while(flag)
	{
		int choice=0;
		printf("欢迎, 用户%s!\n", username);
		printf("*************************\n");
		printf("1. 查询电影场次\n");
		printf("2. 查询个人订单\n");
		printf("3. 更改个人信息\n");
		printf("4. 账户余额操作\n");
		printf("5. 登出\n");
		printf("请输入选项:");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				cst_find_cma(path);
				break;
			case 2:
				break;
			case 3:
				changeInfo(path, username);
				break;
			case 4:
				TopUp(path, username);
				break;
			case 5:
				flag=0;
				break;
			default:
				printf("非法输入！\n");
		}
	}
}

