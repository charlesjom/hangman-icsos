#!/bin/bash
sudo make install
qemu-system-x86_64 -fda ics-os-floppy.img
