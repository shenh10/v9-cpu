#!/bin/sh
rm -f xc xem emhello funcall os0 os1 os2 os3 lab1 lab2
gcc -o xc -O3 -m32 -Ilinux -Iroot/lib root/bin/c.c
gcc -o xem -O3 -m32 -Ilinux -Iroot/lib root/bin/em.c -lm
./xc -o lab1 -Iroot/lib root/usr/os/lab1.c
./xc -o lab2 -Iroot/lib root/usr/os/lab2.c
./xem lab1
./xem lab2
