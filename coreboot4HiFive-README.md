# coreboot

## 简介

coreboot之前被称为LinuxBIOS，是一个旨在替换专有固件（BIOS/UEFI）的软件项目，其轻量级固件旨在加载执行32/64位操作系统。由于coreboot需要初始化裸机，必须将其移植到其支持到每一个芯片组和主板上。因此，coreboot只支持有限数量到硬件平台和主板型号。

## 历史

coreboot项目始于1999年冬天的洛斯阿拉莫斯国家实验室（LANL）的高级计算实验室，旨在创建一个可以快速启动、智能处理错误的BIOS。

它的版权基于GPL协议。

主要贡献者有LANL、SiS、AMD、Coresystem和Linux Nerworx，以及主板厂商MSI、Gigabyte和Tyan。这些主板厂商与标准BIOS一起提供coreboot，或者提供某些主板的硬件接口规范。

Google部分赞助了coreboot。从2009年开始CME集团（期货交易）开始支持coreboot。

coreboot曾经连续7年（2007-2014）获得Google夏季编码（Google Summer of Code，Google举办到一个编程比赛）。

除了最初的三种型号，所有到chromebook都支持coreboot。

Das U-boot的部分代码被吸收进coreboot，用于支持ARM指令集架构。

2017年5月1日，英特尔在其管理的固件中确认并修复了远程提权漏洞（CVE-2017-5689），这是coreboot/libreboot用户怀疑到一个漏洞。任何包含因特尔标准远程管理技术的平台（Active Management Technology / Small Business Technology），从2008年的Nehalem到2017年到Kaby Lake，在IME（Intel Management Engine）中都存在一个远程利用到安全漏洞。IME内的另一安全风险是英特尔博锐蜂窝无线电，可以远程访问硬件组件，甚至破坏计算机硬件。

## 设计

coreboot一般用于加载linux内核，但它也可以加载独立到ELF（不依赖执行环境、裸机程序），例如：SeaBIOS（开源的传统BIOS实现）、TianoCore（开源的UEFI实现）、GNU GRUB、Etherboot（网络操作系统加载器）

coreboot主要通过C语言实现，只有少量的汇编代码。选择C语言是 由于这样可以更轻松的进行代码审计，这有助与代码安全的提高。源代码根据GPL2许可发布。

coreboot执行最小化的硬件初始化，然后把控制器交给操作系统。一但操作系统被执行就不会在执行coreboot代码。x86下仅仅执行很少的代码就切换到32位模式（最大部分BIOS运行在16位模式），这个与UEFI固件相同。

coreboot本身没有提供BIOS调用服务，而是通过SeaBIOS payload实现，这允许coreboot加载操作系统。然而，大多数现代操作系统以另一种方式访问硬件，并且在早期初始化期间仅使用BIOS调用，并且作为回退机制。

coreboot设计成多个阶段

1. bootblock ： 获取FLASH访问权限，并查找引导rom stage
2. rom stage ： 内存和早期到芯片初始化， 并查找引导ram stage
3. ram stage ：设备枚举资源分配、创建ACPI表以及SMM句柄，并查找加载payload
4. payload


coreboot把以上阶段到binary打包进一个文件，这样构成一个固件。固件可以烧写到对应系统的FLASH中。bootblock一般由机器自动加载（类似BIOS自动加载MBR），其他阶段由上一个阶段通过文件结构查找并加载进内存执行。

## 变种

coreboot有一些变种

- librecore 此变种更注重自由，非x86固件开发框架
- libreboot 此变种目的在于删除私有的二进制blob

# HiFive1

HiFive1是一个基于RISC-V的开源的兼容Arduino的开发套件。此套件基于首款商用RISC-V SOC Freedom E310。

## HiFive1规格和特定

