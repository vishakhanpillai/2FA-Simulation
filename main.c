#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define USERNAME_SIZE 50
#define PASSWORD_SIZE 50
#define OTP_SIZE 6
#define MAX_USERS 100

typedef struct user{
    char username[USERNAME_SIZE];
    char password[PASSWORD_SIZE];
}user;

//Function to Generate OTP
void generateOTP( char otp[]){
    srand(time(0)); // gives a unique starting point for generating random number
    int i;
    for( i = 0; i < OTP_SIZE; i++){
        otp[i] = '0' + (rand() % 10);
    }
    otp[OTP_SIZE] = '\0';

    FILE *otpFile = fopen("otp.txt", "w"); // creates or modifies a file named otp.txt in write mode
    if(otpFile != NULL){
        fprintf(otpFile, "Your OTP Is: %s\n", otp);
        fclose(otpFile);
    }

    system(" start powershell -NoExit -Command Get-Content otp.txt");
}

//Function to Add users to a file for persistant storage
void saveUsersToFile(user user){
    FILE *file = fopen("user.txt", "a"); // creates a file user.txt in 'append' mode
    if(file != NULL){
        fprintf(file, "%s %s\n", user.username, user.password);
        fclose(file);
    }
}

// Function to load users from a file
int loadUser( user users[], int *userCount){
    FILE *file = fopen("user.txt", "r");
    *userCount = 0;

    if( file != NULL ){
        while(fscanf(file, "%s %s", users[*userCount].username, users[*userCount].password) != EOF){
            (*userCount)++;
        }
        fclose(file);
        return 1;
    }
    return 0;
}

// Function to check whether the user exists or not
int checkUserExists( char username[], user users[], int userCount){
    int i;

    for( i = 0; i < userCount; i++){
        if(strcmp(users[i].username, username) == 0){
            return 1;
        }
    }
    return 0;
}

// Function to Add a new User
void registerUser(){
    user users[MAX_USERS];
    int userCount = 0;
    loadUser(users, &userCount);

    user newUser;
    printf("===== User Registration Window =====\n");
    printf("Enter Username: ");
    scanf("%s", newUser.username);
    printf("Enter Password: ");
    scanf("%s", newUser.password);

    if(checkUserExists(newUser.username, users, userCount)){
        printf("User Already Exists. Please Try a Different Username.\n");
        return;
    }

    saveUsersToFile(newUser);
    printf("Registration Successful!!\n");
}

// Function to Login
int loginUser(){
    user user[MAX_USERS];
    int userCount = 0;
    loadUser(user, &userCount);

    if(userCount == 0){
        printf("No Users registered Yet. Please Register as a User First.\n");
        return 0;
    }

    char username[USERNAME_SIZE];
    char password[PASSWORD_SIZE];

    printf("===== User Login =====\n");
    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    int i = 0;

    for( i = 0; i < userCount; i++){
        if(strcmp(user[i].username, username) == 0 && strcmp(user[i].password, password) == 0){
            printf("Login Successful!!\n");

            char otp[OTP_SIZE + 1];
            generateOTP(otp); // Generates the OTP

            printf("Enter the OTP Sent To Your Device: ");
            char enteredOTP[OTP_SIZE + 1];
            scanf("%s", enteredOTP);

            if(strcmp(enteredOTP, otp) == 0){
                printf("2FA Verification Successful!\n");
                return 1;
            }
            else{
                printf("Invalid OTP, Verification Failed!\n");
                return 0;
            }

        }
    }

    printf("Invalid username or password.\n");
    return 0;
    
}

void menu(){
    printf("\n===== Two Factor Authentication System Menu =====\n");
    printf("1. Register User\n");
    printf("2. Login User\n");
    printf("3. Exit\n");
    printf("Enter Your Choice: ");
}

int main(){
    int choice;

    while (1)
    {
        menu();
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            registerUser();
            break;
        case 2:
            if(loginUser()){
                printf("Login Successful. Access Granted!\n");
            }
            else{
                printf("Login Unsuccessful. Access Denied!\n");
            }
            break;
        case 3:
            printf("Thanks For Swinging By!");
            return 0;        
        default:
            printf("Invalid Choice. Please Try Again\n");
        }
    }
    return 0;
}
