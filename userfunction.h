#ifndef _USERFUNCTION_H
#define _USERFUNCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <windows.h>
#include "judge.h"
#define MAX 101
void changeInfo(char path[], char username[]);
void TopUp(char path[], char username[]);
void cst_find_cma(char path[]);

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

void TopUp(char path[], char username[])
{
	FILE *in, *out;
	char filename[MAX]={'\0'};
	char user1[MAX]={'\0'}, NAME[MAX]={'\0'}, gender[MAX]={'\0'}, password[MAX]={'\0'}, tel[MAX]={'\0'}, email[MAX]={'\0'};
	double remain=0, topup=0;
	char option='\0';
	strncpy(filename, path, strlen(path)-8);
	strcat(filename, "accounts\\user\\");
	strcat(filename, username);
	strcat(filename, ".acc");
	if((in=fopen(filename, "r"))!=NULL)
	{
		fscanf(in, "%s", user1);
		fscanf(in, "%s", NAME);
		fscanf(in, "%s", gender);
		fscanf(in, "%s", tel);
		fscanf(in, "%s", password);
		fscanf(in, "%s", email);
		fscanf(in, "%lf", &remain);
		fclose(in);
		printf("用户当前的余额为：%.2lf\n", remain);
		printf("请输入充值金额：");
		scanf("%lf", &topup);
		printf("确定要充值%.2lf元吗？是(Y)，否(N)\n", topup);
		getchar();
		scanf("%c", &option);
		switch(option)
		{
			case 'Y':
				remain=remain+topup; 
				out=fopen(filename, "w"); 
				fprintf(out, "%s\n", user1);
				fprintf(out, "%s\n", NAME);
				fprintf(out, "%s\n", gender);
				fprintf(out, "%s\n", tel);
				fprintf(out, "%s\n", password);
				fprintf(out, "%s\n", email);
				fprintf(out, "%lf\n", remain);
				if(fclose(out)!=0)
				{
					fprintf(stderr, "系统错误！\n");
				}
				else
				{
					printf("充值成功！您现在余额为：%.2lf\n", remain);
				}
				break;
			case 'N':
				printf("正退出充值页面...\n");
				break;
			default:
				printf("非法输入！\n"); 
		}
	}
	else
	{
		fprintf(stderr, "系统错误！\n");
	}
}

void cst_find_cma(char path[])
{
	getchar();
    char cma[20]={'\0'};
    printf("请输入你想要查找的影院：");
    gets(cma);
    char to_search[MAX]={'\0'}; //欲查找的文件，支持通配符
    strncpy(to_search, path, strlen(path)-8);
    strcat(to_search, "cma_info\\*.txt");
    long handle;                                       //用于查找的句柄
    struct _finddata_t fileinfo;                       //文件信息的结构体
    handle = _findfirst(to_search, &fileinfo);
    //printf("%s\n", fileinfo.name);
    //打开所遍历到的文件
    char pathA[255] = {'\0'};
    char filename[255] = {'\0'};
    char str[255] = {'\0'};
    strncpy(pathA, path, strlen(path)-9);
    strcat(cma, ".txt");
    int temp = 0;
    if (strcmp(fileinfo.name, cma) == 0)
    {
        temp = 1;
        wsprintf(filename, "\\cma_info\\%s", fileinfo.name);
        strcat(pathA, filename);
        FILE *fp = NULL;
        fp = fopen(pathA, "r");
        printf("此电影院的影片场次如下：\n");
        fgets(str, 255, (FILE *)fp);
        while (!feof(fp))
        {
            printf("%s", str);
            fgets(str, 255, (FILE *)fp);
        }
    }
    while (!_findnext(handle, &fileinfo)) //循环查找其他符合的文件，知道找不到其他的为止
    {
        //printf("%s\n", fileinfo.name);
        if (strcmp(cma, fileinfo.name) == 0)
        {
            temp = 1;
            memset(pathA, '\0', sizeof(pathA));
            strncpy(pathA, path, strlen(path)-9);
            wsprintf(filename, "\\cma_info\\%s", fileinfo.name);
            strcat(pathA, filename);
            FILE *fp = NULL;
            fp = fopen(pathA, "r");
            char str[255];
            printf("此电影院的影片场次如下：\n");
            fgets(str, 255, (FILE *)fp);
            while (!feof(fp))
            {
                printf("%s", str);
                fgets(str, 255, (FILE *)fp);
            }
        }
    }
    if (temp == 0)
    {
        printf("你输入的影院不存在");
    }
    _findclose(handle); //别忘了关闭句柄
}
#endif
/*int main(int argc, char *argv[])
{
	char username[20] = "zcy";
	changeInfo(argv[0], username);
	return 0;
}*/

	
