DESCRIPTION = "Linux kernel for Dreambox DM500PLUS"
LICENSE = "GPL"
PV = "2.6.12"
PR = "r2"

# -rX is the patch revision - it's not related to this package's PR
SRC_URI = "ftp://ftp.kernel.org/pub/linux/kernel/v2.6/linux-2.6.12.tar.bz2 \
	http://sources.dreamboxupdate.com/download/kernel-patches/linux-2.6.12-dream-ppc-r5.patch.bz2;patch=1;pnum=1"

S = "${WORKDIR}/linux-2.6.12"

inherit kernel

FILES_kernel-image = "/boot/zImage.elf /boot/autoexec.bat"

export OS = "Linux"
ARCH = "ppc"
KERNEL_IMAGETYPE = "zImage"
KERNEL_OUTPUT = "arch/ppc/boot/images/zImage.elf"

do_configure_prepend() {
	oe_machinstall -m 0644 ${S}/arch/ppc/configs/dm500plus_defconfig ${S}/.config || die "no default configuration for ${MACHINE} available."
	oe_runmake oldconfig
}

kernel_do_stage_append() {
	mkdir -p ${STAGING_KERNEL_DIR}/include/asm-m68k
	cp -fR ${S}/include/asm-m68k/* ${STAGING_KERNEL_DIR}/include/asm-m68k/
	mkdir -p ${STAGING_KERNEL_DIR}/include/platforms/4xx
	cp -fR ${S}/arch/ppc/platforms/* ${STAGING_KERNEL_DIR}/include/platforms/
}

do_install_append () {
	install -d ${D}/boot
	install -m 0755 arch/ppc/boot/images/zImage.elf ${D}/boot/zImage.elf
	echo "/flash/bootlogo.elf" > ${D}/boot/autoexec.bat
	echo "/flash/zImage.elf" >> ${D}/boot/autoexec.bat
}

pkg_preinst_kernel-image () {
	[ -d /proc/stb ] && mount -o rw,remount /boot
	true
}

pkg_postinst_kernel-image () {
	[ -d /proc/stb ] && mount -o ro,remount /boot
	true
}

pkg_prerm_kernel-image () {
	[ -d /proc/stb ] && mount -o rw,remount /boot
	true
}

pkg_postrm_kernel-image () {
	[ -d /proc/stb ] && mount -o ro,remount /boot
	true
}