- 微控制器：SiFive Freedom E310（FE310）
  - IP核：E31 Coreplex
  - 架构：32BIT RV32IMAC
  - 主频：320+MHz
  - 性能：1.61DMIPs/MHz，2.73Coremark/MHz
  - 内存：16KB指令缓存，16KB数据存储器
  - 其他功能：硬件乘除法器，调试模块，灵活到时钟（片上振荡器、PLLs）
- 操作电压：3.3V和1.8V
- 输入电压：5VUSB供电，或者7-12V DC接口供电
- IO电压：3.3V或者5V
- 数字IO口：19个
- PWM引脚：9个
- SPI控制器：
- 外部中断引脚：19个
- 外部唤醒引脚：1个
- Flash存储器：外接SPI Flash，128Mbit
- 主机接口（microUSB）:编程、调试、UART通讯（通过FT2232分别与芯片到JTAG和UART连接）
- 外形尺寸：68mm * 51mm
- 重：22g

## 开发工具freedom-e-sdk介绍

### 获取

命令：git clone --recursive https://github.com/sifive/freedom-e-sdk.git

### 工具链构建

命令：make tools BOARD = freedom-e300-hifive1

此命令会编译gcc、binutils、gdb以及openocd

gcc、binutils、gdb位于于**work/build/riscv-gnu-toolchain/riscv64-unknown-elf/prefix**

openocd位于**work/build/openocd/prefix**

### 目录介绍

> bsp
> > drivers 驱动
> > env C语言启动代码
> > include 头文件
> > libwrap gcc库支持（实现系统调用接口）
>
> FreedomStudio 
> openocd openocd 源码
> riscv-gnu-toolchain gcc、bintuils、gdb 源码
> software 示例代码，开发目录
> work 工具链生成目录

### 开发简介

开发只需要通过freedom-e-sdk根目录下的makefile，就可以进行编译下载操作。有兴趣可以研究一下此makefile，这样对于理解整个开发过程有一定帮助。

直接运行make将输出帮助信息

#### 编译

命令：make softwore BOARD=freedom-e300-hifive1 PROGRAM=hello

此命令意思为：给目标板（freedom-e300-hifive1）编译software下hello项目

**BOARD**用于指定目标主板的型号（支持到主板对于bsp/env下的一个目录）

**PROGRAM**用于指定要编译到项目，位于software下到一个文件夹

#### 下载

命令：make upload BOARD=freedom-e300-hifive1 PROGRAM=hello

此命令意思为：下载software下hello项目到目标板（freedom-e300-hifive1）

**BOARD**用于指定目标主板的型号（支持到主板对于bsp/env下的一个目录）

**PROGRAM**用于指定要编译到项目，位于software下到一个文件夹

# riscv架构coreboot代码结构

当前coreboot代码并没有支持真实硬件，只有模拟器（qemu/spike）的支持。

coreboot启动过程被分为三个阶段（bootblock、rom stage、ram stage），这三个过程为三个独立的可执行文件。

以下分析基于spike平台。

## bootblock

bootblock为机器上电执行的代码，入可位于src/arch/riscv/bootblock.S中

此文件负责初始化堆栈、初始化hart相关的数据结构、初始化异常、然后转入C程序入口

bootblock有通用到C语言部分，它提供了一个通用到初始化引导流程。源代码位于src/lib/bootblock.c中

初始化过程主要通过四个函数实现，具体平台可以根据具体情况具体实现。

```c
// 早期芯片相关初始化
__attribute__((weak)) void bootblock_soc_early_init(void) { /* do nothing */ }
// 早期主板相关初始化
__attribute__((weak)) void bootblock_mainboard_early_init(void) { /* no-op */ }
// SOC初始化
__attribute__((weak)) void bootblock_soc_init(void) { /* do nothing */ }
// 主板初始化
__attribute__((weak)) void bootblock_mainboard_init(void) { /* do nothing */ }
```

加载并执行rom stage通过**run_romstage**实现

## rom stage

rom stage入口位于src/arch/riscv/stages.c中。**stage_entry** 不进行.data .bsss数据段初始化，这是因为这部分工作被加载过程代替了。

