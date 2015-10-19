sudo rmmod calc
make
sudo insmod ./calc.ko

sudo mknod /dev/calc0 c 300 0
sudo mknod /dev/calc1 c 300 1
sudo mknod /dev/calc2 c 300 2
sudo mknod /dev/calc3 c 300 3

sudo chmod a+r+w /dev/calc*

sudo echo "5" > /dev/calc0
sudo echo "6" > /dev/calc1
sudo echo "+" > /dev/calc2
cat /dev/calc3


