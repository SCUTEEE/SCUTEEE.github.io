---
layout: article
title: IO系统
permalink: /courses/freshman/principle-of-computer/IO系统
mathjax: true
mermaid: false
chart: false
mathjax_autoNumber: true
mode: normal
tags: 计算机科学
key: principle-of-computer-7-IO系统
nav_key: courses
show_edit_on_github: false
show_date: false
sidebar:
  nav: principle-of-computer
aside:
  toc: true
---

<!--more-->

# 概述

* IO系统功能：管理主机与外设以及外设与外设之间的信息交换，由硬件和软件共同完成此项任务。
* IO系统组成：
  * 软件
  * 硬件：
    * 计算机总线
    * IO接口
      * 地址信息
      * 数据信息
      * 命令信息
      * 状态信息
* IO接口分类
  1. 按数据传送方式：串行、并行
  2. 按CPU访问外设的控制方式：程序查询、中断、DMA、通道控制、I/O处理机
  3. 按是否需要统一的控制时钟：同步、异步
  4. 按通用性：通用、专用