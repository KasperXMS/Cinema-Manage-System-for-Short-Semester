#include"reglog.h"

//-----主函数-----
int main(int argc, char *argv[])			//argv[0]包含了文件路径信息 
{
	switch(WelcomeUI(argv[0]))
	{
		case 0:
			printf("退出中\n");
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