rom stage主程序位于src/mainboard/emulation/spike-riscv/romstage.c中

此函数比较简单，初始化串口、打印内存信息、引导下一个过程

下一个过程又框架提供的**run_ramstage**实现

## ram stage

ram stage入口位于src/arch/riscv/stages.c中。**stage_entry** 不进行.data .bsss数据段初始化，这是因为这部分工作被加载过程代替了。

ram stage有通用到C语言部分，它提供一个通用到初始化引导流程。源代码位于src/lib/hardwaremain.c中

ram stage把启动过程分为12步
```c
typedef enum {
	BS_PRE_DEVICE,
	BS_DEV_INIT_CHIPS,
	BS_DEV_ENUMERATE,
	BS_DEV_RESOURCES,
	BS_DEV_ENABLE,
	BS_DEV_INIT,
	BS_POST_DEVICE,
	BS_OS_RESUME_CHECK,
	BS_OS_RESUME,
	BS_WRITE_TABLES,
	BS_PAYLOAD_LOAD,
	BS_PAYLOAD_BOOT,
} boot_state_t;
```

每个过程分为三步：Entry callbacks、State Actions、Exit callbacks

每个过程通过boot_state描述，State Actions框架以及实现。

Entry callbacks、Exit callbacks用户可以根据具体平台实现。

Entry callbacks、Exit callbacks为回调函数列表

一个回调通过boot_state_callback结构描述，boot_state_callback可以构成链表记录同一个过程中同一个步骤的所有回调函数

boot_state_init_entry结构体用于记录一个回调，以及其启动步骤

并定义了一个宏BOOT_STATE_INIT_ENTRY，用于把boot_state_init_entry类型的变量放入同一个段，这样便于初始化（建立回调函数与boot_state的关联）

boot_state_schedule_static_entries函数用于建立回调与boot_state到关联

bs_walk_state_machine用于遍历boot_state数组，一步一步执行初始化及引导过程

## 引导与加载

coreboot把bootblock、rom stage、ram stage以及payload打包成一个固件文件

bootblock一般由硬件直接加载进内存（类似BIOS加载MBR）。

其他阶段通过上一个阶段解析固件文件找到并加载进内存执行。

执行过程一般需要具体架构实现（这与程序到权限有关），这个函数被命名为arch_prog_run（riscv源码位于src/arch/riscv/boot.c中）

## 固件文件结构

固件顶层是一个固定的块结构，此结构把固件文件分成固定大小到块，每一个块具有名字。

名字为FMAP的块存放了块布局信息。块信息通过两个结构体描述，fmap、fmap_area

```c
struct fmap {
	uint8_t  signature[8];		/* "__FMAP__" (0x5F5F464D41505F5F) */
	uint8_t  ver_major;			/* major version */
	uint8_t  ver_minor;			/* minor version */
	uint64_t base;				/* address of the firmware binary */
	uint32_t size;				/* size of firmware binary in bytes */
	uint8_t  name[FMAP_STRLEN];	/* name of this firmware binary */
	uint16_t nareas;			/* number of areas described by fmap_areas[] below */
	struct fmap_area areas[];
} __attribute__((packed));

struct fmap_area {
	uint32_t offset;			/* offset relative to base */
	uint32_t size;				/* size in bytes */
	uint8_t  name[FMAP_STRLEN];	/* descriptive name */
	uint16_t flags;				/* flags for this area */
}  __attribute__((packed));
```

名字为COREBOOT块，存放了cbfs。

cbfs内存试图如下，其中一个component对应一个文件

```
/---------------\ <-- Start of ROM
| /-----------\ | --|
| | Header    | |   |
| |-----------| |   |
| | Name      | |   |-- Component
| |-----------| |   |
| |Data       | |   |
| |..         | |   |
| \-----------/ | --|
|               |
| /-----------\ |
| | Header    | |
| |-----------| |
| | Name      | |
| |-----------| |
| |Data       | |
| |..         | |
| \-----------/ |
|               |
| ...           |
|               |
\---------------/
```

