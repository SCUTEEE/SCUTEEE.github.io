---
layout: article
title: 计算机组成原理
permalink: /courses/freshman/principle-of-computer/index
mathjax: false
mermaid: false
chart: false
mathjax_autoNumber: false
mode: immersive
tags: 计算机科学
key: principle-of-computer-index
nav_key: courses
show_edit_on_github: false
show_date: false
sidebar:
  nav: principle-of-computer
aside:
  toc: true
header:
  theme: dark
article_header:
  type: overlay
  theme: dark
  background_color: '#ffffff'
  background_image:
    src: http://p.ananas.chaoxing.com/star/1024_0/1384312343887gonph.jpg
    gradient: 'linear-gradient(0deg, rgba(0, 0, 0 , .5), rgba(0, 0, 0, .5))'
---

<!--more-->
<!-- more -->

# 复习要点

1. 2进制、8进制，16进制，10进制的表示格式以及互相转换
   > * 10 转 2、8、16：整数用除法，小数用乘法
   > * 2、8、16 转10：乘以权重再相加
   > * 2、8、16 互转：对应数字直接转换
2. 原码、反码、补码、移码的表示格式以及数据表示范围。
   > * 原码：最高位是符号位
   > * 反码：直接取反，符号位同原码
   > * 补码：正数同原码，负数反码加一
   > * 移码：补码加上 127（使最负的数=0）
3. IEEE754单精度、双精度机器数格式表示，真值与IEEE754机器数格式之间的转换。
   > * 单精度：32=1+8+23
   > * 双精度：64=1+11+52
   > * 尾数用补码，阶码用移码
   > * 阶码取最大值时，尾数=0 表示无穷，尾数≠0 表示 NaN
4. ASCII编码、汉字编码、字模、奇偶校验码的基本知识。
   > ASCII：8位，30H 为 '0'，41H 为 'A'，61H 为 'a'
   > 
   > * 外码：输入的方式（如拼音、五笔）
   > * 内码：区位码、国标码、机内码
   >   * 国标码 = 区位码 + 2020H；（跳过前32个）
   >   * 机内码 = 国标码 + 8080H；（最高位置1）
   > * 字模（字形码）：用于显示
   >
   > 奇校验：奇数个 1；偶校验：偶数个 1
5. 定点整数和定点小数的补码计算（加法和减法）。
   > 加法：连同符号位一起做加法
   >
   > 减法：减数取反后相加
6. 补码计算加减运算判断是否溢出有哪些方法？变形补码法如何判断溢出？
   > * 单符号位：同号数相加，结果符号不同，则溢出
   > * 最高有效位：最高有效位和符号位必须同时进位或借位，否则溢出
   > * 双符号位（变形补码）：使用两个符号位，00 表示正数，11 表示负数，运算后若出现 01 表示正溢，10 表示负溢
7. 指数和尾数都用补码格式，求浮点数的加法和减法，并给出计算过程。
   > 1. 对阶：小数点位置对齐
   > 2. 求和
   > 3. 规格化：
   >    * 左规：左移直到尾数最高位与符号位不同
   >    * 右规：右移直到整数部分为 0
   > 4. 舍入：0舍1入（相当于四舍五入）
8. 按地址码个数分类，指令可分为几类？各什么功能？
  > * 四地址指令：(A1)OP(A2)→A3，(A4)→下一条指令地址
  > * 三地址指令：(A1)OP(A2)→A3，(PC)→下一条指令地址
  > * 二地址指令：(A1)OP(A2)→A2，(PC)→下一条指令地址
  > * 一地址指令：OP(A)→A 或 (AX)OP(A)→AX
  > * 零地址指令：空操作、停机、堆栈
9.  指令格式由哪两部分组成？操作码和地址码各有什么作用？指令字长和机器字长具有什么关系？
    > * 指令 = 操作码+地址码
    > * 操作码：指令中表示机器操作性质和种类的部分
    > * 地址码：操作数的地址
    > * 指令字长 ≤ 机器字长
10. 缩短指令长度有哪些方法？
    > * 结果存放在目的操作数地址中
    > * 用CPU中的寄存器隐含一个OP数
    > * 把地址隐含在寄存器中
