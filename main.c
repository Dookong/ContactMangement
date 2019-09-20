#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *file;

void init();
void addContact();
void search();
void editContact();
void delContact();

void delLine(int l);

int main() {
    init();
    char cmd;
    while (1){
        printf("-------------------------------------\n");
        printf("0.종료\n1.검색\n2.삽입\n3.수정\n4.삭제\n");
        printf("\n원하시는 메뉴를 숫자로 입력해주세요!\n");
        printf("메뉴 입력:");
        scanf("%c", &cmd);

        switch (cmd){
            default:
                printf("\n\n--프로그램 종료--\n");
                return 0;
            case '1':
                search();
                break;
            case '2':
                addContact();
                break;
            case '3':
                editContact();
                break;
            case '4':
                delContact();
        }
        while (getchar() != '\n');
    }
}

void init() {
    if((file = fopen("2018008468_ParkHyeonJun.csv", "r")) == NULL){
        printf("파일 생성합니다\n");
        FILE *init = fopen("contact2.csv", "r");
        file = fopen("2018008468_ParkHyeonJun.csv", "w");
        char buf[1024];

        while (!feof(init)){
            fgets(buf, 512, init);
            fputs(buf, file);
        }
        fclose(init);
    }
    //test
    else{
        char tmp[200];
        fscanf(file, "%s", tmp);
        printf("Name: %s,", strtok(tmp, ","));
        printf(" Phone: %s\n", strtok(NULL, ","));
    }
    fclose(file);
}

void search() {
    char input[50], tmp[512];
    char* check;
    char* result[10000];

    printf("\n---연락처 검색---\n");
    printf("검색어: ");
    scanf("%s", input);
    //int i = 0;
    file = fopen("2018008468_ParkHyeonJun.csv", "r+");
    while (!feof(file)){
        fgets(tmp, 512, file);
        if(strstr(tmp, input) != NULL)
            printf("%s\n", tmp);
            //result[i++] = tmp;
    }
    fclose(file);
}

void addContact() {
    char name[50], phone[11];
    printf("\n---연락처 삽입---\n");
    while(getchar() != '\n');
    printf("이름: ");
    scanf("%[^\n]", name);
    if(name == NULL || (strcmp(name, "") == 0)){
        printf("이름은 공백일 수 없습니다.\n"); //TODO: ╔ Bug!!
        return;
    } else{
        printf("%s\n", name);
    }

    while(getchar() != '\n');
    printf("전화번호: ");
    scanf("%[^\n]", phone);
    if((strcmp(phone, "") == 0)){
        printf("전화번호는 공백일 수 없습니다.\n");
        return;
    }

    file = fopen("2018008468_ParkHyeonJun.csv", "r+");
    fseek(file, 0L, SEEK_END);
    fprintf(file, "\n%s,%s", name, phone);
    fclose(file);

    printf("연락처 삽입 완료!\n");
}

void editContact() {
    printf("\n---연락처 수정---\n");
}

void delContact() {
    char input[50], buf[512];
    char* name;
    printf("\n---연락처 삭제---\n");
    while(getchar() != '\n');
    printf("이름: ");
    scanf("%[^\n]", input);

    file = fopen("2018008468_ParkHyeonJun.csv", "r");
    int i =1, j=1;
    while (!feof(file)){
        j++;
        fgets(buf, 512, file);
        name = strtok(buf, ",");
        if(strcmp(input, name) == 0)
            break;
        i++;
    }
    fclose(file);
    if(i == j)
        printf("일치하는 이름을 찾을 수 없습니다\n");
    else delLine(i);
}

void delLine(int l){
    file = fopen("2018008468_ParkHyeonJun.csv", "r");
    char tmp;
    int i =1;

    FILE* copy = fopen("copy.csv", "w");
    if(l == 1){
        while (getc(file) != '\n');
        tmp = getc(file);
        while(tmp != EOF){
            putc(tmp, copy);
            tmp = getc(file);
        }
    }
    else{
        tmp = getc(file);
        while( tmp != EOF){
            if(tmp == '\n')
                i++;
            if(i != l)
                putc(tmp, copy);
            tmp = getc(file);
        }
    }
    fclose(file);
    fclose(copy);
    remove("2018008468_ParkHyeonJun.csv");
    rename("copy.csv", "2018008468_ParkHyeonJun.csv");

    printf("연락처 삭제 완료!\n");
}