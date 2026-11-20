#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"
mkdir -p build/stage3-root/boot/grub build/stage3-root/EFI/BOOT
clang -target x86_64-unknown-none-elf -ffreestanding -fno-stack-protector -fno-pic -fno-pie -mno-red-zone -mno-sse -mno-mmx -mcmodel=small -O2 -c kernel/entry.S -o build/stage3-entry.o
clang -target x86_64-unknown-none-elf -ffreestanding -fno-stack-protector -fno-pic -fno-pie -mno-red-zone -mno-sse -mno-mmx -mcmodel=small -O2 -c kernel/kernel.c -o build/stage3-kernel.o
ld.lld -nostdlib -static -z max-page-size=0x1000 -T kernel/linker.ld -o build/unios-kernel.elf build/stage3-entry.o build/stage3-kernel.o
grub-file --is-x86-multiboot2 build/unios-kernel.elf
cp build/unios-kernel.elf build/stage3-root/boot/unios-kernel.elf
cat > build/stage3-root/boot/grub/grub.cfg <<'EOF'
set timeout=3
set default=0
set gfxmode=800x600x32
set gfxpayload=keep

menuentry "UniOS Stage 3 - kernel x86_64" {
    multiboot2 /boot/unios-kernel.elf
    boot
}

menuentry "UniOS etapa 2 - shell UEFI" {
    chainloader /EFI/BOOT/BOOTX64.EFI
}
EOF
clang --target=x86_64-pc-win32-coff -std=c11 -O2 -ffreestanding -fshort-wchar -fno-stack-protector -fno-builtin -mno-red-zone -c src/unios.c -o build/stage3-efi.obj
lld-link /subsystem:efi_application /entry:efi_main /nodefaultlib /machine:x64 /out:build/stage3-root/EFI/BOOT/BOOTX64.EFI build/stage3-efi.obj
grub-mkrescue -o build/unios-stage3.iso build/stage3-root >/dev/null 2>&1
printf 'UniOS Stage 3 ISO: %s/build/unios-stage3.iso\nKernel ELF: %s/build/unios-kernel.elf\n' "$PWD" "$PWD"
