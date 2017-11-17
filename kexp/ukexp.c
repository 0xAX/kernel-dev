#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/netlink.h>

struct msghdr msg;
static int socket_fd;
static struct iovec iov;
static struct nlmsghdr *nlh = NULL;
static struct sockaddr_nl src_addr, dest_addr;

int main()
{
        /* create netlink socket */
	socket_fd = socket(PF_NETLINK, SOCK_RAW, 31);
	if (socket_fd < 0)
		return -1;

        /* fill netlink source address */
	memset(&src_addr, 0, sizeof(src_addr));
	src_addr.nl_family = AF_NETLINK;
	src_addr.nl_pid = getpid();

        /* bind an address to the netlink socket */
	bind(socket_fd, (struct sockaddr*)&src_addr, sizeof(src_addr));

        /* fill netlink destination address */
	memset(&dest_addr, 0, sizeof(dest_addr));
	dest_addr.nl_family = AF_NETLINK;
	dest_addr.nl_pid = 0;
	dest_addr.nl_groups = 0;

        /* fill netlink message header */
	nlh = (struct nlmsghdr *)malloc(NLMSG_SPACE(1024));
	memset(nlh, 0, NLMSG_SPACE(1024));
	nlh->nlmsg_len = NLMSG_SPACE(1024);
	nlh->nlmsg_pid = getpid();
	nlh->nlmsg_flags = 0;

        /* fill message */
	strcpy(NLMSG_DATA(nlh), "Hello");

        /* fill message header */
	iov.iov_base = (void *)nlh;
	iov.iov_len = nlh->nlmsg_len;
	msg.msg_name = (void *)&dest_addr;
	msg.msg_namelen = sizeof(dest_addr);
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;

        /* send message to kernel */
	sendmsg(socket_fd, &msg, 0);
	/* read message from kernel */
	recvmsg(socket_fd, &msg, 0);

	printf("Received message payload: %s\n", NLMSG_DATA(nlh));
	close(socket_fd);

        return 0;
}
