#include <linux/module.h> /* Needed by all modules */
#include <linux/kernel.h> /* For KERN_INFO */
#include <linux/slab.h>
#include <linux/device.h>

extern ssize_t get_void_size(void);
extern void submit_void_ptr(void *p);
extern ssize_t get_int_array_size(void);
extern void submit_int_array_ptr(int *p);
extern void submit_struct_ptr(struct device *p);
extern void checker_kfree(void *p);

static void *ptrVoid;
static int *ptrInt;
static struct device *p;

int __init mod_init(void){
    ssize_t voidSize = get_void_size();
    ptrVoid = kmalloc(voidSize, GFP_KERNEL);
    submit_void_ptr(ptrVoid);

    ssize_t intSize = get_int_array_size();
    ptrInt = kmalloc(sizeof(int)*intSize, GFP_KERNEL);
    submit_int_array_ptr(ptrInt);

    p = kmalloc(sizeof(struct device), GFP_KERNEL);
    submit_struct_ptr(p);

    return 0;
}

void __exit mod_exit(void){
    checker_kfree(ptrVoid);
    checker_kfree(ptrInt);
    checker_kfree(p);

    return;
}

module_init(mod_init);
module_exit(mod_exit);

MODULE_DESCRIPTION("1.4");
MODULE_AUTHOR("Maksym Andreiev");
MODULE_LICENSE("GPL");