sudo rmmod calc
make
sudo insmod ./calc.ko

sudo mknod /dev/calc0 c 300 0
sudo mknod /dev/calc1 c 300 1

sudo chmod a+r+w /dev/calc*

sudo echo "5" > /dev/calc0
cat /dev/calc1


