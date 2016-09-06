# dump_kern_symbols

The `dump_kern_symbols` module provides simple module which dumps some kernel symbols which are related
to sections boundaries.

## Usage

```
$ cd dump_kern_symbols
$ make
$ sudo insmod dump_kern_symbols.ko
```

The `dump_kern_symbols` module will create `/proc/kern_syms_info` file:

```
cat /proc/kern_syms_info 
                     		Start                  End                      Size

_text physical addr: 		[0x1000000]            [16777216]               [7906806 bytes]
_text virtual  addr: 		[0xffffffff81000000]   [18446744071578845184]

__bss physical addr: 		[0x201e000]            [33677312]               [11468800 bytes]
__bss virtual  addr: 		[0xffffffff8201e000]   [18446744071595745280]
```
