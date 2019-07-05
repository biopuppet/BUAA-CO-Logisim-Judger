#include <stdio.h>
#include <string.h>

#define MAXLN (500)

typedef struct entry
{
    int pc;
    int regwrite;
    int regaddr;
    int regdata;
    int memwrite;
    int memaddr;
    int memdata;
} Entry;

char buf[MAXLN], buf_log[MAXLN];

void usage()
{
    printf("usage: ./lfmt.exe <logisim_logging_file> <expected_result_file>\n");
    printf("\tPlease make sure your logisim logging header settings strictly follow the rules below:\n");
    printf("\t<PC> <RegWrite> <RegAddr> <RegData> <MemWrite> <MemAddr> <MemData>\n");
    return;
}

int parse(int width, int start)
{
    int num = 0;

    switch (width)
    {
    case 32:
        num = 0;
        for (int i = start; i < start + 40; i += 5)
        {
            num <<= 4;
            num += (buf[i] - '0') * 8 + (buf[i + 1] - '0') * 4 + (buf[i + 2] - '0') * 2 + (buf[i + 3] - '0');
        }
        break;
    case 5:
        return (buf[start] - '0') * 16 + (buf[start+2] - '0') * 8 + (buf[start+3] - '0') * 4 + (buf[start+4] - '0') * 2 + buf[start+5] - '0';
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

    if (!strcmp(argv[1], "-h") || argc < 3)
    {
        usage();
        return -1;
    }
    if ((fp_logging = fopen(argv[1], "r")) == NULL)
    {
        printf("cannot open %s for reading.\n", argv[1]);
        return -2;
    }
    if ((fp_output = fopen("output.txt", "w")) == NULL)
    {
        printf("cannot open %s\n for writing.\n", argv[2]);
        goto error1;
    }
    if ((fp_exp = fopen(argv[2], "r")) == NULL)
    {
        printf("cannot open %s\n for reading.\n", argv[2]);
        goto error2;
    }
    
    fgets(buf, MAXLN, fp_logging); // header
    while (fgets(buf, MAXLN, fp_logging) != NULL) {
        //printf("%s", buf);
        entry.pc = (parse(32, 0) << 2) + 0x3000;
        entry.regwrite = buf[40] - '0';
        entry.regaddr = parse(5, 42);
        entry.regdata = parse(32, 49);
        entry.memwrite = buf[89] - '0';
        entry.memaddr = parse(5, 91) << 2;
        entry.memdata = parse(32, 98);
        if (entry.regwrite && entry.regaddr) {
            fprintf(fp_output, "@%08x: $%2d <= %08x\n", entry.pc, entry.regaddr, entry.regdata);
        }
        if (entry.memwrite) {
            fprintf(fp_output, "@%08x: *%08x <= %08x\n", entry.pc, entry.memaddr, entry.memdata);
        }
    }
    fclose(fp_output);
    fp_output = fopen("output.txt", "r");
   
    /* file compare */
    fgets(buf, MAXLN, fp_exp); // @bug: 0x3000
    for (line = 1; fgets(buf, MAXLN, fp_exp) != NULL; ++line) {
        if (fgets(buf_log, MAXLN, fp_output) == NULL) {
            printf("your logisim output is short at line %d:\n******%s******\n", line, argv[2]);
            puts(buf);
            break;
        }
        if (buf[strlen(buf) - 1] == '\n') {
            buf[strlen(buf) - 1] = '\0';
        }
        if (buf_log[strlen(buf_log) - 1] == '\n') {
            buf_log[strlen(buf_log) - 1] = '\0';
        }
        if (strcmp(buf_log, buf)) {
            printf("found mismatch at line %d:\n", line);
            printf("******output.txt******\n");
            puts(buf_log);
            printf("******%s******\n", argv[2]);
            puts(buf);
        }
    }
    if (fgets(buf_log, MAXLN, fp_output) != NULL) {
        printf("your logisim output is too much at line %d:\n", line);
        printf("******output.txt******\n");
        puts(buf_log);
        printf("******%s******\n", argv[2]);
        puts(buf);
    }

    fclose(fp_exp);
error2:
    fclose(fp_output);
error1:
    fclose(fp_logging);
    return 0;
}