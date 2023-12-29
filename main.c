#include "function.h"

//uid生成
void uid_automatically_generated(USER *header, USER *write) {
    USER *point_next_node = header;
    if (point_next_node->next == NULL) {
        write->n = 1;
        itoa(23045301, write->UID, 10);
    } else {
        while (point_next_node->next) {
            point_next_node = point_next_node->next;
            if (point_next_node->next == NULL) {
                write->n = point_next_node->n + 1;
            }
            int temp = 23045300 + write->n;
            itoa(temp, write->UID, 10);
        }
    }
    point_next_node->next = write;
}

//Determine whether the information entered by the developer is correct
int Determine(USER *write) {
    if (strlen(write->name) > 20 || strlen(write->name) < 2) {
        printf("name error\n");
        return 0;
    }
    if (strlen(write->password) != 5) {
        printf("password error\n");
        return 0;
    }
    if (write->score > 100) {
        printf("score error");
        return 0;
    }
    return 1;
}

//把用户数据写入文件
void Data_Input(USER *header) {
    int n;
    printf("How many users do you need to enter?\nplease input:");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        USER *write_data = (USER *) malloc(sizeof(USER));
        write_data->next = NULL;
        printf("Username must be more than 2 characters and less than 20 characters\n");
        printf("input user's name:");
        scanf("%s", write_data->name);
        printf("Password can only be 5 characters\n");
        printf("input user's password:");
        scanf("%s", write_data->password);
        printf("score can only be the double\n");
        printf("input user's score:\n");
        scanf("%lf", &(write_data->score));
        if (Determine(write_data) == 0) {
            free(write_data);
            continue;
        }
        uid_automatically_generated(header, write_data);
        write_data->Number_of_answers = 0;
        FILE *pf = fopen(FILE_PATH, "a");
        if (pf) {
            printf("file open success\n");
        } else {
            perror("file open error\n");
        }
        fwrite(write_data, sizeof(USER), 1, pf);
        if (fflush(pf) == 0) { //将缓冲区的东西写入文件
            printf("write success\n");
        } else {
            perror("error:");
            return;
        }
        fclose(pf);
        header = Creat_user_list();
        print_user_data(header);
    }

}

void Delete_specific_user(USER *header) {
    USER *point_next_node = header;
    char uid[9];
    int flag = 0;
    printf("please the user' UID you want to delete\n");
    scanf("%s", uid);
    while (point_next_node->next) {
        if (strcmp(point_next_node->next->UID, uid) == 0) {
            USER *temp = point_next_node->next;
            point_next_node->next = point_next_node->next->next;
            flag = 1;
            free(temp);
            break;
        }
        point_next_node = point_next_node->next;
    }
    if (flag) {
        printf("Modified user data");
    }
    //更改文件里面的信息
    FILE *pf = fopen(FILE_PATH, "w");
    if (pf) {
        printf("file open success\n");
    } else {
        perror("file open error\n");
    }
    while (point_next_node->next) {
        point_next_node = point_next_node->next;
        fwrite(point_next_node, sizeof(USER), 1, pf);
    }
    if (fflush(pf) == 0) { //将缓冲区的东西写入文件
        printf("flush success\n");
    } else {
        perror("error:");
        return;
    }
    fclose(pf);
    printf("Modified user data");
    print_user_data(header);
}

//把用户数据写入文件的菜单
void write_user_information(USER *header) {
    printf("------------------------------------------------------------\n");
    printf("-----------------1.Data Input                 --------------\n");
    printf("-----------------2.Delete specific user -------------------------------\n");
    printf("------------------------------------------------------------\n");
    int option;
    printf("please input option\n");
    scanf("%d", &option);
    switch (option) {
        case 1:
            Data_Input(header);
            break;
        case 2:
            Delete_specific_user(header);
            break;
        default:
            printf("the option is error\n");
    }
}

//创建用户链表
USER *Creat_user_list() {
    USER *header = (USER *) malloc(sizeof(USER));
    USER *point_next_node = header;
    FILE *pf = fopen(FILE_PATH, "r");
    if (pf == NULL) {
        printf("Failed to open the file.\n");
        return NULL;
    }
    while (!feof(pf)) {
        USER *next_node = (USER *) malloc(sizeof(USER));
        if (next_node == NULL) {
            printf("Memory allocation failed.\n");
            return NULL;
        }
        if (!(fread(next_node, 1, sizeof(USER), pf))) {
            break; // 文件已到达末尾，退出循环
        }
        point_next_node->next = next_node;
        point_next_node = next_node;
    }
    point_next_node->next = NULL;
    fclose(pf);
    return header;
}


