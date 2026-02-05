#include "common.h"
#include "persist.h"

#include <linux/init.h>
#include <linux/kmod.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h>

int PersistBinary(const char *binary_path,  char **argv)
{

    int exit_code = INAT_FAILURE;
    int ret = 0;
    char *envp[] = {NULL};

    if (NULL == binary_path)
    {
        goto end;
    }

    if (NULL == argv)
    {
        goto end;
    }

    ret = call_usermodehelper(binary_path, argv, envp, UMH_NO_WAIT);
    if (ret)
    {
        goto end;
    }
    exit_code = INAT_SUCCESS;
end:
    return exit_code;
}