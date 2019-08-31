#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "gadgets.h"

#define MAX 101

int session_arrange(char path[], char cinema[], int newhall, int newstart, int newtime);

int main(int argc, char *argv[])
{
	int newtime=0, newhall=0;
	char cinema[MAX]={'\0'}, newstart[MAX]={'\0'};
	{
		scanf("%s", cinema);
		scanf("%d", &newhall);
		scanf("%s", newstart);
		scanf("%d", &newtime);
		printf("%d\n", session_arrange(argv[0], cinema, newhall, hhmm2min(newstart), newtime));
	}
}
//path�����������в���argv[0](���ڱ�ĺ����������path)��cinemaӰԺ��4�ִ��룬newhall�¼���Ӱ���ţ�newstart�¼��볡�ο�ʼʱ�䣬newtime�³�����ʱ��
int session_arrange(char path[], char cinema[], int newhall, int newstart, int newtime)
{ 
	typedef struct{
		int hall;
		int start;
		int end;
		int time;
		char starts[20];
		char ends[20];
	}Sessiontime;			//���ݶ�������ڽṹ��
	int value=0;
	char filename[MAX]={'\0'}, buffering[MAX]={'\0'};
	FILE *fp1, *fp2;
	int i=0, n=0, newend=newstart+newtime, IOTime=10, sweeptime=10;
	strncpy(filename, path, strlen(path)-15);
	strcat(filename, "cma_info\\");
	strcat(filename, cinema);
	strcat(filename, ".txt");
	if((fp1=fopen(filename, "r"))!=NULL)
	{
		for(n=0; !feof(fp1); n++)
		{
			fscanf(fp1, "%s", buffering);//��ȡӰԺ�ļ��г�������(ʵ�ʲ������������+1�ģ�����Ӱ�������������)
		}
		fclose(fp1);
		char** session_ID=(char**)malloc(n*sizeof(char*));
		for(i=0;i<n;i++)
		{
			session_ID[i]=(char*)malloc(20*sizeof(char));//��ά����������
		}
		fp1=fopen(filename, "r");
		Sessiontime* sessions=(Sessiontime*)malloc(n*sizeof(Sessiontime));//��̬�ṹ������
		for(i=0;i<n;i++)
		{
			fp2=NULL;
			fscanf(fp1, "%s", session_ID[i]);
			memset(filename, 0, MAX*sizeof(char));
			strncpy(filename, path, strlen(path)-15);
			strcat(filename, "session_info\\");
			strcat(filename, session_ID[i]);
			strcat(filename, ".txt");
			if((fp2=fopen(filename, "r"))!=NULL)
			{
				for(int j=0;j<3;j++)
				{
					fscanf(fp2, "%s", buffering);
				}
				fscanf(fp2, "%d", &sessions[i].hall);
				fscanf(fp2, "%s", sessions[i].starts);
				fscanf(fp2, "%s", sessions[i].ends);
				fscanf(fp2, "%d", &sessions[i].time);
				sessions[i].start=hhmm2min(sessions[i].starts);
				sessions[i].end=hhmm2min(sessions[i].ends);//���б�򿪳����ļ���ȡ��Ϣ
			}
			else
			{
				fprintf(stderr, "File open error_2!\n");
			}
			fclose(fp2);
			if(sessions[i].hall==newhall)
			{
				if(newend<sessions[i].start)
				{
					if((sessions[i].start-newend)<(2*IOTime+sweeptime))
					{
						return 0;
					}
					else
					{
						value=1;
					}
				}
				else
				{
					if(newstart>sessions[i].end)
					{
						if((newstart-sessions[i].end)>(2*IOTime+sweeptime))
						{
							value=1;
						}
						else
						{
							return 0;
						}
					}
					else
					{
						return 0;
					}
				}
			}
			else
			{
				value=1;
				if(abs(newend-sessions[i].end)<(IOTime+sweeptime)) return 0;
				if((sessions[i].start-newend)<IOTime && (sessions[i].start-newend)>0) return 0;
				if(abs(newstart-sessions[i].start)<IOTime) return 0;
				if((newstart-sessions[i].end)<IOTime && (newstart-sessions[i].end)>0) return 0;
			}
		}								//��Щ��΢���Ե��߼�������ͼ��������
	}
	else
	{
		fprintf(stderr, "File open error_1!\n");
	} 
	return value;
} 