上图中的文件头Header使用结构体cbfs_file描述

```c
struct cbfs_file {
	uint8_t magic[8];
	/* length of file data */
	uint32_t len;
	uint32_t type;
	/* offset to struct cbfs_file_attribute or 0 */
	uint32_t attributes_offset;
	/* length of header incl. variable data */
	uint32_t offset;
	char filename[];
} __PACKED;
```

其中offset、len描述了数据的位置，如下图

```
/--------\  <- start
| Header |
|--------|  <- sizeof(struct cbfs_file)
| Name   |
|--------|  <- 'offset'
| Data   |
| ...    |
\--------/  <- start + 'offset' + 'len'
```

然后再用Data保存stage、payload，为此定义了一些其他到数据结构

## 终端

终端代码位于src/console中

console.c是主要到框架代码，里面声明了一个简单到框架，可以终端可以使用多种硬件设备

init.c主要导出了终端初始化函数

vtxprintf.c、vsprintf.c、printk.c几个文件通过console.c提供到接口，实现了类C语言printf的printk函数

其他，是一些简单到辅助函数

# 移植

## 问题与对策

### 问题

- coreboot源码是基于RV64的

- RAM空间太小，无法把固件加载进内存运行

### 解决途径

要支持RV32首先需要修改编译选项，让编译器汇编器生成32未代码
然后编译报错后对源码进行修改
主要涉及汇编文件中的汇编指令与C语言中32位64位数据类型问题

RAM空间不足问题，这个暂时无法解决。HiFive1是一个评估板，更多是用于验证IP核的
这里，我剔除cbfs文件，直接在Flash中布局程序，上一个阶段直接跳转到下一个阶段

## 修改

### 编译选项相关

这个需要修改编译系统给编译器汇编器传递参数

首先，我们移植HiFive1需要创建两个目录src/soc/sifive、src/mainboard/sifive，分别用于存放soc和主板相关代码

在SOC目录下新建文件Kconfig，内容如下

```
config SOC_SIFIVE_E300				# 定义SOC的宏
	# 选择需要到模块
	select ARCH_RISCV
	select ARCH_BOOTBLOCK_RISCV
	select ARCH_VERSTAGE_RISCV
	select ARCH_ROMSTAGE_RISCV
	select ARCH_RAMSTAGE_RISCV
	select BOOTBLOCK_CONSOLE
	# 选择串口工作模式
    select HAVE_UART_SPECIAL
	bool
	default n

if SOC_SIFIVE_E300

# 传递给编译器到信息
config RISCV_ARCH
    string
    default "rv32imac"

config RISCV_ABI
    string
    default "ilp32"

endif
```

然后修改src/arch/riscv下到Makefile.inc

```
riscv_flags = -I$(src)/arch/riscv/ -mcmodel=medany -march=$(CONFIG_RISCV_ARCH) -mabi=$(CONFIG_RISCV_ABI)
riscv_asm_flags = -march=$(CONFIG_RISCV_ARCH) -mabi=$(CONFIG_RISCV_ABI)

bootblock-c-ccopts += $(riscv_flags)
bootblock-S-ccopts += $(riscv_asm_flags)

romstage-c-ccopts += $(riscv_flags)
romstage-S-ccopts += $(riscv_asm_flags)

ramstage-c-ccopts += $(riscv_flags)
ramstage-S-ccopts += $(riscv_asm_flags)
```

### 汇编指令相关

在RV32、RV64下，访问一个字的指令不一样这部分代码通过宏实现实现在src/arch/riscv/include/bits.h中。

部分硬编码的指令编译会保存，可以根据编译器提示手动修改

