//
//  main.c
//  threadPool
//
//  Created by Apus on 2018/11/16.
//  Copyright © 2018年 kangyf. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/types.h>

void * print_a(void *);
void * print_b(void *);
void testDate();
void canada();
void PrintYear (int year);
void process();
#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

int main(int argc, const char * argv[]) {
    /*
    pthread_t t0;
    pthread_t t1;
    if(pthread_create(&t0,  NULL, print_a,NULL)==-1){
        puts("fail to create pthread t0");
        exit(1);
    }
    if(pthread_create(&t1, NULL, print_b, NULL) == -1){
        puts("fail to create pthread t1");
        exit(1);
    }
    
    void * result;
    if(pthread_join(t0, &result) == -1){
        puts("fail to recollect t0");
        exit(1);
    }
    
    if(pthread_join(t1, &result) == -1){
        puts("fail to recollect t1");
        exit(1);
    }
     */
    
    //testDate();
    //canada();
    /**
    int year = 2018;
    PrintYear(2018);
     */

    process();
    
    return 0;
}

void process(){
    int lenth = 3;
    pid_t pid[lenth];
    char *msg;
    int k;
    for(int i=0; i<lenth; i++){
        pid[i]=fork();
        
        switch(pid[i]){
                //子进程执行部分
            case 0:
                printf("%d\n", getpid());
                msg="Child process is running.\n";
                k=3;
                break;
            case -1:
                printf("%d", getpid());
                perror("Process creation failed.\n");
                break;
                //父进程执行部
            default:
                printf("%d", getpid());
                msg="Parent process is running.\n";
                k=5;
                break;
        }
    }

    
    //父子进程共同执行部分
    while(k>0){
        puts(msg);
        sleep(1);
        k--;
    }
}


void canada(){
   // int date1[] = {31,29,31,30,31,30,31,31,30,31,30,31};
    int date2[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    //int year = 2018;
    
    printf("星期日\t");
    printf("星期一\t");
    printf("星期二\t");
    printf("星期三\t");
    printf("星期四\t");
    printf("星期五\t");
    printf("星期六\n");
    int dateNum = ARRAY_SIZE(date2);
 
    

   /*
    for(int i=0; i<dateNum;i++){
       // printf("%d\n",date1[i]);
        printf("星期日\t");
        printf("星期一\t");
        printf("星期二\t");
        printf("星期三\t");
        printf("星期四\t");
        printf("星期五\t");
        printf("星期六\n");
        for(int i=0; i<date2[i]; i++){
            printf(<#const char *restrict, ...#>)
        }
         printf("========================================================\n");
    }*/
   
}

/*判断是平年还是闰年*/
int IsLeap (int year) {
    if((year%4==0)&& (year%100!=0) || (year%400==0))
        return 1;
    else
        return 0;
}
/*计算今年的第一天是星期几*/
int FirstWeeday (int year) {
    int days = (year-1)*365 + (year-1)/4 - (year-100)/100 + (year-1)/400;
    return days%7;
}
/*打印星期*/
void PrintWeedTitl () {
    int i;
    for(i = 0;i<7;i++){
        switch(i) {
            case 0 : printf("  星期日  ");break;
            case 1 : printf("星期一  ");break;
            case 2 : printf("星期二  ");break;
            case 3 : printf("星期三  ");break;
            case 4 : printf("星期四  ");break;
            case 5 : printf("星期五  ");break;
            case 6 : printf("星期六  ");break;
            default : break;
        }
    }
    printf("\n");
}
/*打印月份*/
void PrintMonTitl(int month) {
    switch(month) {
        case 0 : printf("1月\n");break;
        case 1 : printf("2月\n");break;
        case 2 : printf("3月\n");break;
        case 3 : printf("4月\n");break;
        case 4 : printf("5月\n");break;
        case 5 : printf("6月\n");break;
        case 6 : printf("7月\n");break;
        case 7 : printf("8月\n");break;
        case 8 : printf("9月\n");break;
        case 9 : printf("10月\n");break;
        case 10 : printf("11月\n");break;
        case 11 : printf("12月\n");break;
        default : break;
    }
}
/*格式化输出日历*/
void PrintYear (int year) {
    int m,i,d;
    char c='  ';
    int MONTH[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if(IsLeap(year)) MONTH[1] = 29;
    int firstwed = FirstWeeday(year);
    printf("Year: %d\n",year);
    printf("========================\n");
    for(m = 0;m<12;m++) {
        PrintMonTitl(m);
        PrintWeedTitl();
        for(d=1;d<=MONTH[m];d++) {
            if(d == 1) {
                for(i = 0;i<firstwed;i++)
                    printf("%5c  ",c);
                printf("%5d  ",d);
            }
            else {
                printf("%5d  ",d);
            }
            if((firstwed+d-1)%7 == 6) printf("\n");
        }
        firstwed = (firstwed + MONTH[m])%7;
        printf("\n");
    }
    
}

void testDate(){
    time_t t;
    t = time(NULL);
    struct tm *p;
    p = gmtime(&t);
    
    printf("%d年\n", 1900+p->tm_year);
    printf("%d月\n", p->tm_mon);
    printf("%d号\n", p->tm_mday);
    printf("星期%d\n", p->tm_wday);
    printf("第%d天\n", p->tm_yday);
    printf("%d秒\n", p->tm_sec);
}

// 线程A 方法
void * print_a(void *a){
    for(int i = 0;i < 100; i++){
        if(i%2==0){
            sched_yield();
        }
       printf("aa%d\t",i);
    }
    return NULL;
}

// 线程B 方法
void * print_b(void *b){
    for(int i=0;i<100;i++){
        if(i % 2 == 1){
            sched_yield();
        }
        printf("bb%d\t",i);
    }
    return NULL;
}

