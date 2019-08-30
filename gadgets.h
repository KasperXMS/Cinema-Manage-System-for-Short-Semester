#ifndef _GADGETS_H
#define _GADGETS_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int hhmm2min(char timestr[])
{
	int i=0;
	int hour=0, min=0;
	switch(strlen(timestr))
	{
		case 4:
			hour=timestr[0]-48;
			min=(timestr[2]-48)*10+timestr[3]-48; // h:mm
			break;
		case 5:
			hour=(timestr[0]-48)*10+timestr[1]-48;
			min=(timestr[3]-48)*10+timestr[4]-48; //hh:mm
			break;
		default:
			hour=111;
			min=3339;	//wrong time format
	}
	return hour*60+min;
}

char *min2hhmm(int min)
{
	int hour=min/60;
	int hmin=min%60;
	static char h[6]={'\0'}, m[3]={'\0'};
	memset(h, 0, 6*sizeof(char));
	if(hmin<10)
	{
		m[0]=48;
		m[1]=hmin+48;      //H:0m
	}
	else
	{
		m[0]=hmin/10+48;
		m[1]=hmin%10+48;   //H:mm
	}
	if(hour<10)
	{
		h[0]=hour+48;	   //h:M
	}
	else
	{
		h[0]=hour/10+48;
		h[1]=hour%10+48;   //hh:M
	}
	strcat(h,":");
	strcat(h,m);
	return h;		   //combine
}

#endif
