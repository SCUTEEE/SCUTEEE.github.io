---
layout: article
title: 树莓派 4 全面设置（20200608更新）
tags: [教程, 树莓派]
author: Todd Zhou
license: false
show_author_profile: true
mathjax: false
mermaid: false
chart: false
mathjax_autoNumber: false
mode: normal
key: 2020-04-30-raspberry-pi-4-setup
pageview: true
comment: true
show_edit_on_github: false
show_date: true
aside:
  toc: true
---

把树莓派 4 打造成学习利器。

<!--more-->
<!-- more -->

# 前言

终于买了新的树莓派，我将尝试将之前搭过的环境在树莓派上重新搭建一次，同时尝试一些新东西。记录一下配置的过程。你需要准备：

<table>
  <tr>
    <td>
      <a href="https://www.raspberrypi.org/products/raspberry-pi-3-model-b-plus/" target="_blank">树莓派4B</a>
    </td>
    <td>
      <img src="https://res.cloudinary.com/canonical/image/fetch/f_auto,q_auto,fl_sanitize,w_236,h_151/https://assets.ubuntu.com/v1/a999bb5f-Raspberry+Pi+4.png" >
    </td>
  </tr>
  <tr>
    <td>
      <a href="https://ubuntu.com/download/raspberry-pi" target="_blank">Raspbian Buster Lite</a>
    </td>
    <td>
      <img src="https://www.raspberrypi.org/app/uploads/2012/02/Raspian_SD-150x150.png">
    </td>
  </tr>
  <tr>
    <td>
      <a href="https://ubuntu.com/download/raspberry-pi" target="_blank">TF卡、电脑、WiFi 网络</a>
    </td>
    <td>
      <img src="https://www.raspberrypi.org/app/uploads/2019/06/Pi4-Plugging-In-Help-Page-Animation.gif" width="250">
    </td>
  </tr>
</table>

# 第一次开机

## 上电前的准备

由于树莓派4 采用了 micro HDMI 接口，而我又没这种线，所以用不了屏幕，需要通过 SSH 来连接。开机之前，先用电脑在 TF 卡的根目录下新建一个名为 `SSH` 的空文件（文件名大写，无后缀）。

为了提前连接 wifi，在用电脑在 TF 卡的根目录下新建一个名为 `wpa_supplicant.conf` 的文件，然后输入（对应位置改为WiFi名和密码）：

```bash
country=CN
ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
update_config=1
 
network={
ssid="WiFi名"
psk="WiFi密码"
key_mgmt=WPA-PSK
priority=1
}
```

上电后，树莓派就会自动连接 WiFi，并开启 SSH。然后通过电脑连接树莓派，初始账户名为 `pi`，密码为 `raspberry`。

