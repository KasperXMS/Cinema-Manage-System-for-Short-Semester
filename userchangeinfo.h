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
	char filename[255];
	int choice = 0, flag = 1; 
	char newPassword1[MAX], newPassword2[MAX], newTel[MAX], newEmail[MAX];
	
	strncpy(filename, path, strlen(path) - 8);//copy, 14�ǳ�����λ������.exe��λ�� 
	strcat(filename, "accounts\\user\\");
	strcat(filename, username);//ƴ��
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
		printf("��ѡ��\n");
		printf("1. �޸�����\n");
		printf("2. �޸ĵ绰\n");
		printf("3. �޸�����\n");
		printf("4. ����\n");
		scanf("%d", &choice);
		
		switch(choice)
		{
			case 1:
					flag = 1;
					while(flag)
					{
						printf("�����������룺\n" );
						scanf("%s" , newPassword1);
						printf("���ٴ�ȷ�������룺\n");
						scanf("%s", newPassword2);
						if (strcmp(newPassword1, newPassword2) == 0)
						{
							if (judgeUsername(newPassword1) == 1)
							{
								if (strcmp(newPassword1, password) != 0)
								{
									strcpy(password, newPassword1);
									printf("�޸ĳɹ���\n");
									flag = 0;
								}
								else
								{
									printf("������ԭ������ͬ\n");
								}
							}
							else
							{
								printf("�Ƿ����룡\n");
							}
						}
						else
						{
							printf("�������벻һ������������\n"); 
						}
					}
					flag = 1;
					break;
			case 2:
					flag = 1;
					while(flag)
					{
						printf("�������µĵ绰:\n");
						scanf("%s", newTel);
						if (judgeTel(newTel) == 1)
						{
							if (strcmp(newTel, tel) != 0)
							{
								strcpy(tel, newTel);
								printf("�޸ĳɹ���\n"); 
								flag = 0;
							}
							else
							{
								printf("������ԭ�绰��ͬ\n");
							}
						}
						else
						{
							printf("�Ƿ����룡\n");
						}
					}
					flag = 1;
					break; 
			case 3:
					flag = 1;
					while(flag)
					{
						printf("�������µ����䣺\n");
						scanf("%s", newEmail);
						if (judgeEmail(newEmail) == 1)
						{
							if (strcmp(email, newEmail) != 0)
							{
								strcpy(email, newEmail);
								printf("�޸ĳɹ���\n");
								flag = 0;
							}
							else
							{
								printf("������ԭ������ͬ\n");
							}
						}
						else
						{
							printf("�Ƿ����룡\n");
						}
					}
					flag = 1;
					break;
			case 4:
					flag = 0;
					break;
			default:
					printf("�Ƿ����룡\n");
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

	
