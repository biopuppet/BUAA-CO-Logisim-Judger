/*
Copyright (C) 2019-2020 Liu Fengbo <biopuppet@outlook.com>

LogJudge is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License (LGPL) as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

LogJudge program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this program. If not, see
<http://www.gnu.org/licenses/>.

*/

#include <stdio.h>
#include <string.h>

struct item {
  const char *name;
  int width;
  unsigned val;
};

enum {
  PC = 0,
  RegWrite,
  RegAddr,
  RegData,
  MemWrite,
  MemAddr,
  MemData,
};

#define VERSION    "1.0.0"
#define LINE_LEN   (138 + 2)

static char buf[LINE_LEN];

static struct item items[] = {
  {
    .name = "PC",
    .width = 32,
  },
  {
    .name = "RegWrite",
    .width = 1,
  },
  {
    .name = "RegAddr",
    .width = 5,
  },
  {
    .name = "RegData",
    .width = 32,
  },
  {
    .name = "MemWrite",
    .width = 1,
  },
  {
    .name = "MemAddr",
    .width = 5,
  },
  {
    .name = "MemData",
    .width = 32,
  },
};

static struct item *ordered_items[7];

static void usage(const char *arg)
{
  fprintf(
    stdout,
    "Usage: %s [OPTION] <logging_file>\n"
    "Convert Logisim logging output into readable format.\n"
    "Options:\n"
    "-h, --help\tdisplay help message and exit\n"
    "-v, --version\tdisplay version info and exit\n",
    arg);
}

static const char *version =
  "LogJudge " VERSION "\n"
  "Copyright (C) 2019-2020 Liu Fengbo <biopuppet@outlook.com>";

char *parse(struct item *item, char *p)
{
  int num;
  int shift;

  if (!item || !p) {
    return NULL;
  }

  switch (item->width) {
  case 32:
    shift = 40;
    num = 0;
    int i;
    for (i = 0; i < 40; i += 5) {
      num <<= 4;
      num += (p[i] - '0') * 8 + (p[i + 1] - '0') * 4 +
             (p[i + 2] - '0') * 2 + (p[i + 3] - '0');
    }
    break;
  case 5:
    shift = 7;
    num = (p[0] - '0') * 16 + (p[2] - '0') * 8 + (p[3] - '0') * 4 +
          (p[4] - '0') * 2 + p[5] - '0';
    break;
  case 1:
    shift = 2;
    num = p[0] - '0';
    break;
  default:
    shift = 0;
    num = 0;
    break;
  }

  item->val = num;
  return p + shift;
}

int main(int argc, char **argv)
{
  FILE *fp_logging, *fp_output;
  const char *logging_file;
  char *p;
  int i, j;

  if (argc != 2) {
    goto print_usage;
  }
  if (!strcmp(argv[1], "-v") || !strcmp(argv[1], "--version")) {
    puts(version);
    return 0;
  }
  else if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
    goto print_usage;
  }

  logging_file = argv[argc - 1];

  if ((fp_logging = fopen(logging_file, "r")) == NULL) {
    fprintf(stderr, "No such file `%s'\n", logging_file);
    return -2;
  }

  fp_output = stdout;

  for (i = 0; i < 7; ++i) {
    char tmp[10] = {0};
    fscanf(fp_logging, " %10s", tmp);
    for (j = 0; j < 7; ++j) {
      if (!strcmp(tmp, items[j].name)) {
        ordered_items[i] = items + j;
        break;
      }
    }
    if (j >= 7) {
      fprintf(stderr, "Unrecognized logging header at `%s'\n", tmp);
      goto out_logging;
    }
  }

  fgets(buf, LINE_LEN, fp_logging);
  while (fgets(buf, LINE_LEN, fp_logging) != NULL) {
    for (i = 0, p = buf; i < 7; ++i) {
      while (*p != '0' && *p != '1') {
        ++p;
      }
      p = parse(ordered_items[i], p);
    }

    /* Adjust PC and memory address */
    items[PC].val = (items[PC].val << 2) + 0x3000;
    items[MemAddr].val <<= 2;

    if (items[RegWrite].val && items[RegAddr].val) {
      fprintf(fp_output, "@%08x: $%2d <= %08x\n", items[PC].val,
              items[RegAddr].val, items[RegData].val);
    }
    if (items[MemWrite].val) {
      fprintf(fp_output, "@%08x: *%08x <= %08x\n", items[PC].val,
              items[MemAddr].val, items[MemData].val);
    }
  }

out_logging:
  fclose(fp_logging);
  return 0;

print_usage:
  usage(argv[0]);
  return 0;
}
