#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"

for tool in clang pacman curl bsdtar zstd depmod grub-mkrescue grub-mkstandalone cpio gzip parted mkfs.fat mcopy dd ldd; do
  command -v "$tool" >/dev/null || { echo "Falta a ferramenta: $tool" >&2; exit 1; }
done

KVER="${UNIOS_KERNEL_VERSION:-$(uname -r)}"
KERNEL="/usr/lib/modules/$KVER/vmlinuz"
if [[ ! -r "$KERNEL" ]]; then
  KERNEL=/boot/vmlinuz-linux-cachyos
fi
[[ -r "$KERNEL" ]] || { echo "Kernel CachyOS $KVER nao encontrado." >&2; exit 1; }
[[ -d "/usr/lib/modules/$KVER" ]] || { echo "Modulos do kernel $KVER nao encontrados." >&2; exit 1; }

BUILD="$PWD/build/unios-linux"
ROOT="$BUILD/root"
PKGCACHE="$PWD/build/stage3-pkgcache"
mkdir -p "$PKGCACHE"
rm -rf "$ROOT" "$BUILD/iso-root"
mkdir -p "$ROOT"/{bin,sbin,etc,dev,proc,sys,run,tmp,root,mnt/UniOS,usr/bin,usr/lib,usr/lib64,usr/share/udhcpc,lib/modules/$KVER} "$BUILD/iso-root/boot/grub"
chmod 1777 "$ROOT/tmp"

BUSYBOX_PKG="$PKGCACHE/busybox.pkg.tar.zst"
if [[ ! -s "$BUSYBOX_PKG" ]]; then
  BUSYBOX_URL="$(pacman -Sp busybox | head -n1)"
  curl -L --fail --output "$BUSYBOX_PKG" "$BUSYBOX_URL"
fi
bsdtar -xOf "$BUSYBOX_PKG" usr/bin/busybox > "$ROOT/bin/busybox"
chmod 755 "$ROOT/bin/busybox"
while IFS= read -r applet; do
  [[ "$applet" == busybox ]] && continue
  ln -sfn busybox "$ROOT/bin/$applet"
done < <("$ROOT/bin/busybox" --list)
ln -sfn ../bin/busybox "$ROOT/sbin/modprobe"
ln -sfn ../bin/busybox "$ROOT/sbin/insmod"

