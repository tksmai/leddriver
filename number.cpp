#include <iostream>
#include <wiringPi.h>

struct ledcode
{
    int *num;
    int *pos;
    ledcode(int *t_num, int *t_pos);
    int *toarr();
};

ledcode::ledcode(int *t_num, int *t_pos)
{
    num = t_num;
    pos = t_pos;
}

int *ledcode::toarr()
{
    int *c = new int[16];
    int i, j;
    j = 0;
    for (i = 0; i < 8; i++)
    {
        c[j] = num[i];
        j++;
    }

    for (i = 0; i < 8; i++)
    {
        c[j] = pos[i];
        j++;
    }
    return c;
}

class number
{
  private:
    int sdi;
    int rclk;
    int srclk;
    int led_rst[16] = {
        1, 1, 1, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0};
    // number
    // DP, middle, left_top, left_bot, bot, right_bot, right_top, top
    int num_led_0[8] = {1, 1, 0, 0, 0, 0, 0, 0};
    int num_led_1[8] = {1, 1, 1, 1, 1, 0, 0, 1};
    int num_led_2[8] = {1, 0, 1, 0, 0, 1, 0, 0};
    int num_led_3[8] = {1, 0, 1, 1, 0, 0, 0, 0};
    int num_led_4[8] = {1, 0, 0, 1, 1, 0, 0, 1};
    int num_led_5[8] = {1, 0, 0, 1, 0, 0, 1, 0};
    int num_led_6[8] = {1, 0, 0, 0, 0, 0, 1, 0};
    int num_led_7[8] = {1, 1, 1, 1, 1, 0, 0, 0};
    int num_led_8[8] = {1, 0, 0, 0, 0, 0, 0, 0};
    int num_led_9[8] = {1, 0, 0, 1, 0, 0, 0, 0};
    // number with point
    int num_led_0p[8] = {0, 1, 0, 0, 0, 0, 0, 0};
    int num_led_1p[8] = {0, 1, 1, 1, 1, 0, 0, 1};
    int num_led_2p[8] = {0, 0, 1, 0, 0, 1, 0, 0};
    int num_led_3p[8] = {0, 0, 1, 1, 0, 0, 0, 0};
    int num_led_4p[8] = {0, 0, 0, 1, 1, 0, 0, 1};
    int num_led_5p[8] = {0, 0, 0, 1, 0, 0, 1, 0};
    int num_led_6p[8] = {0, 0, 0, 0, 0, 0, 1, 0};
    int num_led_7p[8] = {0, 1, 1, 1, 1, 0, 0, 0};
    int num_led_8p[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    int num_led_9p[8] = {0, 0, 0, 1, 0, 0, 0, 0};
    // position
    int pos_led_5[8] = {0, 0, 0, 0, 1, 0, 0, 0};
    int pos_led_6[8] = {0, 0, 0, 0, 0, 1, 0, 0};
    int pos_led_7[8] = {0, 0, 0, 0, 0, 0, 1, 0};
    int pos_led_8[8] = {0, 0, 0, 0, 0, 0, 0, 1};

    int i = 0;
    void show_core(ledcode *);

  public:
    number(int r_sdi, int r_rclk, int r_srclk);
    void gpio_init();
    void pulse(int pin);
    void loop_show();
};

int main(int argv, char *args[])
{
    number n(5, 6, 7);
    n.loop_show();
    return 0;
}

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