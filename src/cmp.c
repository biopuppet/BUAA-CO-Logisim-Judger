/*
Copyright 2019 biopuppet

LogJudge is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License (LGPL) as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

LogJudge program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

*/

#include <stdio.h>
#include <string.h>

#include "logjudge.h"

/* file compare */
void cmp(const char *exp, const char *log)
{
    FILE *fp_log = NULL;
    FILE *fp_exp = NULL;
    char exp_buf[MAXLN] = {0};
    char log_buf[MAXLN] = {0};

    if ((fp_exp = fopen(exp, "r")) == NULL) {
        printf("cannot open %s for reading.\n", exp);
        return;
    }

    if ((fp_log = fopen(log, "r")) == NULL) {
        printf("cannot open %s for reading.\n", log);
        goto error2;
    }

    /*
     * Omit first line cuz Logisim starts logging once circuit state starts to
     * change.
     */
    fgets(exp_buf, MAXLN, fp_exp);  // @TODO: 0x3000

    unsigned line = 1;
    for (; fgets(exp_buf, MAXLN, fp_exp) != NULL; ++line) {
        if (fgets(log_buf, MAXLN, fp_log) == NULL) {
            printf("your logisim output is short at line %d:\n", line);
            puts(exp_buf);
            break;
        }
        if (exp_buf[strlen(exp_buf) - 1] == '\n') {
            exp_buf[strlen(exp_buf) - 1] = '\0';
        }
        if (log_buf[strlen(log_buf) - 1] == '\n') {
            log_buf[strlen(log_buf) - 1] = '\0';
        }
        if (strcmp(log_buf, exp_buf)) {
            printf("found mismatch at line %d:\n", line);
            printf("******output.txt******\n");
            puts(log_buf);
            printf("******exp.txt******\n");
            puts(exp_buf);
        }
    }
    if (fgets(log_buf, MAXLN, fp_log) != NULL) {
        printf("your logisim output is too much at line %d:\n", line);
        printf("******output.txt******\n");
        puts(log_buf);
        printf("******exp.txt******\n");
        puts(exp_buf);
    }

    fclose(fp_log);
error2:
    fclose(fp_exp);
}