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
    int num_led_1[8] = {1, 1, 1, 1, 1, 0, 0, 1};
    int num_led_2[8] = {1, 0, 0, 0, 0, 0, 1, 0}; //
    int num_led_6[8] = {1, 0, 0, 0, 0, 0, 1, 0};
    int num_lef_8[8] = {1, 0, 0, 0, 0, 0, 0, 0};
    int num_led_6p[8] = {0, 0, 0, 0, 0, 0, 1, 0};
    int num_lef_8p[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    // position
    int pos_led_5[8] = {0, 0, 0, 0, 1, 0, 0, 0};
    int pos_led_6[8] = {0, 0, 0, 0, 0, 1, 0, 0};
    int pos_led_7[8] = {0, 0, 0, 0, 0, 0, 1, 0};
    int pos_led_8[8] = {0, 0, 0, 0, 0, 0, 0, 1};

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
    // DP, middle, left_top, left_bot, bot, right_bot, right_top, top
    // int led[16] = {
    //     0, 0, 0, 0, 0, 0, 0, 0,
    //     0, 0, 0, 0, 1, 0, 0, 1};
    // int led2[16] = {
    //     1, 0, 0, 0, 1, 1, 1, 0,
    //     0, 0, 0, 0, 0, 0, 0, 1};
    ledcode lc(
        this->num_led_6p,
        this->pos_led_8);
    int *led = lc.toarr();
    int i;
    do
    {
        this->gpio_init();
        for (i = 0; i < 16; i++)
        {
            ::digitalWrite(this->sdi, this->led_rst[i]);
            this->pulse(this->srclk);
        }
        this->pulse(this->rclk);

        this->gpio_init();
        for (i = 0; i < 16; i++)
        {
            ::digitalWrite(this->sdi, led[i]);
            this->pulse(this->srclk);
        }
        this->pulse(this->rclk);

        // this->gpio_init();
        // for (i = 0; i < 16; i++)
        // {
        //     ::digitalWrite(this->sdi, led2[i]);
        //     this->pulse(this->srclk);
        // }
        // this->pulse(this->rclk);

        // this->gpio_init();
        // for (i = 0; i < 16; i++)
        // {
        //     ::digitalWrite(this->sdi, led_rst[i]);
        //     this->pulse(this->srclk);
        // }
        // this->pulse(this->rclk);
    } while (0);
}
