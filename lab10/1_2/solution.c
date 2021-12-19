#include <linux/module.h> /* Needed by all modules */
#include <linux/kernel.h> /* For KERN_INFO */

extern void call_me(const char* message);

int __init hello_init(void)
{
    printk(KERN_INFO "Module load!\n");
    call_me("Hello from my module!");

    return 0;
}

void __exit hello_exit(void)
{
    printk(KERN_INFO "Module exit!\n");

    return;
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_DESCRIPTION("1.2");
MODULE_AUTHOR("Maksym Andreiev");
MODULE_LICENSE("GPL");