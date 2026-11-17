#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"
mkdir -p build/esp/EFI/BOOT
clang --target=x86_64-pc-win32-coff -std=c11 -O2 -ffreestanding -fshort-wchar -fno-stack-protector -fno-builtin -mno-red-zone -c src/unios.c -o build/unios.obj
lld-link /subsystem:efi_application /entry:efi_main /nodefaultlib /machine:x64 /out:build/esp/EFI/BOOT/BOOTX64.EFI build/unios.obj
rm -f build/unios.img
truncate -s 256M build/unios.img
parted -s build/unios.img mklabel gpt \
  mkpart primary fat32 1MiB 65MiB set 1 esp on \
  mkpart primary fat32 65MiB 100% set 2 msftdata on
truncate -s 64M build/esp-part.img
mkfs.fat -F 32 -n UNIBOOT build/esp-part.img >/dev/null
mcopy -i build/esp-part.img -s build/esp/EFI ::/EFI
truncate -s $(((256 * 2048 - 33 - 133120) * 512)) build/data-part.img
mkfs.fat -F 32 -n UNIOS build/data-part.img >/dev/null
mmd -i build/data-part.img ::/UNIOS
printf 'UniOS log volume\n' > build/UNIOS.TAG
mcopy -i build/data-part.img build/UNIOS.TAG ::/UNIOS.TAG
dd if=build/esp-part.img of=build/unios.img bs=512 seek=2048 conv=notrunc status=none
dd if=build/data-part.img of=build/unios.img bs=512 seek=133120 conv=notrunc status=none
printf 'UniOS pronto. Grave diretamente esta imagem USB: %s/build/unios.img\n' "$PWD"
