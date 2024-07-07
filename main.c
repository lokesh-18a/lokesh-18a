#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#define MAX_ACCTS 100
// Structure to represent Bank Account
struct bankAccount{
    char accountHolder[100];
    float balance;
    long int accountNo;
    int pin;
    int hasPin;
};
int min = 1000000000;
int max = 9999999999;
// Function to create a new bank account
void createAccount(struct bankAccount accounts[],int numAccounts){
    if(numAccounts < MAX_ACCTS){
        printf("Enter Account holder name: ");
        scanf("%s",accounts[numAccounts].accountHolder);
        srand(time(0));
        int num = rand() % (max - min + 1) + min;
        accounts[numAccounts].accountNo = num;
        printf("Account Number: %ld generated successfully.\n",accounts[numAccounts].accountNo);
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
    bool val = validAccountNumber(accountno);
    if(val){
        for(int i=0;i<numAccounts;i++){
            if(accounts[i].accountNo == accountno){
                accounts[i].hasPin = 1;
                break;
            }
        }
    }
    else{
        printf("Invalid Account Number. Exiting to Main Menu....\n");
        return;
    }
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
                accounts[i].pin = temp;
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
    int enteredPin,pinAttempts = 0, correctPin = 0;
    for(int i = 0;i < numAccounts;i++){
        if(accountNumber == accounts[i].accountNo){
            while(pinAttempts < 3 && !correctPin){
                printf("Enter your 4-digit PIN: ");
                scanf("%d",&enteredPin);
                if(enteredPin == accounts[i].pin){
                    correctPin = 1;
                    accounts[i].balance += amount;
                    printf("Deposit Successful. New Balance = %.4f\n",accounts[i].balance);
                }
                else{
                    pinAttempts++;
                    printf("Incorrect PIN. %d attempts remaining. \n",3 - pinAttempts);
                }
            }
            if(!correctPin){
                printf("Too many incorrect PIN attempts. Deposit failed.\n");
                return;
            }
        }
    }
    printf("Account not found. Deposit Failed!.\n");
}

/* Function to perform a withdrawal from a Bank Account*/
void withdrawal(struct bankAccount accounts[],int numAccounts,long int accountNumber,float amount){
    int enteredPin,pinAttempts = 0, correctPin = 0;
    for(int i = 0;i < numAccounts;i++){
        if(accounts[i].accountNo == accountNumber){
            while(pinAttempts < 3 && !correctPin){
                printf("Enter your 4-digit PIN: ");
                scanf("%d",&enteredPin);
                if(enteredPin == accounts[i].pin){
                    correctPin = 1;
                    if(amount <= accounts[i].balance){
                        accounts[i].balance -= amount;
                        printf("Withdrawal Successful. New Balance = %.4f\n",accounts[i].balance);
                    }
                    else
                        printf("Insufficient Funds Poor Peasant \U0001F612\n");
                }
                else{
                    pinAttempts++;
                    printf("Incorrect PIN. %d attempts remaining. \n",3 - pinAttempts);
                }
            }
            if(!correctPin){
                printf("Too many incorrect PIN attempts. Withdrawal failed.\n");
                return;
            }
        }
    }
    printf("Account not found. Withdrawal Failed!.\n");
}

/* Function to Check Bank Balance*/
void check(const struct bankAccount accounts[], int numAccounts,long int accountNumber){
    int enteredPin,pinAttempts = 0, correctPin = 0;
    for(int i = 0;i < numAccounts;i++){
        if(accountNumber == accounts[i].accountNo){
            while(pinAttempts < 3 && !correctPin){
                printf("Enter your 4-digit PIN: ");
                scanf("%d",&enteredPin);
                if(enteredPin == accounts[i].pin){
                    correctPin = 1;
                    printf("Account Found. Getting Details....\n");
                    printf("Account Holder : %s\nAccount Number : %ld\nBalance : %.4f\n",accounts[i].accountHolder,accounts[i].accountNo,accounts[i].balance);
                    return;
                }
                else{
                    pinAttempts++;
                    printf("Incorrect PIN. %d attempts remaining. \n",3 - pinAttempts);
                }
            }
            if(!correctPin){
                printf("Too many incorrect PIN attempts. Balance check failed.\n");
                return;
            }
        }
    }
    printf("Account not found. Unable to check balance.\n");
}
bool validAccountNumber(int accountNumber){
    if (accountNumber >= min && accountNumber <= max)
        return true;
    return false;
}
bool validAmount(float amount){
    if (amount >= 0.00 && amount <= 200000)
        return true;
    return false;
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
                   bool val = validAccountNumber(accountNumber);
                   if(val){
                        printf("Enter Deposit amount : ");
                        scanf("%f",&amount);
                        bool val2 = validAmount(amount);
                        if(val2){
                            deposit(accounts,numAccounts,accountNumber,amount);
                        }
                        else
                            printf("Invalid Amount. Exiting to Main Menu....\n");
                   }
                   else
                        printf("Invalid Account Number. Exiting to Main Menu....\n");                      
                   break;
            case 4:
                   printf("Enter Account Number for withdrawal : ");
                   scanf("%ld",&accountNumber);
                   bool val = validAccountNumber(accountNumber);
                   if(val){
                        printf("Enter Withdrawal amount : ");
                        scanf("%f",&amount);
                        bool val2 = validAmount(amount);
                        if(val2){
                            withdrawal(accounts,numAccounts,accountNumber,amount);
                        }
                        else
                            printf("Invalid Amount. Exiting to Main Menu....\n");
                   }
                   else
                        printf("Invalid Account Number. Exiting to Main Menu....\n");
                   break;
            case 5: 
                   printf("Enter Account Number to check Balance : ");
                   scanf("%ld",&accountNumber);
                   bool val = validAccountNumber(accountNumber);
                   if(val){
                        check(accounts,numAccounts,accountNumber);
                   }
                   else
                        printf("Exiting to Main Menu....\n");
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