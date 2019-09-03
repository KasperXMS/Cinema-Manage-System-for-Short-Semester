#ifndef _STRUCT_H
#define _STRUCT_H

typedef struct Order{   //�����ṹ��
    char ID[MAXSIZE];       //�û�ID
    char MovName[MAXSIZE];  //ӰƬ��
    char Startime[6]; //ӰƬ��ʼʱ��
    char Stoptime[6]; //ӰƬ����ʱ��
    char CinName[MAXSIZE];  //ӰԺ��
    char Sessions[MAXSIZE]; //����
    int MovieRoom;          //Ӱ��
    int SeatNum;            //��λ��
    int seat[3][2];         //��λ��Ϣ
    int del;                //�Ƿ�ɾ������
    int legal;              //�����Ƿ�Ϸ�
    struct{                 //�µ�ʱ��
        int year;
        int month;
        int day;
        int hour;
        int min;
    }date;
    int  cost;               //�ܻ��ѽ��
    int MoneyAccount;       //�˻����
}Order;

typedef struct movie{//������Ϣ�ṹ��
    char SessioNum[13];     //���κ�
    char MovName[MAXSIZE];  //ӰƬ��
    char CinName[MAXSIZE];  //ӰԺ��
    int MovieRoom;          //Ӱ��
    char Startime[6];           //��ʼʱ��
    char Stoptime[6];           //����ʱ��
    int time;               //��ʱ��
    int AllticketNum;       //��Ʊ��
    int remainTicket;       //��Ʊ��
    double price;           //Ʊ��
    char language[20];      //��������
    char MovType[6];        //ӰƬ����
    float discount;         //�Ż�����
    int row;                //������
    int colum;              //������
    int seat[MAXSIZE][MAXSIZE];//��λ��Ϣ
}SessionDetail;

#endif
