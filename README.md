# BUAA-CO-Logisim-Judger
Convert Logisim logging output into readable format.

## Usage
```sh
make
./logjudge -h   # display help message
./logjudge -v   # show version info
./logjudge logging.txt > output.txt  # convert format and print
fc output.txt expected.txt # Windows
diff output.txt expected.txt # Linux
```

## TODO
 - [ ] Logisim的logging功能不记录第一条指令，目前需要手动修正

## Contribution
Welcome PRs & issues!
  
## License
GPL v3.0