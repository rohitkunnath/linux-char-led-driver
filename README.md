# Linux Character Device Driver – Virtual LED

A simple Linux **character device driver** that simulates an LED.  
It demonstrates how to implement file operations (`open`, `read`, `write`, `release`) in kernel space and communicate with user-space through `/dev`.

---

## 🧠 What This Project Demonstrates
- Linux kernel module programming  
- Character device registration using `misc_register()`  
- Kernel ↔ User space communication via `read`/`write`  
- Basic use of `printk`, `dmesg`, and kernel logs for debugging  

---

## 🛠️ Requirements
- Ubuntu / Debian (or any Linux with build-essential)
- Kernel headers (`sudo apt install build-essential linux-headers-$(uname -r)`)
- GCC, Make

---

## 🧱 Folder Structure
linux-char-led-driver/
├── src/
│ ├── led_driver.c
│ └── test_led_user.c
├── Makefile
└── README.md

yaml
Copy code

---

## ⚙️ Build Instructions

make
This compiles:

led_driver.ko → kernel module

test_led_user → user-space application

▶️ Run & Test
Insert the module
```bash
sudo insmod src/led_driver.ko
dmesg | tail -n 10
```
Check device
```bash
ls /dev/virt_led
```
Read LED state
```bash
./src/test_led_user
```
Toggle LED
```bash
./src/test_led_user 1
./src/test_led_user 0
```
View kernel logs
```bash
dmesg | tail -n 10
```
Remove driver
```bash
sudo rmmod led_driver
```
