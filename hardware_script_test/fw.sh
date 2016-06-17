#!/bin/sh
echo 11 > /sys/class/gpio/export
echo  9 > /sys/class/gpio/export
echo 12 > /sys/class/gpio/export
echo 22 > /sys/class/gpio/export
echo 27 > /sys/class/gpio/export
echo 18 > /sys/class/gpio/export

echo out > /sys/class/gpio/gpio11/direction
echo out > /sys/class/gpio/gpio9/direction
echo out > /sys/class/gpio/gpio12/direction
echo out > /sys/class/gpio/gpio22/direction
echo out > /sys/class/gpio/gpio27/direction
echo out > /sys/class/gpio/gpio18/direction

echo 1 > /sys/class/gpio/gpio11/value
echo 0 > /sys/class/gpio/gpio9/value
echo 1 > /sys/class/gpio/gpio12/value
echo 1 > /sys/class/gpio/gpio22/value
echo 0 > /sys/class/gpio/gpio27/value 
echo 1 > /sys/class/gpio/gpio18/value 
