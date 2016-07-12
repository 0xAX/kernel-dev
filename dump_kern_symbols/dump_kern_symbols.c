#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/kallsyms.h>
#include <linux/seq_file.h>

/*
 * TODO:
 *  * Add other sections
 */
typedef u64 virt_addr_t;

static struct proc_dir_entry *kernel_symbols_info;

static int kern_syms_proc_show(struct seq_file *m, void *v)
{
	phys_addr_t __text = (phys_addr_t)__pa_symbol(kallsyms_lookup_name("_text"));
	virt_addr_t __text_v = (virt_addr_t)kallsyms_lookup_name("_text");

	phys_addr_t __etext = (phys_addr_t)__pa_symbol(kallsyms_lookup_name("_etext"));
	
	phys_addr_t __bss_start = (phys_addr_t)__pa_symbol(kallsyms_lookup_name("__bss_start"));
	virt_addr_t __bss_start_v = (virt_addr_t)kallsyms_lookup_name("__bss_start");

	phys_addr_t __bss_stop = (phys_addr_t)__pa_symbol(kallsyms_lookup_name("__bss_stop"));

	seq_printf(m, "                     \t\tStart                  End\t\t\tSize\n\n");
	seq_printf(m, "_text physical addr: \t\t[%#llx]            [%llu]\t\t[%llu bytes]\n", __text, __text, __etext - __text);
	seq_printf(m, "_text virtual  addr: \t\t[%#llx]   [%llu]\n", __text_v, __text_v);

	seq_printf(m, "\n");

	seq_printf(m, "__bss physical addr: \t\t[%#llx]            [%llu]\t\t[%llu bytes]\n", __bss_start, __bss_start, __bss_stop - __bss_start);
	seq_printf(m, "__bss virtual  addr: \t\t[%#llx]   [%llu]\n", __bss_start_v, __bss_start_v);

	return 0;
}

static int kern_syms_open(struct inode *inode, struct file *file)
{
	return single_open(file, kern_syms_proc_show, NULL);
}

static const struct file_operations kern_syms_fops = {
	.open		= kern_syms_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static int __init dump_pts_init(void)
{
	kernel_symbols_info = proc_create("kern_syms_info", 0, NULL, &kern_syms_fops);

	if (!kernel_symbols_info)
	{
		pr_info("Error creating /proc/kernel_pages directory");
		return -ENOMEM;
	}

        return 0;
}

static void __exit dump_pts_cleanup(void)
{
	remove_proc_entry("kern_syms_info", NULL);
}

module_init(dump_pts_init);
module_exit(dump_pts_cleanup);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Alexander Kuleshov <kuleshovmail@gmail.com>");
MODULE_DESCRIPTION("Expose page tables to the /proc.");