//遍历打印链表(测试）
void print_user_data(USER *header) {
    USER *point_next_User = header->next;
    while (point_next_User) {
        printf("UID:%s\t", point_next_User->UID);
        printf("name:%-3s\t", point_next_User->name);
        printf("password:%s\t", point_next_User->password);
        printf("Number of answers:%d\n", point_next_User->Number_of_answers);
        point_next_User = point_next_User->next;
    }
}

//检查密码是否正确
USER *Check_password_correct(USER *header, char UID[9], char password[6]) {
    USER *point_next_node = header->next;
    while (point_next_node) {
        if (strcmp(point_next_node->UID, UID) == 0) {
            system("cls");
            printf("find the UID\n");
            if (strcmp(point_next_node->password, password) == 0) {
                printf("password correct!\nlog in\n");
                return point_next_node;

            } else {
                printf("password error!");
                return NULL;
            }
        }
        point_next_node = point_next_node->next;
    }
    return NULL;
}

//准备登录
int prepare() {
    printf("log in\n");
    printf("------------------------------------\n");
    printf("-------1.new user-------------------\n");
    printf("-------2.old user-------------------\n");
    printf("-------3.Developer mode-------------\n");
    printf("------------------------------------\n");
    printf("input your operate:");
    int option;
    scanf("%d", &option);
    option--;
    if (getch()) { system("cls"); }
    return option;
}

//创建新用户节点
int Creat_new_user(USER *header) {
    USER *new_user = (USER *) malloc(sizeof(USER));
    USER *point_node = header;
    if (header->next == NULL) {
        new_user->n = 1;
        itoa(23045300 + new_user->n, new_user->UID, 10);
    }
    while (point_node->next) {
        point_node = point_node->next;
        if (point_node->next == NULL) {
            new_user->n = point_node->n + 1;
            itoa(new_user->n + 23045300, new_user->UID, 10);
        }
    }
    new_user->Number_of_answers = 0;
    printf("your UID is %s\n", new_user->UID);
    printf("Username must be more than 2 characters and less than 20 characters\n");
    printf("input your name:");
    scanf("%s", new_user->name);
    printf("Password can only be  5 characters\n");
    printf("input your password:");
    scanf("%s", new_user->password);
    if (Determine(new_user) == 0) {
        free(new_user);
        printf("please try again!!!\n");
        return 0;
    }
    FILE *pf = fopen(FILE_PATH, "a");
    if (pf) {
        printf("success\n");
    } else {
        perror("error");
    }
    new_user->score = 0;
    fwrite(new_user, 1, sizeof(USER), pf);
    fclose(pf);
    new_user->next = header->next;
    header->next = new_user;
    return 1;
}

//登录
char *log_in(USER *header) {

    char UID[9] = {0};
    switch (prepare()) {
        case 0: {
            int t = Creat_new_user(header);
            if (!t) {
                log_in(header);
            }
        }
//            break;
        case 1:
            printf("log in-----\n");
            printf("please input UID:");
            scanf("%s", UID);
            char password[6];
            printf("please your password:");
            scanf("%s", password);
            if (Check_password_correct(header, UID, password) == NULL) {
                printf("UID error!!!\n");
                log_in(header);
            }
            break;
        case 2: {
            printf("Developer mode log in .......\n");
            char UID1[9];
            char password1[6];
            printf("please input UID:");
            scanf("%s", UID1);
            printf("please your password:");
            scanf("%s", password1);
            if (strcmp(UID1, "23045304") == 0) {
                printf("UID correct!\n");
                if (strcmp(password1, "12345") == 0) {
                    printf("password correct!\n");
                    write_user_information(header);
                } else {
                    printf("password error\n");

                }
            } else {
                printf("UID error!\n");

            }
            log_in(header);
            break;
        }

        default:
            printf("operate error,please input again\n");
            log_in(header);
    }
    char *Uid = (char *) malloc(sizeof(char) * 9);
    strcpy(Uid, UID);
    return Uid;
}

//打印菜单
int print_menu() {
    printf("------------------------------------------------------------\n");
    printf("---------1.PERSONAL INFORMATION            -----------------\n");
    printf("---------2.START ANSWERING QUESTIONS       -----------------\n");
    printf("---------3.RANKING LIST                    -----------------\n");
    printf("---------4.HISTORY RECORD                  ----------------\n");
    printf("---------0.EXIT                            ----------------\n");
    printf("------------------------------------------------------------\n");
    printf("input your operate:\n");
    int option;
    scanf("%d", &option);
    return option;
}

//打印个人信息
void print_the_user(USER *header, char UID[9]) {
    USER *point_next_node = header->next;
    int i = 1;
    while (point_next_node) {
        if (strcmp(point_next_node->UID, UID) == 0) {
            printf("\nUID:%s", point_next_node->UID);
            printf("\nname:%s", point_next_node->name);
            printf("\npassword:%s", point_next_node->password);
            printf("\nscore:%lf", point_next_node->score);
            printf("\nNumber of answers:%d\n", point_next_node->Number_of_answers);
            i = 0;
        }
        point_next_node = point_next_node->next;
    }
    if (i) {
        printf("not find the user!!!\n error!!!");
    }
}

