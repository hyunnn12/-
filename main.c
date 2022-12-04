#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//한 학생의 정보 입력
struct student {
    int number;
    double thistest;
    double lasttest;
};

//학생수를 받아 그 수대로 랜덤으로 학생의 정보를 입력한 정보들을 입력받음
void insert_student(struct student list[], int size) {
    for (int i = 0; i < size; i++) {
        list[i].number = 21812000 + rand() % 100; //학번
        list[i].thistest = rand() % 451 / 100.00; //이번 학점
        list[i].lasttest = rand() % 451 / 100.00; //저번 학점
    }
}

//랜덤으로 받은 학생들의 학번, 이번성적, 저번성적을 출력함
void print_student(struct student list[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%3d번 학생은 (학번: %d, 이번학기학점: %0.2f, 저번학기학점: %0.2f)입니다\n", i + 1, list[i].number, list[i].thistest, list[i].lasttest);
    }
}

//성적이 제일 높은 학생의 정보 출력
void best_student(struct student list[], int size) {
    struct student super_stu;

    super_stu = list[0];
    for (int i = 1; i < size; i++) {
        if (list[i].thistest > super_stu.thistest)//성적이 큰사람이 하나씩 비교되도록 반복문을 넣는다
            super_stu = list[i];
    }
    printf("학점이 가장 높은 학생은 (학번: %d, 이번학기학점: %0.2f)입니다\n", super_stu.number, super_stu.thistest);
}

//성적이 높은 순서대로 입력받는다
void who_is_best(struct student list[], int size) {
    struct student temp;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (list[j].thistest < list[j + 1].thistest) {
                temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }
}

//저번학기 성적보다 이번학기 성적이 1.5배오른 학생을 입력받음
void better_than_yesterday(struct student list[], int size, int count[]) {
    for (int i = 0; i < size; i++) {
        if (list[i].thistest / list[i].lasttest >= 1.5)
            count[i] = count[i] + 1;
    }
}

//5퍼센트 안에 성적이 드는 학생들 입력받음
void all_star(struct student list[], int size, int count[]) {
    for (int i = 0; i < size / 20; i++) {
        count[i] = count[i] + 2;
    }
}

/*이번 학기 1등에게 전액 장학금, 지난학기보다 1.5배증가한 학생에게 50프로, 5프로안에 성적든 학생에게 50프로,
  1.5배 증가하면서 5프로 안에든 학생에게 70프로의 장학금지급하는 값을 출력*/
void scholarship(struct student list[], int size, int count[]) {
    printf("%d 학생은 100퍼센트 장학금 대상(이번학기 1등)\n", list[0].number);
    for (int i = 1; i < size; i++) {
        if (count[i] == 1)
            printf("%d 학생은 50퍼센트 장학금 대상(지난학기보다 성적 1.5배 증가\n", list[i].number);
        else if (count[i] == 2)
            printf("%d 학생은 50퍼센트 장학금 대상(5퍼센트의 성적)\n", list[i].number);
        else if (count[i] == 3)
            printf("%d 학생은 70퍼센트 장학금 대상(지난학기보다 성적 1.5배 증가, 5퍼센트의 성적)\n", list[i].number);
    }
}
int main(void)
{
    struct student list[100];
    int size;
    int count[100] = { 0 };
    srand(time(NULL));

    printf("인원을 입력하시오 : ");//인원수 입력받음
    scanf("%d", &size);

    printf("\n");
    printf("학생정보 입력중...\n\n");
    insert_student(list, size);
    printf("\n");

    printf("학생정보 출력중...\n\n");
    print_student(list, size);//받은 인원수 안에 학생들을 랜덤으로 정보 출력
    printf("\n");

    printf("1등학생정보 입력중...\n\n");
    best_student(list, size);//1등학생 정보 출력
    printf("\n");

    printf("성적순으로 정렬중...\n\n");
    who_is_best(list, size);

    printf("학생정보입력중...\n\n");
    print_student(list, size);//성적순대로 학생들 나열
    printf("\n");

    printf("지난학기보다 성적이 1.5배오른 학생 검색중...\n\n");
    better_than_yesterday(list, size, count);
    printf("\n");

    printf("5퍼센트의 성적을 가진 학생들 검색중...\n\n");
    all_star(list, size, count);
    printf("\n");

    printf("장학금 대상 출력중...\n\n");
    scholarship(list, size, count);//마지막 장학금받는 학생들 나열
}