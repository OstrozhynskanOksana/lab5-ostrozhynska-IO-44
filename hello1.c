// SPDX-License-Identifier: GPL-2.0
/*
 * Lab 5: module hello1 - exports print_hello() and keeps the list
 */

#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/types.h>
#include <linux/list.h>
#include <linux/ktime.h>
#include <linux/slab.h>

#include "hello1.h"

MODULE_AUTHOR("Oksana Ostrozhynska <ostrozhynska.oksana_io44@edu.kpi.ua>");
MODULE_DESCRIPTION("Lab 5: hello1 exports print_hello()");
MODULE_LICENSE("Dual BSD/GPL");

struct hello_event {
	struct list_head list;
	ktime_t start;
	ktime_t end;
};

static LIST_HEAD(hello_list);

int print_hello(void)
{
	struct hello_event *ev;

	ev = kmalloc(sizeof(*ev), GFP_KERNEL);
	if (!ev)
		return -ENOMEM;

	ev->start = ktime_get();
	pr_info("Hello, world!\n");
	ev->end = ktime_get();

	list_add_tail(&ev->list, &hello_list);

	return 0;
}
EXPORT_SYMBOL(print_hello);

static int __init hello1_init(void)
{
	pr_info("loaded\n");
	return 0;
}

static void __exit hello1_exit(void)
{
	struct hello_event *ev, *tmp;

	list_for_each_entry_safe(ev, tmp, &hello_list, list) {
		pr_info("print time: %lld ns\n",
			ktime_to_ns(ktime_sub(ev->end, ev->start)));
		list_del(&ev->list);
		kfree(ev);
	}
	pr_info("Goodbye!\n");
}

module_init(hello1_init);
module_exit(hello1_exit);
