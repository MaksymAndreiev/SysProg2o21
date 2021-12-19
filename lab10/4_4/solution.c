#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/hrtimer.h>
#include <linux/ktime.h>
#include <linux/time64.h>
#define NSEC_PER_MSEC 1000000L

extern void check_timer(void);

static struct hrtimer hr_timer;
static unsigned long delays[20];
static int dnum = sizeof(delays)/sizeof(delays[0]);
module_param_array(delays, ulong,&dnum, S_IRUGO|S_IWUSR);

enum hrtimer_restart timer_callback( struct hrtimer *timer_for_restart )
{
    static unsigned int i = 0;
    i++;
    ktime_t currtime , interval;
    currtime  = ktime_get();
    interval = ktime_set(0,delays[i] * NSEC_PER_MSEC);
    hrtimer_forward_now(timer_for_restart,interval);
    check_timer();
    return HRTIMER_RESTART;
}

int __init mod_init(void)
{
    ktime_t ktime = ktime_set( 0, delays[0] * NSEC_PER_MSEC);
    hrtimer_init( &hr_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL );
    hr_timer.function = &timer_callback;
    check_timer();
    hrtimer_start( &hr_timer, ktime, HRTIMER_MODE_REL );
    return 0;
}

void __exit mod_exit(void)
{
    int ret;
    ret = hrtimer_cancel( &hr_timer );
    if (ret) printk("The timer was still in use...\n");
    printk("HR Timer module uninstalling\n");
}
module_init(mod_init);
module_exit(mod_exit);

MODULE_DESCRIPTION("Task 4.4");
MODULE_AUTHOR("Maksym Andreiev");
MODULE_LICENSE("GPL");