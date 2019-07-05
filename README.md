# BUAA-CO-Logisim-Judger

## 下载与安装
```bash
git clone https://github.com/Gone157/BUAA-CO-Logisim-Judger.git
cd BUAA-CO-Logisim-Judger
gcc logjudge.c -o logjudge.exe
```

## 使用方法
```bash
./logjudge.exe [-h] [<logging file> <expected result file>]
```
注意logjudge.exe**严格要求**logging的selection设置如下：
![logging_setting](http://github.com/Gone157/BUAA-CO-Logisim-Judger/pic/logging_setting.png)

## TODO
- logisim的logging功能不记录第一条指令，目前需要手动修正
- 或许可以不规定死logging格式？