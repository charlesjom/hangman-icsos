# modified Makefile
install:
	mount ics-os-floppy.img mnt -tmsdos -oloop
	cp apps/* mnt/apps/
	umount mnt
	chmod 666 ics-os-floppy.img