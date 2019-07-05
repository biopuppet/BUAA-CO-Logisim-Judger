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
本仓库已包含2个文件样例，操作如下：
```bash
./logjudge.exe logging.txt exp.txt
```
执行完毕后，会由logging文件生成一个格式化后的output.txt文件，随后对output.txt与exp.txt进行对拍，并在控制台输出mismatch的部分。

也可以直接在bat/cmd里`fc output.txt exp.txt`，效果类似。
注意本对拍器**严格要求**logging的selection设置如下：
![logging_setting](https://github.com/Gone157/BUAA-CO-Logisim-Judger/tree/master/pic/logging_setting.png)
| 序号  |   信号   |  位宽  |
| :---: | :------: | :----: |
|   1   |    pc    | 32-bit |
|   2   | RegWrite | 1-bit  |
|   3   | RegAddr  | 5-bit  |
|   4   | RegData  | 32-bit |
|   5   | MemWrite | 1-bit  |
|   6   | MemAddr  | 32-bit  |
|   7   | MemData  | 32-bit |

## TODO
- logisim的logging功能不记录第一条指令，目前需要手动修正
- 或许可以不规定死logging格式？但是大家的命名都五花八门，没有一个统一规范，于是这里规定死了。

## Contribution
- 欢迎各类issue，pr，一起快乐对拍！
  
## License
GPL v3.0