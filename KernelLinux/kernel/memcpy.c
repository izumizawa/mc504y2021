#include <linux/syscalls.h>

SYSCALL_DEFINE3(memcpy, void __user *, src, void __user *, dst,
        unsigned long, len)
{
    void *buf;

    buf = kmalloc(len, GFP_KERNEL);
    if (!buf)
        return -ENOMEM;

    if (copy_from_user(buf, src, len))
        return -EFAULT;

    if (copy_to_user(dst, buf, len))
        return -EFAULT;

    kfree(buf);
    return 0;
}