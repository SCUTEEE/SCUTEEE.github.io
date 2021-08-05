---
layout: article
title: Image Processing in C
permalink: /software/cips/index
mathjax: false
mermaid: false
chart: false
mathjax_autoNumber: false
mode: immersive
tags: [图像处理, C]
key: 0-cips-index
nav_key: software
show_edit_on_github: false
show_date: false
sidebar:
  nav: cips
aside:
  toc: true
header:
  theme: dark
article_header:
  type: overlay
  theme: dark
  background_color: '#ffffff'
  background_image:
    src: https://media.geeksforgeeks.org/wp-content/cdn-uploads/Clanguage-1024x341.png
    gradient: 'linear-gradient(0deg, rgba(0, 0, 0 , .5), rgba(0, 0, 0, .5))'
---

<!--more-->

&emsp;&emsp;《Image Processing in C, Second Edition》by Dwayne Phillips 的中文翻译（有一定精简），仅用作学习使用。

其他资料：

* [UQC146S1: Introduction to Image Processing in C](http://www.cems.uwe.ac.uk/~irjohnso/uqc146s1.html#C)

## 序言

&emsp;&emsp;本书是图像处理的基础教程。每章都会用图文解释基础概念，将处理结果用图像展示出来，并用 C 实现处理过程。书中的内容来自于 *the  C/C++  Users  Journal* 杂志从 1990 到 1998 年间刊登的文章，以及本书在 1994 年出版的第一版。这本第二版在每章中都包含了新的内容。

&emsp;&emsp;本书第一版的目标是（1）介绍图像处理（2）提供图像处理工具（3）提供图像处理软件作为后续深入学习的基础（4）使上述资源都能被使用不同电脑的人获得。

&emsp;&emsp;这些目标现在也保持不变，但现在情况有很多变化。本书的更新则反应了这些变化。网络的广泛使用，使得很多免费图像能提供给我们这些想要处理图像的人。同时，还有很多廉价的软件可以用来显示图像、转换图像格式。

&emsp;&emsp;家庭电脑和笔记本中的操作系统已经有一定历史了。它们提供了扁平、虚拟内存模型，方便将整张图片加载到内存中，以供后续处理。据此，本书中依赖的基础软件经过了修订。

&emsp;&emsp;本书中的软件可以在 32 位系统上运行（Windows 95，98，NT 和各种 UNIX）。我使用了 D.J. Delorie’s port of the (free) GNU C compiler (DJGPP,see www.delorie.com) 来编译（译者注：代码可以在 [http://homepages.inf.ed.ac.uk/rbf/BOOKS/PHILLIPS/](http://homepages.inf.ed.ac.uk/rbf/BOOKS/PHILLIPS/) 处获取）。使用其他 C/C++ 编译器也能正常编译。该软件可以处理 8-bit 的灰度图，图片格式要求是 TIFF 或 BMP. 可以用其他软件将图片转换成这种格式。

* 第0章介绍了 C 语言图像处理系统。这章结合了图像处理软件中的很多概念，以及如何使用该软件。
* 第1章提供了图像文件输入输出（I/O）的例程，这些例程其余的图像操作中均有使用。
* 第2章介绍了如何在屏幕上显示图片，并将图片数据写入文本再打印出来。我现在将显示图片这项工作交给图片浏览器来做。
* 第3章介绍了 halftoning technique，用于将将灰度图像转换为看起来有灰色阴影的黑白图像。这章还介绍了如何用这个方法打印墙上的海报。
* 第4章深入研究了直方图和直方图均衡化（histogram equalizetion）。直方图可以让你改变图片的对比度。本章提供了输出直方图的程序，以及将图片拼接在一起的程序。
* 第5章介绍了边缘检测，一种图像处理中的基本操作

## 译者的话

&emsp;&emsp;目前大部分图像处理的教程是基于 python+numpy+opencv/PIL，但大部分都是“掉包”，并没有深入探讨各种算子实现的细节。而基于 c 的图像处理能让我们更深入地学习，为后续优化做准备。

&emsp;&emsp;本书写于 2000 年，我与 2021 年 1 月开始翻译，预计 2021 年 5 月全部译完。由于作者使用的系统和 C 编译器太古老，原程序很难编译成功，所以我重新将代码整理了一下，能用现在流行的 gcc 编译通过（在 linux 上测试通过，Windows10 需要按安装 gcc）。你可以在 [https://scuteee.com/software/cips/code/](https://scuteee.com/software/cips/code/) 中找到各章代码。

&emsp;&emsp;关于版权问题，