// SPDX-License-Identifier: GPL-2.0
/*
 * Lab 5: module hello2 - has the count parameter, calls print_hello()
 */

#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include <linux/types.h>

#include "hello1.h"

MODULE_AUTHOR("Oksana Ostrozhynska <ostrozhynska.oksana_io44@edu.kpi.ua>");
MODULE_DESCRIPTION("Lab 5: hello2 calls print_hello() from hello1");
MODULE_LICENSE("Dual BSD/GPL");

static uint count = 1;
module_param(count, uint, 0444);
MODULE_PARM_DESC(count, "How many times to print \"Hello, world!\" (default 1, max 10)");

static int __init hello2_init(void)
{
	uint i;
	int ret;

	if (count > 10) {
		pr_err("count=%u is too big (must be <= 10), not loading\n",
		       count);
		return -EINVAL;
	}

	if (count == 0 || (count >= 5 && count <= 10))
		pr_warn("count=%u is 0 or between 5 and 10, continuing\n",
			count);

	for (i = 0; i < count; i++) {
		ret = print_hello();
		if (ret)
			return ret;
	}

	return 0;
}

static void __exit hello2_exit(void)
{
	pr_info("Goodbye!\n");
}

module_init(hello2_init);
module_exit(hello2_exit);
