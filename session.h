#include <stdio.h>
#define MAXSIZE 101
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
    int Curseat[MAXSIZE][2];   //��ռ��λ��Ϣ
}SessionDetail;

void ShowSession(SessionDetail session);
SessionDetail Read_session_to_struct(FILE *fp, SessionDetail session);
void ShowSession(SessionDetail session)
{
    int i = 0;
    printf("+--------------------------------------------------------------------------------------------------------------------------------------------------+\n");
    printf("|���α��     |ӰƬ����      |ӰԺ���� |Ӱ���� |��ʼʱ�� |����ʱ�� |��ʱ�� |����λ |��Ʊ�� |Ʊ��   |�������� |��Ӱ����|�Ż����� |������ |������ |\n");
    printf("+--------------------------------------------------------------------------------------------------------------------------------------------------+\n");
    printf("|%-13s|%-14s|%-9s|%-7d|%-9s|%-9s|",session.SessioNum,session.MovName,session.CinName,
           session.MovieRoom,session.Startime,session.Stoptime);
    printf("%-7d|%-7d|%-7d|%-7.2lf|%-9s|%-8s|%-9.2f|", session.time,session.AllticketNum,session.remainTicket,session.price,session.language,
           session.MovType,session.discount);
    printf("%-7d|%-7d|\n", session.row,session.colum);
    printf("+--------------------------------------------------------------------------------------------------------------------------------------------------+\n");
    printf("��ռ��λ��Ϣ:\n");
    for (i = 0; i < session.AllticketNum - session.remainTicket; i++)
           printf("%d��%d��\n", session.Curseat[i][0], session.Curseat[i][1]);
}
SessionDetail Read_session_to_struct(FILE *fp, SessionDetail session)
{
    int i = 0, seat = 0, seatx = 0, seaty = 0;
    fscanf(fp, "%s%s%s%d", session.SessioNum, session.MovName, session.CinName, &session.MovieRoom);
    fscanf(fp, "%s%s%d%d", session.Startime, session.Stoptime, &session.time, &session.AllticketNum);
    fscanf(fp, "%d%lf%s%s", &session.remainTicket, &session.price, session.language, session.MovType);
    fscanf(fp, "%f%d%d", &session.discount, &session.row, &session.colum);
    while (!feof(fp))
    {
        fscanf(fp, "%d", &seat);
        seatx = seat / 100;
        seaty = seat % 100;
        session.Curseat[i][0] = seatx;
        session.Curseat[i++][1] = seaty;
    }
    return session;
}