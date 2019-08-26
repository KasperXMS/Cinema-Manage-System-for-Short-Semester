#include <stdio.h>

int judgeUsername(char);
//判断用户名密码格式是否符合要求 ，符合要求返回1，否则返回0
int judge(char username[])
{
	int i = 0, len = 0, flag = 1; 
	
	for (i = 0; username[i] != '\0'; i++)
	{
		len++;
	}
	//确定字符串长度 
	i = 0;
	if (len >= 6 && len <= 10)//判断字符串长度是否符合要求 
	{
		while (flag == 1 && i < len) 
		{
			if (username[i] >= '0' && username[i] <= '9' || username[i] >= 'A' && username[i] <= 'Z' || username[i] >= 'a' && username[i] <= 'z')
			//逐个检查每个字符是否为字母或数字
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
//判断电话号码格式是否符合要求 ，符合要求返回1，否则返回0
int judgeTel(char telnumber[])
{
	int i = 0, len = 0, flag = 1; 
	for (i = 0; telnumber[i] != '\0'; i++)
	{
		len++;
	}
	//确定字符串长度 
	i = 0;
	if (len == 11)//判断字符串长度是否符合要求
	{
		while (flag == 1 && i < len) 
		{
			if (telnumber[i] >= '0' && telnumber[i] <= '9')
			//逐个检查每个字符是否为数字 
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
	//确定字符串长度 
	i = 0;
	while (flag == 1 && i < len)
	{
		if (email[i] >= '0' && email[i] <= '9' || email[i] >= 'A' && email[i] <= 'Z' || email[i] >= 'a' && email[i] <= 'z' || email[i] == '@' || email[i] == '_' || email[i] == '.')
		//判断字符串中是否有非法字符 
		{ 
			if (flag_1 == 0)//“@”之前的字符
			{
				if (email[i] == '.')//只能包含数字字母下划线
				{
					flag = 0;
				}
				if (email[i] == '_')//两个下划线不能相连 
				{
					if (email[i + 1] == '_')
					{
						flag = 0;
					}
				}
			}
			if (email[i] == '@')//判断是否包含"@" 
			{
				flag_1 = 1;
			}
			if (flag_1 == 1)//包含"@"的情况下 
			{
				if (email[i] == '.')//判断"@"后是否有"." 
				{
					flag_2 = 1;
					if (email[i + 1] == '.')//如果两个"."连在一起则不符合要求 
					{
						flag = 0;
					}
				}
				
				if (email[i + 1] == '@')//如果出现两次"@"，判定为不符合要求
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
	
