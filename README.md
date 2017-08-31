# LED计时器

## 4位LED数码管模块

4位LED数码管模块基本说明：

1. 采用2片595驱动数码管，需要单片机3路IO口，根据数码管动态扫描原理进行显示；
2. 宽工作电压3.3V到5V；
3. PCB板尺寸：71mm*22mm
4. 数码管型号：0.36 4位共阳

## Edison接线说明

使用模块包含：

1. Intel Edison底板 + Edison模块，安装ubilinux系统；
2. Arduino扩展板；
3. 4位LED数码管模块；

接线说明：

// TODO

## LED计时器原理

每位LED编码如下：

``` cpp
//      0
//      --
//   5 |  | 1
//      --  6
//   4 |  | 2
//      --  .
//      3   7

// With out point(7), only digit
static const uint8_t LED[] =
{
    // 0     1     2     3     4
    0xC0, 0xF9, 0xA4, 0xB0, 0x99,
    // 5     6     7     8     9
    0x92, 0x82, 0xF8, 0x80, 0x90,
};

// With point(7)
static const uint8_t LED_WITH_POINT[] =
{
    // 0     1     2     3     4
    0x40, 0x79, 0x24, 0x30, 0x19,
    // 5     6     7     8     9
    0x12, 0x02, 0x78, 0x00, 0x10,
};
```

所以在时间更新时，按照顺序，依次刷入对应的要显示的值即可。

## TODO

增加控制模块，用遥控器控制计时重置、计时暂停等。
