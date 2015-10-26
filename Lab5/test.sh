sudo rmmod timer
make
sudo insmod ./timer.ko
sudo echo "5" > /sys/hello/HelloWorld
sudo echo "0" > /sys/hello/HelloWorld
sudo rmmod timer
dmesg > info.txt
