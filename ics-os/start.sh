#!/bin/bash
cd contrib
cd hangman
make
make install
make clean
cd ../..
sudo make install
qemu-system-x86_64 -fda ics-os-floppy.img
