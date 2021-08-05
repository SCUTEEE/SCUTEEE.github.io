---
layout: article
title: Manim 教程
mathjax: false
mermaid: false
chart: false
mathjax_autoNumber: false
toc: true
mode: immersive
tags: [教程, 项目, 多图预警]
author: Todd Zhou
show_author_profile: true
pageview: false
comment: true
key: 2020-03-30-manim-tutorial
header:
  theme: dark
article_header:
  type: overlay
  theme: dark
  align: center
  background_color: '#ccccd6'
  background_image:
    src: https://i.loli.net/2020/03/30/uSOVQk3yEnPwZox.jpg
    gradient: 'linear-gradient(0deg, rgba(0, 0, 0 , .5), rgba(0, 0, 0, .5))'
---

用 Manim 作出精美的数学视频！

<!--more-->

# 简介与安装

&emsp;&emsp;[Manim](https://github.com/3b1b/manim) 是一个用于绘制数学视频的动画引擎。下面是一个介绍视频：

<div class="extensions extensions--video">
  <iframe src="//player.bilibili.com/player.html?aid=74182503&bvid=BV16E41187Bd&cid=126904152&page=1"
    frameborder="no" scrolling="no" allowfullscreen="true">
  </iframe>
</div>

&emsp;&emsp;Windows 用户可以根据 [知乎：3Blue1Brown的动画引擎如何配置？](https://zhuanlan.zhihu.com/p/70243739) 来安装 Manim。Mac 和 Linux 用户请自行查找相关资料。

# Hello, world!

&emsp;&emsp;按照惯例，我们以 Hello, world! 作为第一个程序。在 manim-master 解压出的文件夹中新建 `HelloWorld.py` 文件，输入以下代码：

<details>
<summary><code>Hello, world!代码</code></summary>
{% highlight python linenos %}
from manimlib.imports import *  # 导入manimlib

class HelloWorld(Scene):  # 从 Scene 创建子类
    def construct(self):  # 开始定义动画
        helloWorld = TextMobject("Hello, world!")
        self.play(Write(helloWorld))
        self.wait()
{% endhighlight %}
<hr>
</details>

&emsp;&emsp;我们来一行行看我们的代码：

1. `from manimlib.imports import *` 导入 manimlib.imports 模块，必不可少的。
2. `class HelloWorld(Scene):` 从 Scene 创建一个子类 HelloWorld. Scene 可以理解是一个空画布，而 HelloWorld 则定义在画布上的动画
3. `def construct(self):……` 向空画布中添加一系列动画。后面的代码我们以后再深入学习。

&emsp;&emsp;写好代码后，我们需要使用 manim 来生成 mp4视频文件。在 Anaconda Prompt 中进入到 manim-master文件夹，运行渲染命令：

```powershell
python -m manim HelloWorld.py HelloWorld -lp
```

&emsp;&emsp;各个参数的意义如下：

1. `-m manim` 以脚本模式运行 manim 模块
2. `HelloWorld.py` 动画文件的地址
3. `HelloWorld` 动画文件中要生成动画的类
4. `-lp` 以低画质（low）模式渲染，渲染完后预览（preview）。更多参数可以参考 [文件的执行](https://github.com/cai-hust/manim-tutorial-CN#1-%E6%96%87%E4%BB%B6%E7%9A%84%E6%89%A7%E8%A1%8C)

&emsp;&emsp;就会出现以下视频：

<center><img src="https://i.loli.net/2020/03/30/VZYS4Tef9hjG2BF.gif"></center>

# Manim 对象与方法

Manim 动画中所有的东西都是类，而所有的类都基于 `Mobject` （Math object），从 `Mobject` 出发引申出各种文字、图形等子类。类的方法则定义了各种动画。

## 文字

### 初始化

文字对应于 `TextMobject()`，其初始化方法如下：

```python
# 初始化 TextMobject 对象
class WriteText(Scene): 
    def construct(self):
        #一般文字 
        text1 = TextMobject("Euler’s formula:")

        #LaTeX
        text2 = TextMobject(r"$\rm{e}^{i\pi}+1=0$")

        #LaTeX环境
        text3 = TextMobject(r"""$$
            \begin{cases}
            \rm{e}^{i\theta}=\cos\theta+i\sin\theta\\
            \rm{e}^{-i\theta}=\cos\theta-i\sin\theta
            \end{cases}
            $$
        """)

        text1.move_to(1*UP)
        text3.move_to(1.2*DOWN+1*RIGHT)
        self.add(text1)
        self.play(Write(text2))
        self.play(ShowCreation(text3))
        self.wait(3)
```

&emsp;&emsp;运行渲染命令后，可以得到这样的视频： <a href="https://s1.ax1x.com/2020/04/01/G8Wrh6.gif" data-lightbox="text" data-title="初始化文字"> WriteText.gif（点击查看）</a>

&emsp;&emsp;在上面的程序中，我们利用了三种不同的字符串来初始化 `TextMobject()`：

1. 使用一般字符串。效果和普通的文字一样
2. 使用 raw 字符串+LaTeX，显示出 LaTeX 公式
3. 使用 raw `"""` 字符串+LaTeX环境+LaTeX，显示大括号与公式组

&emsp;&emsp;这里唯一要说明的就是 `\` 符号。在一般字符串中，`\` 作为转义字符，要输入 `\` 必须使用 `\\`；而在 `r` 字符串中，直接输入 `\` 即可。

&emsp;&emsp;此外，这段视频也展示了三种不同的出场方式。以后我们常用的就是这三种。

### 改变字体属性

```python
# 设置 TextMobject 属性
class SetText(Scene): 
    def construct(self):
        # 改变颜色
        textColor = TextMobject("A","B","C","D","E","F")
        textColor[0].set_color(RED)
        textColor[1].set_color(ORANGE)
        textColor[2].set_color(YELLOW)
        textColor[3].set_color(GREEN)
        textColor[4].set_color(BLUE)
        self.play(Write(textColor))

        #设置字体大小
        textSmaller = TextMobject("Small Text")
        textSmaller.scale(0.8)
        textSmaller.move_to(DOWN)
        textBigger = TextMobject("Bigger Text")
        textBigger.next_to(textSmaller,0.5*DOWN,buff=2.5)
        self.play(Write(textSmaller), Write(textBigger))

        #在动画中改变大小
        self.play(ApplyMethod(textColor.scale,2))

        #改变字体位置
        textDL = TextMobject("DOWN+LEFT")
        textDL.to_edge(DOWN+LEFT)
        textUR = TextMobject("UP+RIGHT")
        textUR.to_edge(UP+RIGHT)
        self.add(textDL, textUR)

        #旋转
        textRotate=TextMobject(r"$\rightarrow$")
        textRotate.shift(UP)
        textRotate.rotate(PI/4)
        self.play(Write(textRotate))
        for i in range(360):
            self.wait(0.1)
            textRotate.rotate(PI/180)
        self.wait(0.5)
        textRotate.flip(LEFT)

        self.wait(0.5)
```

&emsp;&emsp;我们不再一一解释命令了，对应视频 <a href="https://i.loli.net/2020/04/05/8EhcS5KPTyZiufb.gif" data-lightbox="text" data-title="设置文字"> SetText.gif（点击查看）</a> 就可以知道命令的作用。唯一要说明的，就是颜色是预定义的，如果要自定义颜色，可以在 `manimlib-constants.py` 里定义。

### 字体变换

&emsp;&emsp;在数学教学视频中，我们经常通过字体之间的移动、渐变等来表示函数变换。最常用的就是 `Transform` 和 `ReplacementTransform`。这两者都能用于从一个文字变到另一个文字，但有如下区别：

* `Transform(A, B)` 将 A 的文字、样式替换为 B 的文字、样式，但屏幕上显示的依然是 A
* `ReplacementTransform` 将 A 的文字、样式替换为 B 的文字、样式，但屏幕上显示的是 B

---

<details>
<summary>Transform代码示例</summary>

{% highlight python linenos %}
class TransformationText1V2(Scene):
    def construct(self):
        texto1 = TextMobject("First text")
        texto1.to_edge(UP)
        texto2 = TextMobject("Second text")
        self.play(Write(texto1))
        self.wait()
        self.play(Transform(texto1,texto2))
        self.wait()
{% endhighlight %}

</details>

<center><img src="https://s1.ax1x.com/2020/04/05/GDnQjx.gif"></center>

---

<details>
<summary>ReplacementTransform代码示例1</summary>

{% highlight python linenos %}
class TransformationText2(Scene):
    def construct(self):
        text1 = TextMobject("Function")
        text2 = TextMobject("Derivative")
        text3 = TextMobject("Integral")
        text4 = TextMobject("Transformation")
        self.play(Write(text1))
        self.wait()
        #Trans text1 -> text2
        self.play(ReplacementTransform(text1,text2))
        self.wait()
        #Trans text2 -> text3
        self.play(ReplacementTransform(text2,text3))
        self.wait()
        #Trans text3 -> text4
        self.play(ReplacementTransform(text3,text4))
        self.wait()
{% endhighlight %}

</details>

<center><img src="https://i.loli.net/2020/04/05/6ZkTKC9e1xfM5UA.gif"></center>

---

<details>
<summary>ReplacementTransform代码示例2</summary>

{% highlight python linenos %}
class CopyTextV1(Scene):
    def construct(self):
        formula = TexMobject(
            "\\frac{d}{dx}", #0
            "(", #1
            "u", #2
            "+", #3
            "v", #4
            ")", #5
            "=", #6
            "\\frac{d}{dx}", #7
            "u", #8
            "+", #9
            "\\frac{d}{dx}", #10
            "v" #11
            )
        formula.scale(2)
        self.play(Write(formula[0:7]))
        self.wait()
        self.play(
            ReplacementTransform(formula[2].copy(),formula[8]),
            ReplacementTransform(formula[4].copy(),formula[11]),
            ReplacementTransform(formula[3].copy(),formula[9])
            )
        self.wait()
        self.play(
            ReplacementTransform(formula[0].copy(),formula[7]),
            ReplacementTransform(formula[0].copy(),formula[10])
            )
        self.wait()
{% endhighlight %}

</details>

<center><img src="https://i.loli.net/2020/04/05/oquyFmiEU1f4arQ.gif"></center>

---

# 参考资料

* [直观的数学：3Blue1Brown 动画制作教程](https://zhuanlan.zhihu.com/p/108839666)
* [github: manim-tutorial-CN](https://github.com/cai-hust/manim-tutorial-CN)
* [github: AnimationsWithManim](https://github.com/Elteoremadebeethoven/AnimationsWithManim)