```c
#if __riscv_xlen == 32
	#define SLL32    ssl
	#define STORE    sw
	#define LOAD     lw
	#define LOG_REGBYTES 2
#elif __riscv_xlen == 64
	#define SLL32    sllw
	#define STORE    sd
	#define LOAD     ld
	#define LOG_REGBYTES 3
#endif

#define REGBYTES (1 << LOG_REGBYTES)	// 一个机器字有多少个字节
```

由于RV32、RV64访问内存指令到差异，这会影响访问物理内存宏到定义。这部分实现在src/arch/riscv/include/vm.h中

```c
#if __riscv_xlen == 32
DEFINE_MPRV_READ(mprv_read_u8, uint8_t, lbu)
DEFINE_MPRV_READ(mprv_read_u16, uint16_t, lhu)
DEFINE_MPRV_READ(mprv_read_u32, uint32_t, lw)
DEFINE_MPRV_READ(mprv_read_long, long, lw)
DEFINE_MPRV_READ(mprv_read_ulong, unsigned long, lw)
DEFINE_MPRV_WRITE(mprv_write_u8, uint8_t, sb)
DEFINE_MPRV_WRITE(mprv_write_u16, uint16_t, sh)
DEFINE_MPRV_WRITE(mprv_write_u32, uint32_t, sw)
DEFINE_MPRV_WRITE(mprv_write_long, long, sw)
DEFINE_MPRV_WRITE(mprv_write_ulong, unsigned long, sw)
#elif __riscv_xlen == 64
DEFINE_MPRV_READ(mprv_read_u8, uint8_t, lbu)
DEFINE_MPRV_READ(mprv_read_u16, uint16_t, lhu)
DEFINE_MPRV_READ(mprv_read_u32, uint32_t, lwu)
DEFINE_MPRV_READ(mprv_read_u64, uint32_t, ld)
DEFINE_MPRV_READ(mprv_read_long, long, ld)
DEFINE_MPRV_READ(mprv_read_ulong, unsigned long, ld)
DEFINE_MPRV_WRITE(mprv_write_u8, uint8_t, sb)
DEFINE_MPRV_WRITE(mprv_write_u16, uint16_t, sh)
DEFINE_MPRV_WRITE(mprv_write_u32, uint32_t, sw)
DEFINE_MPRV_WRITE(mprv_write_u64, uint64_t, sd)
DEFINE_MPRV_WRITE(mprv_write_long, long, sd)
DEFINE_MPRV_WRITE(mprv_write_ulong, unsigned long, sd)
#endif
```

### 数据类型相关

coreboot有专门的抽象数据类型，用于定义机器字长，这部分实现在src/arch/riscv/include/stdin.h中

```c
#if __riscv_xlen == 32
typedef s32     intptr_t;
typedef u32     uintptr_t;
#elif __riscv_xlen == 64
typedef s64     intptr_t;
typedef u64     uintptr_t;
#endif
```

数据类型会影响很多C程序，这部分一般编译时会报错，可以根据编译器提示进行修改

### 内存布局

这部分由链接脚本指定，coreboot平台实现了一些宏（src/include/memlayout.h），这些宏用于方便定义各个阶段的内存位置

但coreboot认为各个阶段都是加载进内存的（代码段与数据段是连续的），而HiFive1这种MCU结构可以直接在Flash中执行，需要对此文件进行修正

HiFive1内存布局如下

```
#define RAM_START   0x80000000
#define FLASH_START 0x20400000

SECTIONS
{
    BOOTBLOCK(       FLASH_START, 64K)
    ROMSTAGE ( FLASH_START + 64K, 64K)
    RAMSTAGE (FLASH_START + 128K, 64K)

    SRAM_START          (RAM_START)
    STACK               (RAM_START + 4K, 4K)
    PAGETABLES          (RAM_START + 8K, 4K)
    PRERAM_CBMEM_CONSOLE(RAM_START + 12K, 4K)
    SRAM_END            (RAM_START + 16k)
}
```

### 终端支持

这部分参照部分SOC的代码，以及src/console/console.c。

