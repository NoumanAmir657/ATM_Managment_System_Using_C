#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 50
void create_account(void);
void cash_withdraw(void);
void cash_deposit(void);
void account_summary(void);
int check_balance(void);
void display(void); //displays the menu

//structure for customer account data
struct customer{
    char username[SIZE];
    char password[SIZE];
    int balance;
};
time_t t;


int main(){
    time(&t);
    FILE *names_list = NULL;
    names_list = fopen("usernames.txt", "a"); //creation of username.txt which contains name of users who have made their account
    fclose(names_list);

    while(1){
        display();
        int choice = 0;
        printf("Enter choice for the task you want to do: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:{
                create_account();
                break;
            }
            case 2:{
                cash_withdraw();
                break;
            }
            case 3:{
                cash_deposit();
                break;
            }
            case 4:{
                account_summary();
                break;
            }
            case 5:{
                check_balance();
                break;
            }
            case 6:{
                exit(0);
            }
        }
    }
}

void display(){
    system("clear");
    printf("\t\t ATM SYSTEM \t\t\n");
    printf("1: Create Account\n");
    printf("2: Cash_Withdraw\n");
    printf("3: Cash_Deposit\n");
    printf("4: Account Summary\n");
    printf("5: Check Balance\n");
    printf("6: Exit\n");
}

void create_account(){
    struct customer a;
    struct customer b;
    char temp[100];
    char found = 'F';
    FILE *names_list = NULL;
    FILE *new = NULL;
    while (1){
        found = 'F';
        printf("Enter Username: ");
        scanf("%s", a.username);
        printf("Enter Password: ");
        scanf("%s", a.password);
        names_list = fopen("usernames.txt", "r");
        //check whether name already exists in username.txt or not
        while (1){
            if (fread(&b, sizeof(b), 1, names_list) == 0){
                break;
            }
            if (strcmp(b.username, a.username) == 0){
                found = 'T';
                break;
            }
        }
        fclose(names_list);
        if (found == 'F'){
            names_list = fopen("usernames.txt", "a");
            sprintf(temp, "./Names/%s.txt", a.username);
            new = fopen(temp, "w"); //creates file with username
            printf("Enter the amount that you want to save in your new account: ");
            scanf("%d", &a.balance);
            fprintf(new, "Amount Deposited when account was made: %d TimeStamp: %s \n", a.balance, ctime(&t));
            fwrite(&a, sizeof(a), 1, names_list);
            fclose(new);
            fclose(names_list);
            break;
        }
        else if(found == 'T'){
            printf("Username already exists!!! Enter a new Username.\n");
        }
    }
}


void cash_withdraw(){
    struct customer a;
    struct customer b;
    int withdraw = 0;
    char temp[100];
    char found = 'F';
    FILE *names_list = NULL;
    FILE *new = NULL;

    printf("Enter Username: ");
    scanf("%s", a.username);
    names_list = fopen("usernames.txt", "r+");
    while (1){
        if (fread(&b, sizeof(b), 1, names_list) == 0){
            break;
        }
        if (strcmp(b.username, a.username) == 0){
            found = 'T';
            break;
        }
    }

    if (found == 'T'){
        do{
            printf("Enter amount less than your balance to withdraw: ");
            scanf("%d", &withdraw);
        }while(b.balance < withdraw);
        b.balance = b.balance - withdraw;
        fseek(names_list, -(int)sizeof(b), SEEK_CUR); //moves the file pointer to the previous record
        fwrite(&b, sizeof(b), 1, names_list);
        fclose(names_list);

        sprintf(temp, "./Names/%s.txt", a.username);
        new = fopen(temp, "a");
        fprintf(new, "You withdrawed: %d TimeStamp: %s\n", withdraw, ctime(&t));
        fclose(new);
    }

    else if(found == 'F'){
        printf("User does not exist!");
    }

}

void cash_deposit(){
    struct customer a;
    struct customer b;
    int deposit = 0;
    char temp[100];
    char found = 'F';
    FILE *names_list = NULL;
    FILE *new = NULL;

    printf("Enter Username: ");
    scanf("%s", a.username);
    names_list = fopen("usernames.txt", "r+");
    while (1){
        if (fread(&b, sizeof(b), 1, names_list) == 0){
            break;
        }
        if (strcmp(b.username, a.username) == 0){
            found = 'T';
            break;
        }
    }

    if (found == 'T'){
        do{
            printf("Enter Amount to deposit. It should be multiple of 10: ");
            scanf("%d", &deposit);
        }while((deposit % 10) != 0);
        b.balance = b.balance + deposit;
        fseek(names_list, -(int)sizeof(b), SEEK_CUR); //moves the file pointer to the previous record
        fwrite(&b, sizeof(b), 1, names_list);
        fclose(names_list);

        sprintf(temp, "./Names/%s.txt", a.username);
        new = fopen(temp, "a");
        fprintf(new, "You deposited: %d TimeStamp: %s\n", deposit, ctime(&t));
        fclose(new);
    }

    else if(found == 'F'){
        printf("User does not exist!");
    }
}

void account_summary(){
    struct customer a;
    struct customer b;
    char c;
    int deposit = 0;
    char temp[100];
    char found = 'F';
    FILE *names_list = NULL;
    FILE *new = NULL;

    printf("Enter Username: ");
    scanf("%s", a.username);
    printf("Enter Password: ");
    scanf("%s", a.password);
    names_list = fopen("usernames.txt", "r+");
    while (1){
        if (fread(&b, sizeof(b), 1, names_list) == 0){
            break;
        }
        if (strcmp(b.username, a.username) == 0){
            found = 'T';
            break;
        }
    }

    fclose(names_list);
    if (found == 'T' && strcmp(b.password, a.password) == 0){
        sprintf(temp, "./Names/%s.txt", a.username);
        new = fopen(temp, "r");
        printf("\t\tAccount Summary\n");
        while (fgets(temp, 100, new) != NULL){
            printf("\t\t%s", temp);
        }
        fclose(new);
    }
    else {
        printf("User does not exist or Password is wrong\n");
    }
    fflush(stdin);
    getc(stdin);
    getc(stdin);
}

int check_balance(){
    struct customer a;
    struct customer b;
    char c;
    int deposit = 0;
    char temp[100];
    char found = 'F';
    FILE *names_list = NULL;
    FILE *new = NULL;

    printf("Enter Username: ");
    scanf("%s", a.username);
    printf("Enter Password: ");
    scanf("%s", a.password);
    names_list = fopen("usernames.txt", "r+");
    while (1){
        if (fread(&b, sizeof(b), 1, names_list) == 0){
            break;
        }
        if (strcmp(b.username, a.username) == 0){
            found = 'T';
            break;
        }
    }

    fclose(names_list);
    if (found == 'T' && strcmp(b.password, a.password) == 0){
        printf("Your Balance is: %d", b.balance);
    }
    else{
        printf("User does not exist or Password is wrong!");
    }
    fflush(stdin);
    getc(stdin);
    getc(stdin);
}
