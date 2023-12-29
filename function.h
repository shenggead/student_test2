//
// Created by ���� and ��˼�� on 2023/12/13.
//
//#define TURE 1
#ifndef PUPIL_TEST2_FUNCTION_H
#define PUPIL_TEST2_FUNCTION_H

#endif //PUPIL_TEST2_FUNCTION_H
#define FILE_PATH "A:\\code\\c++\\pupil_test2\\user_information.txt"
#define FILE_PATH1(x) x

//ͷ�ļ�����
#include <malloc.h>
#include <string.h>
#include "stdio.h"
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
#include "malloc.h"
#include<conio.h>
//�û���Ϣ�ṹ��
typedef struct USER {
    int Number_of_answers;//�������
    int n;
    char UID[9];
    char name[20];
    char password[6];
    double score;
    struct USER *next;
} USER;

//ö��
enum Option {
    EXIT,
    PERSONAL_INFORMATION,
    START_ANSWERING_QUESTIONS,
    RANKING_LIST,
    HISTORY_RECORD,
};

USER *Creat_user_list();

//���û�����д���ļ�
void Data_Input(USER *header);

//uid����
void uid_automatically_generated(USER* header,USER* write);
//Determine whether the information entered by the developer is correct
int Determine(USER *write);
//Delete specific user
void Delete_specific_user(USER* header);
//���û�����д���ļ��Ĳ˵�
void write_user_information(USER *header);

//��������Ƿ���ȷ
USER *Check_password_correct(USER *header, char UID[9], char password[6]);

//������ӡ����(���ԣ�
void print_user_data(USER *header);

//׼����¼
int prepare();

//��ӡ������Ϣ
void print_the_user(USER *header, char UID[9]);

//�������û��ڵ�
int Creat_new_user(USER *header);

//��¼
char *log_in(USER *header);

//��ӡ�˵�
int print_menu();

//����
void Rank(USER *header);

//��ӡ����
void print_rank(USER *header);

//��������
void score_update(char UID[9], double score1, USER *header);

//��������д���ļ�
void Score_updates_written(USER *header);

//
//���⺯�� ����������

typedef struct question {
    int num;//����num��¼���
    int a;
    char c;
    int b;
    int r;//������ȷ��r
//    int arr[3];
    struct question *next;
} question;

//�������һ����Ŀ
question *cq();

//����һ����������ʮ����Ŀ
question *queslink10(question *h);

//��ӡ��Ŀ��������
void print_link(question *h);

//����ӼǷ�ģ��
int ans[11][4] = {-1};
int score = 0;

void answer(question *h);//����һ�ι���


//�ܴ������ //������
int pa(question *h);//print answer


//�Ѵ����¼д���ļ�
void Write_answer_records(question *header,char UID[9]);


//��ȡ�����¼
question *read_answer_records(char UID[9]);

void print_question_record(question *header);
//��ӡ�����¼
void print_question_records(question *header, int arr[11][4]);//Output records