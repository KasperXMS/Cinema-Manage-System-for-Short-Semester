#ifndef _USERCHANGEINFO_H
#define _USERCHANGEINFO_H

#include <stdio.h>
#include <string.h> 
#include "judge.h"
#define MAX 101
void changeInfo(char path[], char username[]);
void changeInfo(char path[], char username[])
{
	FILE *in, *out;
	char buff[255];
	char password[MAX]={'\0'};
	char NAME[MAX]={'\0'}, gender[10]={'\0'}, tel[MAX]={'\0'}, email[MAX]={'\0'};
	double remain=0.00;
	char filename[255]={'\0'};
	int choice = 0, flag = 1; 
	char newPassword1[MAX], newPassword2[MAX], newTel[MAX], newEmail[MAX];
	
	strncpy(filename, path, strlen(path) - 8);//copy, 14是程序名位数加上.exe的位数 
	strcat(filename, "accounts\\user\\");
	strcat(filename, username);//拼接
	strcat(filename, ".acc");
	in = fopen(filename, "r");
	
	fscanf(in, "%s", username);
	fscanf(in, "%s", NAME);
	fscanf(in, "%s", gender);
	fscanf(in, "%s", tel);
	fscanf(in, "%s", password);
	fscanf(in, "%s", email);
	fscanf(in, "%lf", &remain);
	
	while (flag)
	{
		printf("请选择：\n");
		printf("1. 修改密码\n");
		printf("2. 修改电话\n");
		printf("3. 修改邮箱\n");
		printf("4. 返回\n");
		scanf("%d", &choice);
		
		switch(choice)
		{
			case 1:
					flag = 1;
					while(flag)
					{
						printf("请输入新密码：\n" );
						scanf("%s" , newPassword1);
						printf("请再次确认新密码：\n");
						scanf("%s", newPassword2);
						if (strcmp(newPassword1, newPassword2) == 0)
						{
							if (judgeUsername(newPassword1) == 1)
							{
								if (strcmp(newPassword1, password) != 0)
								{
									strcpy(password, newPassword1);
									printf("修改成功！\n");
									flag = 0;
								}
								else
								{
									printf("不能与原密码相同\n");
								}
							}
							else
							{
								printf("非法输入！\n");
							}
						}
						else
						{
							printf("两次密码不一致请重新输入\n"); 
						}
					}
					flag = 1;
					break;
			case 2:
					flag = 1;
					while(flag)
					{
						printf("请输入新的电话:\n");
						scanf("%s", newTel);
						if (judgeTel(newTel) == 1)
						{
							if (strcmp(newTel, tel) != 0)
							{
								strcpy(tel, newTel);
								printf("修改成功！\n"); 
								flag = 0;
							}
							else
							{
								printf("不能与原电话相同\n");
							}
						}
						else
						{
							printf("非法输入！\n");
						}
					}
					flag = 1;
					break; 
			case 3:
					flag = 1;
					while(flag)
					{
						printf("请输入新的邮箱：\n");
						scanf("%s", newEmail);
						if (judgeEmail(newEmail) == 1)
						{
							if (strcmp(email, newEmail) != 0)
							{
								strcpy(email, newEmail);
								printf("修改成功！\n");
								flag = 0;
							}
							else
							{
								printf("不能与原邮箱相同\n");
							}
						}
						else
						{
							printf("非法输入！\n");
						}
					}
					flag = 1;
					break;
			case 4:
					flag = 0;
					break;
			default:
					printf("非法输入！\n");
		}
		fclose(in);
		if((out = fopen(filename, "w+"))!=NULL){
			fprintf(out, "%s\n", username);
		fprintf(out, "%s\n", NAME);
		fprintf(out, "%s\n", gender);
		fprintf(out, "%s\n", tel);
		fprintf(out, "%s\n", password);
		fprintf(out, "%s\n", email);
		fprintf(out, "%.2lf\n", remain);
		fclose(out);
		}
		else
		{
			fprintf(stderr, "Cannot open the file!\n");
		}
		
	}						 
	
}

#endif
/*int main(int argc, char *argv[])
{
	char username[20] = "zcy";
	changeInfo(argv[0], username);
	return 0;
}*/

	
