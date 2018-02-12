#include <iostream>
#include <wiringPi.h>

struct ledcode
{
    int *num;
    int *pos;
    ledcode(int *t_num, int *t_pos)
    {
        num = t_num;
        pos = t_pos;
    };
    int *toarr()
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
    };
};

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
