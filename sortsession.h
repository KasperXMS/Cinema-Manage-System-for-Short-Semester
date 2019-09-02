#ifndef _SORTSESSION_H
#define _SORTSESSION_H 


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <io.h>
#include "gadgets.h"
#define MAX_LENGTH_OF_LINE 1024
void SetPositionByLine(FILE *fp,int line);//���ļ�ָ�붨λ��ָ����
int cmpUp(const void *a, const void *b);//����qsort������������ 
int cmpDown(const void *a, const void *b);//����qsort������������
int cmpUpFloat(const void *a, const void *b);//����qsort��������Float�ͱ���
void TimeSort(char path[], char cinema[], char date[], char movie[], int opt);//����ӳʱ������(argv[0], ӰԺ��, ����(MMDD) )
void RemainSort(char path[], char cinema[], char date[], char movie[], int opt);//��ʣ��Ʊ������
void PriceSort(char path[], char cinema[], char date[], char movie[], int opt);//��Ʊ������
int cmpUp(const void *a, const void *b)
{
	return (*(int*)a - *(int*)b);
}
int cmpDown(const void *a, const void *b)
{
	return (*(int*)b - *(int*)a);
}
int cmpUpFloat(const void *a, const void *b)
{
	return (*(float*)a - *(float*)b);
}
typedef struct SESSION_INFO{
	char sessionNum[20];	//���α�� 
	char name[255];	//��Ӱ���� 
	char cinema[255];	//ӰԺ���� 
	char hallNum[5];	//Ӱ����
	int startTime;	//��ʼʱ�䣨���ӣ� 
	int endtime; 	//����ʱ�䣨���ӣ� 
	int length;		//��Ӱʱ�� 
	int totalseat;	//����λ 
	int remain;		//ʣ��Ʊ�� 
	float price;	//Ʊ�� 
	char language[10];	//����CHN/ENG... 
	char type[10];	//��Ӱ����
	float discount;	//�Ż����� 
}SESSION;
SESSION initialize();//��ʼ���ṹ�� 
void SetPositionByLine(FILE *fp,int line)
{   
    int i=0;
    char buffer[MAX_LENGTH_OF_LINE+1]={'\0'};
    fpos_t pos;
    rewind(fp);
    for(i=1;i<line;i++)
        fgets(buffer,MAX_LENGTH_OF_LINE,fp);
    fgetpos(fp,&pos);
}
SESSION initialize()
{
	SESSION session;
	memset(session.cinema, 0, sizeof(session.cinema));
	session.discount = 0;
	session.endtime = 0;
	memset(session.hallNum, 0, sizeof(session.hallNum));
	memset(session.language, 0, sizeof(session.language));
	session.length = 0;
	memset(session.name, 0, sizeof(session.name));
	session.price = 0;
	session.remain = 0;
	memset(session.sessionNum, 0, sizeof(session.sessionNum));
	session.startTime = 0;
	session.totalseat = 0;
	memset(session.type, 0, sizeof(session.type));
	return session;
}
void TimeSort(char path[], char cinema[], char date[], char movie[], int opt)
{
	int len = 0, i = 0, j = 0, k = 0, startTime2[20] = {0};
	char filePath[255] = {0}, filename[255] = {0}, filename_half_1[255] = {0},  filename_half_2[255] = {0}, startTimeStr[6] = {0}, endTimeStr[6] = {0};
	SESSION session = initialize();
	FILE *fp = NULL;
	if (opt == 1)
		strcpy(filename_half_1, date);
	else if (opt == 2)
	{
		strcpy(filename_half_1, cinema);
		strcat(filename_half_1, date);
	}
	else if (opt == 3)
	{
	strcpy(filename_half_1, cinema);
	strcat(filename_half_1, date);//�������ӰԺ�������ڱ��浽 filename_half_1
	}
	//����session_info�ļ���,�ҵ�����Ӱ�������ڵ��ļ�
	struct _finddata_t FileInfo;
	long Handle;
	strncpy(filePath, path, strlen(path) - 15);
	strcat(filePath, "session_info\\");
	strcat(filePath, "*.txt");//������Ϣ�ļ������ļ�·��
	if (opt == 1)
	{
		//�ҵ��ļ����еĵ�һ���ļ�����ȡ�ļ��� 
		if((Handle=_findfirst(filePath,&FileInfo))==-1L)
			printf("û���ҵ�ƥ�����Ŀ\n");
		else
		{
			strncpy(filename_half_2, FileInfo.name + 4, strlen(FileInfo.name) - 12);//����ǰ�ļ�����ӰԺ�����ڱ��浽filename_half_2
			if (strcmp(filename_half_1, filename_half_2) == 0) //��鵱ǰ�ļ�����ӰԺ��������֮ǰ������Ƿ�һ�� 
			{
				strncpy(filename, path, strlen(path) - 15);
				strcat(filename, "session_info\\");
				strcat(filename, FileInfo.name);
				fp = fopen(filename, "r");
				SetPositionByLine(fp, 2);
				fscanf(fp, "%s", session.name);
				if (strcmp(movie, session.name) == 0)
				{
					SetPositionByLine(fp, 5);//��λfp����5��
					fscanf(fp, "%s", startTimeStr);//����5�����ݱ��浽�ַ�������startTimeStr
					startTime2[i] = hhmm2min(startTimeStr);//��ʱ���ַ���ת�������������浽����startTime2[i]�� 
					i++;
				}
				fclose(fp);
			}
			//������������������ͬ�� 
			while(_findnext(Handle,&FileInfo)==0)
			{
				strncpy(filename_half_2, FileInfo.name + 4, strlen(FileInfo.name) - 12);
				if (strcmp(filename_half_1, filename_half_2) == 0)
				{
					memset(filename, 0, sizeof(filename));
					strncpy(filename, path, strlen(path) - 15);
					strcat(filename, "session_info\\");
					strcat(filename, FileInfo.name);
					fp = fopen(filename, "r");
					SetPositionByLine(fp, 2);
					fscanf(fp, "%s", session.name);
					if (strcmp(movie, session.name) == 0)
					{
						SetPositionByLine(fp, 5);
						fscanf(fp, "%s", startTimeStr);
						startTime2[i] = hhmm2min(startTimeStr); 
						i++;			
					}
					fclose(fp);
				}
			}
		}
		_findclose(Handle);
		
		qsort(startTime2, i, sizeof(int), cmpUp);//��������ʱ�������startTime2[i]������������ 
		printf("���α��      ӰƬ��         ӰԺ   Ӱ��   ����   ��ʼʱ��   ����ʱ��   ʱ��   ��λ��   ��Ʊ��   Ʊ��   ����   ӰƬ����   �ۿ���\n");
		//�����ļ��У�����Ϊ֮ǰ���浽startTime2[i]�еĴ�����Ȼ���ź�����������ζ�Ӧ�����ļ��ж�Ӧ�У����������ļ���� 
		while (j < i)
		{
			memset(filename, 0, sizeof(filename));
			if((Handle=_findfirst(filePath,&FileInfo))==-1L)
			printf("û���ҵ�ƥ�����Ŀ\n");
			else
			{	
				strncpy(filename_half_2, FileInfo.name + 4, strlen(FileInfo.name) - 12);
				if (strcmp(filename_half_1, filename_half_2) == 0) 
				{
					strncpy(filename, path, strlen(path) - 15);
					strcat(filename, "session_info\\");
					strcat(filename, FileInfo.name);
					fp = fopen(filename, "r");
					SetPositionByLine(fp, 2);
					fscanf(fp, "%s", session.name);
					if (strcmp(movie, session.name) == 0)
					{
						SetPositionByLine(fp, 1);
						fscanf(fp, "%s", session.sessionNum);
						fscanf(fp, "%s", session.name);
						fscanf(fp, "%s", session.cinema);
						fscanf(fp, "%s", session.hallNum);
						fscanf(fp, "%s", startTimeStr);
						session.startTime = hhmm2min(startTimeStr);
						if (session.startTime == startTime2[j])
						{
							fscanf(fp, "%s", endTimeStr);
							fscanf(fp, "%d", &session.length);
							fscanf(fp, "%d", &session.totalseat);
							fscanf(fp, "%d", &session.remain);
							fscanf(fp, "%f", &session.price);
							fscanf(fp, "%s", session.language);
							fscanf(fp, "%s", session.type);
							fscanf(fp, "%f", &session.discount);
							printf("%-14s%-15s%-7s%-7s%-7s%-11s%-11s%-7d%-9d%-9d%-7.2f%-7s%-11s%.1f\n", session.sessionNum, session.name, session.cinema, session.hallNum, date, startTimeStr, endTimeStr, session.length, session.totalseat, session.remain, session.price, session.language, session.type, session.discount);
							if (startTime2[j] == startTime2[j+1])
								k++;
							else
								j++;
						}
					}
					fclose(fp);	
				}	
				while(_findnext(Handle,&FileInfo)==0)
				{
					strncpy(filename_half_2, FileInfo.name + 4, strlen(FileInfo.name) - 12);
					if (strcmp(filename_half_1, filename_half_2) == 0) 
					{
						memset(filename, 0, sizeof(filename));
						strncpy(filename, path, strlen(path) - 15);
						strcat(filename, "session_info\\");
						strcat(filename, FileInfo.name);
						fp = fopen(filename, "r");
						SetPositionByLine(fp, 2);
						fscanf(fp, "%s", session.name);
						if (strcmp(movie, session.name) == 0)
						{
							SetPositionByLine(fp, 1);
							fscanf(fp, "%s", session.sessionNum);
							fscanf(fp, "%s", session.name);
							fscanf(fp, "%s", session.cinema);
							fscanf(fp, "%s", session.hallNum);
							fscanf(fp, "%s", startTimeStr);
							session.startTime = hhmm2min(startTimeStr);  
							if (session.startTime == startTime2[j])
							{
								fscanf(fp, "%s", endTimeStr);
								fscanf(fp, "%d", &session.length);
								fscanf(fp, "%d", &session.totalseat);
								fscanf(fp, "%d", &session.remain);
								fscanf(fp, "%f", &session.price);
								fscanf(fp, "%s", session.language);
								fscanf(fp, "%s", session.type);
								fscanf(fp, "%f", &session.discount);
								printf("%-14s%-15s%-7s%-7s%-7s%-11s%-11s%-7d%-9d%-9d%-7.2f%-7s%-11s%.1f\n", session.sessionNum, session.name, session.cinema, session.hallNum, date, startTimeStr, endTimeStr, session.length, session.totalseat, session.remain, session.price, session.language, session.type, session.discount);
								if (startTime2[j] == startTime2[j+1])
									k++;
								else
									j++;
							}
						}
						fclose(fp);
					} 
				}
			}
			_findclose(Handle);
			j += k;
		}
	}
	else if (opt == 2)
	{
		//�ҵ��ļ����еĵ�һ���ļ�����ȡ�ļ��� 
		if((Handle=_findfirst(filePath,&FileInfo))==-1L)
			printf("û���ҵ�ƥ�����Ŀ\n");
		else
		{
			strncpy(filename_half_2, FileInfo.name, strlen(FileInfo.name) - 8);//����ǰ�ļ�����ӰԺ�����ڱ��浽filename_half_2
			if (strcmp(filename_half_1, filename_half_2) == 0) //��鵱ǰ�ļ�����ӰԺ��������֮ǰ������Ƿ�һ�� 
			{
				strncpy(filename, path, strlen(path) - 15);
				strcat(filename, "session_info\\");
				strcat(filename, FileInfo.name);
				fp = fopen(filename, "r");
				SetPositionByLine(fp, 2);
				fscanf(fp, "%s", session.name);
				if (strcmp(movie, session.name) == 0)
				{
					SetPositionByLine(fp, 5);//��λfp����5��
					fscanf(fp, "%s", startTimeStr);//����5�����ݱ��浽�ַ�������startTimeStr
					startTime2[i] = hhmm2min(startTimeStr);//��ʱ���ַ���ת�������������浽����startTime2[i]�� 
					i++;
				}
				fclose(fp);
				//������������������ͬ�� 
				while(_findnext(Handle,&FileInfo)==0)
				{
					strncpy(filename_half_2, FileInfo.name, strlen(FileInfo.name) - 8);
					if (strcmp(filename_half_1, filename_half_2) == 0)
					{
						memset(filename, 0, sizeof(filename));
						strncpy(filename, path, strlen(path) - 15);
						strcat(filename, "session_info\\");
						strcat(filename, FileInfo.name);
						fp = fopen(filename, "r");
						SetPositionByLine(fp, 2);
						fscanf(fp, "%s", session.name);
						if (strcmp(movie, session.name) == 0)
						{
							SetPositionByLine(fp, 5);
							fscanf(fp, "%s", startTimeStr);
							startTime2[i] = hhmm2min(startTimeStr); 
							i++;			
						}
						fclose(fp);
					}
				}
			}
		}
		_findclose(Handle);
		qsort(startTime2, i, sizeof(int), cmpUp);//��������ʱ�������startTime2[i]������������ 
		printf("���α��      ӰƬ��         ӰԺ   Ӱ��   ����   ��ʼʱ��   ����ʱ��   ʱ��   ��λ��   ��Ʊ��   Ʊ��   ����   ӰƬ����   �ۿ���\n");
		//�����ļ��У�����Ϊ֮ǰ���浽startTime2[i]�еĴ�����Ȼ���ź�����������ζ�Ӧ�����ļ��ж�Ӧ�У����������ļ���� 
		while (j < i)
		{
			memset(filename, 0, sizeof(filename));
			if((Handle=_findfirst(filePath,&FileInfo))==-1L)
			printf("û���ҵ�ƥ�����Ŀ\n");
			else
			{	
				strncpy(filename_half_2, FileInfo.name, strlen(FileInfo.name) - 8);
				if (strcmp(filename_half_1, filename_half_2) == 0) 
				{
					strncpy(filename, path, strlen(path) - 15);
					strcat(filename, "session_info\\");
					strcat(filename, FileInfo.name);
					fp = fopen(filename, "r");
					SetPositionByLine(fp, 2);
					fscanf(fp, "%s", session.name);
					if (strcmp(movie, session.name) == 0)
					{
						SetPositionByLine(fp, 1);
						fscanf(fp, "%s", session.sessionNum);
						fscanf(fp, "%s", session.name);
						fscanf(fp, "%s", session.cinema);
						fscanf(fp, "%s", session.hallNum);
						fscanf(fp, "%s", startTimeStr);
						session.startTime = hhmm2min(startTimeStr);
						if (session.startTime == startTime2[j])
						{
							fscanf(fp, "%s", endTimeStr);
							fscanf(fp, "%d", &session.length);
							fscanf(fp, "%d", &session.totalseat);
							fscanf(fp, "%d", &session.remain);
							fscanf(fp, "%f", &session.price);
							fscanf(fp, "%s", session.language);
							fscanf(fp, "%s", session.type);
							fscanf(fp, "%f", &session.discount);
							printf("%-14s%-15s%-7s%-7s%-7s%-11s%-11s%-7d%-9d%-9d%-7.2f%-7s%-11s%.1f\n", session.sessionNum, session.name, session.cinema, session.hallNum, date, startTimeStr, endTimeStr, session.length, session.totalseat, session.remain, session.price, session.language, session.type, session.discount);
							if (startTime2[j] == startTime2[j+1])
								k++;
							else
								j++;
						}
					}
				}
			}
			fclose(fp);
			while(_findnext(Handle,&FileInfo)==0)
			{
				strncpy(filename_half_2, FileInfo.name, strlen(FileInfo.name) - 8);
				if (strcmp(filename_half_1, filename_half_2) == 0)
				{
					memset(filename, 0, sizeof(filename));
					strncpy(filename, path, strlen(path) - 15);
					strcat(filename, "session_info\\");
					strcat(filename, FileInfo.name);
					fp = fopen(filename, "r");
					SetPositionByLine(fp, 2);
					fscanf(fp, "%s", session.name);
					if (strcmp(movie, session.name) == 0)
					{
						SetPositionByLine(fp, 1);
						fscanf(fp, "%s", session.sessionNum);
						fscanf(fp, "%s", session.name);
						fscanf(fp, "%s", session.cinema);
						fscanf(fp, "%s", session.hallNum);
						fscanf(fp, "%s", startTimeStr);
						session.startTime = hhmm2min(startTimeStr);  
						if (session.startTime == startTime2[j])
						{
							fscanf(fp, "%s", endTimeStr);
							fscanf(fp, "%d", &session.length);
							fscanf(fp, "%d", &session.totalseat);
							fscanf(fp, "%d", &session.remain);
							fscanf(fp, "%f", &session.price);
							fscanf(fp, "%s", session.language);
							fscanf(fp, "%s", session.type);
							fscanf(fp, "%f", &session.discount);
							printf("%-14s%-15s%-7s%-7s%-7s%-11s%-11s%-7d%-9d%-9d%-7.2f%-7s%-11s%.1f\n", session.sessionNum, session.name, session.cinema, session.hallNum, date, startTimeStr, endTimeStr, session.length, session.totalseat, session.remain, session.price, session.language, session.type, session.discount);
							if (startTime2[j] == startTime2[j+1])
								k++;
							else
								j++;
						}
					}
					fclose(fp);			
				}
			}
			_findclose(Handle);
			j += k;
		}
	}
	else if (opt == 3)
	{ 
		//�ҵ��ļ����еĵ�һ���ļ�����ȡ�ļ��� 
		if((Handle=_findfirst(filePath,&FileInfo))==-1L)
			printf("û���ҵ�ƥ�����Ŀ\n");
		else
		{
			strncpy(filename_half_2, FileInfo.name, strlen(FileInfo.name) - 8);//����ǰ�ļ�����ӰԺ�����ڱ��浽filename_half_2
			if (strcmp(filename_half_1, filename_half_2) == 0) //��鵱ǰ�ļ�����ӰԺ��������֮ǰ������Ƿ�һ�� 
			{
				strncpy(filename, path, strlen(path) - 15);
				strcat(filename, "session_info\\");
				strcat(filename, FileInfo.name);
				fp = fopen(filename, "r");
				SetPositionByLine(fp, 5);//��λfp����5��
				fscanf(fp, "%s", startTimeStr);//����5�����ݱ��浽�ַ�������startTimeStr
				startTime2[i] = hhmm2min(startTimeStr);//��ʱ���ַ���ת�������������浽����startTime2[i]�� 
				fclose(fp);
				i++;
			}
			//������������������ͬ�� 
			while(_findnext(Handle,&FileInfo)==0)
			{
				strncpy(filename_half_2, FileInfo.name, strlen(FileInfo.name) - 8);
				if (strcmp(filename_half_1, filename_half_2) == 0)
				{
					memset(filename, 0, sizeof(filename));
					strncpy(filename, path, strlen(path) - 15);
					strcat(filename, "session_info\\");
					strcat(filename, FileInfo.name);
					fp = fopen(filename, "r");
					SetPositionByLine(fp, 5);
					fscanf(fp, "%s", startTimeStr);
					startTime2[i] = hhmm2min(startTimeStr); 
					fclose(fp);
					i++;			
				}
			}
			_findclose(Handle);
		}
		
		qsort(startTime2, i, sizeof(int), cmpUp);//��������ʱ�������startTime2[i]������������ 
		printf("���α��      ӰƬ��         ӰԺ   Ӱ��   ����   ��ʼʱ��   ����ʱ��   ʱ��   ��λ��   ��Ʊ��   Ʊ��   ����   ӰƬ����   �ۿ���\n");
		//�����ļ��У�����Ϊ֮ǰ���浽startTime2[i]�еĴ�����Ȼ���ź�����������ζ�Ӧ�����ļ��ж�Ӧ�У����������ļ���� 
		while (j < i)
		{
			memset(filename, 0, sizeof(filename));
			if((Handle=_findfirst(filePath,&FileInfo))==-1L)
			printf("û���ҵ�ƥ�����Ŀ\n");
			else
			{	
				strncpy(filename_half_2, FileInfo.name, strlen(FileInfo.name) - 8);
				if (strcmp(filename_half_1, filename_half_2) == 0) 
				{
					strncpy(filename, path, strlen(path) - 15);
					strcat(filename, "session_info\\");
					strcat(filename, FileInfo.name);
					fp = fopen(filename, "r");
					fscanf(fp, "%s", session.sessionNum);
					fscanf(fp, "%s", session.name);
					fscanf(fp, "%s", session.cinema);
					fscanf(fp, "%s", session.hallNum);
					fscanf(fp, "%s", startTimeStr);
					session.startTime = hhmm2min(startTimeStr);
					if (session.startTime == startTime2[j])
					{
						fscanf(fp, "%s", endTimeStr);
						fscanf(fp, "%d", &session.length);
						fscanf(fp, "%d", &session.totalseat);
						fscanf(fp, "%d", &session.remain);
						fscanf(fp, "%f", &session.price);
						fscanf(fp, "%s", session.language);
						fscanf(fp, "%s", session.type);
						fscanf(fp, "%f", &session.discount);
						printf("%-14s%-15s%-7s%-7s%-7s%-11s%-11s%-7d%-9d%-9d%-7.2f%-7s%-11s%.1f\n", session.sessionNum, session.name, session.cinema, session.hallNum, date, startTimeStr, endTimeStr, session.length, session.totalseat, session.remain, session.price, session.language, session.type, session.discount);
						if (startTime2[j] == startTime2[j+1])
							k++;
						else
							j++;
					}
					fclose(fp);
				
				}
				while(_findnext(Handle,&FileInfo)==0)
				{
					strncpy(filename_half_2, FileInfo.name, strlen(FileInfo.name) - 8);
					if (strcmp(filename_half_1, filename_half_2) == 0)
					{
						memset(filename, 0, sizeof(filename));
						strncpy(filename, path, strlen(path) - 15);
						strcat(filename, "session_info\\");
						strcat(filename, FileInfo.name);
						fp = fopen(filename, "r");
						fscanf(fp, "%s", session.sessionNum);
						fscanf(fp, "%s", session.name);
						fscanf(fp, "%s", session.cinema);
						fscanf(fp, "%s", session.hallNum);
						fscanf(fp, "%s", startTimeStr);
						session.startTime = hhmm2min(startTimeStr);  
						if (session.startTime == startTime2[j])
						{
							fscanf(fp, "%s", endTimeStr);
							fscanf(fp, "%d", &session.length);
							fscanf(fp, "%d", &session.totalseat);
							fscanf(fp, "%d", &session.remain);
							fscanf(fp, "%f", &session.price);
							fscanf(fp, "%s", session.language);
							fscanf(fp, "%s", session.type);
							fscanf(fp, "%f", &session.discount);
							printf("%-14s%-15s%-7s%-7s%-7s%-11s%-11s%-7d%-9d%-9d%-7.2f%-7s%-11s%.1f\n", session.sessionNum, session.name, session.cinema, session.hallNum, date, startTimeStr, endTimeStr, session.length, session.totalseat, session.remain, session.price, session.language, session.type, session.discount);
							if (startTime2[j] == startTime2[j+1])
								k++;
							else
								j++;
						}
						fclose(fp);			
					}
				}
			}
			_findclose(Handle);
			j += k;
		}	
	} 
}
void RemainSort(char path[], char cinema[], char date[], char movie[], int opt)
{
	int len = 0, i = 0, j = 0, k =0, remain2[20] = {0};
	char filePath[255] = {0}, filename[255] = {0}, filename_half_1[255] = {0},  filename_half_2[255] = {0}, startTimeStr[6] = {0}, endTimeStr[6] = {0};
	SESSION session = initialize();
	FILE *fp = NULL;
	if (opt == 1)
		strcpy(filename_half_1, date);
	else if (opt == 2)
	{
		strcpy(filename_half_1, cinema);
		strcat(filename_half_1, date);
	}
	else if (opt == 3)
	{
	strcpy(filename_half_1, cinema);
	strcat(filename_half_1, date);//�������ӰԺ�������ڱ��浽 filename_half_1
	}
	
	//����session_info�ļ���,�ҵ�����Ӱ�������ڵ��ļ�
	struct _finddata_t FileInfo;
	long Handle;
	strncpy(filePath, path, strlen(path) - 15);
	strcat(filePath, "session_info\\");
	strcat(filePath, "*.txt");//������Ϣ�ļ������ļ�·��
	if (opt == 1)
	{ 
		//�ҵ��ļ����еĵ�һ���ļ�����ȡ�ļ��� 
		if((Handle=_findfirst(filePath,&FileInfo))==-1L)
			printf("û���ҵ�ƥ�����Ŀ\n");
		else
		{
			strncpy(filename_half_2, FileInfo.name + 4, strlen(FileInfo.name) - 12);
			if (strcmp(filename_half_1, filename_half_2) == 0)
			{
				strncpy(filename, path, strlen(path) - 15);
				strcat(filename, "session_info\\");
				strcat(filename, FileInfo.name);
				fp = fopen(filename, "r");
				SetPositionByLine(fp, 2);
				fscanf(fp, "%s", session.name);
				if (strcmp(movie, session.name) == 0)
				{
					SetPositionByLine(fp, 9);//��λfp����9��
					fscanf(fp, "%d", &remain2[i]);//����9�����ݱ�������remain2[i]��
					i++;
				}
				fclose(fp);
			} 
			//������������������ͬ�� 
			while(_findnext(Handle,&FileInfo)==0)
			{
				strncpy(filename_half_2, FileInfo.name + 4, strlen(FileInfo.name) - 12);
				if (strcmp(filename_half_1, filename_half_2) == 0) 
				{
					memset(filename, 0, sizeof(filename));
					strncpy(filename, path, strlen(path) - 15);
					strcat(filename, "session_info\\");
					strcat(filename, FileInfo.name);
					fp = fopen(filename, "r");
					SetPositionByLine(fp, 2);
					fscanf(fp, "%s", session.name);
					if (strcmp(movie, session.name) == 0)
					{
						SetPositionByLine(fp, 9);
						fscanf(fp, "%d", &remain2[i]);
						i++;			
					}
					fclose(fp);
				} 
			}
		}
		_findclose(Handle);
		qsort(remain2, i, sizeof(int), cmpDown);//����������Ʊ��������remain2[i]���н������� 
		printf("���α��      ӰƬ��         ӰԺ   Ӱ��   ����   ��ʼʱ��   ����ʱ��   ʱ��   ��λ��   ��Ʊ��   Ʊ��   ����   ӰƬ����   �ۿ���\n");
		//�����ļ��У�����Ϊ֮ǰ���浽remain2[i]�еĴ�����Ȼ���ź�����������ζ�Ӧ�����ļ��ж�Ӧ�У����������ļ���� 
		while (j < i)
		{
			memset(filename, 0, sizeof(filename));
			if((Handle=_findfirst(filePath,&FileInfo))==-1L)
			printf("û���ҵ�ƥ�����Ŀ\n");
			else
			{	
				strncpy(filename_half_2, FileInfo.name + 4, strlen(FileInfo.name) - 12);
				if (strcmp(filename_half_1, filename_half_2) == 0) 
				{
					strncpy(filename, path, strlen(path) - 15);
					strcat(filename, "session_info\\");
					strcat(filename, FileInfo.name);
					fp = fopen(filename, "r");
					SetPositionByLine(fp, 2);
					fscanf(fp, "%s", session.name);
					if (strcmp(movie, session.name) == 0)
					{
						SetPositionByLine(fp, 1);
						fscanf(fp, "%s", session.sessionNum);
						fscanf(fp, "%s", session.name);
						fscanf(fp, "%s", session.cinema);
						fscanf(fp, "%s", session.hallNum);
						fscanf(fp, "%s", startTimeStr);
						fscanf(fp, "%s", endTimeStr);					
						fscanf(fp, "%d", &session.length);
						fscanf(fp, "%d", &session.totalseat);
						fscanf(fp, "%d", &session.remain);
						if (session.remain == remain2[j])
						{
							fscanf(fp, "%f", &session.price);
							fscanf(fp, "%s", session.language);
							fscanf(fp, "%s", session.type);
							fscanf(fp, "%f", &session.discount);
							printf("%-14s%-15s%-7s%-7s%-7s%-11s%-11s%-7d%-9d%-9d%-7.2f%-7s%-11s%.1f\n", session.sessionNum, session.name, session.cinema, session.hallNum, date, startTimeStr, endTimeStr, session.length, session.totalseat, session.remain, session.price, session.language, session.type, session.discount);
							if (remain2[j] == remain2[j+1])
								k++;
							else
								j++;
						}	
					}
					fclose(fp);
				} 
				while(_findnext(Handle,&FileInfo)==0)
				{
					strncpy(filename_half_2, FileInfo.name + 4, strlen(FileInfo.name) - 12);
					if (strcmp(filename_half_1, filename_half_2) == 0) 
					{
						memset(filename, 0, sizeof(filename));
						strncpy(filename, path, strlen(path) - 15);
						strcat(filename, "session_info\\");
						strcat(filename, FileInfo.name);
						fp = fopen(filename, "r");
						SetPositionByLine(fp, 2);
						fscanf(fp, "%s", session.name);
						if (strcmp(movie, session.name) == 0)
						{
							SetPositionByLine(fp, 1);
							fscanf(fp, "%s", session.sessionNum);
							fscanf(fp, "%s", session.name);
							fscanf(fp, "%s", session.cinema);
							fscanf(fp, "%s", session.hallNum);
							fscanf(fp, "%s", startTimeStr);
							fscanf(fp, "%s", endTimeStr);					
							fscanf(fp, "%d", &session.length);
							fscanf(fp, "%d", &session.totalseat);
							fscanf(fp, "%d", &session.remain);
							if (session.remain == remain2[j])
							{
								fscanf(fp, "%f", &session.price);
								fscanf(fp, "%s", session.language);
								fscanf(fp, "%s", session.type);
								fscanf(fp, "%f", &session.discount);
								printf("%-14s%-15s%-7s%-7s%-7s%-11s%-11s%-7d%-9d%-9d%-7.2f%-7s%-11s%.1f\n", session.sessionNum, session.name, session.cinema, session.hallNum, date, startTimeStr, endTimeStr, session.length, session.totalseat, session.remain, session.price, session.language, session.type, session.discount);
								if (remain2[j] == remain2[j+1])
									k++;
								else
									j++;
							}
						}
						fclose(fp);	
					}		
				}
			}
			_findclose(Handle);
			j += k;
		}
	}
	else if (opt == 2)
	{ 
		//�ҵ��ļ����еĵ�һ���ļ�����ȡ�ļ��� 
		if((Handle=_findfirst(filePath,&FileInfo))==-1L)
			printf("û���ҵ�ƥ�����Ŀ\n");
		else
		{
			strncpy(filename_half_2, FileInfo.name, strlen(FileInfo.name) - 8);//����ǰ�ļ�����ӰԺ�����ڱ��浽filename_half_2
			if (strcmp(filename_half_1, filename_half_2) == 0) //��鵱ǰ�ļ�����ӰԺ��������֮ǰ������Ƿ�һ�� 
			{
				strncpy(filename, path, strlen(path) - 15);
				strcat(filename, "session_info\\");
				strcat(filename, FileInfo.name);
				fp = fopen(filename, "r");
				SetPositionByLine(fp, 2);
				fscanf(fp, "%s", session.name);
				if (strcmp(movie, session.name) == 0)
				{
					SetPositionByLine(fp, 9);//��λfp����9��
					fscanf(fp, "%d", &remain2[i]);//����9�����ݱ�������remain2[i]��
					i++;
				}
				fclose(fp);
			}
			//������������������ͬ�� 
			while(_findnext(Handle,&FileInfo)==0)
			{
				strncpy(filename_half_2, FileInfo.name, strlen(FileInfo.name) - 8);//����ǰ�ļ�����ӰԺ�����ڱ��浽filename_half_2
				if (strcmp(filename_half_1, filename_half_2) == 0) //��鵱ǰ�ļ�����ӰԺ��������֮ǰ������Ƿ�һ�� 
				{
					memset(filename, 0, sizeof(filename));
					strncpy(filename, path, strlen(path) - 15);
					strcat(filename, "session_info\\");
					strcat(filename, FileInfo.name);
					fp = fopen(filename, "r");
					SetPositionByLine(fp, 2);
					fscanf(fp, "%s", session.name);
					if (strcmp(movie, session.name) == 0)
					{
						SetPositionByLine(fp, 9);
						fscanf(fp, "%d", &remain2[i]);
						i++;			
					}
					fclose(fp);
				}
			}
			_findclose(Handle);
		}
		qsort(remain2, i, sizeof(int), cmpDown);//����������Ʊ��������remain2[i]���н������� 
		printf("���α��      ӰƬ��         ӰԺ   Ӱ��   ����   ��ʼʱ��   ����ʱ��   ʱ��   ��λ��   ��Ʊ��   Ʊ��   ����   ӰƬ����   �ۿ���\n");
		//�����ļ��У�����Ϊ֮ǰ���浽remain2[i]�еĴ�����Ȼ���ź�����������ζ�Ӧ�����ļ��ж�Ӧ�У����������ļ���� 
		while (j < i)
		{
			memset(filename, 0, sizeof(filename));
			if((Handle=_findfirst(filePath,&FileInfo))==-1L)
			printf("û���ҵ�ƥ�����Ŀ\n");
			else
			{	
				strncpy(filename_half_2, FileInfo.name, strlen(FileInfo.name) - 8);//����ǰ�ļ�����ӰԺ�����ڱ��浽filename_half_2
				if (strcmp(filename_half_1, filename_half_2) == 0) //��鵱ǰ�ļ�����ӰԺ��������֮ǰ������Ƿ�һ�� 
				{
					strncpy(filename, path, strlen(path) - 15);
					strcat(filename, "session_info\\");
					strcat(filename, FileInfo.name);
					fp = fopen(filename, "r");
					SetPositionByLine(fp, 2);
					fscanf(fp, "%s", session.name);
					if (strcmp(movie, session.name) == 0)
					{
						SetPositionByLine(fp, 1);
						fscanf(fp, "%s", session.sessionNum);
						fscanf(fp, "%s", session.name);
						fscanf(fp, "%s", session.cinema);
						fscanf(fp, "%s", session.hallNum);
						fscanf(fp, "%s", startTimeStr);
						fscanf(fp, "%s", endTimeStr);					
						fscanf(fp, "%d", &session.length);
						fscanf(fp, "%d", &session.totalseat);
						fscanf(fp, "%d", &session.remain);
						if (session.remain == remain2[j])
						{
							fscanf(fp, "%f", &session.price);
							fscanf(fp, "%s", session.language);
							fscanf(fp, "%s", session.type);
							fscanf(fp, "%f", &session.discount);
							printf("%-14s%-15s%-7s%-7s%-7s%-11s%-11s%-7d%-9d%-9d%-7.2f%-7s%-11s%.1f\n", session.sessionNum, session.name, session.cinema, session.hallNum, date, startTimeStr, endTimeStr, session.length, session.totalseat, session.remain, session.price, session.language, session.type, session.discount);
							if (remain2[j] == remain2[j+1])
								k++;
							else
								j++;
						}	
					}
					fclose(fp);
				}
			}
			while(_findnext(Handle,&FileInfo)==0)
			{
				strncpy(filename_half_2, FileInfo.name, strlen(FileInfo.name) - 8);//����ǰ�ļ�����ӰԺ�����ڱ��浽filename_half_2
				if (strcmp(filename_half_1, filename_half_2) == 0) //��鵱ǰ�ļ�����ӰԺ��������֮ǰ������Ƿ�һ�� 
				{
					memset(filename, 0, sizeof(filename));
					strncpy(filename, path, strlen(path) - 15);
					strcat(filename, "session_info\\");
					strcat(filename, FileInfo.name);
					fp = fopen(filename, "r");
					SetPositionByLine(fp, 2);
					fscanf(fp, "%s", session.name);
					if (strcmp(movie, session.name) == 0)
					{
						SetPositionByLine(fp, 1);
						fscanf(fp, "%s", session.sessionNum);
						fscanf(fp, "%s", session.name);
						fscanf(fp, "%s", session.cinema);
						fscanf(fp, "%s", session.hallNum);
						fscanf(fp, "%s", startTimeStr);
						fscanf(fp, "%s", endTimeStr);					
						fscanf(fp, "%d", &session.length);
						fscanf(fp, "%d", &session.totalseat);
						fscanf(fp, "%d", &session.remain);
						if (session.remain == remain2[j])
						{
							fscanf(fp, "%f", &session.price);
							fscanf(fp, "%s", session.language);
							fscanf(fp, "%s", session.type);
							fscanf(fp, "%f", &session.discount);
							printf("%-14s%-15s%-7s%-7s%-7s%-11s%-11s%-7d%-9d%-9d%-7.2f%-7s%-11s%.1f\n", session.sessionNum, session.name, session.cinema, session.hallNum, date, startTimeStr, endTimeStr, session.length, session.totalseat, session.remain, session.price, session.language, session.type, session.discount);
							if (remain2[j] == remain2[j+1])
								k++;
							else
								j++;
						}
					}
				}
				fclose(fp);			
			}
			_findclose(Handle);
			j += k;
		}
	}
	else if (opt == 3)
	{
		//�ҵ��ļ����еĵ�һ���ļ�����ȡ�ļ��� 
		if((Handle=_findfirst(filePath,&FileInfo))==-1L)
			printf("û���ҵ�ƥ�����Ŀ\n");
		else
		{
			strncpy(filename_half_2, FileInfo.name, strlen(FileInfo.name) - 8);//����ǰ�ļ�����ӰԺ�����ڱ��浽filename_half_2
			if (strcmp(filename_half_1, filename_half_2) == 0) //��鵱ǰ�ļ�����ӰԺ��������֮ǰ������Ƿ�һ�� 
			{
				strncpy(filename, path, strlen(path) - 15);
				strcat(filename, "session_info\\");
				strcat(filename, FileInfo.name);
				fp = fopen(filename, "r");
				SetPositionByLine(fp, 9);//��λfp����9��
				fscanf(fp, "%d", &remain2[i]);//����9�����ݱ�������remain2[i]��
				fclose(fp);
				i++;
			}
			//������������������ͬ�� 
			while(_findnext(Handle,&FileInfo)==0)
			{
				strncpy(filename_half_2, FileInfo.name, strlen(FileInfo.name) - 8);
				if (strcmp(filename_half_1, filename_half_2) == 0)
				{
					memset(filename, 0, sizeof(filename));
					strncpy(filename, path, strlen(path) - 15);
					strcat(filename, "session_info\\");
					strcat(filename, FileInfo.name);
					fp = fopen(filename, "r");
					SetPositionByLine(fp, 9);
					fscanf(fp, "%d", &remain2[i]);
					fclose(fp);
					i++;			
				}
			}
		}
		_findclose(Handle);
		qsort(remain2, i, sizeof(int), cmpDown);//�������˼۸������remain2[i]���н������� 
		printf("���α��      ӰƬ��         ӰԺ   Ӱ��   ����   ��ʼʱ��   ����ʱ��   ʱ��   ��λ��   ��Ʊ��   Ʊ��   ����   ӰƬ����   �ۿ���\n");
		//�����ļ��У�����Ϊ֮ǰ���浽remain2[i]�еĴ�����Ȼ���ź�����������ζ�Ӧ�����ļ��ж�Ӧ�У����������ļ���� 
		while (j < i)
		{
			k = 0;
			memset(filename, 0, sizeof(filename));
			if((Handle=_findfirst(filePath,&FileInfo))==-1L)
			printf("û���ҵ�ƥ�����Ŀ\n");
			else
			{	
				strncpy(filename_half_2, FileInfo.name, strlen(FileInfo.name) - 8);
				if (strcmp(filename_half_1, filename_half_2) == 0) 
				{
					strncpy(filename, path, strlen(path) - 15);
					strcat(filename, "session_info\\");
					strcat(filename, FileInfo.name);
					fp = fopen(filename, "r");
					fscanf(fp, "%s", session.sessionNum);
					fscanf(fp, "%s", session.name);
					fscanf(fp, "%s", session.cinema);
					fscanf(fp, "%s", session.hallNum);
					fscanf(fp, "%s", startTimeStr);
					fscanf(fp, "%s", endTimeStr);					
					fscanf(fp, "%d", &session.length);
					fscanf(fp, "%d", &session.totalseat);
					fscanf(fp, "%d", &session.remain);
					if (session.remain == remain2[j])
					{
						fscanf(fp, "%f", &session.price);
						fscanf(fp, "%s", session.language);
						fscanf(fp, "%s", session.type);
						fscanf(fp, "%f", &session.discount);
						printf("%-14s%-15s%-7s%-7s%-7s%-11s%-11s%-7d%-9d%-9d%-7.2f%-7s%-11s%.1f\n", session.sessionNum, session.name, session.cinema, session.hallNum, date, startTimeStr, endTimeStr, session.length, session.totalseat, session.remain, session.price, session.language, session.type, session.discount);
						if (remain2[j] == remain2[j+1])
							k++;
						else
							j++;
					}
					fclose(fp);
				
				}
				while(_findnext(Handle,&FileInfo)==0)
				{
					strncpy(filename_half_2, FileInfo.name, strlen(FileInfo.name) - 8);
					if (strcmp(filename_half_1, filename_half_2) == 0)
					{
						memset(filename, 0, sizeof(filename));
						strncpy(filename, path, strlen(path) - 15);
						strcat(filename, "session_info\\");
						strcat(filename, FileInfo.name);
						fp = fopen(filename, "r");
						fscanf(fp, "%s", session.sessionNum);
						fscanf(fp, "%s", session.name);
						fscanf(fp, "%s", session.cinema);
						fscanf(fp, "%s", session.hallNum);
						fscanf(fp, "%s", startTimeStr);
						fscanf(fp, "%s", endTimeStr);					
						fscanf(fp, "%d", &session.length);
						fscanf(fp, "%d", &session.totalseat);
						fscanf(fp, "%d", &session.remain);
						if (session.remain == remain2[j])
						{
							fscanf(fp, "%f", &session.price);
							fscanf(fp, "%s", session.language);
							fscanf(fp, "%s", session.type);
							fscanf(fp, "%f", &session.discount);
							printf("%-14s%-15s%-7s%-7s%-7s%-11s%-11s%-7d%-9d%-9d%-7.2f%-7s%-11s%.1f\n", session.sessionNum, session.name, session.cinema, session.hallNum, date, startTimeStr, endTimeStr, session.length, session.totalseat, session.remain, session.price, session.language, session.type, session.discount);
							if (remain2[j] == remain2[j+1])
								k++;
							else
								j++;
						}
						fclose(fp);			
					}
				}
			}
			_findclose(Handle);
			j += k;	
		}
	}
}
void PriceSort(char path[], char cinema[], char date[], char movie[], int opt)
{
	int len = 0, i = 0, j = 0, k = 0;
	float price2[20] = {0};
	char filePath[255] = {0}, filename[255] = {0}, filename_half_1[255] = {0},  filename_half_2[255] = {0}, startTimeStr[6] = {0}, endTimeStr[6] = {0};
	SESSION session = initialize();
	FILE *fp = NULL;
	if (opt == 1)
		strcpy(filename_half_1, date);
	else if (opt == 2)
	{
		strcpy(filename_half_1, cinema);
		strcat(filename_half_1, date);
	}
	else if (opt == 3)
	{
		strcpy(filename_half_1, cinema);
		strcat(filename_half_1, date);//�������ӰԺ�������ڱ��浽 filename_half_1
	}
	//����session_info�ļ���,�ҵ�����Ӱ�������ڵ��ļ�
	struct _finddata_t FileInfo;
	long Handle;
	strncpy(filePath, path, strlen(path) - 15);
	strcat(filePath, "session_info\\");
	strcat(filePath, "*.txt");//������Ϣ�ļ������ļ�·��
	if (opt == 1)
	{
		//�ҵ��ļ����еĵ�һ���ļ�����ȡ�ļ��� 
		if((Handle=_findfirst(filePath,&FileInfo))==-1L)
			printf("û���ҵ�ƥ�����Ŀ\n");
		else
		{
			strncpy(filename_half_2, FileInfo.name + 4, strlen(FileInfo.name) - 12);
			if (strcmp(filename_half_1, filename_half_2) == 0)
			{
				strncpy(filename, path, strlen(path) - 15);
				strcat(filename, "session_info\\");
				strcat(filename, FileInfo.name);
				fp = fopen(filename, "r");
				SetPositionByLine(fp, 2);
				fscanf(fp, "%s", session.name);
				if (strcmp(movie, session.name) == 0)
				{
					SetPositionByLine(fp, 10);//��λfp����10��
					fscanf(fp, "%f", &price2[i]);//����9�����ݱ�������price2[i]��
					i++;
				}
				fclose(fp);
			}
			//������������������ͬ�� 
			while(_findnext(Handle,&FileInfo)==0)
			{
				strncpy(filename_half_2, FileInfo.name + 4, strlen(FileInfo.name) - 12);
				if (strcmp(filename_half_1, filename_half_2) == 0)
				{
					memset(filename, 0, sizeof(filename));
					strncpy(filename, path, strlen(path) - 15);
					strcat(filename, "session_info\\");
					strcat(filename, FileInfo.name);
					fp = fopen(filename, "r");
					SetPositionByLine(fp, 2);
					fscanf(fp, "%s", session.name);
					if (strcmp(movie, session.name) == 0)
					{
						SetPositionByLine(fp, 10);
						fscanf(fp, "%f", &price2[i]);
						i++;
					}
					fclose(fp);
				}
			}
		}
		_findclose(Handle);
		qsort(price2, i, sizeof(int), cmpUpFloat);//�������˼۸������price2[i]������������ 
		printf("���α��      ӰƬ��         ӰԺ   Ӱ��   ����   ��ʼʱ��   ����ʱ��   ʱ��   ��λ��   ��Ʊ��   Ʊ��   ����   ӰƬ����   �ۿ���\n");
		//�����ļ��У�����Ϊ֮ǰ���浽remain2[i]�еĴ�����Ȼ���ź�����������ζ�Ӧ�����ļ��ж�Ӧ�У����������ļ���� 
		while (j < i)
		{
			k = 0;
			memset(filename, 0, sizeof(filename));
			if((Handle=_findfirst(filePath,&FileInfo))==-1L)
			printf("û���ҵ�ƥ�����Ŀ\n");
			else
			{	
				strncpy(filename_half_2, FileInfo.name + 4, strlen(FileInfo.name) - 12);
				if (strcmp(filename_half_1, filename_half_2) == 0) 
				{
					strncpy(filename, path, strlen(path) - 15);
					strcat(filename, "session_info\\");
					strcat(filename, FileInfo.name);
					fp = fopen(filename, "r");
					SetPositionByLine(fp, 2);
					fscanf(fp, "%s", session.name);
					if (strcmp(movie, session.name) == 0)
					{
						SetPositionByLine(fp, 1);
						fscanf(fp, "%s", session.sessionNum);
						fscanf(fp, "%s", session.name);
						fscanf(fp, "%s", session.cinema);
						fscanf(fp, "%s", session.hallNum);
						fscanf(fp, "%s", startTimeStr);
						fscanf(fp, "%s", endTimeStr);					
						fscanf(fp, "%d", &session.length);
						fscanf(fp, "%d", &session.totalseat);
						fscanf(fp, "%d", &session.remain);
						fscanf(fp, "%f", &session.price);
						if (session.price == price2[j])
						{ 
							fscanf(fp, "%s", session.language);
							fscanf(fp, "%s", session.type);
							fscanf(fp, "%f", &session.discount);
							printf("%-14s%-15s%-7s%-7s%-7s%-11s%-11s%-7d%-9d%-9d%-7.2f%-7s%-11s%.1f\n", session.sessionNum, session.name, session.cinema, session.hallNum, date, startTimeStr, endTimeStr, session.length, session.totalseat, session.remain, session.price, session.language, session.type, session.discount);
							if (price2[j] == price2[j+1])
								k++;
							else
								j++;
						}
					}
					fclose(fp);
				}
				while(_findnext(Handle,&FileInfo)==0)
				{
					strncpy(filename_half_2, FileInfo.name + 4, strlen(FileInfo.name) - 12);
					if (strcmp(filename_half_1, filename_half_2) == 0)
					{
						memset(filename, 0, sizeof(filename));
						strncpy(filename, path, strlen(path) - 15);
						strcat(filename, "session_info\\");
						strcat(filename, FileInfo.name);
						fp = fopen(filename, "r");
						SetPositionByLine(fp, 2);
						fscanf(fp, "%s", session.name);
						if (strcmp(movie, session.name) == 0)
						{
							SetPositionByLine(fp, 1);
							fscanf(fp, "%s", session.sessionNum);
							fscanf(fp, "%s", session.name);
							fscanf(fp, "%s", session.cinema);
							fscanf(fp, "%s", session.hallNum);
							fscanf(fp, "%s", startTimeStr);
							fscanf(fp, "%s", endTimeStr);					
							fscanf(fp, "%d", &session.length);
							fscanf(fp, "%d", &session.totalseat);
							fscanf(fp, "%d", &session.remain);
							fscanf(fp, "%f", &session.price);
							if (session.price == price2[j])
							{ 
								fscanf(fp, "%s", session.language);
								fscanf(fp, "%s", session.type);
								fscanf(fp, "%f", &session.discount);
								printf("%-14s%-15s%-7s%-7s%-7s%-11s%-11s%-7d%-9d%-9d%-7.2f%-7s%-11s%.1f\n", session.sessionNum, session.name, session.cinema, session.hallNum, date, startTimeStr, endTimeStr, session.length, session.totalseat, session.remain, session.price, session.language, session.type, session.discount);
								if (price2[j] == price2[j+1])
									k++;
								else
									j++;
							}
						}
						fclose(fp);	
					}
				}
			}
			_findclose(Handle);
			j += k;
		}
	}
	else if (opt == 2)
	{
		//�ҵ��ļ����еĵ�һ���ļ�����ȡ�ļ��� 
		if((Handle=_findfirst(filePath,&FileInfo))==-1L)
			printf("û���ҵ�ƥ�����Ŀ\n");
		else
		{
			strncpy(filename_half_2, FileInfo.name, strlen(FileInfo.name) - 8);//����ǰ�ļ�����ӰԺ�����ڱ��浽filename_half_2
			if (strcmp(filename_half_1, filename_half_2) == 0) //��鵱ǰ�ļ�����ӰԺ��������֮ǰ������Ƿ�һ�� 
			{
				strncpy(filename, path, strlen(path) - 15);
				strcat(filename, "session_info\\");
				strcat(filename, FileInfo.name);
				fp = fopen(filename, "r");
				SetPositionByLine(fp, 2);
				fscanf(fp, "%s", session.name);
				if (strcmp(movie, session.name) == 0)
				{
					SetPositionByLine(fp, 10);//��λfp����10��
					fscanf(fp, "%f", &price2[i]);//����9�����ݱ�������price2[i]��
					i++;
				}
				fclose(fp);
			}
			//������������������ͬ�� 
			while(_findnext(Handle,&FileInfo)==0)
			{
				strncpy(filename_half_2, FileInfo.name, strlen(FileInfo.name) - 8);
				if (strcmp(filename_half_1, filename_half_2) == 0)
				{
					memset(filename, 0, sizeof(filename));
					strncpy(filename, path, strlen(path) - 15);
					strcat(filename, "session_info\\");
					strcat(filename, FileInfo.name);
					fp = fopen(filename, "r");
					SetPositionByLine(fp, 2);
					fscanf(fp, "%s", session.name);
					if (strcmp(movie, session.name) == 0)
					{
						SetPositionByLine(fp, 10);
						fscanf(fp, "%f", &price2[i]);
						i++;
					}
					fclose(fp);
				}
			}
		}
		_findclose(Handle);
		qsort(price2, i, sizeof(int), cmpUpFloat);//�������˼۸������price2[i]������������ 
		printf("���α��      ӰƬ��         ӰԺ   Ӱ��   ����   ��ʼʱ��   ����ʱ��   ʱ��   ��λ��   ��Ʊ��   Ʊ��   ����   ӰƬ����   �ۿ���\n");
		//�����ļ��У�����Ϊ֮ǰ���浽remain2[i]�еĴ�����Ȼ���ź�����������ζ�Ӧ�����ļ��ж�Ӧ�У����������ļ���� 
		while (j < i)
		{
			k = 0;
			memset(filename, 0, sizeof(filename));
			if((Handle=_findfirst(filePath,&FileInfo))==-1L)
			printf("û���ҵ�ƥ�����Ŀ\n");
			else
			{	
				strncpy(filename_half_2, FileInfo.name, strlen(FileInfo.name) - 8);
				if (strcmp(filename_half_1, filename_half_2) == 0) 
				{
					strncpy(filename, path, strlen(path) - 15);
					strcat(filename, "session_info\\");
					strcat(filename, FileInfo.name);
					fp = fopen(filename, "r");
					SetPositionByLine(fp, 2);
					fscanf(fp, "%s", session.name);
					if (strcmp(movie, session.name) == 0)
					{
						SetPositionByLine(fp, 1);
						fscanf(fp, "%s", session.sessionNum);
						fscanf(fp, "%s", session.name);
						fscanf(fp, "%s", session.cinema);
						fscanf(fp, "%s", session.hallNum);
						fscanf(fp, "%s", startTimeStr);
						fscanf(fp, "%s", endTimeStr);					
						fscanf(fp, "%d", &session.length);
						fscanf(fp, "%d", &session.totalseat);
						fscanf(fp, "%d", &session.remain);
						fscanf(fp, "%f", &session.price);
						if (session.price == price2[j])
						{ 
							fscanf(fp, "%s", session.language);
							fscanf(fp, "%s", session.type);
							fscanf(fp, "%f", &session.discount);
							printf("%-14s%-15s%-7s%-7s%-7s%-11s%-11s%-7d%-9d%-9d%-7.2f%-7s%-11s%.1f\n", session.sessionNum, session.name, session.cinema, session.hallNum, date, startTimeStr, endTimeStr, session.length, session.totalseat, session.remain, session.price, session.language, session.type, session.discount);
							if (price2[j] == price2[j+1])
								k++;
							else
								j++;
						}
					}
					fclose(fp);
				}
				while(_findnext(Handle,&FileInfo)==0)
				{
					strncpy(filename_half_2, FileInfo.name, strlen(FileInfo.name) - 8);
					if (strcmp(filename_half_1, filename_half_2) == 0)
					{
						memset(filename, 0, sizeof(filename));
						strncpy(filename, path, strlen(path) - 15);
						strcat(filename, "session_info\\");
						strcat(filename, FileInfo.name);
						fp = fopen(filename, "r");
						SetPositionByLine(fp, 2);
						fscanf(fp, "%s", session.name);
						if (strcmp(movie, session.name) == 0)
						{
							SetPositionByLine(fp, 1);
							fscanf(fp, "%s", session.sessionNum);
							fscanf(fp, "%s", session.name);
							fscanf(fp, "%s", session.cinema);
							fscanf(fp, "%s", session.hallNum);
							fscanf(fp, "%s", startTimeStr);
							fscanf(fp, "%s", endTimeStr);					
							fscanf(fp, "%d", &session.length);
							fscanf(fp, "%d", &session.totalseat);
							fscanf(fp, "%d", &session.remain);
							fscanf(fp, "%f", &session.price);
							if (session.price == price2[j])
							{ 
								fscanf(fp, "%s", session.language);
								fscanf(fp, "%s", session.type);
								fscanf(fp, "%f", &session.discount);
								printf("%-14s%-15s%-7s%-7s%-7s%-11s%-11s%-7d%-9d%-9d%-7.2f%-7s%-11s%.1f\n", session.sessionNum, session.name, session.cinema, session.hallNum, date, startTimeStr, endTimeStr, session.length, session.totalseat, session.remain, session.price, session.language, session.type, session.discount);
								if (price2[j] == price2[j+1])
									k++;
								else
									j++;
							}
						}
						fclose(fp);	
					}
				}
			}
			_findclose(Handle);
			j += k;
		}
	}
	else if (opt == 3)
	{ 
		//�ҵ��ļ����еĵ�һ���ļ�����ȡ�ļ��� 
		if((Handle=_findfirst(filePath,&FileInfo))==-1L)
			printf("û���ҵ�ƥ�����Ŀ\n");
		else
		{
			strncpy(filename_half_2, FileInfo.name, strlen(FileInfo.name) - 8);//����ǰ�ļ�����ӰԺ�����ڱ��浽filename_half_2
			if (strcmp(filename_half_1, filename_half_2) == 0) //��鵱ǰ�ļ�����ӰԺ��������֮ǰ������Ƿ�һ�� 
			{
				strncpy(filename, path, strlen(path) - 15);
				strcat(filename, "session_info\\");
				strcat(filename, FileInfo.name);
				fp = fopen(filename, "r");
				SetPositionByLine(fp, 10);//��λfp����10��
				fscanf(fp, "%f", &price2[i]);//����9�����ݱ�������price2[i]��
				fclose(fp);
				i++;
			}
			//������������������ͬ�� 
			while(_findnext(Handle,&FileInfo)==0)
			{
				strncpy(filename_half_2, FileInfo.name, strlen(FileInfo.name) - 8);
				if (strcmp(filename_half_1, filename_half_2) == 0)
				{
					memset(filename, 0, sizeof(filename));
					strncpy(filename, path, strlen(path) - 15);
					strcat(filename, "session_info\\");
					strcat(filename, FileInfo.name);
					fp = fopen(filename, "r");
					SetPositionByLine(fp, 10);
					fscanf(fp, "%f", &price2[i]);
					fclose(fp);
					i++;			
				}
			}
			_findclose(Handle);
		}
		
		qsort(price2, i, sizeof(int), cmpUpFloat);//�������˼۸������price2[i]������������ 
		printf("���α��      ӰƬ��         ӰԺ   Ӱ��   ����   ��ʼʱ��   ����ʱ��   ʱ��   ��λ��   ��Ʊ��   Ʊ��   ����   ӰƬ����   �ۿ���\n");
		//�����ļ��У�����Ϊ֮ǰ���浽remain2[i]�еĴ�����Ȼ���ź�����������ζ�Ӧ�����ļ��ж�Ӧ�У����������ļ���� 
		while (j < i)
		{
			k = 0;
			memset(filename, 0, sizeof(filename));
			if((Handle=_findfirst(filePath,&FileInfo))==-1L)
			printf("û���ҵ�ƥ�����Ŀ\n");
			else
			{	
				strncpy(filename_half_2, FileInfo.name, strlen(FileInfo.name) - 8);
				if (strcmp(filename_half_1, filename_half_2) == 0) 
				{
					strncpy(filename, path, strlen(path) - 15);
					strcat(filename, "session_info\\");
					strcat(filename, FileInfo.name);
					fp = fopen(filename, "r");
					fscanf(fp, "%s", session.sessionNum);
					fscanf(fp, "%s", session.name);
					fscanf(fp, "%s", session.cinema);
					fscanf(fp, "%s", session.hallNum);
					fscanf(fp, "%s", startTimeStr);
					fscanf(fp, "%s", endTimeStr);					
					fscanf(fp, "%d", &session.length);
					fscanf(fp, "%d", &session.totalseat);
					fscanf(fp, "%d", &session.remain);
					fscanf(fp, "%f", &session.price);
					if (session.price == price2[j])
					{ 
						fscanf(fp, "%s", session.language);
						fscanf(fp, "%s", session.type);
						fscanf(fp, "%f", &session.discount);
						printf("%-14s%-15s%-7s%-7s%-7s%-11s%-11s%-7d%-9d%-9d%-7.2f%-7s%-11s%.1f\n", session.sessionNum, session.name, session.cinema, session.hallNum, date, startTimeStr, endTimeStr, session.length, session.totalseat, session.remain, session.price, session.language, session.type, session.discount);
						if (price2[j] == price2[j+1])
							k++;
						else
							j++;
					}
					fclose(fp);
				
				}
				while(_findnext(Handle,&FileInfo)==0)
				{
					strncpy(filename_half_2, FileInfo.name, strlen(FileInfo.name) - 8);
					if (strcmp(filename_half_1, filename_half_2) == 0)
					{
						memset(filename, 0, sizeof(filename));
						strncpy(filename, path, strlen(path) - 15);
						strcat(filename, "session_info\\");
						strcat(filename, FileInfo.name);
						fp = fopen(filename, "r");
						fscanf(fp, "%s", session.sessionNum);
						fscanf(fp, "%s", session.name);
						fscanf(fp, "%s", session.cinema);
						fscanf(fp, "%s", session.hallNum);
						fscanf(fp, "%s", startTimeStr);
						fscanf(fp, "%s", endTimeStr);					
						fscanf(fp, "%d", &session.length);
						fscanf(fp, "%d", &session.totalseat);
						fscanf(fp, "%d", &session.remain);
						fscanf(fp, "%f", &session.price);
						if (session.price == price2[j])
						{ 
							fscanf(fp, "%s", session.language);
							fscanf(fp, "%s", session.type);
							fscanf(fp, "%f", &session.discount);
							printf("%-14s%-15s%-7s%-7s%-7s%-11s%-11s%-7d%-9d%-9d%-7.2f%-7s%-11s%.1f\n", session.sessionNum, session.name, session.cinema, session.hallNum, date, startTimeStr, endTimeStr, session.length, session.totalseat, session.remain, session.price, session.language, session.type, session.discount);
							if (price2[j] == price2[j+1])
								k++;
							else
								j++;
						}
						fclose(fp);			
					}
				}
			}
			j += k;
		}
	}
}
//int main(int argc, char *argv[])
//{
//	char cinema[5] = {"DDYY"};
//	char date[5] = {"0831"};
//	char movie[20] = {"Avengers3"};
//	PriceSort(argv[0], cinema, date, movie, 2);
//	return 0;
//}

#endif
