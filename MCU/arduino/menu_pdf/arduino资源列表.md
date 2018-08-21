
## 1. PWM口资源=======================
### a. ATMEGA 2560   Arduino MEGA 2560  一共 12 个 PWM口=================

    Timer0  8bit  PWM  (13) 和 4  
            两个独立比较输出单元  OC0A-PB7  PWM13口  OC0B-PG5-PWM4口  支持 pwm输出功能

    Timer2  8bit PWM 10 和 9
            两个独立比较输出单元  OC2A-PB4-PWM10口    OC2B-PH6-PWM9口   支持 pwm输出功能

    Timer1  16bit  PWM  11  12 口
            三个独立比较输出单元 OC1A-PB5-PWM11口  OC1B-PB6-PWM12口   ( OC1C-PB7(与OC0A复用)-PWM13口 ) 
        支持 pwm输出功能

    Timer3  16bit  PWM  2  3  5
            三个独立比较输出单元  OC3A-PE3-PWM5口  OC3B-PE4-PWM2口   OC3C-PE5-PWM3口 
        支持 pwm输出功能

    Timer4  16bit  PWM 6 7 8
            三个独立比较输出单元  OC4A-PH3-PWM6口  OC4B-PH4-PWM7口   OC4C-PH5-PWM8口 
        支持 pwm输出功能


    Timer5  16bit  无PWM   44
        三个独立比较输出单元  OC5A-PL3  OC5B-PL4   OC5C-PL5  
        支持 pwm输出功能


### b. ATMEGA   328P   Arduino  uno  一共六个 PWM 口======================

      Timer0  8bit  PWM  5 和 6
              两个独立比较输出单元  
          OC0A-PD6  PWM 6 口  
          OC0B-PD5 -PWM 5 口  支持 pwm输出功能

      Timer2  8bit PWM 3 和 11
              两个独立比较输出单元  
          OC2A-PB3-PWM11口 复用 SPI的MOSI 口 
          OC2B-PD3-PWM3口   支持 pwm输出功能

      Timer1  16bit  PWM 9 10口
              两个独立比较输出单元  
          OC1A-PB1-PWM9口    
          OC1B-PB2-PWM10口   支持 pwm输出功能	

### pwm口：
      timer   bits   channel   Arduino pin   Mega2560 pin
      timer0   8       A          6              13
      timer0   8       B          5              4
      timer1   16      A          9              11
      timer1   16      B          10             12
      timer2   8       A          11             10
      timer2   8       B          3              9
      timer3   16      A          -              5
      timer3   16      B          -              2
      timer3   16      C          -              3
      timer4   16      A          -              6
      timer4   16      B          -              7
      timer4   16      C          -              8
      timer5   16      A          -              44
      timer5   16      B          -              45
      timer5   16      C          -              46


## 2. 中断口资源====================================

      型号         int.0 int.1 int.2 int.3 int.4 int.5
      UNO\Ethernet  2     3 　 　 　 　
      Mega2560      2     3     21     20    19   18
      Leonardo      3     2     0      1 　 　
      Due           　所有IO口均可
      
## 3. 通信
    a. 串口
    b. i2c
    c. spi
    d. can

## 4. pwm 冷门知识
### a. 普通io延时实现
```c
int pin = 13;
void setup() {
  pinMode(pin, OUTPUT);
}
void loop(){
  digitalWrite(pin, HIGH);
  delayMicroseconds(100); // Approximately 10% duty cycle @ 1KHz
  digitalWrite(pin, LOW);
  delayMicroseconds(1000 - 100);
}
// 时间周期是 1000 us = 1ms, 所以一秒循环 1000次, 因此 频率Frequency 是 1 KHz,
// 每个循环中, 有电(高电平状态)的比率是 100/1000 * 100% = 10%, 所以 duty cycle (占空比)为 10%;
// 模拟的电压为 5Volt x 10% = 0.5 Volt 的电压!
```
    这种方法的好处是任意一个IO管脚都可以实现，而坏处是 频率和占空比都会受到中断的影响，而变的不准确。
    在一个是，做了这个，cpu就干不了其他的事情了。
