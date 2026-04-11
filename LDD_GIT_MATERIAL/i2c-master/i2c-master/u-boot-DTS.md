
### UBoot DTB vs Kernel DTB

    - There are 2 dtb. 
    - The u-boot dtb and the kernel dtb. They are 2 different things. 
    - U-boot board dts/dtb is not always used, not mandatory, by the way in u-boot you can use the "u-boot" dtb embedding it into u-boot or concatenating it to u-boot.
    - The u-boot source uses the u-boot DTB while Linux uses Linux DTB when kernel boots. 
    
### Device Tree Structure (DTS) is needed both in bootloader and kernel source code - See the reason below

    - The u-boot version is a stripped down version as there are not as many peripherals needed to boot. 
    - You always use the kernel version for Linux i.e. u-boot passes this one to Linux (as well as load bzImage or vmlinux).
    - Many of the u-boot drivers are almost identical to Linux. Obviously, you can make the same argument for all the u-boot drivers
    - Most are copies of the Linux drivers with interrupts replaced by polling routines. Using the same open-firmware interface enables them to match closer.


### U-Boot DTB

    - Uboot has separate DTS file, which can be set as CONFIG_DEFAULT_DEVICE_TREE in uboot defconfig. 
    - This DTS file is built with uboot image, meaning it is a part of uboot image.
    - Refer to doc/README.fdt-control for more details.

### Kernel DTB

    - Syntax of uboot DTS file is same as Linux kernel DTS file. Linux DTS file is compiled into DTB file and used as separately for parsing hardware configuration by Linux kernel. 
    - Linux DTB image is flashed separately from Linux kernel image.
    - Linux kernel uses the DTB passed by u-boot. But the DTB passed by u-boot is not the uboot's DTB. 
    - It is the Kernel's DTB (present in kernel sources). The uboot DTB is used by uboot during boot-up, to configure the devices, before the kernel is even loaded in memory.
 
### U-Boot DTB Configuration

 The board device tree has the same binding as the kernel. It is integrated within the U-Boot binaries: u-boot.bin

    - By default, it is appended at the end of the code (CONFIG_OF_SEPARATE).
    - It can be embedded in the U-Boot binary (CONFIG_OF_EMBED). This is particularly useful for debugging since it enables easy .elf file loading.

The U-Boot device tree (u-boot.dtb) can be also provided as external file loaded by FSBL when U-Boot code is started (u-boot-nodtb.bin: code without device tree): device tree address is provided as boot parameter (in r2 register).

A default device tree is available in the defconfig file (by setting CONFIG_DEFAULT_DEVICE_TREE).

You can either select another supported device tree using the DEVICE_TREE make flag. 
For BBB board, the corresponding file is <dts-file-name>.dts in arch/arm/dts/am335x_evm.dts.

How to build Device tree source code in u-boot

    $ make DEVICE_TREE=<dts-file-name>
 