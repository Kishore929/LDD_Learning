### How to install yocto images
 
#### 1. Format SD card and create single partition

	$ cd /home/km/poky-zeus-bbb/meta-bbb/scripts
	$ sudo ./mk1parts.sh --mmc /dev/sdx

#### 2. Copy console image in to sd card

	$ cd /home/km/poky-zeus-bbb/meta-bbb/scripts
	$ sudo ./km-bbb-yocto-install.sh <--mmc /dev/sdx> <--image console>

