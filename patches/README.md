# Linux kernel patches

Here are some patches for the Linux kernel from upstream to get some
useful debug information.

## x86-e820-early-mm-dump.patch

This patch adds simple function that prints information about avilable
memory regions collected by `e820` during early setup.

Example:

```
Early memory map:

[USABLE]     base: 0x0 size: 0x654336
[RESERVED]   base: 0x654336 size: 0x1024
[RESERVED]   base: 0x983040 size: 0x65536
[USABLE]     base: 0x1048576 size: 0x3220045824
[RESERVED]   base: 0x3221094400 size: 0x131072
[RESERVED]   base: 0x4294705152 size: 0x262144
```