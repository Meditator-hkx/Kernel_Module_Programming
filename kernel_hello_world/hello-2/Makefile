obj-m += hello-2.o

all:
	make -C /lib/modules/`uname -r`/build/ M=$(PWD) modules

clean:
	make -C /lib/modules/`uname -r`/build/ M=$(PWD) clean
