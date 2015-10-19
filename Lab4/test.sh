sudo rm -f /dev/calc*
sudo rmmod calc
make
sudo insmod ./calc.ko

sudo mknod /dev/calc0 c 200 0
sudo mknod /dev/calc1 c 200 1
sudo mknod /dev/calc2 c 200 2
sudo mknod /dev/calc3 c 200 3

sudo chmod a+w+r /dev/calc*

sudo echo "4 + 5 ="
sudo echo "4" > /dev/calc0
sudo echo "5" > /dev/calc1
sudo echo "+" > /dev/calc2
cat /dev/calc3

sudo echo "27 - 16 ="
sudo echo "27" > /dev/calc0
sudo echo "16" > /dev/calc1
sudo echo "-" > /dev/calc2
cat /dev/calc3

sudo echo "5 * 5 ="
sudo echo "5" > /dev/calc0
sudo echo "5" > /dev/calc1
sudo echo "*" > /dev/calc2
cat /dev/calc3

sudo echo "27 / 3 ="
sudo echo "27" > /dev/calc0
sudo echo "3" > /dev/calc1
sudo echo "/" > /dev/calc2
cat /dev/calc3

sudo echo "27 / 0 ="
sudo echo "27" > /dev/calc0
sudo echo "0" > /dev/calc1
sudo echo "/" > /dev/calc2
cat /dev/calc3

sudo echo "27 d 16 ="
sudo echo "27" > /dev/calc0
sudo echo "16" > /dev/calc1
sudo echo "d" > /dev/calc2
cat /dev/calc3
