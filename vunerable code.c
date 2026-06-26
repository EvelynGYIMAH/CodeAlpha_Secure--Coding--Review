#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
void login_system(){
    char saved_password[] = "AdminSecret123";
    char user_password[16];
    char log_message[100];
    printf("Enter admin password:");
//Vulnerability 1: Insecure Input
    gets(user_password);
    if (strcmp(user_password, saved_password)==0){
        printf("Access Granted!\n");
//Vulnerability 2: Hardcoded sensitivity file path
        FILE *fptr =fopen("/var/log/secure_app.log","a");
        if (fptr ==NULL) return;
// Vulnerability 3:Risk of buffer overflow via concatenation
        strcpy(log_message, "User successfully logged in with password:");
        strcat(log_message, user_password);
        fprintf(ftpr, "%s\n", log_message);
        fclose(ftpr);
    }else{
        printf("Access Denied!\n");
        }
}
int main()
{
   login_system();
    return 0;
}
