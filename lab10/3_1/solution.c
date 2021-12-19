#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/device.h>
#include <linux/kernel.h>

#define  CLASS_NAME  "ebb"

static int Major;
static struct class*  charClass  = NULL;
static struct device* charDevice = NULL;
static char msg[256];
static char *msg_Ptr;
static char * node_name;
module_param(node_name,charp,0);

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
    return 0;
}

int __init mod_init(void)
{
    printk(KERN_NOTICE "Module loaded!\n");

    Major = register_chrdev(0, node_name, &fops);

    if (Major < 0) {
        printk(KERN_ALERT "Registering char device failed with %d\n", Major);
        return Major;
    }
    sprintf(msg, "%d\n", Major);
    msg_Ptr = msg;

    // Register the device class
    charClass = class_create(THIS_MODULE, CLASS_NAME);
    if (IS_ERR(charClass)){
        unregister_chrdev(Major, node_name);
        printk(KERN_ALERT "Failed to register device class\n");
        return PTR_ERR(charClass);
    }

    // Register the device driver
    charDevice = device_create(charClass, NULL, MKDEV(Major, 0), NULL, node_name);
    if (IS_ERR(charDevice)){
        class_destroy(charClass);
        unregister_chrdev(Major, node_name);
        printk(KERN_ALERT "Failed to create the device\n");
        return PTR_ERR(charDevice);
    }
    return 0;
}

void __exit mod_exit(void)
{
    device_destroy(charClass, MKDEV(Major, 0));
    class_unregister(charClass);
    class_destroy(charClass);
    unregister_chrdev(Major, node_name);
    printk(KERN_NOTICE "Module unloaded!\n" );
}

module_init(mod_init);
module_exit(mod_exit);

MODULE_DESCRIPTION("Task 3.1");
MODULE_AUTHOR("Maksym Andreiev");
MODULE_LICENSE("GPL");