11. 如何进行可变长操作码扩展？（可参考P83页和P145页4.1题）
12. 有哪些操作数寻址方式？每种方式是如何寻址的？
    > * 隐含寻址：某个操作数（或操作数地址）隐含在某个通用寄存器
    > * 立即寻址：地址码部分是操作数本身
    > * 寄存器寻址：地址码字段直接给出寄存器编号
    > * 直接寻址：地址码部分给出操作数的有效地址
    > * 间接寻址：地址码部分给出存放操作数地址的存储单元的地址（简称：地址的地址）
    > * 寄存器间接寻址：指令地址码部分给出寄存器地址，操作数地址在指定的寄存器中
    > * 变址寻址：变址寄存器的内容与形式地址相加为操作数的有效地址
    > * 基址寻址：指令中的形式地址与基址寄存器的内容之和，作为操作数有效地址
    > * 相对寻址：程序计数器PC的当前内容与指令地址码部分给出的形式地址相加做为操作数的地址
    > * 堆栈寻址：操作数地址由堆栈指针SP指定
13. 8086有哪些寄存器？各有什么用途？8086标志寄存器有哪些标志位？各有何含义？
    > * 段寄存器：CS、DS、SS、ES，指示相应段的首址的高16位
    > * 通用R（8个16位R）：
    >   * SI、DI、SP、BP
    >   * AX、BX、CX、DX
    > * IP（指令指针）：指令地址=CS<<4+IP
    > * 标志寄存器FR（Flags Register）：CF、PF、AF、ZF、SF、TF、IF、DF、OF
14. 固定长操作码和扩展操作码指令条数计算
    > 固定长：条数 = 2^操作码长度
    > 扩展：略
15. CISC和RISC是什么含义？RISC机器具有什么特点？
    > * CISC (Complex Instruction Set Computer)复杂指令系统计算机
    >   * 执行一条指令要多次访问主存
    >   * 执行一条指令需要多个微周期
    >   * 流水线作业中，长指令的执行，妨碍其他指令的操作。
    >   * 寻址方式复杂，不易优化
    > * RISC (Reduced Instruction Set Computer)精简指令系统计算机
    >   * 指令系统选取使用频率最高的一些简单指令
    >   * 指令格式力求一致，寻址方式尽量简单
    >   * 指令的操作尽量都在CPU芯片上的寄存器之间进行，只有取数/存数指令访问主存
    >   * 指令尽量在一个周期内完成，注重编译的优化
    >   * 采用硬布线控制逻辑
16. CPU中通常有哪些寄存器？各有什么作用？
    > * 数据缓冲寄存器（DR）：暂时存放由内存读出的指令或者数据
    > * 指令寄存器（IR）：保存当前正在执行的一条指令
    > * 程序计数器（PC）：存放当前要执行的指令的地址（下一条指令的地址）
    > * 数据地址寄存器（AR）：保存当前CPU所访问的内存单元的地址
    > * 通用寄存器（Ri）：为算术运算和逻辑运算指令提供源操作数
    > * 状态条件寄存器（PSW）：保存算术指令和逻辑指令运行结果状态
17. 时钟周期、机器周期、CPU周期、存储周期和指令周期的概念以及相互之间的关系。
    > * 时钟周期：又称T周期（节拍脉冲，节拍周期），CPU执行一个微操作命令（控制信号）的最小时间单位。时钟周期通常定义为机器主频的倒数
    > * 机器周期：又称为CPU周期（节拍电位） ，以CPU从内存中读取一条指令字所需要的最短时间为基准
    > * 指令周期：是指从内存取出一条指令并完成该指令所需要的总时间。
18. 熟悉方框图语言设计指令周期的方法。对于给定的CPU结构图，会用方框图语言画出常见指令的执行流程（几个CPU周期？每个周期要完成的功能和发出哪些操作信号？）
    > * 方框：代表一个CPU周期
    > * 菱形：通常用来表示某种判别或测试，它依附于前面一个CPU周期，而不单独占用一个CPU周期
    > * ~ 表示公操作，例如中断处理、通道处理
19. 指令、微指令、程序、微程序有什么关系？水平微指令和垂直微指令各有什么特点？
    > * 微命令 组合→微指令 组合→微程序 组合→机器指令 组合→程序
    > * 水平型微指令：优点：一条微指令可同时发送多个微命令，微指令执行效率高，速度快，较灵活，并行操作能力强；微程序较短。缺点：微指令字长较长，明显地增加了控制存储器的横向容量。
    > 垂直型微指令：主要特点：微指令字采用短格式，每条微指令只能控制一二个微操作，并行控制能力差。但由于微指令和机器指令格式相类似，对于用户来说，垂直型微指令比较直观，容易掌握和便于使用。微指令字短，减少了横向控制存储器的容量；但微程序长，影响了执行的速度。
