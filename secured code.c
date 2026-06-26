#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PASSWORD_LIMIT 16
#define LOG_LIMIT 128

void login_system() {
    // In a production environment, this should be a salted cryptographic hash stored securely.
    char saved_password[] = "AdminSecret123";
    char user_password[PASSWORD_LIMIT];
    char log_message[LOG_LIMIT];

    printf("Enter admin password: ");

    // Remediation 1: Safe input restriction using fgets
    if (fgets(user_password, sizeof(user_password), stdin) == NULL) {
        return;
    }

    // Remove trailing newline character added by fgets
    user_password[strcspn(user_password, "\n")] = '\0';

    if (strcmp(user_password, saved_password) == 0) {
        printf("Access Granted!\n");

        FILE *fptr = fopen("app_access.log", "a"); // Relative path or configuration-driven
        if (fptr == NULL) {
            perror("Error opening log file");
            return;
        }

        // Remediation 2 & 3: Safe string building preventing buffer overflows
        snprintf(log_message, sizeof(log_message), "User successfully logged in with password tokens.");

        fprintf(fptr, "%s\n", log_message);
        fclose(fptr);
    } else {
        printf("Access Denied!\n");
    }
}

int main() {
    login_system();
    return 0;
}