### b. 通过定时器和比较器来实现
```c
// Arduino UNO 的 MCU 有三個 timer,
// 其中 timer0 控制 pin 5, pin 6; timer1 控制 pin 9, pin 10; timer 2 控制 pin 11, pin 3;
// 所以, 我们可以对这些 pin 用 analogWrite(pin, val); 输出 0 到 255 的 val 值到 pin ;
// 如果输出 val 是 0, 它会偷偷直接改用 digitalWrite(pin, 0); 输出低电平,
// 如果 val 是 255, 也是会偷偷直接改用 digitalWrite(pin, 1); 輸出高电平!
// 如果 val 是 1 到 254, 会下命令请 pin 脚对应的 timer定时器帮忙!!

// 系统时钟通过分屏器会接到定时器上，每来一个时钟，定时器的计数器 TCNT? 的 计数值counter会加1，
// 定时器有几种计数模式，一般有 增计数模式、减计数模式、增减计数模式。
// 每個 定时器timer 的分频 Prescaler 是独立设置的, 通常可以設 1, 2, 4, 8, 64, 256, or 1024 等,
// 这必须查看 单片机 MCU 的 手册datasheet.

// 要设定 定时器timer 的 计数模式Mode， 可以通过修改 timer 的控制寄存器, TCCR?A, TCCR?B(TCCR1A, TCCR1B,TCCR2A, TCCR2B),
// 注意以 ATmega328 為例, TCCR?A 和 TCCR?B 要合起來用, 此處的 A, B 和 通道channel A, channel B无关，不是一个事!!

// Arduino 每个 timer 有两个比较器, 分別命名 OCR?A 和 OCR?B ,
// 其中 ? 是 0, 1, 2 分別对应到 timer0, timer1, 和 timer2 着三个定时器.
// 每当 定时器的计数器 TCNT? 的值 等于 比较器的值，定时器就有在这个时刻改变 通道的电平，
// 而当计数器 TCNT? 溢出时， 通道的电平也可能改变。

// arduino-1.8.1\hardware\arduino\avr\cores\arduino\wiring_analog.c
// arduino-1.8.1\hardware\arduino\avr\cores\arduino\wiring.c
//  analogWrite() 的实现
那 PWM 的 Frequency 可不可以更改?
A: 可以, 偷改 timer 的 Prescaler 就可以達到更改 Frequency 的目的 !
   但是, 千萬不要更改 timer0 的 Prescaler, 否則 millis( ) 和 micros( ) 以及 delay() 都會受到影響 !!!
   以下是以 timer1 控制的 pin 9, pin 10 為例(注意兩個 pin 的頻率相同!)
   在你的 setup( ) { 內, 寫如下兩句即可:
      int fff = 3;  // 可以是 1, 2, 3, 4, 5
      TCCR1B = TCCR1B & 0xF8 | fff;
  其中 fff 與對應頻率如下:
  fff   Prescaler   Frequency
   1           1        31372.549 Hz
   2           8          3921.569
   3         64            490.196   <--DEFAULT
   4       256           122.549
   5    1024               30.637 Hz

至於 timer2 控制的 pin 11 和 pin 3,
則在 setup( ) { 內寫:
     TCCR2B = TCCR2B & 0xF8 | ?;
此處的 ? 可以有七種:
   ?  Prescaler   Frequency
   1         1       31372.549 Hz
   2         8         3921.569
   3            32          980.392
   4        64         490.196   <--DEFAULT
   5      128         245.098
   6      256         122.549
   7    1024           30.637 Hz

如果你堅持要改 timer0 的 Prescaler, 以更改 pin 5, pin 6 的 PWM 頻率:
   (注意 millis( ) 和 micros( ) 以及 delay() 都會受到影響 !! )
則在 setup( ) { 內寫:
     TCCR0B = TCCR0B & 0xF8 | ?;
此處的 ? 可以有五種:
   ?  Prescaler   Frequency
   1          1       362500 Hz
   2          8           7812.5
   3        64             976.5625   <--DEFAULT
   4      256             244.140625
   5    1024               61.03515625 Hz

參考:
   http://playground.arduino.cc/Main/TimerPWMCheatsheet
   http://www.atmel.com/Images/doc8161.pdf
   
脉冲生成模式控制位（WGM）：用来设置时钟的模式
时钟选择位（CS）：设置时钟的预定标器
输出模式控制位（COMnA和COMnB）：使能/禁用/反相 输出A和输出B
输出比较器（OCRnA和OCRnB）：当计数器等于这两个值时，输出值根据不同的模式进行变化

你改这几个寄存器就好了，我之前用的是arduino nuo 。
下面这个例子以Timer2为例，把Pin3和Pin11作为快速PWM的两个输出管脚。其中：
WGM的设置为011，表示选择了快速PWM模式；
COM2A和COM2B设置为10，表示A和B输出都是非反转的PWM；
CS的设置为100，表示时钟周期是系统时钟的1/64；
OCR2A和OCR2B分别是180和50，表示两路输出的占空比；

pinMode(3, OUTPUT);  
pinMode(11, OUTPUT);  
TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);  
TCCR2B = _BV(CS22);  
OCR2A = 180;  
OCR2B = 50;  
这段代码看上去有点晕，其实很简单。_BV(n)的意思就是1< COM2A1，表示COM2A的第1位（靠，其实是第2位，不过程序员们是从0开始数数的）。所以_BV(COM2A1)表示COM2A = 10；
类似的，_BV(WGM21) | _BV(WGM20) 表示 WGM2 = 011。

在Arduino Duemilanove开发板，上面这几行代码的结果为：
输出 A 频率: 16 MHz / 64 / 256 = 976.5625Hz
输出 A 占空比: (180+1) / 256 = 70.7%
输出 B 频率: 16 MHz / 64 / 256 = 976.5625Hz
输出 B 占空比: (50+1) / 256 = 19.9%

CS就是改它的分频数的。比如你改成TCCR2B = _BV(CS20)。你用示波器测它的变化貌似会达到44KHZ。

analogWrite(); 的变化好像就是是980hz，490hz。你自己多试验一下。
你可以参考http://www.diy-robots.com/?p=852
   
   
```


