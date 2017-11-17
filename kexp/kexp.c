#include <linux/module.h>
#include <net/sock.h>
#include <linux/netlink.h>
#include <linux/skbuff.h>

struct sock *socket = NULL;

static void recvmsg(struct sk_buff *skb)
{
        int res;
        int pid;
        struct nlmsghdr *nlh = (struct nlmsghdr*)skb->data;
        char *received_msg = (char*)nlmsg_data(nlh);
        size_t msg_len = strlen(received_msg);
        struct sk_buff *skb_out;

        printk(KERN_INFO "Netlink received msg payload:%s\n", received_msg);

        /* getting pid of sending process */
        pid = nlh->nlmsg_pid;
        
        skb_out = nlmsg_new(6, 0); /* 6 is message size */
	if (!skb_out) {
		printk(KERN_ERR "Failed to allocate new skb\n");
		return;
        }
        nlh = nlmsg_put(skb_out, 0, 0, NLMSG_DONE, msg_len, 0);
        NETLINK_CB(skb_out).dst_group = 0;
        strncpy(nlmsg_data(nlh), received_msg, msg_len);


        res = nlmsg_unicast(socket, skb_out, pid);

	if (res)
                printk(KERN_INFO "Error while sending back to user\n");
}

struct netlink_kernel_cfg cfg =
{
    .input = recvmsg,
};

static int __init kexp_mod_init(void)
{
        printk("Entering: %s\n",__FUNCTION__);

        socket = netlink_kernel_create(&init_net, 31, &cfg);
        if (!socket)
        {
                printk(KERN_ALERT "Error creating NETLINK socket.\n");
                return -1;
        }

        return 0;
}

static void __exit kexp_mod_cleanup(void)
{
        printk(KERN_INFO "kexp module exiting...\n");
        netlink_kernel_release(socket);
}


module_init(kexp_mod_init);
module_exit(kexp_mod_cleanup);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Alexander Kuleshov <kuleshovmail@gmail.com>");
MODULE_DESCRIPTION("Expose page tables to the /proc.");
