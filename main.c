#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define MAX_ACCTS 100
// Structure to represent Bank Account
struct bankAccount{
    char accountHolder[100];
    float balance;
    long int accountNo;
    int pin;
    int hasPin;
};
// Function to create a new bank account
void createAccount(struct bankAccount accounts[],int numAccounts){
    if(numAccounts < MAX_ACCTS){
        printf("Enter Account holder name: ");
        scanf("%s",accounts[numAccounts].accountHolder);
        printf("Enter Account number: ");
        scanf("%ld",&accounts[numAccounts].accountNo);;
        // Initially Bank Balance set to zero (0.00)
        accounts[numAccounts].balance = 0.00;
        numAccounts++;
        printf("Account created successfully.\n");
    }
    else{
        printf("cannot create more accounts.\n");
        printf("Maximum limit reached.\n");
        printf(" Please come after lunch time!!.");
    }
}
// Function for pin creation for deposits and withdrawals
void pinCreation(struct bankAccount accounts[],int numAccounts){
    int key,pin,temp;
    long int accountno;
    printf("Are you sure to create pin?\n");
    printf("Enter 0 for No and 1 for Yes\n");
    scanf("%d",&key);
    if(key){
        int accountFound = 0;
        printf("Enter Account number:");
        scanf("%ld",&accountno);
        for(int i=0;i<numAccounts;i++){
            if(accounts[i].accountNo == accountno){
                accountFound = 1;
                printf("Account Found Successfully!\n");
                printf("Enter the 4 digit password\n");
                scanf("%d",&pin);
                while(pin < 1000 || pin > 9999){
                    printf("Invalid PIN. Please enter a 4-digit number: ");
                    scanf("%d",&pin);
                }
                printf("Please Enter the PIN Again!\n");
                scanf("%d",&temp);
                while(temp!=pin){
                    printf("PINs do not match. Please Enter the PIN Again!\n");
                    scanf("%d",&temp);
                }
                printf("PIN created successfully!\n");
                break;
            }
        }
        if(!accountFound){
            printf("Account Not Found!\n");
            printf("Try Again!\n");
        }
    }
}

/* Function to perform a deposit into Bank Account*/
void deposit(struct bankAccount accounts[],int numAccounts,long int accountNumber,float amount){
    for(int i=0;i<numAccounts;i++){
        if(accountNumber == accounts[i].accountNo){
            accounts[i].balance += amount;
            printf("Deposit Successful. New Balance = %.4f\n",accounts[i].balance);
            return;
        }
    }
    printf("Account not found. Deposit Failed!.\n");
}

/* Function to perform a withdrawal from a Bank Account*/
void withdrawal(struct bankAccount accounts[],int numAccounts,long int accountNumber,float amount){
    for(int i=0;i<numAccounts;i++){
        if(accounts[i].accountNo == accountNumber){
            if(amount <= accounts[i].balance){
                accounts[i].balance -= amount;
                printf("Withdrawal Successful. New Balance = %.4f\n",accounts[i].balance);
                return;
            }
            else{
                printf("Insufficient funds. Withdrawal failed!!\n");
                return;
            }
        }
        else{
            printf("Account not found. Withdrawal failed\n");
        }
    }
}

/* Function to Check Bank Balance*/
void check(const struct bankAccount accounts[], int numAccounts,long int accountNumber){
    for(int i=0;i < numAccounts;i++){
        if(accountNumber == accounts[i].accountNo){
            printf("Account Holder : %s\nAccount Number : %ld\nBalance : %.4f\n",accounts[i].accountHolder,accounts[i].accountNo,accounts[i].balance);
            return;
        }
    }
    else{
        printf("Account not found. Unable to check balance.\n");
    }
}

int main(){
    struct bankAccount accounts[MAX_ACCTS];
    int numAccounts = 0;
    int choice;
    long int accountNumber;
    float amount;
    do{
        printf("\nConsole Bank\n");
        printf("1. Create a New Account\n");
        printf("2. PIN Creation\n");
        printf("3. Deposit\n");
        printf("4. Withdrawal\n");
        printf("5. Check Balance\n");
        printf("6. Exit\n");
        printf("Enter my(your) choice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                   createAccount(accounts, numAccounts);
                   break;
            case 2:
                   pinCreation(accounts,numAccounts);
                   break;
            case 3:
                   printf("Enter Account Number for deposit : ");
                   scanf("%ld",&accountNumber);
                   printf("Enter Deposit amount : ");
                   scanf("%f",&amount);
                   deposit(accounts,numAccounts,accountNumber,amount);
                   break;
            case 4:
                   printf("Enter Account Number for withdrawal : ");
                   scanf("%ld",&accountNumber);
                   printf("Enter Withdrawal amount : ");
                   scanf("%f",&amount);
                   withdrawal(accounts,numAccounts,accountNumber,amount);
                   break;
            case 5: 
                   printf("Enter Account Number to check Balance : ");
                   scanf("%ld",&accountNumber);
                   check(accounts,numAccounts,accountNumber);
                   break;
            case 6:
                   printf("Exiting the Bank. Thank You!\n");
                   break;
            default:
                    printf("Invalid choice. Please enter a valid option.\n");
        } 
    }
    while(choice!=6);
    return 0;
}