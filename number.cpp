
#include "number.h"

number::number(int r_sdi, int r_rclk, int r_srclk)
{
    if (wiringPiSetup() == -1)
    {
        //when initialize wiring failed,print messageto screen
        printf("setup wiringPi failed !");
        return;
    }
    sdi = r_sdi;
    rclk = r_rclk;
    srclk = r_srclk;
}

/**
 * GPIO初始化
 */
void number::gpio_init()
{

    ::pinMode(this->sdi, OUTPUT);   //make P0 output
    ::pinMode(this->rclk, OUTPUT);  //make P0 output
    ::pinMode(this->srclk, OUTPUT); //make P0 output
    ::digitalWrite(this->sdi, 0);
    ::digitalWrite(this->rclk, 0);
    ::digitalWrite(this->srclk, 0);
}

/**
 * 升位
 */
void number::pulse(int pin)
{
    ::digitalWrite(pin, 0);
    ::digitalWrite(pin, 1);
}

/**
 * 循环显示
 */
void number::loop_show()
{
    ledcode *lc1 = new ledcode(this->num_led_3p, this->pos_led_5);
    ledcode *lc2 = new ledcode(this->num_led_1, this->pos_led_6);
    ledcode *lc3 = new ledcode(this->num_led_4, this->pos_led_7);
    ledcode *lc4 = new ledcode(this->num_led_1, this->pos_led_8);
    do
    {
        this->show_core(lc1);
        this->show_core(lc2);
        this->show_core(lc3);
        this->show_core(lc4);
    } while (1);
}

/**
 * 数码管显示核心函数
 */
void number::show_core(ledcode *lc)
{
    int *led = lc->toarr();
    this->gpio_init();
    for (this->i = 0; this->i < 16; this->i++)
    {
        ::digitalWrite(this->sdi, this->led_rst[this->i]);
        this->pulse(this->srclk);
    }
    this->pulse(this->rclk);

    this->gpio_init();
    for (this->i = 0; this->i < 16; this->i++)
    {
        ::digitalWrite(this->sdi, led[this->i]);
        this->pulse(this->srclk);
    }
    this->pulse(this->rclk);

    free(led);
    led = nullptr;
}