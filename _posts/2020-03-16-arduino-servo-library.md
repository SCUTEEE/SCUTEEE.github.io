---
layout: article
title: Arduino 伺服电机库使用说明 #文章标题
tags: [教程, Arduino] #文章标签
author: lyf #作者名#必须先与管理员沟通
show_author_profile: false #是否显示作者
mathjax: false #是否开启 LaTeX 输入
mermaid: false #是否开启 mermaid 输入
chart: false #是否开启chart输入
mathjax_autoNumber: false #是否开启 LaTeX 自动编号
mode: normal
key: courses-index #文章唯一标识符
pageview: false #是否开启阅读量统计#要设置 key
comment: false #是否开启评论
show_edit_on_github: false
show_date: false #是否显示文章日期
aside:
  toc: true #是否显示目录
---

本文档翻译自 Arduino [官网](https://www.arduino.cc/en/Reference/Servo) ，介绍了官方 Servo 库的使用方式
<!--more-->

## Introduction 简介


This library allows an Arduino board to control RC (hobby) servo motors. Servos have integrated gears and a shaft that can be precisely controlled. Standard servos allow the shaft to be positioned at various angles, usually between 0 and 180 degrees. Continuous rotation servos allow the rotation of the shaft to be set to various speeds. 

这个库允许 Arduino 板控制 RC(Hobby) 伺服电机。伺服系统有完整的齿轮和一个可以精确控制的轴。标准伺服系统允许轴以不同角度定位，通常在0到180度之间。连续旋转伺服允许将轴的旋转设置为不同的速度。

The Servo library supports up to 12 motors on most Arduino boards and 48 on the Arduino Mega. On boards other than the Mega, use of the library disables analogWrite() (PWM) functionality on pins 9 and 10, whether or not there is a Servo on those pins. On the Mega, up to 12 servos can be used without interfering with PWM functionality; use of 12 to 23 motors will disable PWM on pins 11 and 12.  

伺服库在大多数 Arduino 板上最多支持12个电机，在 Arduino Mega 上最多支持48个电机。在Mega以外的板上，使用 Servo 库会禁用引脚9和10上的 AnalogWrite()(PWM) 功能，无论这些引脚上是否有伺服电机。在Mega上，最多可以使用12个伺服电机而不会干扰脉宽调制功能；使用12到23个电机将禁用引脚11和12上的脉宽调制。

## Circuit 电路

Servo motors have three wires: power, ground, and signal. The power wire is typically red, and should be connected to the 5V pin on the Arduino board. The ground wire is typically black or brown and should be connected to a ground pin on the Arduino board. The signal pin is typically yellow, orange or white and should be connected to a digital pin on the Arduino board. Note that servos draw considerable power, so if you need to drive more than one or two, you'll probably need to power them from a separate supply (i.e. not the +5V pin on your Arduino). Be sure to connect the grounds of the Arduino and external power supply together.

伺服电机有三根电线：电源线、地线和信号线。电源线通常为红色，应连接到 Arduino 板上的 5V 引脚。地线通常为黑色或棕色，应连接到 Arduino 板上的接地引脚。信号引脚通常为黄色、橙色或白色，应连接到 Arduino 板上的数字引脚。请注意，伺服电机需要消耗相当大的功率，因此如果您需要驱动多个伺服电机，您可能需要从单独的电源为它们供电（即不使用 Arduino 上的+5V引脚）。确保将 Arduino 接地引脚和外部电源的地线连接在一起。

## Fountions 库函数
### 初始化
1. 将伺服电机初始化到某一引脚  
Attach the Servo variable to a pin. Note that in Arduino 0016 and earlier, the Servo library supports only servos on only two pins: 9 and 10.
        
        attach()
* Syntax 语法

        servo.attach(pin)
        servo.attach(pin, min, max)

* Parameters 参数

        servo: a variable of type Servo
        pin: the number of the pin that the servo is attached to
        min (optional): the pulse width, in microseconds, corresponding to the minimum (0-degree) angle on the servo (defaults to 544)
        脉冲宽度，以微秒为单位，对应于伺服上的最小（0度）角度（默认为544）
        max (optional): the pulse width, in microseconds, corresponding to the maximum (180-degree) angle on the servo (defaults to 2400)

* Example  
            
        #include <Servo.h> 

        Servo myservo;

        void setup() { 
            myservo.attach(9);
        } 

        void loop() {} 

### 控制电机旋转
1. 
    Writes a value to the servo, controlling the shaft accordingly. On a standard servo, this will set the angle of the shaft (in degrees), moving the shaft to that orientation. On a continuous rotation servo, this will set the speed of the servo (with 0 being full-speed in one direction, 180 being full speed in the other, and a value near 90 being no movement).  
    向伺服电机写入一个值，并相应地控制轴转动。在标准伺服电机上，这将设置轴的角度（以度为单位），将轴移动到该方向。在连续旋转伺服电机上，这将设置伺服的速度（0表示一个方向上的全速，180表示另一个方向上的全速，接近90的值表示没有移动）。  
    
        write()

* Syntax
        
        servo.write(angle)

* Parameters
        
        servo: a variable of type Servo
        angle: the value to write to the servo, from 0 to 180

* Example  
                
        #include <Servo.h> 

        Servo myservo;

        void setup() { 
            myservo.attach(9);
            myservo.write(90);  // set servo to mid-point
        } 

        void loop() {} 

2.  
    Writes a value in microseconds (uS) to the servo, controlling the shaft accordingly. On a standard servo, this will set the angle of the shaft. On standard servos a parameter value of 1000 is fully counter-clockwise, 2000 is fully clockwise, and 1500 is in the middle.  

    以微秒（us）为单位向伺服写入一个值，并相应地控制轴。在标准伺服系统上，这将设置轴的角度。在标准伺服系统中，参数值1000是完全逆时针方向的，2000是完全顺时针的，1500是在中间的。  

    Note that some manufactures do not follow this standard very closely so that servos often respond to values between 700 and 2300. Feel free to increase these endpoints until the servo no longer continues to increase its range. Note however that attempting to drive a servo past its endpoints (often indicated by a growling sound) is a high-current state, and should be avoided.

    请注意，一些制造商没有非常严格地遵循这一标准，因此伺服电机通常可以对700到2300之间的值作出响应。可以随意增加这些端点，直到伺服电机不再继续增加其转动角度。但是请注意，试图驱动伺服电机超过其最大旋转范围（通常由咆哮声表示）是一种高电流状态，应避免。
 
    Continuous-rotation servos will respond to the writeMicrosecond function in an  manner to the write function.

    连续旋转伺服电机将以类似于write()函数的方式响应writemicrosecond功能。
        
        writeMicroseconds()
* Syntax
            
        servo.writeMicroseconds(uS)
* Parameters
            
        servo: a variable of type Servo
        uS: the value of the parameter in microseconds (int)

* Example

        #include <Servo.h> 

        Servo myservo;

        void setup() { 
        myservo.attach(9);
        myservo.writeMicroseconds(1500);  // set servo to mid-point
        } 

        void loop() {} 

### 读取状态
1. 
    Read the current angle of the servo (the value passed to the last call to write()).  
    读取当前伺服电机旋转角度
        
        read()

* Syntax
        
        servo.read()

* Parameters
        
        servo: a variable of type Servo

* Returns
        
        The angle of the servo, from 0 to 180 degrees.

2. Check whether the Servo variable is attached to a pin.  
 
        attached()

* Syntax
        
        servo.attached()

* Parameters
        
        servo: a variable of type Servo

* Returns
       
        true if the servo is attached to pin; false otherwise.

### 解除连接
1. Detach the Servo variable from its pin. If all Servo variables are detached, then pins 9 and 10 can be used for PWM output with analogWrite().
        
        detach()

* Syntax
    
        servo.detach()

* Prameters
    
        servo: a variable of type Servo