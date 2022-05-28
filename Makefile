# Makefile for top level of zCore

ARCH ?= x86_64

.PHONY: help setup update rootfs libc-test other-test image check doc clean

# print top level help
help:
	cargo xtask help

# setup git lfs and git submodules
setup:
	cargo setup

# update toolchain and dependencies
update:
	cargo update-all

# put rootfs for linux mode
rootfs:
	cargo rootfs --arch $(ARCH)

# put libc tests into rootfs
libc-test:
	cargo libc-test --arch $(ARCH)

# put other tests into rootfs
other-test:
	cargo other-test --arch $(ARCH)

# build image from rootfs
image:
	cargo image --arch $(ARCH)

# check code style
check:
	cargo check-style

# ===================================================

# NOT ON MASTER!

RISCV64_ROOTFS_TAR := prebuild.tar.xz
RISCV64_ROOTFS_URL := https://github.com/rcore-os/libc-test-prebuilt/releases/download/0.1/$(RISCV64_ROOTFS_TAR)

prebuilt/linux/riscv64/$(RISCV64_ROOTFS_TAR):
	@wget $(RISCV64_ROOTFS_URL) -O $@

riscv-rootfs:prebuilt/linux/riscv64/$(RISCV64_ROOTFS_TAR)
	@rm -rf riscv_rootfs && mkdir -p riscv_rootfs
	@tar -xvf $< -C riscv_rootfs --strip-components 1
	@ln -s busybox riscv_rootfs/bin/ls

riscv-image:
	@echo building riscv.img
	@rcore-fs-fuse zCore/riscv64.img riscv_rootfs zip
	@qemu-img resize -f raw zCore/riscv64.img +5M

# riscv-image: rcore-fs-fuse riscv-rootfs toolchain linux-user
# 	@echo building riscv.img
# 	@cd riscv_rootfs && mv libc-test libc-test-prebuild
# 	@cd riscv_rootfs &&  git clone $(LIBC_TEST_URL) --depth 1
# 	@cd riscv_rootfs/libc-test && cp config.mak.def config.mak && make ARCH=riscv64 CROSS_COMPILE=riscv64-linux-musl- -j
# 	@cd riscv_rootfs && cp libc-test-prebuild/functional/tls_align-static.exe libc-test/src/functional/
# 	@rcore-fs-fuse zCore/riscv64.img riscv_rootfs zip
# 	@qemu-img resize -f raw zCore/riscv64.img +5M

# ===================================================

# build and open project document
doc:
	cargo doc --open

# clean targets
clean:
	cargo clean
	rm -rf rootfs
	rm -rf ignored/target
	find zCore -maxdepth 1 -name "*.img" -delete

rt-test:
	cd rootfs/x86_64 && git clone https://kernel.googlesource.com/pub/scm/linux/kernel/git/clrkwllms/rt-tests --depth 1
	cd rootfs/x86_64/rt-tests && make
	echo x86 gcc build rt-test,now need manual modificy.
