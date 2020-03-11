# BUAA-CO-Logisim-Judger

## Install
```bash
git clone https://github.com/biopuppet/BUAA-CO-Logisim-Judger.git
cd BUAA-CO-Logisim-Judger
make
```

## Usage
```bash
./logjudge [-hcv]
```
本仓库已包含2个文件样例exp.txt和logging.txt，操作如下：
```bash
./logjudge -h # display help message

./logjudge    # convert (only)
./logjudge -c # convert and compare

./logjudge -v # show version info
```
执行完毕后，会由logging文件生成一个格式化后的output.txt文件，随后对output.txt与exp.txt进行对拍，并在控制台输出mismatch的部分。

也可以直接`fc output.txt exp.txt`，效果类似，推荐使用高级的文本对比工具（eg. VS Code）。
注意本对拍器**严格要求**Logisim的logging功能中的selection设置如下：

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
- Logisim的logging功能不记录第一条指令，目前需要手动修正

## Contribution
- 欢迎各类issue，pr，一起快乐对拍！
  
## License
GPL v3.0