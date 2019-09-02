#ifndef _SORTSESSION_H
#define _SORTSESSION_H 


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <io.h>
#include "gadgets.h"
#define MAX_LENGTH_OF_LINE 1024
void SetPositionByLine(FILE *fp,int line);//将文件指针定位到指定行
int cmpUp(const void *a, const void *b);//用于qsort升序排序整数 
int cmpDown(const void *a, const void *b);//用于qsort降序排序整数
int cmpUpFloat(const void *a, const void *b);//用于qsort升序排序Float型变量
void TimeSort(char path[], char cinema[], char date[], char movie[], int opt);//按放映时间排序(argv[0], 影院名, 日期(MMDD) )
void RemainSort(char path[], char cinema[], char date[], char movie[], int opt);//按剩余票数排序
void PriceSort(char path[], char cinema[], char date[], char movie[], int opt);//按票价排序
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
	char sessionNum[20];	//场次编号 
	char name[255];	//电影名称 
	char cinema[255];	//影院名称 
	char hallNum[5];	//影厅号
	int startTime;	//开始时间（分钟） 
	int endtime; 	//结束时间（分钟） 
	int length;		//电影时长 
	int totalseat;	//总座位 
	int remain;		//剩余票数 
	float price;	//票价 
	char language[10];	//语言CHN/ENG... 
	char type[10];	//电影类型
	float discount;	//优惠政策 
}SESSION;
SESSION initialize();//初始化结构体 
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
	strcat(filename_half_1, date);//将传入的影院名和日期保存到 filename_half_1
	}
	//遍历session_info文件夹,找到所需影厅和日期的文件
	struct _finddata_t FileInfo;
	long Handle;
	strncpy(filePath, path, strlen(path) - 15);
	strcat(filePath, "session_info\\");
	strcat(filePath, "*.txt");//场次信息文件夹中文件路径
	if (opt == 1)
	{
		//找到文件夹中的第一个文件，读取文件名 
		if((Handle=_findfirst(filePath,&FileInfo))==-1L)
			printf("没有找到匹配的项目\n");
		else
		{
			strncpy(filename_half_2, FileInfo.name + 4, strlen(FileInfo.name) - 12);//将当前文件名中影院和日期保存到filename_half_2
			if (strcmp(filename_half_1, filename_half_2) == 0) //检查当前文件名中影院和日期与之前传入的是否一致 
			{
				strncpy(filename, path, strlen(path) - 15);
				strcat(filename, "session_info\\");
				strcat(filename, FileInfo.name);
				fp = fopen(filename, "r");
				SetPositionByLine(fp, 2);
				fscanf(fp, "%s", session.name);
				if (strcmp(movie, session.name) == 0)
				{
					SetPositionByLine(fp, 5);//定位fp到第5行
					fscanf(fp, "%s", startTimeStr);//将第5行内容保存到字符串变量startTimeStr
					startTime2[i] = hhmm2min(startTimeStr);//将时间字符串转换成整数，保存到数组startTime2[i]中 
					i++;
				}
				fclose(fp);
			}
			//继续遍历，后续操作同上 
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
		
		qsort(startTime2, i, sizeof(int), cmpUp);//将储存了时间的数组startTime2[i]进行升序排序 
		printf("场次编号      影片名         影院   影厅   日期   开始时间   结束时间   时长   座位数   余票数   票价   语言   影片类型   折扣率\n");
		//遍历文件夹，次数为之前储存到startTime2[i]中的次数，然后将排好序的数组依次对应搜索文件中对应行，搜索到后将文件输出 
		while (j < i)
		{
			memset(filename, 0, sizeof(filename));
			if((Handle=_findfirst(filePath,&FileInfo))==-1L)
			printf("没有找到匹配的项目\n");
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
		//找到文件夹中的第一个文件，读取文件名 
		if((Handle=_findfirst(filePath,&FileInfo))==-1L)
			printf("没有找到匹配的项目\n");
		else
		{
			strncpy(filename_half_2, FileInfo.name, strlen(FileInfo.name) - 8);//将当前文件名中影院和日期保存到filename_half_2
			if (strcmp(filename_half_1, filename_half_2) == 0) //检查当前文件名中影院和日期与之前传入的是否一致 
			{
				strncpy(filename, path, strlen(path) - 15);
				strcat(filename, "session_info\\");
				strcat(filename, FileInfo.name);
				fp = fopen(filename, "r");
				SetPositionByLine(fp, 2);
				fscanf(fp, "%s", session.name);
				if (strcmp(movie, session.name) == 0)
				{
					SetPositionByLine(fp, 5);//定位fp到第5行
					fscanf(fp, "%s", startTimeStr);//将第5行内容保存到字符串变量startTimeStr
					startTime2[i] = hhmm2min(startTimeStr);//将时间字符串转换成整数，保存到数组startTime2[i]中 
					i++;
				}
				fclose(fp);
				//继续遍历，后续操作同上 
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
		qsort(startTime2, i, sizeof(int), cmpUp);//将储存了时间的数组startTime2[i]进行升序排序 
		printf("场次编号      影片名         影院   影厅   日期   开始时间   结束时间   时长   座位数   余票数   票价   语言   影片类型   折扣率\n");
		//遍历文件夹，次数为之前储存到startTime2[i]中的次数，然后将排好序的数组依次对应搜索文件中对应行，搜索到后将文件输出 
		while (j < i)
		{
			memset(filename, 0, sizeof(filename));
			if((Handle=_findfirst(filePath,&FileInfo))==-1L)
			printf("没有找到匹配的项目\n");
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
		//找到文件夹中的第一个文件，读取文件名 
		if((Handle=_findfirst(filePath,&FileInfo))==-1L)
			printf("没有找到匹配的项目\n");
		else
		{
			strncpy(filename_half_2, FileInfo.name, strlen(FileInfo.name) - 8);//将当前文件名中影院和日期保存到filename_half_2
			if (strcmp(filename_half_1, filename_half_2) == 0) //检查当前文件名中影院和日期与之前传入的是否一致 
			{
				strncpy(filename, path, strlen(path) - 15);
				strcat(filename, "session_info\\");
				strcat(filename, FileInfo.name);
				fp = fopen(filename, "r");
				SetPositionByLine(fp, 5);//定位fp到第5行
				fscanf(fp, "%s", startTimeStr);//将第5行内容保存到字符串变量startTimeStr
				startTime2[i] = hhmm2min(startTimeStr);//将时间字符串转换成整数，保存到数组startTime2[i]中 
				fclose(fp);
				i++;
			}
			//继续遍历，后续操作同上 
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
		
		qsort(startTime2, i, sizeof(int), cmpUp);//将储存了时间的数组startTime2[i]进行升序排序 
		printf("场次编号      影片名         影院   影厅   日期   开始时间   结束时间   时长   座位数   余票数   票价   语言   影片类型   折扣率\n");
		//遍历文件夹，次数为之前储存到startTime2[i]中的次数，然后将排好序的数组依次对应搜索文件中对应行，搜索到后将文件输出 
		while (j < i)
		{
			memset(filename, 0, sizeof(filename));
			if((Handle=_findfirst(filePath,&FileInfo))==-1L)
			printf("没有找到匹配的项目\n");
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
	strcat(filename_half_1, date);//将传入的影院名和日期保存到 filename_half_1
	}
	
	//遍历session_info文件夹,找到所需影厅和日期的文件
	struct _finddata_t FileInfo;
	long Handle;
	strncpy(filePath, path, strlen(path) - 15);
	strcat(filePath, "session_info\\");
	strcat(filePath, "*.txt");//场次信息文件夹中文件路径
	if (opt == 1)
	{ 
		//找到文件夹中的第一个文件，读取文件名 
		if((Handle=_findfirst(filePath,&FileInfo))==-1L)
			printf("没有找到匹配的项目\n");
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
					SetPositionByLine(fp, 9);//定位fp到第9行
					fscanf(fp, "%d", &remain2[i]);//将第9行内容保存数组remain2[i]中
					i++;
				}
				fclose(fp);
			} 
			//继续遍历，后续操作同上 
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
		qsort(remain2, i, sizeof(int), cmpDown);//将储存了余票数的数组remain2[i]进行降序排序 
		printf("场次编号      影片名         影院   影厅   日期   开始时间   结束时间   时长   座位数   余票数   票价   语言   影片类型   折扣率\n");
		//遍历文件夹，次数为之前储存到remain2[i]中的次数，然后将排好序的数组依次对应搜索文件中对应行，搜索到后将文件输出 
		while (j < i)
		{
			memset(filename, 0, sizeof(filename));
			if((Handle=_findfirst(filePath,&FileInfo))==-1L)
			printf("没有找到匹配的项目\n");
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
		//找到文件夹中的第一个文件，读取文件名 
		if((Handle=_findfirst(filePath,&FileInfo))==-1L)
			printf("没有找到匹配的项目\n");
		else
		{
			strncpy(filename_half_2, FileInfo.name, strlen(FileInfo.name) - 8);//将当前文件名中影院和日期保存到filename_half_2
			if (strcmp(filename_half_1, filename_half_2) == 0) //检查当前文件名中影院和日期与之前传入的是否一致 
			{
				strncpy(filename, path, strlen(path) - 15);
				strcat(filename, "session_info\\");
				strcat(filename, FileInfo.name);
				fp = fopen(filename, "r");
				SetPositionByLine(fp, 2);
				fscanf(fp, "%s", session.name);
				if (strcmp(movie, session.name) == 0)
				{
					SetPositionByLine(fp, 9);//定位fp到第9行
					fscanf(fp, "%d", &remain2[i]);//将第9行内容保存数组remain2[i]中
					i++;
				}
				fclose(fp);
			}
			//继续遍历，后续操作同上 
			while(_findnext(Handle,&FileInfo)==0)
			{
				strncpy(filename_half_2, FileInfo.name, strlen(FileInfo.name) - 8);//将当前文件名中影院和日期保存到filename_half_2
				if (strcmp(filename_half_1, filename_half_2) == 0) //检查当前文件名中影院和日期与之前传入的是否一致 
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
		qsort(remain2, i, sizeof(int), cmpDown);//将储存了余票数的数组remain2[i]进行降序排序 
		printf("场次编号      影片名         影院   影厅   日期   开始时间   结束时间   时长   座位数   余票数   票价   语言   影片类型   折扣率\n");
		//遍历文件夹，次数为之前储存到remain2[i]中的次数，然后将排好序的数组依次对应搜索文件中对应行，搜索到后将文件输出 
		while (j < i)
		{
			memset(filename, 0, sizeof(filename));
			if((Handle=_findfirst(filePath,&FileInfo))==-1L)
			printf("没有找到匹配的项目\n");
			else
			{	
				strncpy(filename_half_2, FileInfo.name, strlen(FileInfo.name) - 8);//将当前文件名中影院和日期保存到filename_half_2
				if (strcmp(filename_half_1, filename_half_2) == 0) //检查当前文件名中影院和日期与之前传入的是否一致 
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
				strncpy(filename_half_2, FileInfo.name, strlen(FileInfo.name) - 8);//将当前文件名中影院和日期保存到filename_half_2
				if (strcmp(filename_half_1, filename_half_2) == 0) //检查当前文件名中影院和日期与之前传入的是否一致 
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
		//找到文件夹中的第一个文件，读取文件名 
		if((Handle=_findfirst(filePath,&FileInfo))==-1L)
			printf("没有找到匹配的项目\n");
		else
		{
			strncpy(filename_half_2, FileInfo.name, strlen(FileInfo.name) - 8);//将当前文件名中影院和日期保存到filename_half_2
			if (strcmp(filename_half_1, filename_half_2) == 0) //检查当前文件名中影院和日期与之前传入的是否一致 
			{
				strncpy(filename, path, strlen(path) - 15);
				strcat(filename, "session_info\\");
				strcat(filename, FileInfo.name);
				fp = fopen(filename, "r");
				SetPositionByLine(fp, 9);//定位fp到第9行
				fscanf(fp, "%d", &remain2[i]);//将第9行内容保存数组remain2[i]中
				fclose(fp);
				i++;
			}
			//继续遍历，后续操作同上 
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
		qsort(remain2, i, sizeof(int), cmpDown);//将储存了价格的数组remain2[i]进行降序排序 
		printf("场次编号      影片名         影院   影厅   日期   开始时间   结束时间   时长   座位数   余票数   票价   语言   影片类型   折扣率\n");
		//遍历文件夹，次数为之前储存到remain2[i]中的次数，然后将排好序的数组依次对应搜索文件中对应行，搜索到后将文件输出 
		while (j < i)
		{
			k = 0;
			memset(filename, 0, sizeof(filename));
			if((Handle=_findfirst(filePath,&FileInfo))==-1L)
			printf("没有找到匹配的项目\n");
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
		strcat(filename_half_1, date);//将传入的影院名和日期保存到 filename_half_1
	}
	//遍历session_info文件夹,找到所需影厅和日期的文件
	struct _finddata_t FileInfo;
	long Handle;
	strncpy(filePath, path, strlen(path) - 15);
	strcat(filePath, "session_info\\");
	strcat(filePath, "*.txt");//场次信息文件夹中文件路径
	if (opt == 1)
	{
		//找到文件夹中的第一个文件，读取文件名 
		if((Handle=_findfirst(filePath,&FileInfo))==-1L)
			printf("没有找到匹配的项目\n");
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
					SetPositionByLine(fp, 10);//定位fp到第10行
					fscanf(fp, "%f", &price2[i]);//将第9行内容保存数组price2[i]中
					i++;
				}
				fclose(fp);
			}
			//继续遍历，后续操作同上 
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
		qsort(price2, i, sizeof(int), cmpUpFloat);//将储存了价格的数组price2[i]进行升序排序 
		printf("场次编号      影片名         影院   影厅   日期   开始时间   结束时间   时长   座位数   余票数   票价   语言   影片类型   折扣率\n");
		//遍历文件夹，次数为之前储存到remain2[i]中的次数，然后将排好序的数组依次对应搜索文件中对应行，搜索到后将文件输出 
		while (j < i)
		{
			k = 0;
			memset(filename, 0, sizeof(filename));
			if((Handle=_findfirst(filePath,&FileInfo))==-1L)
			printf("没有找到匹配的项目\n");
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
		//找到文件夹中的第一个文件，读取文件名 
		if((Handle=_findfirst(filePath,&FileInfo))==-1L)
			printf("没有找到匹配的项目\n");
		else
		{
			strncpy(filename_half_2, FileInfo.name, strlen(FileInfo.name) - 8);//将当前文件名中影院和日期保存到filename_half_2
			if (strcmp(filename_half_1, filename_half_2) == 0) //检查当前文件名中影院和日期与之前传入的是否一致 
			{
				strncpy(filename, path, strlen(path) - 15);
				strcat(filename, "session_info\\");
				strcat(filename, FileInfo.name);
				fp = fopen(filename, "r");
				SetPositionByLine(fp, 2);
				fscanf(fp, "%s", session.name);
				if (strcmp(movie, session.name) == 0)
				{
					SetPositionByLine(fp, 10);//定位fp到第10行
					fscanf(fp, "%f", &price2[i]);//将第9行内容保存数组price2[i]中
					i++;
				}
				fclose(fp);
			}
			//继续遍历，后续操作同上 
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
		qsort(price2, i, sizeof(int), cmpUpFloat);//将储存了价格的数组price2[i]进行升序排序 
		printf("场次编号      影片名         影院   影厅   日期   开始时间   结束时间   时长   座位数   余票数   票价   语言   影片类型   折扣率\n");
		//遍历文件夹，次数为之前储存到remain2[i]中的次数，然后将排好序的数组依次对应搜索文件中对应行，搜索到后将文件输出 
		while (j < i)
		{
			k = 0;
			memset(filename, 0, sizeof(filename));
			if((Handle=_findfirst(filePath,&FileInfo))==-1L)
			printf("没有找到匹配的项目\n");
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
		//找到文件夹中的第一个文件，读取文件名 
		if((Handle=_findfirst(filePath,&FileInfo))==-1L)
			printf("没有找到匹配的项目\n");
		else
		{
			strncpy(filename_half_2, FileInfo.name, strlen(FileInfo.name) - 8);//将当前文件名中影院和日期保存到filename_half_2
			if (strcmp(filename_half_1, filename_half_2) == 0) //检查当前文件名中影院和日期与之前传入的是否一致 
			{
				strncpy(filename, path, strlen(path) - 15);
				strcat(filename, "session_info\\");
				strcat(filename, FileInfo.name);
				fp = fopen(filename, "r");
				SetPositionByLine(fp, 10);//定位fp到第10行
				fscanf(fp, "%f", &price2[i]);//将第9行内容保存数组price2[i]中
				fclose(fp);
				i++;
			}
			//继续遍历，后续操作同上 
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
		
		qsort(price2, i, sizeof(int), cmpUpFloat);//将储存了价格的数组price2[i]进行升序排序 
		printf("场次编号      影片名         影院   影厅   日期   开始时间   结束时间   时长   座位数   余票数   票价   语言   影片类型   折扣率\n");
		//遍历文件夹，次数为之前储存到remain2[i]中的次数，然后将排好序的数组依次对应搜索文件中对应行，搜索到后将文件输出 
		while (j < i)
		{
			k = 0;
			memset(filename, 0, sizeof(filename));
			if((Handle=_findfirst(filePath,&FileInfo))==-1L)
			printf("没有找到匹配的项目\n");
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
