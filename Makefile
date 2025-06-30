.PHONY: comp_shroom comp_kernel build_disk cleanup test
.NOTPARALLEL: all

rm:=rm -rf

kernel_cc:=g++
kernel_ld:=ld

kernel_cflags:=-O3 -s -e kmain -nostdlib -ffreestanding -mno-red-zone -fno-stack-protector
kernel_ldflags:=-Tmoss/kernel/kernel.ld -e kmain -nostdlib
kernel_includes:=-Imoss/arch -Imoss/kernel/inc

kernel_src:=$(wildcard moss/kernel/*.cpp) $(wildcard moss/kernel/*/*.cpp)
kernel_targets:=$(patsubst %.cpp,%.o,$(kernel_src))
kernel_dtargets:=$(patsubst %.cpp,%.kernel,$(kernel_src))
kernel_out:=kernel.elf

shroom_cc:=x86_64-w64-mingw32-g++
shroom_gcc:=x86_64-w64-mingw32-gcc

shroom_cflags:=-O3 -s -mno-red-zone -nostdlib -ffreestanding -fno-stack-protector -Wl,--subsystem,10
shroom_ldflags:=-e efi_main -nostdlib
shroom_includes:= -Imoss/shroom/inc -Imoss/shroom/inc/printf -Imoss/shroom/inc/efi -Imoss/arch

shroom_src:=$(wildcard moss/shroom/src/*.cpp) 
cshroom_src:=$(wildcard moss/shroom/src/*/*.c)

shroom_targets:=$(patsubst %.cpp,%.o,$(shroom_src))
cshroom_targets:=$(patsubst %.c,%.o,$(cshroom_src))

shroom_dtargets:=$(patsubst %.cpp,%.shroom,$(shroom_src))
cshroom_dtargets:=$(patsubst %.c,%.cshroom,$(cshroom_src))

shroom_out:=BOOTX64.EFI

image_name:=moss.hdd


qemu:=qemu-system-x86_64
qemu_bios:=-bios /usr/share/ovmf/x64/OVMF.4m.fd
qemu_image:= -drive file=$(image_name),format=raw,if=ide
qemu_flags:=-m 512M -M q35 -display gtk,zoom-to-fit=off



all: comp_shroom comp_kernel build_disk cleanup test

cleanup:
	$(rm) $(kernel_out) $(shroom_out)

#disk building shit

build_disk:
	dd if=/dev/zero bs=1M count=0 seek=64 of=$(image_name).temp
	sgdisk $(image_name).temp -n 1:2048 -t 1:ef00 -m 1
	mformat -i $(image_name).temp@@1M
	mmd -i $(image_name).temp@@1M ::/EFI ::/EFI/BOOT
	mcopy -i $(image_name).temp@@1M BOOTX64.EFI ::/EFI/BOOT
	mcopy -i $(image_name).temp@@1M kernel.elf ::/EFI/BOOT
	cp $(image_name).temp $(image_name)
	$(rm) $(image_name).temp

#qemu test bench


test:
	$(qemu) $(qemu_flags) $(qemu_bios) $(qemu_image)


# compile crap

comp_kernel: $(kernel_dtargets)
	$(kernel_ld) $(notdir $(kernel_targets)) -o $(kernel_out) $(kernel_ldflags)
	$(rm) $(notdir $(kernel_targets))

comp_shroom: $(shroom_dtargets) $(cshroom_dtargets)
	$(shroom_cc) $(notdir $(shroom_targets) $(cshroom_targets)) -o $(shroom_out) $(shroom_cflags) $(shroom_includes) $(shroom_ldflags)
	$(rm) $(notdir $(shroom_targets) $(cshroom_targets))


%.kernel : %.cpp
	$(kernel_cc) $*.cpp -o $(notdir $*.o) -c $(kernel_cflags) $(kernel_includes) $(kernel_ldflags)

%.shroom : %.cpp
	$(shroom_cc) $*.cpp -o $(notdir $*.o) -c $(shroom_cflags) $(shroom_includes)

%.cshroom : %.c
	$(shroom_gcc) $*.c -o $(notdir $*.o) -c $(shroom_cflags) $(shroom_includes)
