#include <intrins.h>
#include <reg51.h>
sbit K1 = P3 ^ 2;
sbit K2 = P3 ^ 3;
unsigned char code DELAY_TAB[3] = {200, 150, 50};
bit dir = 0;
unsigned char speed = 0;
void delay1ms(void)
{
    unsigned char i, j;
    _nop_();
    for (i = 0; i < 10; i++)
        for (j = 0; j < 100; j++)
            _nop_();
}
void delay_speed(void)
{
    unsigned char i, j;

    for (i = 0; i < DELAY_TAB[speed]; i++)
        for (j = 0; j < 200; j++)
            _nop_();
}
void int0_isr(void) interrupt 0 using 1
{
    delay1ms();
    dir = !dir;
    while (K1 == 0)
    {
    }
}
void int1_isr(void) interrupt 2 using 2
{
    delay1ms();
    if (speed >= 2)
        speed = 0;
    else
        speed++;
    while (K2 == 0)
    {
    }
}
void main(void)
{
    unsigned char pat = 0xFE;
    TCON = 0x05;
    EX0 = 1;
    EX1 = 1;
    EA = 1;
    P1 = pat;
    while (1)
    {
        delay_speed();
        if (dir == 0)
            pat = _crol_(pat, 1);
        else
            pat = _cror_(pat, 1);
        P1 = pat;
    }
}