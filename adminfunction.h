#ifndef _ADMINFUNCTION_H
#define _ADMINFUNCTION_H

#include <stdio.h>
#include <string.h> 
#include "judge.h"
#define MAX 101

void Changeinfo(char path[], char username[]);
void Changeinfo(char path[], char username[])
{
	FILE *in, *out;
	char buff[255];
	char password[MAX]={'\0'};
	char NAME[MAX]={'\0'}, cinema[MAX]={'\0'}, email[MAX]={'\0'};
	double remain=0.00;
	char filename[MAX]={'\0'};
	int choice = 0, flag = 1; 
	char newPassword1[MAX], newPassword2[MAX], newEmail[MAX];
	
	strncpy(filename, path, strlen(path) - 8);//copy, 14�ǳ�����λ������.exe��λ�� 
	strcat(filename, "accounts\\admin\\");
	strcat(filename, username);//ƴ��
	strcat(filename, ".acc");
	in = fopen(filename, "r");
	
	fscanf(in, "%s", username);
	fscanf(in, "%s", cinema);
	fscanf(in, "%s", NAME);
	fscanf(in, "%s", email);
	fscanf(in, "%s", password);
	
	while (flag)
	{
		printf("��ѡ��\n");
		printf("1. �޸�����\n");
		printf("2. �޸�����\n");
		printf("3. ����\n");
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
			case 3:
					flag = 0;
					break;
			default:
					printf("�Ƿ����룡\n");
		}
		fclose(in);
		if((out = fopen(filename, "w+"))!=NULL){
		fprintf(out, "%s\n", username);
		fprintf(out, "%s\n", cinema);
		fprintf(out, "%s\n", NAME);
		fprintf(out, "%s\n", email);
		fprintf(out, "%s\n", password);
		fclose(out);
		}
		else
		{
			fprintf(stderr, "Cannot open the file!\n");
		}
		
	}						 
	
}







#endif
