#!/bin/sh

# clear the message queue, then
# insert simple.ko into kernel and remove it again, then
# display the message as a result of doing so

sudo -p "osc"
sudo dmesg -c
clear

printf "beginning script...\n\n"
sudo insmod simple.ko
sudo rmmod simple
sudo dmesg
printf  "\n...end of the script\n\n"