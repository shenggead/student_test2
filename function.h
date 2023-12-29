//
// Created by 艾丹 and 辛思佳 on 2023/12/13.
//
//#define TURE 1
#ifndef PUPIL_TEST2_FUNCTION_H
#define PUPIL_TEST2_FUNCTION_H

#endif //PUPIL_TEST2_FUNCTION_H
#define FILE_PATH "A:\\code\\c++\\pupil_test2\\user_information.txt"
#define FILE_PATH1(x) x

//头文件引用
#include <malloc.h>
#include <string.h>
#include "stdio.h"
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
#include "malloc.h"
#include<conio.h>
//用户信息结构体
typedef struct USER {
    int Number_of_answers;//答题次数
    int n;
    char UID[9];
    char name[20];
    char password[6];
    double score;
    struct USER *next;
} USER;

//枚举
enum Option {
    EXIT,
    PERSONAL_INFORMATION,
    START_ANSWERING_QUESTIONS,
    RANKING_LIST,
    HISTORY_RECORD,
};

USER *Creat_user_list();

//把用户数据写入文件
void Data_Input(USER *header);

//uid生成
void uid_automatically_generated(USER* header,USER* write);
//Determine whether the information entered by the developer is correct
int Determine(USER *write);
//Delete specific user
void Delete_specific_user(USER* header);
//把用户数据写入文件的菜单
void write_user_information(USER *header);

//检查密码是否正确
USER *Check_password_correct(USER *header, char UID[9], char password[6]);

//遍历打印链表(测试）
void print_user_data(USER *header);

//准备登录
int prepare();

//打印个人信息
void print_the_user(USER *header, char UID[9]);

//创建新用户节点
int Creat_new_user(USER *header);

//登录
char *log_in(USER *header);

//打印菜单
int print_menu();

//排名
void Rank(USER *header);

//打印排名
void print_rank(USER *header);

//分数更新
void score_update(char UID[9], double score1, USER *header);

//分数更新写入文件
void Score_updates_written(USER *header);

//
//出题函数 并建立链表

typedef struct question {
    int num;//新增num记录题号
    int a;
    char c;
    int b;
    int r;//新增正确答案r
//    int arr[3];
    struct question *next;
} question;

//随机产生一个题目
question *cq();

//产生一个链表链接十个题目
question *queslink10(question *h);

//打印题目链表！！！
void print_link(question *h);

//答题加记分模块
int ans[11][4] = {-1};
int score = 0;

void answer(question *h);//答题一次过程


//总答题过程 //！！！
int pa(question *h);//print answer


//把答题记录写入文件
void Write_answer_records(question *header,char UID[9]);


//读取答题记录
question *read_answer_records(char UID[9]);

void print_question_record(question *header);
//打印答题记录
void print_question_records(question *header, int arr[11][4]);//Output records