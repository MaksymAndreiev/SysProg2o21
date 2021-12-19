#include <linux/module.h> /* Needed by all modules */
#include <linux/kernel.h> /* For KERN_INFO */

extern int array_sum(short *arr, size_t n);
extern ssize_t generate_output(int sum, short *arr, size_t size, char *buf);
#define CHECKER_MACRO

int __init hello_init(void)
{
    CHECKER_MACRO;
    short inputArr[5] = {0,1,2,3,4};
    unsigned char i;

    for (i = 0;i<10; i++)
    {
        int res = array_sum(inputArr, (sizeof(inputArr)/sizeof(inputArr[0])));
        char outPutBuff[1024];
        ssize_t resOutPutBuff = generate_output(res, inputArr, (sizeof(inputArr)/sizeof(inputArr[0])), outPutBuff);

        if(res ==  10)
        {
            printk(KERN_INFO "%s\n",outPutBuff);
        }
        else
        {
            printk(KERN_ERR "%s\n",outPutBuff);
        }
    }

    return 0;
}

void __exit hello_exit(void)
{CHECKER_MACRO;
    return;
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_DESCRIPTION("1.3");
MODULE_AUTHOR("Maksym Andreiev");
MODULE_LICENSE("GPL");