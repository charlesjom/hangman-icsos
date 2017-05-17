#!/bin/bash
cd contrib
cd hangman
make clean
make install
cd ../..
sudo make install
qemu-system-x86_64 -fda ics-os-floppy.img
