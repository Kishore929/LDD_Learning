## Yocto Zeus 3.0.4 porting on Beagle Bone Black (BBB)
<!-- vim-markdown-toc GitLab -->

* [1. Setup Yocto Build Environment](#1-setup-yocto-build-environment)
	* [1.1. Yocto Configuration](#11-yocto-configuration)
	* [1.2. Version Information](#12-version-information)
	* [1.3. Ubuntu Setup](#13-ubuntu-setup)
* [2. Download Zeus 3.0.3 yocto source code](#2-download-zeus-303-yocto-source-code)
* [3. Initialize the build directory](#3-initialize-the-build-directory)
* [4. Customize the configuration files - Edit local config files](#4-customize-the-configuration-files-edit-local-config-files)
	* [4.1. Customize Variables](#41-customize-variables)
		* [4.1.1. TMPDIR](#411-tmpdir)
		* [4.1.2. DL_DIR](#412-dl_dir)
		* [4.1.3. SSTATE_DIR](#413-sstate_dir)
	* [4.2. ROOT PASSWORD](#42-root-password)
* [5. Types of yocto images](#5-types-of-yocto-images)
	* [5.1. console-image](#51-console-image)
	* [5.2. qt5-image](#52-qt5-image)
	* [5.3. Installer-image](#53-installer-image)
* [6. Build Console Image](#6-build-console-image)
* [7. Copying the binaries to an SD card](#7-copying-the-binaries-to-an-sd-card)
	* [7.1. Create SD card 2 Paritions](#71-create-sd-card-2-paritions)
	* [7.2. Copy MLO & u-boot.img in to SD Card first parition.](#72-copy-mlo-u-bootimg-in-to-sd-card-first-parition)
	* [7.2. Copy Root file system along with Kerel Image in to SD Card Second parition.](#72-copy-root-file-system-along-with-kerel-image-in-to-sd-card-second-parition)
	* [7.3. Summary](#73-summary)
* [8. Booting from the SD card](#8-booting-from-the-sd-card)
* [9.  ERROR 1](#9-error-1)

<!-- vim-markdown-toc -->

Setup Embedded Linux Developemnt environment with Yocto project using Beaglebone black hardware.

Yocto is a set of tools for building a custom embedded Linux distribution. The systems are usually targeted at particular applications like commercial products.

## 1. Setup Yocto Build Environment

### 1.1. Yocto Configuration
Yocto uses **meta-layers** to define the configuration for a system build. Within each meta-layer are recipes, classes and configuration files that support the primary python build tool, **bitbake**.

The meta-bbb layer generates some basic systems with packages that support C, C++, Qt5, Perl and Python development, the languages and tools we commonly use. Other languages are supported.

We use this layer as a template when starting new BeagleBone projects. And We create a new layer "meta-km-bbb" for **KM-BBB Expansion board.**


### 1.2. Version Information
- Yocto Version: Zeus 3.0.3
- Bitbake Version: 1.44
- u-boot version: 2019
- Kernel Version: 4.19.94

### 1.3. Ubuntu Setup
- Ubuntu version 18.04 supports.
- Multi core processor recommanded
- RAM size min. 4GB recommanded.
- Install Kernel Masters OS 2.0 from the below link:

 https://kernelmasters.org/blog/2020/05/17/download-install-kernel-masters-customized-linux/
 
The below packages installed in Ubuntu 18.04

         $ sudo apt install libncurses5-dev python python3-distutils texinfo gawk wget git-core diffstat unzip texinfo gcc-multilib build-essential chrpath socat cpio python3 python3-pip python3-pexpect xz-utils debianutils iputils-ping python3-git python3-jinja2 libegl1-mesa libsdl1.2-dev pylint3 xterm

For all versions of Ubuntu, you should change the default Ubuntu shell from dash to bash by running this command from a shell.

         $ sudo dpkg-reconfigure dash
 
 Choose **NO** to dash when prompted.
## 2. Download Zeus 3.0.3 yocto source code

 - Enter Home Directory

         $ cd ~

 - Clone poky-zeus-bbb repo

        ~$ git clone https://github.com/kernelmasters/poky-zeus-bbb.git

## 3. Initialize the build directory
 - Enter poky repo folder

       ~$ cd poky-zeus-bbb

 - Initialize the build directory

       ~/poky-zeus-bbb$ source oe-init-build-env

After Initalization of build directory, current working directory is build.

## 4. Customize the configuration files - Edit local config files
      BBB configuration files replace with default configuration files

      ~$ cp ~/poky-zeus-bbb/meta-bbb/conf/local.conf.sample ~/poky-zeus-bbb/build/conf/local.conf
      ~$ cp ~/poky-zeus-bbb/meta-bbb/conf/bblayers.conf.sample ~/poky-zeus-bbb/build/conf/bblayers.conf

### 4.1. Customize Variables

The variables you may want to customize are the following:

    TMPDIR
    DL_DIR
    SSTATE_DIR

The defaults for all of these work fine. Adjustments are optional.

#### 4.1.1. TMPDIR

This is where temporary build files and the final build binaries will end up. Expect to use at least 35GB. You probably want at least 50GB available.
The default location is in the build directory, in this example ~/bbb/build/tmp.
If you specify an alternate location as I do in the example conf file make sure the directory is writable by the user running the build.

#### 4.1.2. DL_DIR

This is where the downloaded source files will be stored. You can share this among configurations and build files so I created a general location for this outside the project directory. Make sure the build user has write permission to the directory you decide on.
The default location is in the build directory, ~/bbb/build/sources.

#### 4.1.3. SSTATE_DIR

This is another Yocto build directory that can get pretty big, greater then 5GB. I often put this somewhere else other then my home directory as well.
The default location is in the build directory, ~/bbb/build/sstate-cache.

### 4.2. ROOT PASSWORD

There is only one login user by default, root.

The default password is set to **km** by these two lines in the local.conf file

    INHERIT += "extrausers"
    EXTRA_USERS_PARAMS = "usermod -P km root; "

These two lines force a password change on first login

    INHERIT += "chageusers"
    CHAGE_USERS_PARAMS = "chage -d0 root; "

You can comment them out if you do not want that behavior.

## 5. Types of yocto images

You need to source the Yocto environment into your shell before you can use bitbake. The oe-init-build-env will not overwrite your customized conf files.

    ~$ source ~/poky-zeus-bbb/oe-init-build-env 

    ### Shell environment set up for builds. ###

    You can now run 'bitbake <target>'

    Common targets are:
          core-image-minimal
          core-image-sato
          meta-toolchain
          meta-ide-support

    You can also run generated qemu images with a command like 'runqemu qemux86'

    Other commonly useful commands are:
         - 'devtool' and 'recipetool' handle common recipe tasks
         - 'bitbake-layers' handles common layer tasks
        - 'oe-pkgdata-util' handles common target package tasks

    ~/bbb/build$

 I don’t use any of the Common targets, but instead use my own custom image recipes.

There are a few custom images available in the meta-bbb layer. The recipes for the images can be found in meta-bbb/images/

          core-image-minimal
          core-image-sato
          meta-toolchain
          meta-ide-support

You should add your own custom images to this same directory.

### 5.1. console-image

A basic console developer image. See the recipe meta-bbb/images/console-image.bb for specifics, but some of the installed programs are

    gcc/g++ and associated build tools
    git
    ssh/scp server and client
    python3 with a number of modules

The console-image has a line

    inherit core-image

which is poky-dunfell/meta/classes/core-image.bbclass and pulls in some required base packages. This is useful to know if you create your own image recipe.

### 5.2. qt5-image

This image includes the console-image and adds Qt5 runtime libraries.

### 5.3. Installer-image

This is a minimal image meant only to run from an SD card and whose only purpose is to perform an eMMC installation.

## 6. Build Console Image

To build the console-image run the following command

    ~/poky-zeus-bbb/build$ bitbake console-image

You may occasionally run into build errors related to packages that either failed to download or sometimes out of order builds. The easy solution is to clean the failed package and rerun the build again.

For instance if the build for zip failed for some reason, I would run this

~/bbb/build$ bitbake -c cleansstate zip
~/bbb/build$ bitbake zip

And then continue with the full build.

    ~/poky-zeus-bbb/build$ bitbake console-image

The cleansstate command (with two s’s) works for image recipes as well.

The image files won’t get deleted from the TMPDIR until the next time you build

## 7. Copying the binaries to an SD card

After the build completes, the bootloader, kernel and rootfs image files can be found in <TMPDIR>/deploy/images/beaglebone/.

### 7.1. Create SD card 2 Paritions

The meta-bbb/scripts directory has some helper scripts to format and copy the files to a microSD card.
mk2parts.sh

This script will partition an SD card with the minimal 2 partitions required for the boards.

Insert the microSD into your workstation and note where it shows up.

lsblk is convenient for finding the microSD card.

For example

    km@kernelmasters:~/bbb/meta-bbb$ lsblk
    NAME    MAJ:MIN RM   SIZE RO TYPE MOUNTPOINT
    sda       8:0    0 931.5G  0 disk
    |-sda1    8:1    0  93.1G  0 part /
    |-sda2    8:2    0  93.1G  0 part /home
    |-sda3    8:3    0  29.8G  0 part [SWAP]
    |-sda4    8:4    0     1K  0 part
    |-sda5    8:5    0   100G  0 part /oe5
    |-sda6    8:6    0   100G  0 part /oe6
    |-sda7    8:7    0   100G  0 part /oe7
    |-sda8    8:8    0   100G  0 part /oe8
    |-sda9    8:9    0   100G  0 part /oe9
    `-sda10   8:10   0 215.5G  0 part /oe10
    sdb       8:16   1   7.4G  0 disk
    |-sdb1    8:17   1    64M  0 part
    `-sdb2    8:18   1   7.3G  0 part

I would use sdb for the format and copy script parameters on this machine.

It doesn’t matter if some partitions from the SD card are mounted. The mk2parts.sh script will unmount them.

**BE CAREFUL with this script. It will format any disk on your workstation**

    ~$ cd ~/poky-zeus-bbb/meta-bbb/scripts
    ~/poky-zeus-bbb/meta-bbb/scripts$ sudo ./mk2parts.sh sdb

You only have to format the SD card once.

### 7.2. Copy MLO & u-boot.img in to SD Card first parition. 

**/media/card**

You will need to create a mount point on your workstation for the copy scripts to use.

    ~$ sudo mkdir /media/card

You only have to create this directory once.

**copy_boot.sh**

This script copies the bootloaders (MLO and u-boot) to the boot partition of the SD card.

The script also copies a uEnv.txt file to the boot partition if it finds one in either

    <TMPDIR>/deploy/images/beaglebone/

or in the local directory where the script is run from.

If you are just starting out, you might just want to do this

    ~/poky-zeus-bbb/meta-bbb/scripts$ cp uEnv.txt-example uEnv.txt

This copy_boot.sh script needs to know the TMPDIR to find the binaries. It looks for an environment variable called OETMP.

For instance, if I had this in the local.conf

    TMPDIR="../../build/tmp"


Then I would export this environment variable before running copy_boot.sh

    ~/poky-seus-bbb/meta-bbb/scripts$ export OETMP="../../build/tmp"

Then run the copy_boot.sh script passing the location of SD card

    ~$ sudo umount /dev/sdb1
    ~$ sudo umount /dev/sdb2
    ~/poky-zeus-bbb/meta-bbb/scripts$ ./copy_boot.sh sdb

This script should run very fast.

### 7.2. Copy Root file system along with Kerel Image in to SD Card Second parition. 

**copy_rootfs.sh**

This script copies the zImage Linux kernel, the device tree binaries and the rest of the operating system to the root file system partition of the SD card.

The script accepts an optional command line argument for the image type, for example console or qt5. The default is console if no argument is provided.

The script also accepts a hostname argument if you want the host name to be something other then the default beaglebone.

Here’s an example of how you’d run copy_rootfs.sh

    ~/poky-zeus-bbb/meta-bbb/scripts$ ./copy_rootfs.sh sdb console

or

    ~/poky-zeus-bbb/meta-bbb/scripts$ ./copy_rootfs.sh sdb qt5 bbb

The copy_rootfs.sh script will take longer to run and depends a lot on the quality of your SD card. With a good Class 10 card it should take less then 30 seconds.

The copy scripts will NOT unmount partitions automatically. If an SD card partition is already mounted, the script will complain and abort. This is for safety, mine mostly, since I run these scripts many times a day on different machines and the SD cards show up in different places.

Here’s a realistic example session where I want to copy already built images to a second SD card that I just inserted.

    ~$ sudo umount /dev/sdb1
    ~$ sudo umount /dev/sdb2
    ~$ export OETMP="../../build/tmp"
    ~$ cd ~/poky-zeus-bbb/meta-bbb/scripts
    ~/poky-zeus-bbb/meta-bbb/scripts$ ./copy_boot.sh sdb
    ~/poky-zeus-bbb/meta-bbb/scripts$ ./copy_rootfs.sh sdb console bbb2

Both copy_boot.sh and copy_rootfs.sh are simple scripts meant to be modified for custom use.
### 7.3. Summary

    cd /home/km/poky-zeus-bbb/meta-bbb/scripts
    sudo umount /dev/sdb1
    sudo ./mk2parts.sh sdb
    sudo mkdir /media/card
    cp uEnv.txt-example uEnv.txt
    export OETMP="../../build/tmp"
    sudo umount /dev/sdb1
    sudo umount /dev/sdb2
    ./copy_boot.sh sdb
    sudo umount /dev/sdb1
    ./copy_rootfs.sh sdb console

## 8. Booting from the SD card

The default behavior of the beaglebone is to boot from the eMMC first if it finds a bootloader there.

Holding the S2 switch down when the bootloader starts will cause the BBB to try booting from the SD card first. The S2 switch is above the SD card holder.

If you are using a cape, the S2 switch is usually inaccessible or at least awkward to reach. From the back of the board a temporary jump of P8.43 to ground when the bootloader starts will do the same thing as holding the S2 switch.


## 9.  ERROR 1

 checking for python3... python3
 
 checking version of python3... 3.6.9, ok
 
 configure: error:
   *** These critical programs are missing or too old: GNU ld
   
   *** Check the INSTALL file for required versions.

**Solution:** 
Enable bash shell using the below command

    $ sudo dpkg-reconfigure dash
