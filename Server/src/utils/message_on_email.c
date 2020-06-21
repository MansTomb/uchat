#include "server.h"

void mx_message_on_mail(char *email) {

    char cmd[1024];  // To hold the command.
    // char to[] = "trogalska2208@gmail.com"; // email id of the recepient.
    // char body[] = "Hello World2";    // email body.
    // char tempFile[100];     // name of tempfile.

    // strcpy(tempFile, MX_EMAIL_PATH); // generate temp file name.
    // FILE *fp = fopen(tempFile,"w"); // open it for writing.
    // fprintf(fp,"%s\n",body);        // write body to it.
    // fclose(fp);             // close it.

    sprintf(cmd, "cat < %s | mail -s %s %s", MX_EMAIL_PATH,
            "\"Test email\"", email);   // Prepare command.
    printf("%s", cmd);
    system(cmd);     // execute it.

}