//排名
void Rank(USER *header) {
    USER *point_one = header->next;
    USER *point_two = point_one->next;
    USER temp_user;
    while (point_one) {
        point_two = point_one->next;
        while (point_two) {
            if (point_one->score < point_two->score) {
//                交换
                temp_user = *point_one;
                *point_one = *point_two;
                *point_two = temp_user;
                temp_user.next = point_one->next;//交换后point_one的下一个是point_three用temp存起来
                point_one->next = point_two->next;//point_two的next是point_two
                point_two->next = temp_user.next;
            }
            point_two = point_two->next;
        }
        point_one = point_one->next;
    }
}

//分数更新
void score_update(char UID[9], double score1, USER *header) {
    USER *point_next_node = header->next;
    while (point_next_node) {
        if (strcmp(point_next_node->UID, UID) == 0) {
            point_next_node->Number_of_answers++;
            if (point_next_node->Number_of_answers == 1) {
                point_next_node->score = score1;
            } else {
                point_next_node->score = (point_next_node->score * (point_next_node->Number_of_answers - 1) + score1) /
                                         point_next_node->Number_of_answers;
            }
            return;
        }
        point_next_node = point_next_node->next;
    }
}

//打印排名
void print_rank(USER *header) {
    USER *point_next_rank = header->next;
    int i = 1;
    while (point_next_rank) {
        printf("%d UID:%s\t score:%lf\tnumber of answer %d\n", i, point_next_rank->UID, point_next_rank->score,
               point_next_rank->Number_of_answers);
        point_next_rank = point_next_rank->next;
        i++;
    }
}

//分数更新写入文件
void Score_updates_written(USER *header) {
    FILE *pf = fopen(FILE_PATH, "w");
    if (pf == NULL) {
        return;
    }
    USER *point_next_user = header->next;
    int max = 0;
    while (point_next_user) {
        max = max > point_next_user->n ? max : point_next_user->n;
        point_next_user = point_next_user->next;
    }
    point_next_user = header->next;
    for (int i = 1; i <= max; ++i) {
        while (point_next_user->n == i) {
            fwrite(point_next_user, 1, sizeof(USER), pf);
            point_next_user = point_next_user->next;
        }
    }
    fclose(pf);
}

//随机产生一个题目
question *cq()//create question
{
    question *p = (question *) malloc(sizeof(question));

    int a, b, flag = 0;
    //设置一个随机数种子
    srand((unsigned int) time(NULL));
    do {
        for (int i = 0; i < 2; ++i) {
            //产生随机数0-50之间
            if (i == 0) {
                a = rand() % 51;
            } else {
                b = rand() % 51;
            }
        }
        int j;
        j = rand();
        if (j <= 16383) {
            if (a + b < 50) {
                flag = 1;
                p->a = a;
                p->c = '+';
                p->b = b;
                p->r = a + b;

            }
        } else {
            if (a - b > 0 && a - b < 50) {
                flag = 1;
                p->a = a;
                p->c = '-';
                p->b = b;
                p->r = a - b;
            }
        }

    } while (!flag);
    p->next = NULL;
    return p;
}

//产生一个链表链接十个题目
question *queslink10(question *h) {
    question *p2 = h;
    int j = 1;//int j赋给题号
    for (int i = 0; i < 10; i++)//循环十次
    {
        question *p1 = cq();
        p1->num = j;//j赋给题号
        j++;

        Sleep(1000);

//        (p1->arr)[1] = -1;
        p2->next = p1;
        p2 = p1;
    }
    p2->next = NULL;
    return h;
}

//打印题目链表！！！
void print_link(question *h) {
    question *t = h;
    t = t->next;
    while (t) {
        printf("%d:%d%c%d=?", t->num, t->a, t->c, t->b);//新增打印题号
        t = t->next;
    }
}

void answer(question *h)//答题一次过程
{
    for (int i = 1; i < 4; i++) {
        if (i == 1) {
            scanf("%d", &ans[h->num][i]);
            if (ans[h->num][i] == h->r) {
                score += 10;
                break;
            } else {
                printf("Wrong answer, try again !\n");


            }
        }
        if (i == 2) {
            scanf("%d", &ans[h->num][i]);
            if (ans[h->num][i] == h->r) {
                score += 7;
                break;
            } else {
                printf("Wrong answer, try again !\n");


            }
        }
        if (i == 3) {
            scanf("%d", &ans[h->num][i]);
            if (ans[h->num][i] == h->r) {
                score += 5;
                break;
            } else {
                printf("Three opportunities to answer questions have been exhausted, and the correct answer is %d\n",
                       h->r);
            }
        }

    }
}

