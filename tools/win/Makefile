.PHONY: all build_wgpt build_disk qemu_test bootloader kernel
.NOTPARALLEL: all


gcc                 :=gcc
cc                  :=g++
objcopy             :=objcopy
ld                  :=ld
cls                 :=cls
rm                  :=del

wgpt                :=tools/wgpt.exe
wgpt_src            :=tools/wgpt/wgpt.c
wgpt_cflags         :=-O3 -s

qemu                :=qemu-system-x86_64
qemu_flags          :=-bios tools/bios64.bin -m 512M -vga std -display sdl -name MOSS -machine q35 -usb -device usb-mouse -rtc base=localtime -net none

boot_src            :=$(wildcard boot/*.cpp) $(wildcard std/*.cpp) printf/printf.cpp
boot_inc            :=-Istd -Iboot -Iprintf
boot_cflags	        :=-w -O3 -s -mno-red-zone -ffreestanding -nostdlib -fno-stack-protector -fno-exceptions -fno-rtti -std=c++20
boot_ldflags        :=-nostdlib -Wl,--subsystem,10 -e emain

boot_targets        :=$(patsubst %.cpp,%.boot,$(boot_src))
boot_o_files        :=$(notdir $(patsubst %.cpp,%.o,$(boot_src)))

kernel_src          :=$(wildcard kernel/*.cpp) printf/printf.cpp
kernel_inc          :=-Iinc -Iprintf
kernel_cflags       :=-w -O3 -s -mno-red-zone -ffreestanding -nostdlib -fno-stack-protector -fno-exceptions -fPIE -pie -fno-rtti -std=c++20
kernel_ldflags      :=-e kmain -pie -nostdlib

kernel_targets      :=$(patsubst %.cpp,%.kernel,$(kernel_src))
kernel_o_files      :=$(notdir $(patsubst %.cpp,%.o,$(kernel_src)))

all: bootloader kernel build_disk qemu_test

bootloader: $(boot_targets)
	$(cc) $(boot_o_files) -o BOOTX64.EFI $(boot_inc) $(boot_cflags) $(boot_ldflags)
	$(rm) $(boot_o_files)

kernel: $(kernel_targets)
	$(ld) $(kernel_ldflags) --gc-sections -Tkernel/kernel.ld --image-base=0 -o kernel.obj $(kernel_o_files)
	$(objcopy) --strip-unneeded -O binary kernel.obj kernel.bin
	$(rm) $(kernel_o_files) kernel.obj


build_disk:
	$(wgpt) -i moss.img -ae /EFI/BOOT/ kernel.bin 
	$(rm) BOOTX64.EFI FILE.TXT kernel.bin


qemu_test:
	$(qemu) -drive format=raw,file=moss.img $(qemu_flags)
	$(cls)


build_wgpt:
	$(gcc) -o $(wgpt) $(wgpt_src) $(wgpt_cflags)


%.boot : %.cpp
	$(cc) $*.cpp -o $(notdir $*.o) -c $(boot_inc) $(boot_cflags)

%.kernel : %.cpp
	$(cc) $*.cpp -o $(notdir $*.o) -c $(kernel_inc) $(kernel_cflags)