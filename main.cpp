#include"reglog.h"
#include"userchangeinfo.h"
#define MAX 101

//-----主函数-----
int main(int argc, char *argv[])			//argv[0]包含了文件路径信息 
{
	char username[MAX]={'\0'};
	strcpy(username, WelcomeUI(argv[0]));
	int n=strlen(username);	
	if(strcmp(username, "FAIL")==0)
	{
		printf("退出中\n");
	}
	else
	{
		if(username[n-1]=='1')
		{
			username[n-1]='\0';
			printf("管理员\n");                //用户登陆后界面接口 
		}
		else if(username[n-1]=='2')
		{
			username[n-1]='\0';
			changeInfo(argv[0], username); 			 //管理员登录后界面接口 
		} 
	}
	return 0;
}
