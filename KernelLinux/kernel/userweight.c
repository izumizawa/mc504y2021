#include <linux/syscalls.h>
#include <unistd.h>

SYSCALL_DEFINE1(getuserweight, int, uid)
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

SYSCALL_DEFINE2(setuserweight, int, uid, int, weight)
{
    if (geteuid() != 0)
        return -EACCES;
    if ((uid < 0 && uid != -1) || uid > 65535 || weight <= 0)
        return -EINVAL;

    void *buf;

    buf = kmalloc(sizeof(weight), GFP_USER);
    if (!buf)
        return -ENOMEM;

    // store user weight

    // if (copy_from_user(buf, weight, sizeof(weight)))
    //     return -EFAULT;    

    kfree(buf);
    return 0;
}