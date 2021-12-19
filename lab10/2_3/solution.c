#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "solution_node"
#define MY_MAJOR 240
#define MY_MINOR 0

static dev_t dev;
static struct cdev hcdev;
static int cnt = 1;

static int Device_Open = 0;
static char msg[80];
static char *msg_Ptr;
static unsigned int counter = 0;

static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

static struct file_operations fops = {
        .read = device_read,
        .write = device_write,
        .open = device_open,
        .release = device_release
};


static int device_open(struct inode *inode, struct file *filp)
{
    Device_Open++;
    sprintf(msg, "%u %u\n", Device_Open,counter);
    msg_Ptr = msg;
    try_module_get(THIS_MODULE);
    return 0;
}

static int device_release(struct inode *inode, struct file *filp)
{
    module_put(THIS_MODULE);
    return 0;
}

static ssize_t device_read(struct file *filp, char *buffer, size_t length, loff_t *offset)
{
    int bytes_read = 0;

    if (*msg_Ptr == 0)
        return 0;

    while (length && *msg_Ptr) {
        put_user(*(msg_Ptr++), buffer++);
        length--;
        bytes_read++;
    }
    return bytes_read;
}

static ssize_t device_write(struct file *filp, const char *buf, size_t len, loff_t *off)
{
    counter += len;
    return -EINVAL;
}

int __init mod_init(void)
{
    int ret;
    dev = MKDEV(MY_MAJOR, MY_MINOR);
    ret = register_chrdev_region(dev, cnt , DEVICE_NAME);
    if (ret<0) printk(KERN_ERR"Can not reg dev.");
    cdev_init(&hcdev,&fops);
    hcdev.owner = THIS_MODULE;
    ret = cdev_add(&hcdev,dev,cnt);
    if (ret<0) printk(KERN_ERR"Can not add dev.");

    printk(KERN_INFO"Module load suc.");
    return 0;
}

void __exit mod_exit(void)
{
    cdev_del (&hcdev);
    unregister_chrdev_region(MKDEV(MY_MAJOR, MY_MINOR), cnt);
}

module_init(mod_init);
module_exit(mod_exit);

MODULE_DESCRIPTION("Task 2.3");
MODULE_AUTHOR("Maksym Andreiev");
MODULE_LICENSE("GPL");