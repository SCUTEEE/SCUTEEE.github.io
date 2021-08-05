---
layout: article
title: 树莓派 Ubuntu20.04-arm64 试用与设置
tags: [树莓派, Ubuntu]
author: Todd Zhou
license: false
show_author_profile: true
mathjax: false
mermaid: false
chart: false
mathjax_autoNumber: false
mode: normal
key: 2020-04-27-raspberry-pi-buster-setup
pageview: false
comment: true
show_edit_on_github: false
show_date: true
aside:
  toc: true
---

尝尝 64 位系统的树莓派！

<!--more-->
<!-- more -->

# 前言

之前在自己的博客里已经写过一篇 Raspbian 下的初始配置：[《树莓派初始配置及软件安装》](https://toddzhoufeng.github.io/document/2019/03/30/set-up-raspberrypi/)，最近打算翻新这篇文章时，发现 Ubuntu 已经出了 arm64 的镜像，于是干脆就抛弃了 32 位的渣渣 Raspbian.

本篇文章的环境为：

<table>
  <tr>
    <td>
      <a href="https://www.raspberrypi.org/products/raspberry-pi-3-model-b-plus/" target="_blank">树莓派3B+</a>
    </td>
    <td>
      <img src="https://res.cloudinary.com/canonical/image/fetch/f_auto,q_auto,fl_sanitize,w_236,h_151/https://assets.ubuntu.com/v1/c4a007b6-Raspberry+Pi+3.png" >
    </td>
  </tr>
  <tr>
    <td>
      <a href="https://ubuntu.com/download/raspberry-pi" target="_blank">ubuntu-20.04-preinstalled-server-arm64.img</a>
    </td>
    <td>
      <img src="https://res.cloudinary.com/canonical/image/fetch/f_auto,q_auto,fl_sanitize,w_350,h_227/https://assets.ubuntu.com/v1/9f09965f-1+-+Download+and+install+Ubuntu+Server+on+Raspberry+Pi.svg" width="250">
    </td>
  </tr>
  <tr>
    <td>
      <a href="https://ubuntu.com/download/raspberry-pi" target="_blank">TF卡、鼠标、键盘、显示屏</a>
    </td>
    <td>
      <img src="https://projects-static.raspberrypi.org/projects/raspberry-pi-setting-up/5bfb8f69592ea36d75df9d39b8abc186d7815cb6/en/images/pi-plug-in.gif" width="250">
    </td>
  </tr>
</table>

# 第一次开机

烧录完系统后，插卡，接好显示屏，上电。初始账户名和密码都是 `ubuntu`，系统会要求修改密码。由于是 ubuntu-server，所以没有安装桌面，只有命令行。

开机速度比 Raspbain 慢很多，需要 40~50s.

## 连接 WiFi

18.04 以后 Ubuntu Server 更换了网络管理工具，原理用的 `ifconfig` 没了，取而代之的是 `ip`. 先查看设备名：

```bash
ip a
```

`eth0` 对应于有线网，`wlan0` 对应于无线网。然后修改配置文件：

```bash
sudo nano /etc/netplan/50-cloud-init.yaml
```

```yaml
network:
    ethernets:
        eth0:
            optional: true
            dhcp4: true
    version: 2

    #add wifi setup
    wifis:
        wlan0:
            optional: true
            dhcp4: true
            access-points:
                "SSID": #SSID 替换为wifi名
                    password: "password" #password 替换为 wifi 密码
```

保存后，直接重启 `sudo reboot`。重启过程中会有一个表格，里面有一行是 `wlan0`，如果有 `true` 的字样，说明连接成功。也可以登录后尝试 `ping baidu.com` 看看能不能连接百度。

> 注：在某些教程，会要求修改完配置文件后执行 `sudo netplan try`，以及 `sudo netplan generate`，但我执行完后会出错（netplan-wpa-wlan0.service not found）。我忽略了这个错误，直接重启，依然能连上 wifi.

## 更换源

```bash
sudo mv /etc/apt/sources.list /etc/apt/sources.list.bak
sudo nano /etc/apt/sources.list
```

```bash
#阿里源
deb http://mirrors.aliyun.com/ubuntu-ports/ focal main restricted
deb http://mirrors.aliyun.com/ubuntu-ports/ focal-updates main restricted

deb http://mirrors.aliyun.com/ubuntu-ports/ focal universe
deb http://mirrors.aliyun.com/ubuntu-ports/ focal-updates universe

deb http://mirrors.aliyun.com/ubuntu-ports/ focal multiverse
deb http://mirrors.aliyun.com/ubuntu-ports/ focal-updates multiverse

deb http://mirrors.aliyun.com/ubuntu-ports/ focal-backports main restricted universe multiverse

deb http://mirrors.aliyun.com/ubuntu-ports/ focal-security main restricted 
deb http://mirrors.aliyun.com/ubuntu-ports/ focal-security universe
deb http://mirrors.aliyun.com/ubuntu-ports/ focal-security multiverse
```

然后执行：

```bash
sudo apt update
#如果出错就重启再执行
```

（得找个时间看看这些源到底对应哪些软件）

## 安装桌面（非必需）

官方推荐三种桌面：lubuntu、xubuntu 和 kubuntu，分别采用 lxde、xfce、kde。所占的资源递增，显示效果也递增。你可以从下面选择一条来执行：

```bash
#lubuntu-desktop 3118M
sudo apt-get install lubuntu-desktop

#xubuntu-desktop 2932M
sudo apt-get install xubuntu-desktop

#xubuntu-core 1396M
sudo apt install xubuntu-core^
```

我试了 xubuntu 和 lubuntu，两个都很卡，但相比之下，xubuntu 居然比 lubuntu 流畅？！

安装过程很长，因为会安装一些常用的应用软件，但不要马上离开，因为安装过程中手动需要选择 display manager，这个程序负责登录页面，选择 `lightdm`。然后你可以做一些其他事（可以看看 [scuteee.com](https://scuteee.com) 的其他文章）。总共需要一个多小时。

安装好后重启，桌面是这样的：

* xubuntu：仔细看，中间那个框说的是有一个程序崩溃了🤪

<center><img src="https://i.loli.net/2020/04/27/McZveU52xABEdj4.jpg" title="xubuntu 桌面"></center>

* lubuntu：忘了截图了……类似于电脑上的 Ubuntu.

## VNC（非必需）

VNC 主要是在没显示屏时用的，如果有的话没必要装。实在要装，可以根据下列网址：[https://www.ubuntu18.com/install-vnc-server-ubuntu-18/](https://www.ubuntu18.com/install-vnc-server-ubuntu-18/) 来操作。

## 基础软件

```bash
#C,C++ 编译器
sudo apt install gcc g++ make cmake
```

```bash
#pip
wget https://bootstrap.pypa.io/get-pip.py
sudo python3 get-pip.py
rm get-pip.py
```

# CPU性能测试

我们使用 nbench 来测试。运行以下命令：

```bash
wget http://www.math.utah.edu/~mayer/linux/nbench-byte-2.2.3.tar.gz
tar -xvzf nbench-byte-2.2.3.tar.gz
cd nbench-byte-2.2.3
make
./nbench
```

在 Pi 3B Plus+Ubuntu20.04 arm64 下的测试结果如下：

```bash
BYTEmark* Native Mode Benchmark ver. 2 (10/95)
Index-split by Andrew D. Balsa (11/97)
Linux/Unix* port by Uwe F. Mayer (12/96,11/97)

TEST                : Iterations/sec.  : Old Index   : New Index
                    :                  : Pentium 90* : AMD K6/233*
--------------------:------------------:-------------:------------
NUMERIC SORT        :           516.4  :      13.24  :       4.35
STRING SORT         :          151.79  :      67.82  :      10.50
BITFIELD            :      2.2323e+08  :      38.29  :       8.00
FP EMULATION        :          221.34  :     106.21  :      24.51
FOURIER             :           21785  :      24.78  :      13.92
ASSIGNMENT          :           10.66  :      40.56  :      10.52
IDEA                :            3253  :      49.75  :      14.77
HUFFMAN             :          1056.3  :      29.29  :       9.35
NEURAL NET          :           19.15  :      30.76  :      12.94
LU DECOMPOSITION    :          518.85  :      26.88  :      19.41
==========================ORIGINAL BYTEMARK RESULTS==========================
INTEGER INDEX       : 41.609
FLOATING-POINT INDEX: 27.362
Baseline (MSDOS*)   : Pentium* 90, 256 KB L2-cache, Watcom* compiler 10.0
==============================LINUX DATA BELOW===============================
CPU                 : 4 CPU
L2 Cache            :
OS                  : Linux 5.4.0-1008-raspi
C compiler          : gcc version 9.3.0 (Ubuntu 9.3.0-10ubuntu2)
libc                : libc-2.31.so
MEMORY INDEX        : 9.595
INTEGER INDEX       : 11.016
FLOATING-POINT INDEX: 15.176
Baseline (LINUX)    : AMD K6/233*, 512 KB L2-cache, gcc 2.7.2.3, libc-5.4.38
* Trademarks are property of their respective holder.
```

在 Pi 3 Plus+32 位的 Raspbian Buster（2020-02-13 已关闭桌面）上的测试结果如下：

```bash
BYTEmark* Native Mode Benchmark ver. 2 (10/95)
Index-split by Andrew D. Balsa (11/97)
Linux/Unix* port by Uwe F. Mayer (12/96,11/97)

TEST                : Iterations/sec.  : Old Index   : New Index
                    :                  : Pentium 90* : AMD K6/233*
--------------------:------------------:-------------:------------
NUMERIC SORT        :          831.63  :      21.33  :       7.00
STRING SORT         :          81.999  :      36.64  :       5.67
BITFIELD            :      2.3299e+08  :      39.97  :       8.35
FP EMULATION        :          177.39  :      85.12  :      19.64
FOURIER             :           12100  :      13.76  :       7.73
ASSIGNMENT          :          10.703  :      40.73  :      10.56
IDEA                :          2577.1  :      39.42  :      11.70
HUFFMAN             :          1049.2  :      29.09  :       9.29
NEURAL NET          :          13.308  :      21.38  :       8.99
LU DECOMPOSITION    :          464.45  :      24.06  :      17.37
==========================ORIGINAL BYTEMARK RESULTS==========================
INTEGER INDEX       : 38.446
FLOATING-POINT INDEX: 19.200
Baseline (MSDOS*)   : Pentium* 90, 256 KB L2-cache, Watcom* compiler 10.0
==============================LINUX DATA BELOW===============================
CPU                 : 4 CPU ARMv7 Processor rev 4 (v7l)
L2 Cache            :
OS                  : Linux 4.19.97-v7+
C compiler          : gcc version 8.3.0 (Raspbian 8.3.0-6+rpi1)
libc                : libc-2.28.so
MEMORY INDEX        : 7.938
INTEGER INDEX       : 11.059
FLOATING-POINT INDEX: 10.649
Baseline (LINUX)    : AMD K6/233*, 512 KB L2-cache, gcc 2.7.2.3, libc-5.4.38
* Trademarks are property of their respective holder.
```

在 Pi 4 + 32 位的 Raspbian Buster（2020-02-13 已关闭桌面）上的测试结果如下（从网上找的）：

```bash
BYTEmark* Native Mode Benchmark ver. 2 (10/95)
Index-split by Andrew D. Balsa (11/97)
Linux/Unix* port by Uwe F. Mayer (12/96,11/97)

TEST                : Iterations/sec.  : Old Index   : New Index
                    :                  : Pentium 90* : AMD K6/233*
--------------------:------------------:-------------:------------
NUMERIC SORT        :          1126.1  :      28.88  :       9.48
STRING SORT         :           140.2  :      62.65  :       9.70
BITFIELD            :      2.1127e+08  :      36.24  :       7.57
FP EMULATION        :          257.08  :     123.36  :      28.47
FOURIER             :           24522  :      27.89  :      15.66
ASSIGNMENT          :          19.855  :      75.55  :      19.60
IDEA                :          3942.7  :      60.30  :      17.90
HUFFMAN             :            1876  :      52.02  :      16.61
NEURAL NET          :          31.644  :      50.83  :      21.38
LU DECOMPOSITION    :          944.54  :      48.93  :      35.33
==========================ORIGINAL BYTEMARK RESULTS==========================
INTEGER INDEX       : 56.840
FLOATING-POINT INDEX: 41.088
Baseline (MSDOS*)   : Pentium* 90, 256 KB L2-cache, Watcom* compiler 10.0
==============================LINUX DATA BELOW===============================
CPU                 : 4 CPU ARMv7 Processor rev 3 (v7l)
L2 Cache            : 
OS                  : Linux 4.19.75-v7l+
C compiler          : gcc version 8.3.0 (Raspbian 8.3.0-6+rpi1) 
libc                : libc-2.28.so
MEMORY INDEX        : 11.288
INTEGER INDEX       : 16.833
FLOATING-POINT INDEX: 22.789
Baseline (LINUX)    : AMD K6/233*, 512 KB L2-cache, gcc 2.7.2.3, libc-5.4.38
* Trademarks are property of their respective holder.
```

在 RK3399+64位ubuntu 下的测试结果如下（从网上找的）：

```bash
BYTEmark* Native Mode Benchmark ver. 2 (10/95)
Index-split by Andrew D. Balsa (11/97)
Linux/Unix* port by Uwe F. Mayer (12/96,11/97)

TEST                : Iterations/sec.  : Old Index   : New Index
                    :                  : Pentium 90* : AMD K6/233*
--------------------:------------------:-------------:------------
NUMERIC SORT        :          1242.3  :      31.86  :      10.46
STRING SORT         :          389.92  :     174.23  :      26.97
BITFIELD            :      2.2521e+08  :      38.63  :       8.07
FP EMULATION        :          369.93  :     177.51  :      40.96
FOURIER             :           23017  :      26.18  :      14.70
ASSIGNMENT          :          21.776  :      82.86  :      21.49
IDEA                :          6673.9  :     102.07  :      30.31
HUFFMAN             :          2230.3  :      61.85  :      19.75
NEURAL NET          :           39.53  :      63.50  :      26.71
LU DECOMPOSITION    :          1050.7  :      54.43  :      39.31
==========================ORIGINAL BYTEMARK RESULTS==========================
INTEGER INDEX       : 79.409
FLOATING-POINT INDEX: 44.893
Baseline (MSDOS*)   : Pentium* 90, 256 KB L2-cache, Watcom* compiler 10.0
==============================LINUX DATA BELOW===============================
CPU                 : 6 CPU
L2 Cache            :
OS                  : Linux 4.4.143
C compiler          : gcc version 7.3.0 (Ubuntu/Linaro 7.3.0-27ubuntu1~18.04)
libc                : static
MEMORY INDEX        : 16.723
INTEGER INDEX       : 22.505
FLOATING-POINT INDEX: 24.899
Baseline (LINUX)    : AMD K6/233*, 512 KB L2-cache, gcc 2.7.2.3, libc-5.4.38
* Trademarks are property of their respective holder.
```

总结如下：

|硬件|系统|整数性能|浮点数性能|
|---|---|---|---|
|Pi3B+|64 Ubuntu|41.609|27.362|
|Pi3B+|32 Raspbian|38.446|19.200|
|pi4|32 Raspbian|56.840|41.088|
|RK3399|64 Ubuntu|79.409|44.893|

可以看出 64 位系统能提高一定性能，但也不能弥补硬件的差距。

# 安装 Jupyter Notebook

假设已经安装好了前面的基础软件。直接执行：

```bash
sudo pip3 install jupyter

#下面是扩展，可不装
sudo apt install libxml2-dev libxslt-dev
sudo pip install jupyter_contrib_nbextensions && jupyter contrib nbextension install
```

然后生成配置文件：

```bash
jupyter notebook --generate-config
```

修改配置文件：

```bash
sudo nano ~/.jupyter/jupyter_notebook_config.py
```

```python
#对应行修改为以下内容
c.NotebookApp.ip = '*'
c.NotebookApp.notebook_dir = '/home/ubuntu'
c.NotebookApp.open_browser = False
c.NotebookApp.port = 8888
```

设置密码：

```bash
jupyter notebook password
```

最后启动：

```bash
jupyter notebook
#后台运行
setsid jupyter notebook
```

# Tensorflow lite

安装依赖：

```bash
sudo apt-get install build-essential g++-arm-linux-gnueabihf
```

下载源码：

```bash
git clone https://github.com/tensorflow/tensorflow.git
cd tensorflow
```

```bash
./tensorflow/lite/tools/make/download_dependencies.sh
```

开始编译：

```bash
./tensorflow/lite/tools/make/build_aarch64_lib.sh
```

在 Ubuntu 20.04 上并没有raspicam摄像头的库，只能用 USB 摄像头。

参考：[官网：Build TensorFlow Lite for ARM64 boards](https://www.tensorflow.org/lite/guide/build_arm64)

# 一些机器学习库

```bash
sudo pip3 install numpy matplotlib scipy scikit-learn
```

# 使用感受

感觉并没有比 Raspbian 好多少，反而因为缺少很多库而很难安装软件，如果不使用 Raspberry Pi 的外设，倒是可以考虑作为服务器来用。