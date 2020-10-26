# BUAA-CO-Logisim-Judger
LogJudge is a **light-weight**, **cross-platform** tool for conversion from Logisim logging output to readable format.

e.g. Convert [logging.txt](logging.txt):
```c
PC	RegWrite	RegAddr	RegData	MemWrite	MemAddr	MemData
0000 0000 0000 0000 0000 0000 0000 0001	1	0 0001	1111 1111 1111 1111 0000 0000 0000 0000	0	0 0000	1111 1111 1111 1111 0000 0000 0000 0000
......
0000 0000 0000 0000 0000 0000 0001 1000	1	0 1001	1111 1111 1111 1111 1111 1111 0000 0000	0	0 0001	1000 0000 0000 0000 0000 0000 0000 0000
```
into [expected.txt](expected.txt):
```c
@00003000: $ 1 <= ffff0000
@00003004: $ 1 <= ffff0000
...
@00003060: $ 9 <= ffffff00
```
Note:
  - Logisim-logging does **NOT** record the initial state, thus the first line is missing. However, the initial state is not our concern since it's always the same in most cases.

## Features
  - Works on any end of line sequence(CRLF, LF)
  - The logging ports can be in any order as long as the `header line` is included.

## Usage
```sh
make
./logjudge -h   # display help message
./logjudge -v   # show version info
./logjudge logging.txt > output.txt  # convert format and print
fc output.txt expected.txt # Windows
diff output.txt expected.txt # Linux
```

## Contributing
Welcome all kinds of PRs & issues!
  
## License
[GPLv3](./LICENSE)

## Alternatives
- [buaa-co-p3-judge](https://github.com/karin0/buaa-co-p3-judge)
[@karin0](https://github.com/karin0)'s work helps to assemble and run your .asm program with MARS, load dumped instructions into the ROM in your circuit, simulate it with Logisim and compare the results with output from MARS.
