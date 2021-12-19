#include <linux/kobject.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>

#define IRQ_LINE 8
static int irq = IRQ_LINE, my_dev_id, irq_counter = 0;
static struct kobject *my_kobj;

static irqreturn_t my_interrupt (int irq, void *dev_id)
{
    irq_counter++;
    printk(KERN_INFO"%d\n",irq_counter);
    return IRQ_NONE;
}

static ssize_t my_sys_show(struct kobject *kobj, struct kobj_attribute *attr,char *buf)
{
    int len = 0;
    len = sprintf(buf, "%d\n", irq_counter);
    return len;
}

static ssize_t my_sys_store(struct kobject *kobj, struct kobj_attribute *attr,const char *buf, size_t count)
{
    return 0;
}

static struct kobj_attribute my_attribute =__ATTR(my_sys, 0755, my_sys_show, my_sys_store);

int __init mod_init(void)
{
    int retval;
    my_kobj = kobject_create_and_add("my_kobject", kernel_kobj);
    if (!my_kobj)
        return -ENOMEM;

    retval = sysfs_create_file(my_kobj, &my_attribute.attr);
    if (retval)
        kobject_put(my_kobj);

    if(request_irq(irq,my_interrupt,IRQF_SHARED,"my_interrupt",&my_dev_id))
        return -1;

    return retval;
}

void __exit mod_exit(void)
{
    kobject_put(my_kobj);
    synchronize_irq(irq);
    free_irq(irq,&my_dev_id);
}

module_init(mod_init);
module_exit(mod_exit);

MODULE_DESCRIPTION("Task 4.3");
MODULE_AUTHOR("Maksym Andreiev");
MODULE_LICENSE("GPL");