cp -L "$KERNEL" "$BUILD/vmlinuz-cachyos"
cp /usr/bin/wget "$ROOT/usr/bin/wget"
chmod 755 "$ROOT/usr/bin/wget"
while IFS= read -r library; do
  [[ "$library" = /* ]] || continue
  install -D -m 755 "$library" "$ROOT$library"
done < <(ldd /usr/bin/wget | awk '{for (i=1; i<=NF; i++) if ($i ~ /^\//) {print $i; break}}' | sort -u)

for library in /usr/lib/libnss_dns.so.2 /usr/lib/libnss_files.so.2; do
  [[ ! -r "$library" ]] && continue
  install -D -m 755 "$library" "$ROOT$library"
  while IFS= read -r dependency; do
    [[ "$dependency" = /* ]] || continue
    install -D -m 755 "$dependency" "$ROOT$dependency"
  done < <(ldd "$library" | awk '{for (i=1; i<=NF; i++) if ($i ~ /^\//) {print $i; break}}' | sort -u)
done
if [[ -r /etc/ssl/certs/ca-certificates.crt ]]; then
  install -D -m 644 /etc/ssl/certs/ca-certificates.crt "$ROOT/etc/ssl/certs/ca-certificates.crt"
elif [[ -r /etc/ssl/certs/ca-bundle.crt ]]; then
  install -D -m 644 /etc/ssl/certs/ca-bundle.crt "$ROOT/etc/ssl/certs/ca-certificates.crt"
fi
printf 'passwd: files\ngroup: files\nshadow: files\nhosts: files dns\n' > "$ROOT/etc/nsswitch.conf"
printf '127.0.0.1 localhost\n' > "$ROOT/etc/hosts"
printf 'UniOS\n' > "$ROOT/etc/hostname"
printf 'nameserver 1.1.1.1\n' > "$ROOT/etc/resolv.conf"
cp linux-live/init "$ROOT/init"
cp linux-live/udhcpc.script "$ROOT/usr/share/udhcpc/default.script"
cp linux-live/profile "$ROOT/etc/profile"
chmod 755 "$ROOT/init" "$ROOT/usr/share/udhcpc/default.script"
"$ROOT/bin/busybox" ash -n "$ROOT/init"

# Include host-controller drivers as well as USB storage and SATA drivers.
# USB storage alone does not guarantee that the machine's xHCI/EHCI controller
# is present in this initramfs.
declare -A copied_modules=()
for metadata in modules.order modules.builtin modules.builtin.modinfo modules.builtin.ranges; do
  [[ ! -r "/usr/lib/modules/$KVER/$metadata" ]] || cp "/usr/lib/modules/$KVER/$metadata" "$ROOT/lib/modules/$KVER/"
done
for module in xhci_pci xhci_hcd ehci_pci ehci_hcd uhci_hcd ahci sd_mod scsi_mod rndis_host e1000 8139too usb_storage uas vfat ata_piix; do
  while read -r action path; do
    [[ "$action" == insmod && -r "$path" ]] || continue
    case "$path" in
      /usr/lib/modules/"$KVER"/*) rel="${path#/usr/lib/modules/$KVER/}" ;;
      /lib/modules/"$KVER"/*) rel="${path#/lib/modules/$KVER/}" ;;
      *) continue ;;
    esac
    rel="${rel%.zst}"
    [[ -n "${copied_modules[$rel]:-}" ]] && continue
    copied_modules[$rel]=1
    mkdir -p "$ROOT/lib/modules/$KVER/$(dirname "$rel")"
    if [[ "$path" == *.zst ]]; then
      zstd -q -d -c "$path" > "$ROOT/lib/modules/$KVER/$rel"
    else
      cp "$path" "$ROOT/lib/modules/$KVER/$rel"
    fi
  done < <(modprobe --show-depends -S "$KVER" "$module" 2>/dev/null || true)
done
depmod -b "$ROOT" "$KVER" >/dev/null

KERNEL_NAME="vmlinuz-cachyos-$KVER"
cp "$BUILD/vmlinuz-cachyos" "$BUILD/iso-root/boot/$KERNEL_NAME"

(
  cd "$ROOT"
  find . -print0 | sort -z | cpio --null -o -H newc --owner=0:0 2>/dev/null | gzip -1 > "$BUILD/iso-root/boot/unios-initramfs.cpio.gz"
)
gzip -t "$BUILD/iso-root/boot/unios-initramfs.cpio.gz"
cpio -it < <(gzip -dc "$BUILD/iso-root/boot/unios-initramfs.cpio.gz") | grep -Eq '^(\./)?init
cp linux-live/grub.cfg "$BUILD/iso-root/boot/grub/grub.cfg"
sed -i "s/@KERNEL@/$KERNEL_NAME/g" "$BUILD/iso-root/boot/grub/grub.cfg"
grep -q "initrd /boot/unios-initramfs.cpio.gz" "$BUILD/iso-root/boot/grub/grub.cfg"
grub-mkrescue -o "$PWD/build/unios-linux.iso" "$BUILD/iso-root" >/dev/null 2>&1

# Standalone UEFI loader and a GPT/FAT32 USB image, built entirely in the project.
# Remove previous staging first so an older kernel/initramfs cannot be carried over.
rm -rf "$BUILD/usb" "$BUILD/esp-part.img"
mkdir -p "$BUILD/usb/EFI/BOOT" "$BUILD/usb/boot/grub"
cp "$BUILD/iso-root/boot/$KERNEL_NAME" "$BUILD/usb/boot/"
cp "$BUILD/iso-root/boot/unios-initramfs.cpio.gz" "$BUILD/usb/boot/"
cp "$BUILD/iso-root/boot/grub/grub.cfg" "$BUILD/usb/boot/grub/"
grub-mkstandalone -O x86_64-efi -o "$BUILD/usb/EFI/BOOT/BOOTX64.EFI" --modules="part_gpt fat search search_fs_file linux normal configfile all_video gfxterm terminal serial" "boot/grub/grub.cfg=$BUILD/usb/boot/grub/grub.cfg" >/dev/null 2>&1

truncate -s 256M "$PWD/build/unios-linux.img"
parted -s "$PWD/build/unios-linux.img" mklabel gpt mkpart primary fat32 1MiB 255MiB set 1 esp on
truncate -s 254M "$BUILD/esp-part.img"
mkfs.fat -F 32 -n UNIOS "$BUILD/esp-part.img" >/dev/null
mcopy -i "$BUILD/esp-part.img" -s "$BUILD/usb/EFI" ::/
mcopy -i "$BUILD/esp-part.img" -s "$BUILD/usb/boot" ::/
dd if="$BUILD/esp-part.img" of="$PWD/build/unios-linux.img" bs=512 seek=2048 conv=notrunc status=none

printf 'UniOS Linux ISO: %s/build/unios-linux.iso\nUniOS Linux USB IMG: %s/build/unios-linux.img\nKernel: %s\n' "$PWD" "$PWD" "$KVER"

cp linux-live/grub.cfg "$BUILD/iso-root/boot/grub/grub.cfg"
sed -i "s/@KERNEL@/$KERNEL_NAME/g" "$BUILD/iso-root/boot/grub/grub.cfg"
grep -q "initrd /boot/unios-initramfs.cpio.gz" "$BUILD/iso-root/boot/grub/grub.cfg"
grub-mkrescue -o "$PWD/build/unios-linux.iso" "$BUILD/iso-root" >/dev/null 2>&1

# Standalone UEFI loader and a GPT/FAT32 USB image, built entirely in the project.
# Remove previous staging first so an older kernel/initramfs cannot be carried over.
rm -rf "$BUILD/usb" "$BUILD/esp-part.img"
mkdir -p "$BUILD/usb/EFI/BOOT" "$BUILD/usb/boot/grub"
cp "$BUILD/iso-root/boot/$KERNEL_NAME" "$BUILD/usb/boot/"
cp "$BUILD/iso-root/boot/unios-initramfs.cpio.gz" "$BUILD/usb/boot/"
cp "$BUILD/iso-root/boot/grub/grub.cfg" "$BUILD/usb/boot/grub/"
grub-mkstandalone -O x86_64-efi -o "$BUILD/usb/EFI/BOOT/BOOTX64.EFI" --modules="part_gpt fat search search_fs_file linux normal configfile all_video gfxterm terminal serial" "boot/grub/grub.cfg=$BUILD/usb/boot/grub/grub.cfg" >/dev/null 2>&1

truncate -s 256M "$PWD/build/unios-linux.img"
parted -s "$PWD/build/unios-linux.img" mklabel gpt mkpart primary fat32 1MiB 255MiB set 1 esp on
truncate -s 254M "$BUILD/esp-part.img"
mkfs.fat -F 32 -n UNIOS "$BUILD/esp-part.img" >/dev/null
mcopy -i "$BUILD/esp-part.img" -s "$BUILD/usb/EFI" ::/
mcopy -i "$BUILD/esp-part.img" -s "$BUILD/usb/boot" ::/
dd if="$BUILD/esp-part.img" of="$PWD/build/unios-linux.img" bs=512 seek=2048 conv=notrunc status=none

printf 'UniOS Linux ISO: %s/build/unios-linux.iso\nUniOS Linux USB IMG: %s/build/unios-linux.img\nKernel: %s\n' "$PWD" "$PWD" "$KVER"
