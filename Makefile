obj-m := led_driver.o
KDIR ?= /lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(KDIR) M=$(PWD)/src modules
	gcc -o src/test_led_user src/test_led_user.c

clean:
	$(MAKE) -C $(KDIR) M=$(PWD)/src clean
	rm -f src/test_led_user
