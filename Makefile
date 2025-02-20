.PHONY: all bootloader kernel cleanup test_build tool_wgpt

gcc:=gcc
cc :=g++
ld :=ld
cls:=cls
rm :=del

wgpt		  :=tools/wgpt.exe


wgpt_src      :=tools/wgpt/wgpt.c
wgpt_cflags   :=-O3 -s

test_vm		   :=qemu-system-x86_64
test_vm_flags  :=-drive format=raw,file=moss.img -bios tools/bios64.bin -m 256M -vga std -display sdl -name MOSS -machine q35 -usb -device usb-mouse -rtc base=localtime -net none

boot_src	   :=$(wildcard boot/*.cpp) printf/printf.cpp
boot_inc       :=-Iarch -Iprintf -Iboot
boot_cflags    :=-w -O3 -s -mno-red-zone -ffreestanding -fno-stack-protector -fno-exceptions -fno-rtti -std=c++20
boot_ldflags   :=-nostdlib -Wl,--subsystem,10 -e emain

kernel_src     :=$(wildcard kernel/*.cpp)
kernel_inc	   :=-Iarch -Iprintf
kernel_cflags  :=-w -O3 -s -mno-red-zone -ffreestanding -nostdlib -fno-stack-protector -fno-exceptions -fno-rtti -fPIE -std=c++20
kernel_ldflags :=-e kmain -nostdlib -pie

kernel_targets :=$(patsubst %.cpp,%.o,$(kernel_src))

all: bootloader kernel build_disk cleanup test_build

bootloader:
	$(cc) $(boot_src) -o BOOTX64.EFI $(boot_inc) $(boot_cflags) $(boot_ldflags)

kernel:
	$(cc) $(kernel_src) -c $(kernel_cflags) $(kernel_inc)
	$(ld) $(kernel_ldflags) -Tkernel/kernel.ld --image-base=0 -o kernel.obj $(notdir $(kernel_targets))
	objcopy -O binary kernel.obj kernel.bin

build_disk:
	$(wgpt) -i moss.img -ae /EFI/BOOT/ kernel.bin


cleanup:
	del BOOTX64.EFI DSKIMG.INF FILE.TXT kernel.obj kernel.bin  $(notdir $(kernel_targets))

test_build:
	$(test_vm) $(test_vm_flags)

tool_wgpt:
	$(gcc) $(wgpt_src) -o tools/wgpt.exe $(wgpt_cflags)