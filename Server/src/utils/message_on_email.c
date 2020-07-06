#include "server.h"

void mx_message_on_mail(char *email, char *path) {
    char cmd[1024];  // To hold the command.

    if (!email || *email == '\0')
        return;

    sprintf(cmd, "cat < %s | mail -s %s %s", path, "\"Uchat info\"", email);
    printf("%s\n", cmd);
    system(cmd);     // Execute it.

}