20. 存储器有哪些分类法？按存储材料分为几类？按存取方式分为几类？
    > 1. 按存储介质：半导体、磁介质、光介质等。
    > 2. 按信息的可保存性：易失性、非易失性
    > 3. 按存取方式：RAM、ROM、SAM、DAM
    > 4. 按在计算机系统中的功能：主存储器、辅助存储器、Cache存储器和控制存储器
21. 什么是存储器分层结构？分几层？每层存放什么信息？
    > 1. CPU寄存器：存运算的操作数和结果
    > 2. cache：存放经常访问的数据
    > 3. 主存：存正在运行程序的数据
    > 4. 辅助存储器：存长期保存的数据
    > 5. 脱机大容量存储器
22. SRAM和DRAM具有什么特点？DRAM有哪些刷新方法？
    > * SRAM（S-Static）：
    >   * 存取速度快，集成度低，功耗大
    >   * 不需要刷新
    >   * 用于 Register 或 cache
    > * DRAM（D-Dynamic）：
    >   * 存取速度慢，集成度高，功耗小
    >   * 需要定期刷新
    >   * 用于内存
    > * DRAM 的刷新方式：
    >   * 集中刷新方式：在2ms最大刷新周期内，集中对每一行进行刷新
    >     * 优点：读写操作不受刷新工作影响，系统存取速度比较快。
    >     * 缺点：集中刷新期间必须停止读写，形成一段死区。
    >   * 分散刷新方式：将存储周期分为两段,前段读/写/保持,后段刷新
    >     * 优点： 没有长的死区
    >     * 缺点：存取速度降低，降低整机的速度。刷新过于频繁
    >   * 异步刷新方式：按芯片行数决定所需的刷新周期数,并分散安排在最大刷新周期2ms中。
    >     * 优点：兼有前面两种的优点,对主存利用率和工作速度影响小。
    >     * 缺点：控制上稍复杂。
23. 对于给定规格的SRAM芯片，会求其地址线、数据线要数和存储容量
    > 地址 7 位：A6A0 （行列地址，分时复用）
    > /RAS 行选，/CAS列选（低电平将A6~A0 作为行或列地址锁存）
    > Din 数据输入，Dout数据输出，/WE 写使能
24. 半导体只读存储器（ROM）有哪些种类？各有何特点？
    > 1. 掩模型只读存储器 MROM
    > 2. 可编程（一次编程型）只读存储器 PROM
    > 3. 可擦除可编程（可重编程）只读存储器EPROM
    > 4. 电擦除可重写只读存储器EEPROM（E2PROM）
    （1）字擦除方式 （2）数据块擦除方式
    > 5. 闪速存储器 Flash EPROM
25. 会用给定的存储器芯片进行存储器扩展（包括字扩展、位扩展、字位同时扩展），会画扩展结构图并指出每个芯片的地址空间。
26. 什么是双端口存储器、多体并行交叉存储器、相联存储器、Cache存储器、虚拟存储器？
    > 双端口存储器：具有两组相互独立的读写控制线路
27. 什么是接口？接口的常用功能有哪些？
    > 接口：主机与外设以及外设与外设之间的信息交换的硬件
28. 主机与外设信息传输方式有哪些？说明每种方式的传输过程。
29. 对比查询式和中断式传输的特点。CPU响应外部中断需要具备什么条件？
    > * 查询式：代价低，CPU利用率低
    > * 中断式：提高CPU利用率，复杂（和程序查询方式比），传输效率受限（和DMA方式比）
30. 什么是中断？什么DMA？简要说明中断和DMA的处理过程。
    > * 中断请求、中断判优、中断响应、中断处理、中断返回
    > * 初始化、DMA请求、DMA响应、DMA传送、DMA结束
31.  常用指令和伪指令的格式、功能、使用注意事项要知道。（以PPT和上课所讲内容为准）
32.  说出变量定义、段定义、过程定义的格式和功能。
33. 能写出完整汇编程序的框架。
34. 编写返回一个整数的平方的子程序。
35. 编写求一个数组累加和的子程序。
    > 备注：子程序也叫过程，不需要定义数据段、堆栈段、代码段等，通常以proc开始，以 endp结尾，有特定功能，不能独立运行，只是程序的一部分供其它程序调用。完整程序就要包含数据段、堆栈段、代码段的定义，是可以汇编运行、功能齐全的程序。
36. 编写判断一个数据X符号的子程序。X>0返回1；X=0返回0；X<0返回-1
37. 编写判断一个字符X种类的子程序。X为数字返回0；X为大写字母返回1；X为小写字母返回2，其它字符返回-1.
