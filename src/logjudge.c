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

#include "cmp.h"
#include "logjudge.h"

static char buf[MAXLN], buf_log[MAXLN];

static const char *usage =
    "Usage: ./logjudge [OPTION]\n"
    "Convert Logisim logging output into readable format, and compare it with "
    "standard result.\n\n"
    "Please make sure your logisim logging header settings strictly follow the "
    "format below:\n"
    "\t<PC> <RegWrite> <RegAddr> <RegData> <MemWrite> <MemAddr> <MemData>\n\n"
    "Options:\n"
    "-c\t\tcompare the result with standard result in exp.txt, disabled on default\n"
    "-h\t\tdisplay help message and exit\n"
    "-v, --version\tdisplay version info and exit\n";

static const char *version = "LogJudge " VERSION "\nLicense GPLv3.\n"
                             "Written by biopuppet\n"
                             "Email: biopuppet@outlook.com\n"
                             "Github: https://github.com/biopuppet\n";

int parse(int width, int start)
{
    int num = 0;

    switch (width) {
    case 32:
        num = 0;
        for (int i = start; i < start + 40; i += 5) {
            num <<= 4;
            num += (buf[i] - '0') * 8 + (buf[i + 1] - '0') * 4 +
                   (buf[i + 2] - '0') * 2 + (buf[i + 3] - '0');
        }
        break;
    case 5:
        return (buf[start] - '0') * 16 + (buf[start + 2] - '0') * 8 +
               (buf[start + 3] - '0') * 4 + (buf[start + 4] - '0') * 2 +
               buf[start + 5] - '0';
    default:
        break;
    }

    return num;
}

int main(int argc, char **argv)
{
    FILE *fp_logging, *fp_output, *fp_exp;
    Entry entry;
    int line;
    int cmpflag = 0;

    if (argc > 1) {
        if (!strcmp(argv[1], "-c")) {
            cmpflag = 1;
        }
        else if (!strcmp(argv[1], "-v") || !strcmp(argv[1], "--version")) {
            puts(version);
            return 0;
        }
        else {
            puts(usage);
            return 0;
        }
    }
    if ((fp_logging = fopen(OUT_DIR "/logging.txt", "r")) == NULL) {
        printf("cannot open %s for reading.\n", argv[1]);
        return -2;
    }
    if ((fp_output = fopen(OUT_DIR "/output.txt", "w")) == NULL) {
        printf("cannot open output.txt for writing.\n");
        goto error1;
    }

    fgets(buf, MAXLN, fp_logging);  // header
    while (fgets(buf, MAXLN, fp_logging) != NULL) {
        // puts(buf);
        entry.pc = (parse(32, 0) << 2) + 0x3000;
        entry.regwrite = buf[40] - '0';
        entry.regaddr = parse(5, 42);
        entry.regdata = parse(32, 49);
        entry.memwrite = buf[89] - '0';
        entry.memaddr = parse(5, 91) << 2;
        entry.memdata = parse(32, 98);
        if (entry.regwrite && entry.regaddr) {
            fprintf(fp_output, "@%08x: $%2d <= %08x\n", entry.pc, entry.regaddr,
                    entry.regdata);
        }
        if (entry.memwrite) {
            fprintf(fp_output, "@%08x: *%08x <= %08x\n", entry.pc,
                    entry.memaddr, entry.memdata);
        }
    }
    fclose(fp_output);
    if (cmpflag) {
        cmp(OUT_DIR "/exp.txt", OUT_DIR "/output.txt");
    }

error2:
    fclose(fp_output);
error1:
    fclose(fp_logging);
    return 0;
}