#include"reglog.h"

//-----������-----
int main(int argc, char *argv[])			//argv[0]�������ļ�·����Ϣ 
{
	switch(WelcomeUI(argv[0]))
	{
		case 0:
			printf("�˳���\n");
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
