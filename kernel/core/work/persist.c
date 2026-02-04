#include "common.h"

#include <linux/init.h>
#include <linux/kmod.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h>

int PersistBinary(const char *binary_path, const char **argv)
{

    int exit_code = INAT_FAILURE;
    int ret = 0;
    char *envp[] = {NULL};

    if (NULL == binary_path)
    {
        // DPRINTF("binary_path is NULL");
        goto end;
    }

    if (NULL == argv)
    {
        // DPRINTF("argv is NULL"); idk man wierd issue happening with the DPRINTFs
        goto end;
    }

    ret = call_usermodehelper(binary_path, argv, envp, UMH_NO_WAIT);
    if (ret)
    {
        // DPRINTF("call_usermodehelper failed with an exit code of %d", ret );
        goto end;
    }
    exit_code = INAT_SUCCESS;
end:
    return exit_code;
}