#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_PASSWORD_LENGTH 50

struct user {
    char phone[50];
    char ac[50];
    char password[50];
    float balance;
};

int main(){
    struct user usr, usr1;
    FILE *fp;
    char filename[50], phone[50];
    char existingPassword[MAX_PASSWORD_LENGTH];
    char newPassword[MAX_PASSWORD_LENGTH];
    int opt, choice;
    char cont = 'y';
    float amount;

    printf("\nWhat do you want to do?");
    printf("\n\n1. Register an account");
    printf("\n2. Login to an account");

    printf("\n\nYour choice:\t");
    scanf("%d", &opt);

    if(opt == 1){
        system("clear");
        printf("Enter your account number:\t");
        scanf("%s", usr.ac);
        printf("Enter your phone number:\t");
        scanf("%s", usr.phone);
        printf("Enter your new password:\t");
        scanf("%s", usr.password);
        usr.balance = 0;
        strcpy(filename, usr.phone);
        fp = fopen(strcat(filename, ".dat"), "w");
        fwrite(&usr, sizeof(struct user), 1, fp);
        if(fwrite != 0){
            printf("\n\nAccount successfully registered");
        } else {
            printf("\n\nOops! Please try again!");
        }
        fclose(fp);
    } else if(opt == 2){
        system("clear");
        printf("\nPhone number:\t");
        scanf("%s", phone);
        printf("Password:\t");
        scanf("%s", existingPassword);
        strcpy(filename, phone);
        fp = fopen(strcat(filename, ".dat"), "r");
        if(fp == NULL){
            printf("\nAccount number not registered");
        } else {
            fread(&usr, sizeof(struct user), 1, fp);
            fclose(fp);
            if(strcmp(existingPassword, usr.password) == 0){
                printf("\n\t\tWelcome %s", usr.phone);
                while(cont == 'y'){
                    system("clear");
                    printf("\n\nPress 1 for balance inquiry");
                    printf("\nPress 2 for depositing cash");
                    printf("\nPress 3 for funds withdrawal");
                    printf("\nPress 4 for online transfer");
                    printf("\nPress 5 for password change");
                    printf("\n\nYour choice:\t");
                    scanf("%d", &choice);

                    switch(choice){
                        case 1:
                            printf("\nYour current balance is Ksh.%.2f", usr.balance);
                            break;
                        case 2:
                            printf("\nEnter the amount:\t");
                            scanf("%f", &amount);
                            usr.balance += amount;
                            fp = fopen(filename, "w");
                            fwrite(&usr, sizeof(struct user), 1, fp);
                            if(fwrite != 0) printf("\nSuccessfully deposited.");
                            fclose(fp);
                            break;
                        case 3:
                            printf("\nEnter the amount:\t");
                            scanf("%f", &amount);
                            if(amount > usr.balance) {
                                printf("\nInsufficient balance");
                            } else {
                                usr.balance -= amount;
                                fp = fopen(filename, "w");
                                fwrite(&usr, sizeof(struct user), 1, fp);
                                if(fwrite != 0) printf("\nYou have withdrawn Ksh.%.2f", amount);
                                fclose(fp);
                            }
                            break;
                        case 4:
                            printf("\nPlease enter the phone number to transfer the funds:\t");
                            scanf("%s", phone);
                            printf("\nPlease enter the amount to transfer:\t");
                            scanf("%f", &amount);
                            strcpy(filename, phone);
                            fp = fopen(strcat(filename, ".dat"), "r");
                            if(fp == NULL) printf("\nAccount number not registered");
                            else {
                                fread(&usr1, sizeof(struct user), 1, fp);
                                fclose(fp);
                                if(amount > usr.balance) printf("\nInsufficient balance");
                                else {
                                    fp = fopen(filename, "w");
                                    usr1.balance += amount;
                                    fwrite(&usr1, sizeof(struct user), 1, fp);
                                    fclose(fp);
                                    if(fwrite != 0){
                                        printf("\nYou have successfully transferred Ksh.%.2f to %s", amount, phone);
                                        strcpy(filename, usr.phone);
                                        fp = fopen(strcat(filename, ".dat"), "w");
                                        usr.balance -= amount;
                                        fwrite(&usr, sizeof(struct user), 1, fp);
                                        fclose(fp);
                                    }
                                }
                            }
                            break;
                        case 5:
                            printf("\nPlease enter your current password:\t");
                            scanf("%s", existingPassword);
                            if(strcmp(existingPassword, usr.password) == 0){
                                printf("Enter the new password: ");
                                scanf("%s", newPassword);
                                printf("Confirm the new password: ");
                                char confirmPassword[MAX_PASSWORD_LENGTH];
                                scanf("%s", confirmPassword);
                                
                                if (strcmp(newPassword, confirmPassword) == 0) {
                                    strcpy(usr.password, newPassword);
                                    fp = fopen(filename, "w");
                                    fwrite(&usr, sizeof(struct user), 1, fp);
                                    fclose(fp);
                                    printf("\nPassword successfully changed!");
                                } else {
                                    printf("\nPasswords do not match. Please try again.");
                                }
                            } else {
                                printf("\nIncorrect current password. Password change failed!");
                            }
                            break;
                        default:
                            printf("\nInvalid option");
                    }
                    printf("\nDo you want to continue the transaction [y/n]\t");
                    scanf(" %c", &cont);
                }
            } else {
                printf("\nInvalid password");
            }
        }
    }

    return 0;
}
