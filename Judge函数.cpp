#include <stdio.h>

int judgeUsername(char);
//�ж��û��������ʽ�Ƿ����Ҫ�� ������Ҫ�󷵻�1�����򷵻�0
int judge(char username[])
{
	int i = 0, len = 0, flag = 1; 
	
	for (i = 0; username[i] != '\0'; i++)
	{
		len++;
	}
	//ȷ���ַ������� 
	i = 0;
	if (len >= 6 && len <= 10)//�ж��ַ��������Ƿ����Ҫ�� 
	{
		while (flag == 1 && i < len) 
		{
			if (username[i] >= '0' && username[i] <= '9' || username[i] >= 'A' && username[i] <= 'Z' || username[i] >= 'a' && username[i] <= 'z')
			//������ÿ���ַ��Ƿ�Ϊ��ĸ������
			{
				i++;
			}
			else flag = 0;
		}
	}
	else flag = 0;
	return flag;
}

int judgeTel(char);
//�жϵ绰�����ʽ�Ƿ����Ҫ�� ������Ҫ�󷵻�1�����򷵻�0
int judgeTel(char telnumber[])
{
	int i = 0, len = 0, flag = 1; 
	for (i = 0; telnumber[i] != '\0'; i++)
	{
		len++;
	}
	//ȷ���ַ������� 
	i = 0;
	if (len == 11)//�ж��ַ��������Ƿ����Ҫ��
	{
		while (flag == 1 && i < len) 
		{
			if (telnumber[i] >= '0' && telnumber[i] <= '9')
			//������ÿ���ַ��Ƿ�Ϊ���� 
			{
				i++;
			}
			else flag = 0;
		}
	}
	else flag = 0;
	return flag;
}

int judgeEmail(char);
int judgeEmail(char email[])
{
	int i = 0, len = 0, flag = 1, flag_1 = 0, flag_2 = 0;
	for (i = 0; email[i] != '\0'; i++)
	{
		len++; 
	}
	//ȷ���ַ������� 
	i = 0;
	while (flag == 1 && i < len)
	{
		if (email[i] >= '0' && email[i] <= '9' || email[i] >= 'A' && email[i] <= 'Z' || email[i] >= 'a' && email[i] <= 'z' || email[i] == '@' || email[i] == '_' || email[i] == '.')
		//�ж��ַ������Ƿ��зǷ��ַ� 
		{ 
			if (flag_1 == 0)//��@��֮ǰ���ַ�
			{
				if (email[i] == '.')//ֻ�ܰ���������ĸ�»���
				{
					flag = 0;
				}
				if (email[i] == '_')//�����»��߲������� 
				{
					if (email[i + 1] == '_')
					{
						flag = 0;
					}
				}
			}
			if (email[i] == '@')//�ж��Ƿ����"@" 
			{
				flag_1 = 1;
			}
			if (flag_1 == 1)//����"@"������� 
			{
				if (email[i] == '.')//�ж�"@"���Ƿ���"." 
				{
					flag_2 = 1;
					if (email[i + 1] == '.')//�������"."����һ���򲻷���Ҫ�� 
					{
						flag = 0;
					}
				}
				
				if (email[i + 1] == '@')//�����������"@"���ж�Ϊ������Ҫ��
				{
					flag = 0;
				}
			}
		} 
	i++;
	}
	if (flag_1 == 1 && flag_2 == 1 && flag == 1)
	{}
	else flag = 0;
	return flag;
}
				 
int main()
{
	char test[100];
	scanf("%s/n", test);
	if (judgeEmail(test) == 1)
	printf("legal");
	else printf("illegal");
	return 0;
}
	