需要在SOC目录到Kconfig中添加**select HAVE_UART_SPECIAL**，这样不使用平台实现的一些驱动（8250等）

然后实现5个函数，这部分可以参照freedom-e-sdk代码进行编写

```c
// 初始化UART
void uart_init(int idx);
// 接受一个字符
uint8_t uart_rx_byte(int idx);
// 发送一个字符
void uart_tx_byte(int idx,unsigned char data);
// 刷新终端
void uart_tx_flush(int idx);
// 平台的一些内部数据维护
void uart_fill_lb(void *data)
```

### 执行下一个阶段代码

由于知道每个阶段下一个阶段的起始位置，可以直接使用函数跳转

在src/lib/bootblock.c中添加如下代码跳转到rom stage

```c
((void (*)(void))0x20410000)();
```

在src/soc/sifive/e300/romstage.c中添加如下代码跳转到ram stage

```c
((void (*)(void))0x20420000)();
```

### 链接多个阶段

操作过程通过shell脚本完成，这里简要说明转换过程

#### 把各阶段程序转换为binary

```shell
riscv64-elf-objcopy -O binary build/cbfs/fallback/bootblock.elf bootblock.bin
riscv64-elf-objcopy -O binary build/cbfs/fallback/romstage.elf  romstage.bin
riscv64-elf-objcopy -O binary build/cbfs/fallback/ramstage.elf  ramstage.bin
riscv64-elf-objcopy -O binary hello                             hello.bin
```

#### 把binary放进elf文件

这里以bootblock为例，需要先建立一个汇编文件

```assembly
    .global _start
    .section .text
_start:
    .incbin "bootblock.bin"
```

然后通过汇编器编译，最后生成bootblock-raw.o、romstage-raw.o、ramstage-raw.o、hello-raw.o（最终要加载的用户程序）

```shell
riscv64-elf-as bootblock-raw.S -o bootblock-raw.o
```

#### 链接

链接脚本如下

```
ENTRY(_start)
SECTIONS
{
    .text 0x20400000 :
    {
        . = 0x00000;
        bootblock-raw.o(.text)
        . = 0x10000;
        romstage-raw.o(.text)
        . = 0x20000;
        ramstage-raw.o(.text)
        . = 0x30000;
        hello-raw.o(.text)
    }
}
```

命令

```
riscv64-elf-ld -T coreboot-raw.ld bootblock-raw.o romstage-raw.o ramstage-raw.o hello-raw.o -o coreboot-raw.elf
```

## 下载代码到目标板

下载需要通过如下命令实现

```shell
# 先启动openocd
openocd -f openocd.cfg >/dev/null 2>&1 &

# 再通过gdb下载代码到目标板
riscv64-unknown-elf-gdb coreboot-raw.elf \
    --batch \
    -ex "set remotetimeout 500" \
    -ex "target extended-remote localhost:3333" \
    -ex "monitor reset halt" \
    -ex "monitor flash protect 0 64 last off" \
    -ex "load" \
    -ex "monitor resume" \
    -ex "monitor shutdown" \
    -ex "quit" && echo Successfully uploaded $PROGRAM 
```

## 测试我的代码

### 代码获取

命令：git clone https://github.com/wxjstz/coreboot4HiFive1.git

### 编译工具链

命令：make crossgcc-riscv

### 配置

命令：make menuconfig

设定：

- Mainboard $\Rightarrow$ Mainboard vendor 选择SiFive
- Mainboard $\Rightarrow$ Mainboard model 选择Freedom e300 hifive1
- 取消选择 General setup $\Rightarrow$ Compress ramstage with LZMA
- 取消选择 General setup $\Rightarrow$ Compress romstage and versrage with LZ4
- 取消选择 Console $\Rightarrow$ Send console output to CBMEM buffer
- 取消选择 Console $\Rightarrow$ Send POST codes to an external device

### 编译

命令：make

### 下载

命令：./build-raw























