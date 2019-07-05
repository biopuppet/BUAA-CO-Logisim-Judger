# BUAA-CO-Logisim-Judger

## 下载与安装
```
git clone https://github.com/Gone157/BUAA-CO-Logisim-Judger.git
cd BUAA-CO-Logisim-Judger
gcc logjudge.c -o logjudge.exe
```

## 使用方法
```
./logjudge.exe [-h] [<logging file> <expected result file>]
```

## TODO
- logisim的logging功能不记录第一条指令，目前需要手动修正
- 或许可以不规定死logging格式？