/**
 * hello.c - The Hello World kernel module.
 */
#include <linux/module.h>	/**< Needed by all modules */
#include <linux/kernel.h>	/**< Needed for KERN_INFO */
#include <linux/init.h>		/**< Needed for the macros */

#include "../profiler/kprofiler.h"

#define AUTHOR	"Wayne"
#define DESC	"Hello World"


/**
 * @brief	Get rid of taint message by declaring code as GPL.
 */
MODULE_LICENSE("GPL");
MODULE_AUTHOR(AUTHOR);
MODULE_DESCRIPTION(DESC);
MODULE_SUPPORTED_DEVICE("testdevice");

/**
 * module_param(name, type, permissions_bits);
 */
static int n = 3;
module_param(n, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(n, "An integer");


/**
 * @brief 	Called when the module is insmoded into kernel.
 */
static int __init hello_world_init(void)
{
	printk(KERN_INFO "Hello World.\n");
	prof_begin("Hello World");
	prof_begin("Do nothing");
	prof_end("Do nothing");

	return 0;
}

/**
 * @brief 	Called just before the module is rmmoded.
 */
static void __exit hello_world_exit(void)
{
	prof_end("Hello World");
	prof_dump();
	printk(KERN_INFO "Goodbye.\n");
}

module_init(hello_world_init);
module_exit(hello_world_exit);