//总答题过程 //！！！
int pa(question *h)//print answer
{
    score = 0;
    question *t = h;
    t = t->next;
    while (t) {
        printf("%d:%d%c%d=?", t->num, t->a, t->c, t->b);//新增打印题号
        answer(t);
        t = t->next;
    }
    return score;
}

//把答题记录写入文件
void Write_answer_records(question *header, char UID[9]) {
    char file_path[100];
    sprintf(file_path, "A:\\\\code\\\\c++\\\\pupil_test2\\\\%s.txt", UID);
    FILE *pf = fopen(FILE_PATH1(file_path), "a");
    if (pf == NULL) {
        printf("This is your first time answering  questions");
        pf = fopen(FILE_PATH1(file_path), "w");
        if (pf == NULL) {
            perror("error");
            return;
        }
    }
    question *point_next_node = header->next;

    while (point_next_node) {
        fwrite(point_next_node, sizeof(question), 1, pf);
        point_next_node = point_next_node->next;
    }
    fclose(pf);
}

//读取答题记录
question *read_answer_records(char UID[9]) {
    question *header = (question *) malloc(sizeof(question));//建立一个新链表存储
    char file_path[100];
    sprintf(file_path, "A:\\\\code\\\\c++\\\\pupil_test2\\\\%s.txt", UID);
    FILE *pf = fopen(FILE_PATH1(file_path), "r");
//    printf("%s",FILE_PATH1(file_path));
    if(pf == NULL){
            printf("you don't answer");
            header->next = NULL;
            return header;

    }
    question *point_next_node = header;
//    int i = 1;
    while (!feof(pf)) {
        question *new_node = (question *) malloc(sizeof(question));
        fread(new_node, sizeof(question), 1, pf);
        point_next_node->next = new_node;
        point_next_node = new_node;
        /*for (int j = 1; j <= 3; j++) {
            fscanf(pf, "%d", &arr[i][j]);
        }*/
//        i++;
        point_next_node->next = NULL;
    }
    if (header->next == NULL) {
        printf("you don't answer");
        return header;
    }
    return header;
}

//打印答题记录
void print_question_records(question *header, int arr[11][4])//Output records
{
    if (header->next == NULL) {
        printf("error\n you don't have answered!\n");
        return;
    }
    int i = 1;
    question *t = header;
    t = t->next;
    while (t) {

        printf("%-2d:%-2d%c%-2d=%d\t", t->num, t->a, t->c, t->b, t->r);//新增打印题号
        for (int j = 1; j < 4; j++) {
            if (arr[i][j] >= 0) {
                if (j == 1) {
                    printf("HISTORICAL ANSWERS:");
                }
                printf("%d\t", arr[i][j]);
            }
        }
        printf("\n");
        i++;

        t = t->next;
    }
    printf("score is:%d\n", score);
}

void print_question_record(question *header)//Output records
{
    if (header->next == NULL) {
        printf("error\n you don't have answered!\n");
        return;
    }
    int i = 1;
    question *t = header;
    t = t->next;
    while (t->next) {
        printf("%-2d:%-2d%c%-2d=%d\t", t->num, t->a, t->c, t->b, t->r);//新增打印题号
        printf("\n");
        i++;

        t = t->next;
    }
}

int main() {
    setbuf(stdout, NULL);
//    printf("%d",sizeof(USER));
    USER *header = Creat_user_list();
    print_user_data(header);
    question *h = (question *) malloc(sizeof(question));
    h->next = NULL;
//    print_user_data(header);
    char UID[9];
//    free(header);
    strcpy(UID, log_in(header));
    int option = print_menu();
    while (option != 0) {
        switch (option) {
            case PERSONAL_INFORMATION: {
                print_the_user(header, UID);
                printf("\n");
                break;
            }
            case START_ANSWERING_QUESTIONS: {
                //答题过程
                printf("please wait sometime\n");
                pa(queslink10(h));
                printf("your score is %d!\n", score);
                Write_answer_records(h, UID);
                score_update(UID, score, header);
                Score_updates_written(header);
//                print_user_data(header);
                break;
            }
            case RANKING_LIST: {
                Rank(header);
                print_rank(header);
                print_user_data(header);
                break;
            }
            case HISTORY_RECORD: {
                question *h1;
                h1 = read_answer_records(UID);
                if (h->next == NULL) {
                    print_question_record(h1);
                } else {
                    print_question_records(h, ans);
                    print_question_record(h1);
                }
                break;
            }
            default:
                printf("option error,try again\n");
        }
        printf("press any key to return menu...");
        if (getch()) { system("cls"); }
        option = print_menu();

    }
    printf("exit the program");
    free(h);
    free(header);
    return 0;
}