> 参考：[无屏幕和键盘配置树莓派WiFi和SSH](https://shumeipai.nxez.com/2017/09/13/raspberry-pi-network-configuration-before-boot.html)

## 连接 WiFi

上一步连接成功的话就可以跳过这部分，万一因为各种原因失败了，就找条网线连接路由器，通过电脑 SSH 连上树莓派后，输入：

```bash
sudo raspi-config
```

选择 `2 Network Options`，选择 `Wi-fi`，选择 `CN-China`，然后输入 wifi 名和密码即可。

## 换源&更新

```bash
sudo nano /etc/apt/sources.list
```

用 `#` 注释掉官方源，然后从下面选一条粘贴上去（个人推荐使用清华源）：

```bash
#清华源
deb http://mirrors.tuna.tsinghua.edu.cn/raspbian/raspbian/ buster main non-free contrib
#中科大源
deb http://mirrors.ustc.edu.cn/raspbian/raspbian/ buster main contrib non-free rpi
```

---

```bash
sudo nano /etc/apt/sources.list.d/raspi.list
```

用 `#` 注释掉官方源，然后从下面选一条粘贴上去：

```bash
#清华源
deb http://mirrors.tuna.tsinghua.edu.cn/raspberrypi/ buster main ui
#中科大源
deb http://mirrors.ustc.edu.cn/archive.raspberrypi.org/debian/ buster main ui
```

---

改好后执行：

```bash
sudo apt update
sudo apt upgrade
```

## 设置地区和时间

```bash
sudo raspi-config
```

选择 `4 Loclalisation Options`，选择 `Change Locale`，用空格选中 `zn_CN.UTF-8 UTF-8`，然后回车，选择 `en_GB.UTF-8 UTF-8`。

选择 `4 Loclalisation Options`，选择 `Change Timezone`，选择 `Asia`，选择 `Shanghai`。

## 设置键盘

键盘直接连接树莓派打字时，会出现一些字符错误，所以需要修改键盘键位。如果你不打算直接连接树莓派，可以跳过这步。

```bash
sudo raspi-config
```

选择 `4 Loclalisation Options`，选择 `Change Keyboard Layout`，第一个框回车，第二个框选择最下面的 `Other`，选择 `English(US)`，再选择 `English(US)`，之后一路回车即可。

> 2020.06.06 最近的系统好像设置键盘时有错误，可以参考一下这个 [https://raspberrypi.stackexchange.com/questions/43550/unable-to-reconfigure-locale-in-raspberry-pi](https://raspberrypi.stackexchange.com/questions/43550/unable-to-reconfigure-locale-in-raspberry-pi)

## pip

```bash
#安装 python3 的 pip
sudo apt install python3-pip

#换源
sudo nano /etc/pip.conf
```

将原文件内容改为：

```bash
[global]
timeout = 6000
index-url = https://pypi.tuna.tsinghua.edu.cn/simple
extra-index-url=https://www.piwheels.org/simple/
[install]
use-mirrors = true
mirrors = https://pypi.tuna.tsinghua.edu.cn/simple
trusted-host = mirrors.aliyun.com
```

上面是清华源，其他源也行：

```bash
#阿里云
http://mirrors.aliyun.com/pypi/simple/
#中国科技大学
https://pypi.mirrors.ustc.edu.cn/simple/
#豆瓣(douban)
http://pypi.douban.com/simple/
#中国科学技术大学
http://pypi.mirrors.ustc.edu.cn/simple/
```

换源后可能还是很慢，这是因为 piwheels.org 的服务器在国外。你可以选择把这个源删除，但我建议你不要这样做，因为 piwheels 不同于其他源，具体看这篇文章：[piwheels 是如何为树莓派用户节省时间的](http://www.linuxeden.com/a/60600)。

## 必备软件

```bash
#代码相关
sudo apt install git gcc g++ make cmake build-essential
```

## 代理

一些在国外的软件源、GitHub、pip源如果不走代理的话很慢……如果在国外有服务器的话，可以代理到服务器上。当然，我是没有的，跪求好心人施舍。

```bash
export ALL_PROXY=socks5://127.0.0.1:1080
```

可以将这个保存为指令（先在路由器上设置好固定ip）：

```bash
alias setproxy="export ALL_PROXY=socks5://127.0.0.1:1080"
alias unsetproxy="unset ALL_PROXY"
```

# 桌面显示

因为我手头有一块 3.5 寸 LCD 屏幕，所以打算安装个轻巧的桌面，便于有时候不想开电脑时直接操作，或者有时候显示一些基本信息。

## 安装桌面

我试过 xfce 和 lxde，都很卡；Raspbian 的 pixel 还好，但是也不够轻巧。这里我用的是：i3wm. 

```bash
#安装驱动
sudo apt install xserver-xorg-input-evdev xserver-xorg-input-kbd xserver-xorg-input-mouse
sudo apt install xserver-xorg-video-fbturbo #我一开始时没安装，后面发现少了这个会出错……

#安装 i3wm
sudo apt install i3 lightdm ttf-wqy-zenhei
```

如果你是用 HDMI 连接屏幕的，直接重启就能看到界面。关于 i3wm 怎么用，可以看后面部分。

## 安装3.5寸LCD屏幕

安装驱动：

```bash
sudo rm -rf LCD-show
git clone https://github.com/goodtft/LCD-show.git
chmod -R 755 LCD-show
cd LCD-show/
#注：会导致 raspi-config 的 camera 变为 disabled
sudo ./LCD35-show
#恢复hdmi输出：sudo ./LCD-hdmi
#旋转：sudo ./rotate.sh 90
```

执行完后会自动重启。重启完后会，屏幕会显示命令行。为了能够开机自动进入桌面，我们需要安装 xinit：

```bash
sudo apt install xinit

#配置开机执行命令
sudo nano .xinitrc
```

```bash
#!/bin/bash
exec i3
```

（上面已经安装过，这里只是记录一下自己的经历）尝试使用 `startx` 后依然无法进入，查看 log 后发现缺少了 `fbturbo`，于是安装：

```bash
sudo apt install xserver-xorg-video-fbturbo
```

再次尝试 `startx`，结果屏幕啥都没了……在电脑端重新运行 `./LCD35-show`，等到重启后，LCD 上显示 i3wm 桌面：<a href="https://i.loli.net/2020/05/01/HrKnRYkVQigXLby.jpg" data-lightbox="image" data-title="登录界面图片">点击查看登录界面图片</a>、<a href="https://i.loli.net/2020/04/30/OBc2YWKzEegUM5D.jpg" data-lightbox="image" data-title="桌面图片">点击查看桌面图片</a>

补充一下此时的内存：

```bash
pi@raspberrypi:~ $ free -h
              total        used        free      shared  buff/cache   available
Mem:          1.9Gi        76Mi       1.7Gi       8.0Mi       158Mi       1.7Gi
Swap:          99Mi          0B        99Mi
```

才用了 76M，简单明了，比 Raspbian 自带桌面的好多了。

扩展：[startx 及 xinit 介绍](https://blog.csdn.net/jsh13417/article/details/40148853)

## i3wm 的使用

i3wm 与传统的桌面不一样，准确来讲，它只是窗口管理器，只负责管理各个程序窗口怎么排列，而不像 windows 的桌面那样可以放图标。而且，i3wm 虽然显示了鼠标，但需要靠键盘来启动程序、管理窗口。第一次进入 i3wm 时，会要求你选择 `mod` 键，我选的是 `Win`。

仔细想想，其实桌面的功能无非就是用来打开应用程序，以及调整窗口大小。所以我们要学的也就几个组合键：

1. 打开 Terminal：`mod`+`Enter`
2. 打开应用程序：可以从 Terminal 里打开，也可以按 `mod`+`d`，然后输入应用名
3. 关闭窗口：`mod`+`Shift`+`q`（quit）
4. 改变焦点：`mod`+`方向键`（如果没有方向键，可以用 `j/k/l/;`代替
5. 移动窗口：`mod`+`Shift`+`方向键`
6. 窗口全屏：`mod`+`f`（full window），再按一次退出
7. 改变窗口堆叠方式：
   * 默认方式（平铺）：`mod`+`e`
   * 标签模式（类似于浏览器）：`mod`+`w`（可以用第 4 点来改变焦点）
8. 转换工作区：`mod`+`数字键`

当然，想要达到 windows 那种随心所欲的调整大小，可以看 [官方教程](https://i3wm.org/docs/userguide.html)。

## 设置壁纸

```bash
sudo apt install feh #图片浏览器
```

```bash
sudo nano .config/i3/config
```

```bash
#添加下面一行，会随机播放 ~/picture 里的图片
#不想随机播放就删除 --randomize
exec_always --no-startup-id feh --randomize --bg-fill ~/picture
```

然后按 `mod`+`Shift`+`c` 重新载入配置文件。（随便从 Pixiv 选了一张深色壁纸）

<center><img src="https://i.loli.net/2020/05/01/hz8jJ2RrQ6HVDn3.png" title="我的桌面壁纸"></center>

（好像暴露了我熬夜的不良习惯😱）

## 常用应用软件

#### 终端模拟器及其美化

* 树莓派上的终端模拟器是 `xfce4-termina`，类似的还有 `terminator`
* 如果想要轻量的终端，可以试试 `sakura`，缺点是配色比较单调
* 我使用的是 `xterm`. 下面是我的安装过程和配置文件

```bash
sudo apt install xterm x11-xserver-utils
```

下载 zsh（注：zsh 会多消耗约 10M 内存）：

```bash
sudo apt install zsh
sudo chsh -s /bin/zsh
sudo reboot
```

下载 oh-my-zsh：

```bash
#如果执行失败，直接从 gihub 上下载脚本后拷贝到树莓派执行
sudo sh -c "$(wget -O- https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
```

然后编辑 `sudo nano .zshrc`，在 `theme` 那一行填上自己想要的配色主题（[浏览配色主题](https://github.com/ohmyzsh/ohmyzsh/wiki/External-themes)），或者也可以填 "random"。其他关于 zsh 的设置自行Bing。

修改字体大小。单次修改字体大小可以按住 `Ctrl`，然后用鼠标右键选择。永久修改字体大小可以用：

```bash
nano .Xresources
```

```bash
xterm*locale: true
xterm*utf8: true
xterm*utf8Title: true

xterm*faceName: DejaVu Sans Mono:antialias=True:pixelsize=14
xterm*faceNameDoublesize:WenQuanYi Zen Hei Mono:antialias=True:pixelsize=14
```

最终的效果：

![2020-05-02-051209_480x320_scrot.png](https://i.loli.net/2020/05/02/67P5Ldsg9FEbSiC.png)

---

在这里补充一下，如果不想使用桌面，但又觉得命令行的字体太小，可以用下面这个命令设置：

```bash
sudo dpkg-reconfigure console-setup
#依次选择 UTF-8, latin1 and latin5, TernimusBold, 10x20(……)
```

#### 浏览器

树莓派4 的性能可以支持 Chromium。（Firefox 在树莓派上的表现不是很好）

```bash
sudo apt install chromium-browser
```

只是想简单地浏览网页可以使用：Midori

```bash
sudo apt install midori
```

参考：[5 best lightweight browsers for Raspberry Pi](https://www.addictivetips.com/ubuntu-linux-tips/best-lightweight-browsers-for-raspberry-pi/)

#### 文件浏览器

找了个比较小巧的文件浏览器 Thunar：

```bash
sudo apt install thunar
```

参考：[实用即王道，超好用的 Linux 文件管理器推荐](https://my.oschina.net/editorial-story/blog/1531474)

#### 截图

```bash
#截图软件
sudo apt install scrot

#延迟 2 秒后截图
scrot -d 2 
```

#### 图片浏览器

上面设置壁纸时装的 `feh` 已经足矣。如果想要有 GUI 的图片浏览器，可以试试：Nomacs 和 Mirage。

#### 音/视频播放器

网上很多人推荐 omxplayer，但貌似只能通过 HDMI 输出图像，不能通过 LCD 输出，所以看视频还是用 smplayer 好了。

```bash
sudo apt install omxplayer
```

不过 3.5 寸 LCD 屏幕的刷新率很低，看视频的体验极差。

> 在这里收藏一个 SSD1306O LED 的视频播放教程：[https://github.com/souviksaha97/oled-video-player](https://github.com/souviksaha97/oled-video-player)，方法是用 opencv

# 对系统进行备份

完成以上步骤之后，我们先备份一下，以免后面安装特殊软件时破坏了系统。下面是我的系统：

> 链接：[https://pan.baidu.com/s/1oLqeMPk84PnnAM6UQhSqsQ](https://pan.baidu.com/s/1oLqeMPk84PnnAM6UQhSqsQ)
> 提取码：3p54
> 用户名：pi
> 密码：test2020

重新烧录系统后，记得扩展存储空间：`sudo raspi-config` - `7 Advanced Options` - `A1 Expand File System`

参考：[树莓派学习笔记 篇四：树莓派4B 的系统备份方法大全（全卡+压缩备份）](https://post.smzdm.com/p/apzkgne7/)

# Python库

## numpy

```bash
sudo apt-get install libatlas-base-dev
sudo pip3 install numpy
```

## scikit-learn

```bash
sudo pip3 install scikit-learn
```

## jupyter notebook

先安装 cython：

```bash
sudo apt install cython3
```



```bash
sudo pip3 install jupyter

#下面是扩展，可不装
sudo apt install libxml2-dev libxslt-dev
sudo pip3 install jupyter_contrib_nbextensions && sudo jupyter contrib nbextension install
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
c.NotebookApp.notebook_dir = '/home/pi'
c.NotebookApp.open_browser = False
c.NotebookApp.port = 8888
c.NotebookApp.quit_button = False
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

换主题（用法请自行搜索，下面给出的是我的配置）：

```bash
sudo pip3 install jupyterthemes
jt --lineh 120 -f fira -t grade3 -ofs 10 -nfs 13 -tfs 13 -fs 12 -T -N
```



## opencv 4.2.0

参考：
* [Install OpenCV 4 on Raspberry Pi 4 and Raspbian Buster](https://www.pyimagesearch.com/2019/09/16/install-opencv-4-on-raspberry-pi-4-and-raspbian-buster/)
* [CMake编译OpenCV4.0时opencv_ffmpeg.dll等下载失败的解决思路总结](https://www.cnblogs.com/huluwa508/p/10142718.html)

#### 调整内存和swap

调整 GPU 的内存：

```bash
sudo raspi-config
```

依次选择 `Advanced Options`-`Memory Split`，然后输入 128，确定并重启。

然后增加 swap（针对 1GB ram 的树莓派）：

```bash
sudo nano /etc/dphys-swapfile
```

修改 CONF_SWAPSIZE 和 CONF_MAXSWAP，把后面的数字改为 2048 以上（2GB），然后使 SWAP 空间生效：

```bash
sudo /etc/init.d/dphys-swapfile stop
sudo /etc/init.d/dphys-swapfile start
```

通过下面命令确认：

```bash
free -h
```

#### 安装依赖

接着安装依赖：

```bash
#开发人员工具
sudo apt-get install build-essential cmake ccache pkg-config
#jpeg png tiff 等图像格式工具包
sudo apt-get install libjpeg-dev libtiff5-dev libjasper-dev libpng-dev
#视频格式工具包
sudo apt-get install libavcodec-dev libavformat-dev libswscale-dev libv4l-dev
sudo apt-get install libxvidcore-dev libx264-dev
#GUI库
sudo apt-get install libfontconfig1-dev libcairo2-dev
sudo apt-get install libgdk-pixbuf2.0-dev libpango1.0-dev
sudo apt-get install libgtk2.0-dev libgtk-3-dev
#数值优化函数包
sudo apt-get install libatlas-base-dev gfortran
#header files and a static library for Python
sudo apt-get install python3-dev
```

```bash
sudo pip3 install numpy
```

如果想要支持 python2，额外安装：

```bash
sudo apt-get install python-dev python-numpy
```

#### 下载库文件

```bash
cd ~

#选择适合自己的版本下载
wget -O opencv.zip https://github.com/opencv/opencv/archive/4.2.0.zip
wget -O opencv_contrib.zip https://github.com/opencv/opencv_contrib/archive/4.2.0.zip

unzip opencv.zip
unzip opencv_contrib.zip

mv opencv-4.2.0 opencv
mv opencv_contrib-4.2.0 opencv_contrib
```

#### 生成 cmake 文件

```bash
cd ~/opencv
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=RELEASE \
    -D CMAKE_INSTALL_PREFIX=/usr/local \
    -D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib/modules \
    -D ENABLE_NEON=ON \
    -D ENABLE_VFPV3=ON \
    -D BUILD_TESTS=OFF \
    -D INSTALL_PYTHON_EXAMPLES=OFF \
    -D OPENCV_ENABLE_NONFREE=ON \
    -D CMAKE_SHARED_LINKER_FLAGS=-latomic \
    -D BUILD_EXAMPLES=OFF ..
```

注意，`NEON` 和 `VFPv3` 用于优化 OpenCV 在 ARM 上的性能，但是 Pi Zero W 不支持这两个，需要去掉这两行。

运行过程中会从 `githubusercontent` 下载一些其他文件，但不幸的是，`githubusercontent` 被墙了……所以你需要手动下载。先运行一次cmake，然后需要下载的内容在这个文件：opencv/build/CMakeDownloadLog.txt，下载完后再运行一次 CMake。（有人需要的话我找个时间上传到 github 或 百度网盘）

<div><details>
<summary>运行 cmake 后的输出信息</summary>
{% highlight bash linenos %}
╭─pi@raspberrypi ~/opencv/build
╰─$ cmake -D CMAKE_BUILD_TYPE=RELEASE \
    -D CMAKE_INSTALL_PREFIX=/usr/local \
    -D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib/modules \
    -D ENABLE_NEON=ON \
    -D ENABLE_VFPV3=ON \
    -D BUILD_TESTS=OFF \
    -D INSTALL_PYTHON_EXAMPLES=OFF \
    -D OPENCV_ENABLE_NONFREE=ON \
    -D CMAKE_SHARED_LINKER_FLAGS=-latomic \
    -D BUILD_EXAMPLES=OFF ..
-- The CXX compiler identification is GNU 8.3.0
-- The C compiler identification is GNU 8.3.0
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Detected processor: armv7l
-- Performing Test HAVE_CXX_ATOMICS_WITHOUT_LIB (check file: cmake/checks/atomic_check.cpp)
-- Performing Test HAVE_CXX_ATOMICS_WITHOUT_LIB - Failed
-- Performing Test HAVE_CXX_ATOMICS_WITH_LIB (check file: cmake/checks/atomic_check.cpp)
-- Performing Test HAVE_CXX_ATOMICS_WITH_LIB - Success
-- Found PythonInterp: /usr/bin/python2.7 (found suitable version "2.7.16", minimum required is "2.7")
-- Found PythonLibs: /usr/lib/arm-linux-gnueabihf/libpython2.7.so (found suitable exact version "2.7.16")
Traceback (most recent call last):
  File "<string>", line 1, in <module>
ImportError: No module named numpy.distutils
-- Found PythonInterp: /usr/bin/python3 (found suitable version "3.7.3", minimum required is "3.2")
-- Found PythonLibs: /usr/lib/arm-linux-gnueabihf/libpython3.7m.so (found suitable exact version "3.7.3")
-- Looking for ccache - found (/usr/bin/ccache)
-- Performing Test HAVE_CXX_FSIGNED_CHAR
-- Performing Test HAVE_CXX_FSIGNED_CHAR - Success
-- Performing Test HAVE_C_FSIGNED_CHAR
-- Performing Test HAVE_C_FSIGNED_CHAR - Success
-- Performing Test HAVE_CXX_W
-- Performing Test HAVE_CXX_W - Success
-- Performing Test HAVE_C_W
-- Performing Test HAVE_C_W - Success
-- Performing Test HAVE_CXX_WALL
-- Performing Test HAVE_CXX_WALL - Success
-- Performing Test HAVE_C_WALL
-- Performing Test HAVE_C_WALL - Success
-- Performing Test HAVE_CXX_WERROR_RETURN_TYPE
-- Performing Test HAVE_CXX_WERROR_RETURN_TYPE - Success
-- Performing Test HAVE_C_WERROR_RETURN_TYPE
-- Performing Test HAVE_C_WERROR_RETURN_TYPE - Success
-- Performing Test HAVE_CXX_WERROR_NON_VIRTUAL_DTOR
-- Performing Test HAVE_CXX_WERROR_NON_VIRTUAL_DTOR - Success
-- Performing Test HAVE_C_WERROR_NON_VIRTUAL_DTOR
-- Performing Test HAVE_C_WERROR_NON_VIRTUAL_DTOR - Success
-- Performing Test HAVE_CXX_WERROR_ADDRESS
-- Performing Test HAVE_CXX_WERROR_ADDRESS - Success
-- Performing Test HAVE_C_WERROR_ADDRESS
-- Performing Test HAVE_C_WERROR_ADDRESS - Success
-- Performing Test HAVE_CXX_WERROR_SEQUENCE_POINT
-- Performing Test HAVE_CXX_WERROR_SEQUENCE_POINT - Success
-- Performing Test HAVE_C_WERROR_SEQUENCE_POINT
-- Performing Test HAVE_C_WERROR_SEQUENCE_POINT - Success
-- Performing Test HAVE_CXX_WFORMAT
-- Performing Test HAVE_CXX_WFORMAT - Success
-- Performing Test HAVE_C_WFORMAT
-- Performing Test HAVE_C_WFORMAT - Success
-- Performing Test HAVE_CXX_WERROR_FORMAT_SECURITY
-- Performing Test HAVE_CXX_WERROR_FORMAT_SECURITY - Success
-- Performing Test HAVE_C_WERROR_FORMAT_SECURITY
-- Performing Test HAVE_C_WERROR_FORMAT_SECURITY - Success
-- Performing Test HAVE_CXX_WMISSING_DECLARATIONS
-- Performing Test HAVE_CXX_WMISSING_DECLARATIONS - Success
-- Performing Test HAVE_C_WMISSING_DECLARATIONS
-- Performing Test HAVE_C_WMISSING_DECLARATIONS - Success
-- Performing Test HAVE_CXX_WMISSING_PROTOTYPES
-- Performing Test HAVE_CXX_WMISSING_PROTOTYPES - Failed
-- Performing Test HAVE_C_WMISSING_PROTOTYPES
-- Performing Test HAVE_C_WMISSING_PROTOTYPES - Success
-- Performing Test HAVE_CXX_WSTRICT_PROTOTYPES
-- Performing Test HAVE_CXX_WSTRICT_PROTOTYPES - Failed
-- Performing Test HAVE_C_WSTRICT_PROTOTYPES
-- Performing Test HAVE_C_WSTRICT_PROTOTYPES - Success
-- Performing Test HAVE_CXX_WUNDEF
-- Performing Test HAVE_CXX_WUNDEF - Success
-- Performing Test HAVE_C_WUNDEF
-- Performing Test HAVE_C_WUNDEF - Success
-- Performing Test HAVE_CXX_WINIT_SELF
-- Performing Test HAVE_CXX_WINIT_SELF - Success
-- Performing Test HAVE_C_WINIT_SELF
-- Performing Test HAVE_C_WINIT_SELF - Success
-- Performing Test HAVE_CXX_WPOINTER_ARITH
-- Performing Test HAVE_CXX_WPOINTER_ARITH - Success
-- Performing Test HAVE_C_WPOINTER_ARITH
-- Performing Test HAVE_C_WPOINTER_ARITH - Success
-- Performing Test HAVE_CXX_WSHADOW
-- Performing Test HAVE_CXX_WSHADOW - Success
-- Performing Test HAVE_C_WSHADOW
-- Performing Test HAVE_C_WSHADOW - Success
-- Performing Test HAVE_CXX_WSIGN_PROMO
-- Performing Test HAVE_CXX_WSIGN_PROMO - Success
-- Performing Test HAVE_C_WSIGN_PROMO
-- Performing Test HAVE_C_WSIGN_PROMO - Failed
-- Performing Test HAVE_CXX_WUNINITIALIZED
-- Performing Test HAVE_CXX_WUNINITIALIZED - Success
-- Performing Test HAVE_C_WUNINITIALIZED
-- Performing Test HAVE_C_WUNINITIALIZED - Success
-- Performing Test HAVE_CXX_WSUGGEST_OVERRIDE
-- Performing Test HAVE_CXX_WSUGGEST_OVERRIDE - Success
-- Performing Test HAVE_C_WSUGGEST_OVERRIDE
-- Performing Test HAVE_C_WSUGGEST_OVERRIDE - Failed
-- Performing Test HAVE_CXX_WNO_DELETE_NON_VIRTUAL_DTOR
-- Performing Test HAVE_CXX_WNO_DELETE_NON_VIRTUAL_DTOR - Success
-- Performing Test HAVE_C_WNO_DELETE_NON_VIRTUAL_DTOR
-- Performing Test HAVE_C_WNO_DELETE_NON_VIRTUAL_DTOR - Failed
-- Performing Test HAVE_CXX_WNO_UNNAMED_TYPE_TEMPLATE_ARGS
-- Performing Test HAVE_CXX_WNO_UNNAMED_TYPE_TEMPLATE_ARGS - Failed
-- Performing Test HAVE_C_WNO_UNNAMED_TYPE_TEMPLATE_ARGS
-- Performing Test HAVE_C_WNO_UNNAMED_TYPE_TEMPLATE_ARGS - Failed
-- Performing Test HAVE_CXX_WNO_COMMENT
-- Performing Test HAVE_CXX_WNO_COMMENT - Success
-- Performing Test HAVE_C_WNO_COMMENT
-- Performing Test HAVE_C_WNO_COMMENT - Success
-- Performing Test HAVE_CXX_WIMPLICIT_FALLTHROUGH_3
-- Performing Test HAVE_CXX_WIMPLICIT_FALLTHROUGH_3 - Success
-- Performing Test HAVE_C_WIMPLICIT_FALLTHROUGH_3
-- Performing Test HAVE_C_WIMPLICIT_FALLTHROUGH_3 - Success
-- Performing Test HAVE_CXX_WNO_STRICT_OVERFLOW
-- Performing Test HAVE_CXX_WNO_STRICT_OVERFLOW - Success
-- Performing Test HAVE_C_WNO_STRICT_OVERFLOW
-- Performing Test HAVE_C_WNO_STRICT_OVERFLOW - Success
-- Performing Test HAVE_CXX_FDIAGNOSTICS_SHOW_OPTION
-- Performing Test HAVE_CXX_FDIAGNOSTICS_SHOW_OPTION - Success
-- Performing Test HAVE_C_FDIAGNOSTICS_SHOW_OPTION
-- Performing Test HAVE_C_FDIAGNOSTICS_SHOW_OPTION - Success
-- Performing Test HAVE_CXX_PTHREAD
-- Performing Test HAVE_CXX_PTHREAD - Success
-- Performing Test HAVE_C_PTHREAD
-- Performing Test HAVE_C_PTHREAD - Success
-- Performing Test HAVE_CXX_FOMIT_FRAME_POINTER
-- Performing Test HAVE_CXX_FOMIT_FRAME_POINTER - Success
-- Performing Test HAVE_C_FOMIT_FRAME_POINTER
-- Performing Test HAVE_C_FOMIT_FRAME_POINTER - Success
-- Performing Test HAVE_CXX_FFUNCTION_SECTIONS
-- Performing Test HAVE_CXX_FFUNCTION_SECTIONS - Success
-- Performing Test HAVE_C_FFUNCTION_SECTIONS
-- Performing Test HAVE_C_FFUNCTION_SECTIONS - Success
-- Performing Test HAVE_CXX_FDATA_SECTIONS
-- Performing Test HAVE_CXX_FDATA_SECTIONS - Success
-- Performing Test HAVE_C_FDATA_SECTIONS
-- Performing Test HAVE_C_FDATA_SECTIONS - Success
-- Performing Test HAVE_CXX_MFPU_VFPV3
-- Performing Test HAVE_CXX_MFPU_VFPV3 - Success
-- Performing Test HAVE_CPU_NEON_SUPPORT (check file: cmake/checks/cpu_neon.cpp)
-- Performing Test HAVE_CPU_NEON_SUPPORT - Failed
-- Performing Test HAVE_CXX_MFPU_NEON (check file: cmake/checks/cpu_neon.cpp)
-- Performing Test HAVE_CXX_MFPU_NEON - Success
-- Performing Test HAVE_CPU_FP16_SUPPORT (check file: cmake/checks/cpu_fp16.cpp)
-- Performing Test HAVE_CPU_FP16_SUPPORT - Failed
-- Performing Test HAVE_CXX_MFPU_NEON_FP16_MFP16_FORMAT_IEEE (check file: cmake/checks/cpu_fp16.cpp)
-- Performing Test HAVE_CXX_MFPU_NEON_FP16_MFP16_FORMAT_IEEE - Success
-- Performing Test HAVE_CPU_BASELINE_FLAGS
-- Performing Test HAVE_CPU_BASELINE_FLAGS - Success
-- Performing Test HAVE_CXX_FVISIBILITY_HIDDEN
-- Performing Test HAVE_CXX_FVISIBILITY_HIDDEN - Success
-- Performing Test HAVE_C_FVISIBILITY_HIDDEN
-- Performing Test HAVE_C_FVISIBILITY_HIDDEN - Success
-- Performing Test HAVE_CXX_FVISIBILITY_INLINES_HIDDEN
-- Performing Test HAVE_CXX_FVISIBILITY_INLINES_HIDDEN - Success
-- Performing Test HAVE_C_FVISIBILITY_INLINES_HIDDEN
-- Performing Test HAVE_C_FVISIBILITY_INLINES_HIDDEN - Failed
-- Looking for pthread.h
-- Looking for pthread.h - found
-- Looking for posix_memalign
-- Looking for posix_memalign - found
-- Looking for malloc.h
-- Looking for malloc.h - found
-- Looking for memalign
-- Looking for memalign - found
-- Check if the system is big endian
-- Searching 16 bit integer
-- Looking for sys/types.h
-- Looking for sys/types.h - found
-- Looking for stdint.h
-- Looking for stdint.h - found
-- Looking for stddef.h
-- Looking for stddef.h - found
-- Check size of unsigned short
-- Check size of unsigned short - done
-- Using unsigned short
-- Check if the system is big endian - little endian
-- Found ZLIB: /usr/lib/arm-linux-gnueabihf/libz.so (found suitable version "1.2.11", minimum required is "1.2.3")
-- Found JPEG: /usr/lib/arm-linux-gnueabihf/libjpeg.so (found version "62")
-- Found TIFF: /usr/lib/arm-linux-gnueabihf/libtiff.so (found version "4.1.0")
-- Performing Test HAVE_C_STD_C99
-- Performing Test HAVE_C_STD_C99 - Success
-- Performing Test HAVE_C_WNO_UNUSED_VARIABLE
-- Performing Test HAVE_C_WNO_UNUSED_VARIABLE - Success
-- Performing Test HAVE_C_WNO_UNUSED_FUNCTION
-- Performing Test HAVE_C_WNO_UNUSED_FUNCTION - Success
-- Performing Test HAVE_C_WNO_SHADOW
-- Performing Test HAVE_C_WNO_SHADOW - Success
-- Performing Test HAVE_C_WNO_MAYBE_UNINITIALIZED
-- Performing Test HAVE_C_WNO_MAYBE_UNINITIALIZED - Success
-- Performing Test HAVE_C_WNO_MISSING_PROTOTYPES
-- Performing Test HAVE_C_WNO_MISSING_PROTOTYPES - Success
-- Performing Test HAVE_C_WNO_MISSING_DECLARATIONS
-- Performing Test HAVE_C_WNO_MISSING_DECLARATIONS - Success
-- Performing Test HAVE_C_WNO_IMPLICIT_FALLTHROUGH
-- Performing Test HAVE_C_WNO_IMPLICIT_FALLTHROUGH - Success
-- Found Jasper: /usr/lib/arm-linux-gnueabihf/libjasper.so (found version "1.900.1")
-- Found ZLIB: /usr/lib/arm-linux-gnueabihf/libz.so (found version "1.2.11")
-- Found PNG: /usr/lib/arm-linux-gnueabihf/libpng.so (found version "1.6.36")
-- Looking for /usr/include/libpng/png.h
-- Looking for /usr/include/libpng/png.h - found
-- Looking for semaphore.h
-- Looking for semaphore.h - found
-- Performing Test HAVE_CXX_WNO_SHADOW
-- Performing Test HAVE_CXX_WNO_SHADOW - Success
-- Performing Test HAVE_CXX_WNO_UNUSED
-- Performing Test HAVE_CXX_WNO_UNUSED - Success
-- Performing Test HAVE_CXX_WNO_SIGN_COMPARE
-- Performing Test HAVE_CXX_WNO_SIGN_COMPARE - Success
-- Performing Test HAVE_CXX_WNO_UNDEF
-- Performing Test HAVE_CXX_WNO_UNDEF - Success
-- Performing Test HAVE_CXX_WNO_MISSING_DECLARATIONS
-- Performing Test HAVE_CXX_WNO_MISSING_DECLARATIONS - Success
-- Performing Test HAVE_CXX_WNO_UNINITIALIZED
-- Performing Test HAVE_CXX_WNO_UNINITIALIZED - Success
-- Performing Test HAVE_CXX_WNO_SWITCH
-- Performing Test HAVE_CXX_WNO_SWITCH - Success
-- Performing Test HAVE_CXX_WNO_PARENTHESES
-- Performing Test HAVE_CXX_WNO_PARENTHESES - Success
-- Performing Test HAVE_CXX_WNO_ARRAY_BOUNDS
-- Performing Test HAVE_CXX_WNO_ARRAY_BOUNDS - Success
-- Performing Test HAVE_CXX_WNO_EXTRA
-- Performing Test HAVE_CXX_WNO_EXTRA - Success
-- Performing Test HAVE_CXX_WNO_DEPRECATED_DECLARATIONS
-- Performing Test HAVE_CXX_WNO_DEPRECATED_DECLARATIONS - Success
-- Performing Test HAVE_CXX_WNO_MISLEADING_INDENTATION
-- Performing Test HAVE_CXX_WNO_MISLEADING_INDENTATION - Success
-- Performing Test HAVE_CXX_WNO_DEPRECATED
-- Performing Test HAVE_CXX_WNO_DEPRECATED - Success
-- Performing Test HAVE_CXX_WNO_SUGGEST_OVERRIDE
-- Performing Test HAVE_CXX_WNO_SUGGEST_OVERRIDE - Success
-- Performing Test HAVE_CXX_WNO_INCONSISTENT_MISSING_OVERRIDE
-- Performing Test HAVE_CXX_WNO_INCONSISTENT_MISSING_OVERRIDE - Failed
-- Performing Test HAVE_CXX_WNO_IMPLICIT_FALLTHROUGH
-- Performing Test HAVE_CXX_WNO_IMPLICIT_FALLTHROUGH - Success
-- Performing Test HAVE_CXX_WNO_TAUTOLOGICAL_COMPARE
-- Performing Test HAVE_CXX_WNO_TAUTOLOGICAL_COMPARE - Success
-- Performing Test HAVE_CXX_WNO_MISSING_PROTOTYPES
-- Performing Test HAVE_CXX_WNO_MISSING_PROTOTYPES - Failed
-- Performing Test HAVE_CXX_WNO_REORDER
-- Performing Test HAVE_CXX_WNO_REORDER - Success
-- Performing Test HAVE_CXX_WNO_UNUSED_RESULT
-- Performing Test HAVE_CXX_WNO_UNUSED_RESULT - Success
-- Performing Test HAVE_CXX_WNO_CLASS_MEMACCESS
-- Performing Test HAVE_CXX_WNO_CLASS_MEMACCESS - Success
-- Checking for module 'gtk+-3.0'
--   Found gtk+-3.0, version 3.24.5
-- Checking for module 'gthread-2.0'
--   Found gthread-2.0, version 2.58.3
-- Could not find OpenBLAS include. Turning OpenBLAS_FOUND off
-- Could not find OpenBLAS lib. Turning OpenBLAS_FOUND off
-- Could NOT find Atlas (missing: Atlas_CLAPACK_INCLUDE_DIR)
-- Looking for sgemm_
-- Looking for sgemm_ - not found
-- Looking for pthread.h
-- Looking for pthread.h - found
-- Looking for pthread_create
-- Looking for pthread_create - found
-- Found Threads: TRUE
-- Looking for dgemm_
-- Looking for dgemm_ - found
-- Found BLAS: /usr/lib/arm-linux-gnueabihf/libf77blas.so;/usr/lib/arm-linux-gnueabihf/libatlas.so
-- Looking for cheev_
-- Looking for cheev_ - found
-- A library with LAPACK API found.
-- Performing Test HAVE_CXX_WNO_UNUSED_PARAMETER
-- Performing Test HAVE_CXX_WNO_UNUSED_PARAMETER - Success
-- Performing Test HAVE_CXX_WNO_UNUSED_LOCAL_TYPEDEFS
-- Performing Test HAVE_CXX_WNO_UNUSED_LOCAL_TYPEDEFS - Success
-- Performing Test HAVE_CXX_WNO_SIGN_PROMO
-- Performing Test HAVE_CXX_WNO_SIGN_PROMO - Success
-- Performing Test HAVE_CXX_WNO_TAUTOLOGICAL_UNDEFINED_COMPARE
-- Performing Test HAVE_CXX_WNO_TAUTOLOGICAL_UNDEFINED_COMPARE - Failed
-- Performing Test HAVE_CXX_WNO_IGNORED_QUALIFIERS
-- Performing Test HAVE_CXX_WNO_IGNORED_QUALIFIERS - Success
-- Performing Test HAVE_CXX_WNO_UNUSED_FUNCTION
-- Performing Test HAVE_CXX_WNO_UNUSED_FUNCTION - Success
-- Performing Test HAVE_CXX_WNO_UNUSED_CONST_VARIABLE
-- Performing Test HAVE_CXX_WNO_UNUSED_CONST_VARIABLE - Success
-- Performing Test HAVE_CXX_WNO_SHORTEN_64_TO_32
-- Performing Test HAVE_CXX_WNO_SHORTEN_64_TO_32 - Failed
-- Performing Test HAVE_CXX_WNO_INVALID_OFFSETOF
-- Performing Test HAVE_CXX_WNO_INVALID_OFFSETOF - Success
-- Performing Test HAVE_CXX_WNO_ENUM_COMPARE_SWITCH
-- Performing Test HAVE_CXX_WNO_ENUM_COMPARE_SWITCH - Failed
-- Could NOT find JNI (missing: JAVA_AWT_LIBRARY JAVA_JVM_LIBRARY JAVA_INCLUDE_PATH JAVA_INCLUDE_PATH2 JAVA_AWT_INCLUDE_PATH)
-- VTK is not found. Please set -DVTK_DIR in CMake to VTK build directory, or to VTK install subdirectory with VTKConfig.cmake file
-- Performing Test CXX_HAS_MFPU_NEON
-- Performing Test CXX_HAS_MFPU_NEON - Success
-- Performing Test C_HAS_MFPU_NEON
-- Performing Test C_HAS_MFPU_NEON - Success
-- Looking for dlerror in dl
-- Looking for dlerror in dl - found
-- Performing Test HAVE_C_WNO_UNDEF
-- Performing Test HAVE_C_WNO_UNDEF - Success
-- Performing Test HAVE_C_WNO_SIGN_COMPARE
-- Performing Test HAVE_C_WNO_SIGN_COMPARE - Success
-- ADE: Download: v0.1.1f.zip
-- OpenCV Python: during development append to PYTHONPATH: /home/pi/opencv/build/python_loader
-- Checking for modules 'libavcodec;libavformat;libavutil;libswscale'
--   Found libavcodec, version 58.35.100
--   Found libavformat, version 58.20.100
--   Found libavutil, version 56.22.100
--   Found libswscale, version 5.3.100
-- Checking for module 'libavresample'
--   No package 'libavresample' found
-- Checking for module 'gstreamer-base-1.0'
--   No package 'gstreamer-base-1.0' found
-- Checking for module 'gstreamer-app-1.0'
--   No package 'gstreamer-app-1.0' found
-- Checking for module 'gstreamer-riff-1.0'
--   No package 'gstreamer-riff-1.0' found
-- Checking for module 'gstreamer-pbutils-1.0'
--   No package 'gstreamer-pbutils-1.0' found
-- Checking for module 'libdc1394-2'
--   No package 'libdc1394-2' found
-- Caffe:   NO
-- Protobuf:   NO
-- Glog:   NO
-- Checking for module 'freetype2'
--   Found freetype2, version 22.1.16
-- Checking for module 'harfbuzz'
--   Found harfbuzz, version 2.3.1
-- freetype2:   YES (ver 22.1.16)
-- harfbuzz:    YES (ver 2.3.1)
-- HDF5: Using hdf5 compiler wrapper to determine C configuration
-- Found HDF5: /usr/lib/arm-linux-gnueabihf/hdf5/serial/libhdf5.so;/usr/lib/arm-linux-gnueabihf/libpthread.so;/usr/lib/arm-linux-gnueabihf/libsz.so;/usr/lib/arm-linux-gnueabihf/libz.so;/usr/lib/arm-linux-gnueabihf/libdl.so;/usr/lib/arm-linux-gnueabihf/libm.so (found version "1.10.4")
-- Module opencv_ovis disabled because OGRE3D was not found
-- No preference for use of exported gflags CMake configuration set, and no hints for include/library directories provided. Defaulting to preferring an installed/exported gflags CMake configuration if available.
-- Failed to find installed gflags CMake configuration, searching for gflags build directories exported with CMake.
-- Failed to find gflags - Failed to find an installed/exported CMake configuration for gflags, will perform search for installed gflags components.
-- Failed to find gflags - Could not find gflags include directory, set GFLAGS_INCLUDE_DIR to directory containing gflags/gflags.h
-- Failed to find glog - Could not find glog include directory, set GLOG_INCLUDE_DIR to directory containing glog/logging.h
-- Module opencv_sfm disabled because the following dependencies are not found: Eigen Glog/Gflags
-- Checking for module 'tesseract'
--   No package 'tesseract' found
-- Tesseract:   NO
-- HDF5: Using hdf5 compiler wrapper to determine C configuration
-- Excluding from source files list: modules/imgproc/src/corner.avx.cpp
-- Excluding from source files list: modules/imgproc/src/imgwarp.avx2.cpp
-- Excluding from source files list: modules/imgproc/src/imgwarp.sse4_1.cpp
-- Excluding from source files list: modules/imgproc/src/resize.avx2.cpp
-- Excluding from source files list: modules/imgproc/src/resize.sse4_1.cpp
-- Excluding from source files list: modules/imgproc/src/sumpixels.avx512_skx.cpp
-- Registering hook 'INIT_MODULE_SOURCES_opencv_dnn': /home/pi/opencv/modules/dnn/cmake/hooks/INIT_MODULE_SOURCES_opencv_dnn.cmake
-- opencv_dnn: filter out cuda4dnn source code
-- Excluding from source files list: <BUILD>/modules/dnn/layers/layers_common.avx.cpp
-- Excluding from source files list: <BUILD>/modules/dnn/layers/layers_common.avx2.cpp
-- Excluding from source files list: <BUILD>/modules/dnn/layers/layers_common.avx512_skx.cpp
-- Excluding from source files list: modules/features2d/src/fast.avx2.cpp
-- Performing Test HAVE_CXX_WNO_OVERLOADED_VIRTUAL
-- Performing Test HAVE_CXX_WNO_OVERLOADED_VIRTUAL - Success
-- xfeatures2d/boostdesc: Download: boostdesc_bgm.i
-- xfeatures2d/boostdesc: Download: boostdesc_bgm_bi.i
-- xfeatures2d/boostdesc: Download: boostdesc_bgm_hd.i
-- xfeatures2d/boostdesc: Download: boostdesc_binboost_064.i
-- xfeatures2d/boostdesc: Download: boostdesc_binboost_128.i
-- xfeatures2d/boostdesc: Download: boostdesc_binboost_256.i
-- xfeatures2d/boostdesc: Download: boostdesc_lbgm.i
-- xfeatures2d/vgg: Download: vgg_generated_48.i
-- xfeatures2d/vgg: Download: vgg_generated_64.i
-- xfeatures2d/vgg: Download: vgg_generated_80.i
-- xfeatures2d/vgg: Download: vgg_generated_120.i
-- data: Download: face_landmark_model.dat
-- Performing Test HAVE_CXX_WNO_UNUSED_PRIVATE_FIELD
-- Performing Test HAVE_CXX_WNO_UNUSED_PRIVATE_FIELD - Failed
--
-- General configuration for OpenCV 4.2.0 =====================================
--   Version control:               unknown
--
--   Extra modules:
--     Location (extra):            /home/pi/opencv_contrib/modules
--     Version control (extra):     unknown
--
--   Platform:
--     Timestamp:                   2020-05-02T16:23:42Z
--     Host:                        Linux 4.19.97-v7l+ armv7l
--     CMake:                       3.13.4
--     CMake generator:             Unix Makefiles
--     CMake build tool:            /usr/bin/make
--     Configuration:               RELEASE
--
--   CPU/HW features:
--     Baseline:                    VFPV3 NEON
--       requested:                 DETECT
--       required:                  VFPV3 NEON
--
--   C/C++:
--     Built as dynamic libs?:      YES
--     C++ Compiler:                /usr/bin/c++  (ver 8.3.0)
--     C++ flags (Release):         -fsigned-char -W -Wall -Werror=return-type -Werror=non-virtual-dtor -Werror=address -Werror=sequence-point -Wformat -Werror=format-security -Wmissing-declarations -Wundef -Winit-self -Wpointer-arith -Wshadow -Wsign-promo -Wuninitialized -Winit-self -Wsuggest-override -Wno-delete-non-virtual-dtor -Wno-comment -Wimplicit-fallthrough=3 -Wno-strict-overflow -fdiagnostics-show-option -pthread -fomit-frame-pointer -ffunction-sections -fdata-sections  -mfpu=neon -fvisibility=hidden -fvisibility-inlines-hidden -O3 -DNDEBUG  -DNDEBUG
--     C++ flags (Debug):           -fsigned-char -W -Wall -Werror=return-type -Werror=non-virtual-dtor -Werror=address -Werror=sequence-point -Wformat -Werror=format-security -Wmissing-declarations -Wundef -Winit-self -Wpointer-arith -Wshadow -Wsign-promo -Wuninitialized -Winit-self -Wsuggest-override -Wno-delete-non-virtual-dtor -Wno-comment -Wimplicit-fallthrough=3 -Wno-strict-overflow -fdiagnostics-show-option -pthread -fomit-frame-pointer -ffunction-sections -fdata-sections  -mfpu=neon -fvisibility=hidden -fvisibility-inlines-hidden -g  -O0 -DDEBUG -D_DEBUG
--     C Compiler:                  /usr/bin/cc
--     C flags (Release):           -fsigned-char -W -Wall -Werror=return-type -Werror=non-virtual-dtor -Werror=address -Werror=sequence-point -Wformat -Werror=format-security -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Winit-self -Wpointer-arith -Wshadow -Wuninitialized -Winit-self -Wno-comment -Wimplicit-fallthrough=3 -Wno-strict-overflow -fdiagnostics-show-option -pthread -fomit-frame-pointer -ffunction-sections -fdata-sections  -mfpu=neon -fvisibility=hidden -O3 -DNDEBUG  -DNDEBUG
--     C flags (Debug):             -fsigned-char -W -Wall -Werror=return-type -Werror=non-virtual-dtor -Werror=address -Werror=sequence-point -Wformat -Werror=format-security -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Winit-self -Wpointer-arith -Wshadow -Wuninitialized -Winit-self -Wno-comment -Wimplicit-fallthrough=3 -Wno-strict-overflow -fdiagnostics-show-option -pthread -fomit-frame-pointer -ffunction-sections -fdata-sections  -mfpu=neon -fvisibility=hidden -g  -O0 -DDEBUG -D_DEBUG
--     Linker flags (Release):      -latomic  -Wl,--gc-sections
--     Linker flags (Debug):        -latomic  -Wl,--gc-sections
--     ccache:                      YES
--     Precompiled headers:         NO
--     Extra dependencies:          atomic dl m pthread rt
--     3rdparty dependencies:
--
--   OpenCV modules:
--     To be built:                 aruco bgsegm bioinspired calib3d ccalib core datasets dnn dnn_objdetect dnn_superres dpm face features2d flann freetype fuzzy gapi hdf hfs highgui img_hash imgcodecs imgproc line_descriptor ml objdetect optflow phase_unwrapping photo plot python3 quality reg rgbd saliency shape stereo stitching structured_light superres surface_matching text tracking ts video videoio videostab xfeatures2d ximgproc xobjdetect xphoto
--     Disabled:                    world
--     Disabled by dependency:      -
--     Unavailable:                 cnn_3dobj cudaarithm cudabgsegm cudacodec cudafeatures2d cudafilters cudaimgproc cudalegacy cudaobjdetect cudaoptflow cudastereo cudawarping cudev cvv java js matlab ovis python2 sfm viz
--     Applications:                perf_tests apps
--     Documentation:               NO
--     Non-free algorithms:         YES
--
--   GUI:
--     GTK+:                        YES (ver 3.24.5)
--       GThread :                  YES (ver 2.58.3)
--       GtkGlExt:                  NO
--     VTK support:                 NO
--
--   Media I/O:
--     ZLib:                        /usr/lib/arm-linux-gnueabihf/libz.so (ver 1.2.11)
--     JPEG:                        /usr/lib/arm-linux-gnueabihf/libjpeg.so (ver 62)
--     WEBP:                        build (ver encoder: 0x020e)
--     PNG:                         /usr/lib/arm-linux-gnueabihf/libpng.so (ver 1.6.36)
--     TIFF:                        /usr/lib/arm-linux-gnueabihf/libtiff.so (ver 42 / 4.1.0)
--     JPEG 2000:                   /usr/lib/arm-linux-gnueabihf/libjasper.so (ver 1.900.1)
--     OpenEXR:                     build (ver 2.3.0)
--     HDR:                         YES
--     SUNRASTER:                   YES
--     PXM:                         YES
--     PFM:                         YES
--
--   Video I/O:
--     DC1394:                      NO
--     FFMPEG:                      YES
--       avcodec:                   YES (58.35.100)
--       avformat:                  YES (58.20.100)
--       avutil:                    YES (56.22.100)
--       swscale:                   YES (5.3.100)
--       avresample:                NO
--     GStreamer:                   NO
--     v4l/v4l2:                    YES (linux/videodev2.h)
--
--   Parallel framework:            pthreads
--
--   Trace:                         YES (with Intel ITT)
--
--   Other third-party libraries:
--     Lapack:                      NO
--     Eigen:                       NO
--     Custom HAL:                  YES (carotene (ver 0.0.1))
--     Protobuf:                    build (3.5.1)
--
--   OpenCL:                        YES (no extra features)
--     Include path:                /home/pi/opencv/3rdparty/include/opencl/1.2
--     Link libraries:              Dynamic load
--
--   Python 3:
--     Interpreter:                 /usr/bin/python3 (ver 3.7.3)
--     Libraries:                   /usr/lib/arm-linux-gnueabihf/libpython3.7m.so (ver 3.7.3)
--     numpy:                       /usr/local/lib/python3.7/dist-packages/numpy/core/include (ver 1.18.3)
--     install path:                lib/python3.7/dist-packages/cv2/python-3.7
--
--   Python (for build):            /usr/bin/python2.7
--
--   Java:
--     ant:                         NO
--     JNI:                         NO
--     Java wrappers:               NO
--     Java tests:                  NO
--
--   Install to:                    /usr/local
-- -----------------------------------------------------------------
--
-- Configuring done
-- Generating done
-- Build files have been written to: /home/pi/opencv/build
{% endhighlight %}
</details></div>

#### 编译

```bash
make -j4
```

`-j4` 表示使用 4 个 CPU 核心，这会消耗大量内存。如果是 Pi 3B+，可以调整为 `-j2`。Pi 4B 大概需要 1小时编译完成，Pi 3B+ 则需要 4~5 个小时。

如果最后没有出错（出现 100% 字样），就说明编译成功。

#### 安装

```bash
sudo make install
sudo ldconfig
```

#### 测试

```bash
cd ~
python3
>>> import cv2
>>> cv2.__version__
'4.2.0'
>>> 
```

## tensorflow

网上有预编译的 wheel，就不用从源码编译了。

从 [https://github.com/lhelontra/tensorflow-on-arm/releases](https://github.com/lhelontra/tensorflow-on-arm/releases) 里下载 
tensorflow-2.1.0-cp37-none-linux_armv7l.whl，发送到树莓派里后。

我们需要先注释掉 `/etc/pip.conf` 中 pywheel 那一行，因为 pywheel 中的 hash 值是不正确的。

此外还要安装 cython：

```bash
sudo apt install cython
```

然后用 pip 安装：

```bash
sudo pip3 install tensorflow-2.1.0-cp37-none-linux_armv7l.whl
```

## pytorch

网上有博主已经给出了编译好的文件，直接按照他的方法安装即可：

[树莓派（7）：树莓派4B+安装Pytorch新版本1.3（python3.7）](https://blog.csdn.net/ZhaoDongyu_AK47/article/details/105055856)

~~pytorch1.5 暂时还没编译成功。~~ （2020.06.06 更新：编译最新的 pytorch 成功，参考的是 [CSDN：在树莓派上安装Pytorch](https://blog.csdn.net/weixin_39965127/article/details/102686314)

先将 swap 增大到 4G（看 opencv 部分有步骤，把数值改成 4096 即可）

```bash
sudo apt-get install libopenblas-dev libblas-dev m4 cmake cache cython3 
sudo pip3 install cython pyyaml numpy
git clone --recursive https://github.com/pytorch/pytorch
cd pytorch
git submodule update --remote third_party/protobuf
```

```bash
# Limit the number of parallel jobs in a 1MB Pi to prevent thrashing
# export MAX_JOBS=2

# Disable features that don't make sense on a Pi
export USE_CUDA=0
export USE_CUDNN=0
export USE_MKLDNN=0
export USE_NNPACK=0
export USE_QNNPACK=0
export USE_DISTRIBUTED=0

# Disable testing, which takes ages
export BUILD_TEST=0
```

```bash
#开始编译
python3 setup.py build
#安装
sudo -E python3 setup.py install
```

整个过程大概需要半天时间。弄好之后，执行测试：

```bash
cd ~
python3
>>> import torch
>>> torch.__version__
'1.6.0a0+6a75f65'
>>> torch.cuda.is_available()
False
>>> z = torch.zeros(2,2)
>>> z
tensor([[0., 0.],
        [0., 0.]])
>>>
```

执行测试前一定要先从 pytorch 文件夹里退出来，否则会显示 `NameError: name '_C' is not defined`。

# docker

直接使用官方的安装脚本：

```bash
curl -sSL https://get.docker.com | sudo sh
```

docker 的用法请自行学习。

# nodejs

## 安装

具体版本要看特定的项目。

```bash
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.35.3/install.sh | bash

#nvm install node
#或安装特定版本 nvm install 8
#node --version #output:v14.2.0
```

# 其他

## DLNA

DLAN（DIGITAL LIVING NETWORK ALLIANCE）用于在设备直接分享媒体文件。比如可以在树莓派上下载视频后，直接在电视上观看而无需复制。我们需要安装 minidlna：

```bash
sudo apt install minidlna
```

修改配置文件：

```bash
sudo nano /etc/minidlna.conf
```

修改媒体文件的存储位置。找到下面的位置并添加相关内容（自己按英语注释添加），比如我用了三个文件夹分别存音乐、图片、视频：

```bash
#   * "A" for audio    (eg. media_dir=A,/var/lib/minidlna/music)
#   * "P" for pictures (eg. media_dir=P,/var/lib/minidlna/pictures)
#   * "V" for video    (eg. media_dir=V,/var/lib/minidlna/videos)
#   * "PV" for pictures and video (eg. media_dir=PV,/var/lib/minidlna/digital_ca$
media_dir=A,/home/pi/music
media_dir=P,/home/pi/picture
media_dir=V,/home/pi/video
```

修改 dlna设备名：

```bash
# Name that the DLNA server presents to clients.
# Defaults to "hostname: username".
friendly_name=PiDLNA
```

保存后重启：

```bash
sudo systemctl restart minidlna
```

手机上的 VLC 播放器可以支持查看 dlna。打开后就能看到相关的设备名，点进去就能播放媒体。

还可以通过网页端查看 minidlna 的运行情况。在浏览器输入：`ip地址:8200` 就能看到相关页面。

## 磁力下载

一般用 transmission 或 deluge。我比较喜欢 transmission ，体积比较小，而且多人用。网上已经有很多资料了，可以照着：[用树莓派搭建BT下载服务器](https://shumeipai.nxez.com/2013/09/08/raspberry-pi-bt-download-servers.html) （2013年的老教程）来安装，下面只是简单记录一下安装过程遇到的问题。

如果按照教程修改了 setting.conf 后依然登不上，根据 [官方wiki：Configuration-Files](https://github.com/transmission/transmission/wiki/Configuration-Files)，setting.conf 可能有多个存放位置，你可以依次尝试以下位置：

```bash
/etc/transmission-daemon/settings.json
/var/lib/transmission-daemon/info/settings.json
/home/pi/.config/transmission-daemon/settings.json
```

由于目前并没有多余的硬盘和 usb hub，所以暂时先下载到内存卡里。

## PythonTutor

一个可视化的 python 运行网页，非常适合用来分析算法。有在线版 [http://pythontutor.com/](http://pythontutor.com/)，但访问的速度较慢。可以考虑在本地部署一个。

```bash
git clone https://github.com/pgbovine/OnlinePythonTutor.git
sudo pip3 install bottle
cd OnlinePythonTutor/v5-unity/
python3 bottle_server.py
```

然后访问：`http://树莓派ip地址:8003/visualize.html`（千万不要访问 `http://树莓派ip地址:8003/`，会使得程序退出）

## frp 内网映射

参考自 [一款很好用的内网穿透工具--FRP](https://www.jianshu.com/p/00c79df1aaf0)。

首先要有一台公网服务器（称为服务端），树莓派（称为客户端）。

* 服务端

```bash
wget https://github.com/fatedier/frp/releases/download/v0.29.1/frp_0.29.1_linux_amd64.tar.gz
tar -zxvf  frp_0.29.1_linux_amd64.tar.gz
cd frp_0.29.1_linux_amd64
nano frps.ini #编辑配置文件
```

```bash
[common]
bind_port = 9583//frp服务连接端口，需与frpc的服务端口对应
vhost_http_port = 8080
```

```bash
#开启frp服务
./frps -c ./frps.ini
```

* 客户端

```bash
wget https://github.com/fatedier/frp/releases/download/v0.29.1/frp_0.29.1_linux_arm.tar.gz #这里注意版本同上面一致都为v0.29.1，由于树莓派内核等原因选择frp_0.29.1_linux_amd版本
tar -zxvf  frp_0.29.1_linux_arm.tar.gz
cd frp_0.29.1_linux_arm
nano frpc.ini #编辑配置文件
```

```bash
[common]
server_addr = ip//云服务器外网ip
server_port = 9583//frp服务连接端口，需与frps的服务端口对应

[ssh]//配置ssh连接
type = tcp
local_ip = 127.0.0.1
local_port = 22
remote_port = 6000//服务器远程端口

[web]//配置http服务
type = http
local_port = 80
custom_domains = **.**.com
```

```bash
#开启frp服务
./frpc -c ./frpc.ini
```

然后就可以在外网用 `ssh pi@服务器ip:6000` 来连接内网的树莓派。

## 从U盘启动

由于树莓派4有了 USB3.0，如果能从 USB 运行系统，运行速度会快一点。

目前找到最好的教程是：[How to Boot Raspberry Pi 4 From a USB SSD or Flash Drive](read://https_www.tomshardware.com/?url=https%3A%2F%2Fwww.tomshardware.com%2Fhow-to%2Fboot-raspberry-pi-4-usb)

~~可惜的是，当我实践后，速度并没有提高多少……目前怀疑是U盘的问题~~ 好吧，是我错了，测试的方法和结果如下：

```bash
sudo apt-get install hdparm
lsblk -f
#根据显示信息替换 sda2
sudo hdparm -Tt /dev/sda2
sudo sh -c "sync && echo 3 > /proc/sys/vm/drop_caches"
dd count=50 bs=1M if=/dev/zero of=test.img
rm test.img
dd count=50k bs=8k if=/dev/zero of=test.img
rm test.img
```

|系统位置|Cached Reads(MB/s)|Buffered Reads(MB/s)|写速度(MB/s)(count=50 bs=1M)|写速度（MB/s）(count=50k bs=8k)
|------|-------|------|---------|-----|
|TF卡|740.44|40.21|194|12.8|
|[32G 3.0 U盘](https://post.smzdm.com/p/a99vq39p/)|789.74|77.27|190|10.3|
|[64G 3.0 U盘](https://post.smzdm.com/p/amm5m394/)|743.97|88.89|190|21.0|

测试了很多次，每次都会有小范围浮动。可以看出，写速度差别不大，但读速度差别真的很大。有存电影需求的同学可以考虑一下用 U盘启动。以后等有闲钱了搞个 SSD 试试。

## 散热

树莓派4 的发热真的可怕，如果不用外壳的话，轻轻松松上 80℃。我在淘宝上买了个 Aluminium Heatsink Case（无风扇铝壳），平均温度大概是 51℃，而且刚好能装下屏幕。根据网上文章 [树莓派外壳比较](https://magpi.raspberrypi.org/articles/group-test-best-raspberry-pi-4-thermal-cases-tested-and-ranked) ，有没有风扇只差 4~5℃。当然，最理想的还是上水冷🐶

## 待尝试

[HOWTO: Replace the micro SD card's ext4 root partition by f2fs on the Raspberry PI](http://whitehorseplanet.org/gate/topics/documentation/public/howto_ext4_to_f2fs_root_partition_raspi.html)

> 玩树莓派这么久，感觉 Raspbian 才是最好的系统。