
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/miscdevice.h>
#include <linux/kernel.h>

#define DRIVER_NAME "virt_led"
#define DEVICE_NAME "virt_led"

static ssize_t led_read(struct file *file, char __user *buf, size_t count, loff_t *ppos) {
    char kbuf[16];
    int len;
    static int led_state = 0;
    len = snprintf(kbuf, sizeof(kbuf), "%d\n", led_state);
    if (*ppos > 0) return 0;
    if (copy_to_user(buf, kbuf, len)) return -EFAULT;
    *ppos += len;
    return len;
}

static ssize_t led_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos) {
    char kbuf[16];
    int val = 0;
    if (count >= sizeof(kbuf)) return -EFAULT;
    if (copy_from_user(kbuf, buf, count)) return -EFAULT;
    kbuf[count] = '\0';
    if (kstrtoint(kbuf, 10, &val) == 0) {
        pr_info("%s: setting led state to %d\n", DRIVER_NAME, val ? 1 : 0);
        /* simulate hardware write / memory-mapped I/O here */
    } else {
        return -EINVAL;
    }
    return count;
}

static const struct file_operations led_fops = {
    .owner = THIS_MODULE,
    .read = led_read,
    .write = led_write,
};

static struct miscdevice led_misc = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = DEVICE_NAME,
    .fops = &led_fops,
};

static int __init led_init(void) {
    int ret = misc_register(&led_misc);
    if (ret) {
        pr_err("%s: misc_register failed %d\n", DRIVER_NAME, ret);
        return ret;
    }
    pr_info("%s: registered, /dev/%s created\n", DRIVER_NAME, DEVICE_NAME);
    return 0;
}

static void __exit led_exit(void) {
    misc_deregister(&led_misc);
    pr_info("%s: unregistered\n", DRIVER_NAME);
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rohit K");
MODULE_DESCRIPTION("Virtual LED character driver");
module_init(led_init);
module_exit(led_exit);
