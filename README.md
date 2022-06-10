# Elca

## 简介

​		这是一个化简逻辑函数的小工具，有四种输入模式，一系列优化用户体验的小特性，支持latex输入，具备一键导出Markdown文档功能。而这一切的源头，来自于作者画完一张8*16的真值表和四张4\*4的卡诺图后，喧嚣的内心平静了……

## 使用说明

### classic（经典模式）

- 按提示输入自变量和因变量的值，用空格隔开，以`0`结束
- 为每个因变量输入逻辑表达式，可以输入异或`^`，逻辑非用`!`表示
- 回车得到每个因变量的真值表、极小项之和、最简SOP、卡诺图
- 提示是否输出为Markdown，输入`y`或`Y`程序将Markdown文档输出到指定路径并打开
- 回到模式选择界面，选择`0`退出

### handful（手动输入模式）

- 输入逻辑表达式改为输入真值表，逻辑表达式默认为最简SOP形式

### ~~zen（禅模式）~~开发中

### minium（极小项模式）

- 输入逻辑表达式改为输入因变量的极小项，以`,`隔开并以`)`结尾

## 程序特色

- 可以输入逻辑表达式，支持括号，异或
- 变量支持字符串
- 变量输入时可以使用`latex`语法，输出为Markdown时会直接输出`latex`格式
- 变量支持简写规则：例如变量输入`a_2=a`，你就可以在输入表达式时用`a`来替代`a_2`
- 表达式支持代入之前的结果：例如已经有表达式`x=a+b`，可以输入`y=x+c`。此时`y=a+b+c`
- 表达式可以省略`*`号，程序会自动检测

## 注意事项

- 默认路径为作者的桌面路径，请自行更改
- 因为`^`符号在逻辑里表示异或而在`latex`中代表上标，所以请尽量不要在变量中加入`^`，这样做会导致输出的Markdown文档里`^`被解析成$\oplus$，就像这样：$a^n \rightarrow a\oplus n$。不过好的一点是这不会影响最终计算结果。

## 算法实现

- 使用逆波兰表示法实现了对逻辑表达式的处理
- 使用改进的[Quine-McCluskey算法](https://baike.baidu.com/item/奎因-麦克拉斯基算法/23121029?fr=aladdin)实现了逻辑函数的化简

## 参考资料

[改进的Q-M逻辑函数化简方法 - 百度文库 (baidu.com)](https://wenku.baidu.com/view/586741dc28ea81c758f578e8.html)