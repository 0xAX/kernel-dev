# kernel-sections

The `kernel-sections` module provides simple module which dumps some kernel symbols (sections) which are
related to sections boundaries.

## Usage

```
$ cd dump_kern_symbols
$ make
$ sudo insmod kernel-sections.ko
```

The `kernel-sections` module will create `/proc/kernel-sections` file:

```
cat /proc/kernel-sections
                     		Start                  End                      Size

_text physical addr: 		[0x1000000]            [16777216]               [7906806 bytes]
_text virtual  addr: 		[0xffffffff81000000]   [18446744071578845184]

__bss physical addr: 		[0x201e000]            [33677312]               [11468800 bytes]
__bss virtual  addr: 		[0xffffffff8201e000]   [18446744071595745280]
```
