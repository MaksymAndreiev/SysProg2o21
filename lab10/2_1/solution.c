#include <linux/kernel.h>
#include <linux/kobject.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/module.h>
#include <linux/init.h>

static struct kobject *my_kobj;
static int cnt = 0;

static ssize_t my_sys_show(struct kobject *kobj, struct kobj_attribute *attr,char *buf)
{
    cnt+=1;
    return sprintf(buf, "%d\n", cnt);
}

static ssize_t my_sys_store(struct kobject *kobj, struct kobj_attribute *attr,const char *buf, size_t count)
{
    int ret;

    ret = kstrtoint(buf, 10, &cnt);
    if (ret < 0)
        return ret;

    return count;
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

    return retval;
}

void __exit mod_exit(void)
{
    kobject_put(my_kobj);
}

module_init(mod_init);
module_exit(mod_exit);

MODULE_DESCRIPTION("Task 2.1");
MODULE_AUTHOR("Maksym Andreiev");
MODULE_LICENSE("GPL");