#!/bin/bash

export ARCH=arm

mkdir output

make -C $(pwd) O=output msm8939_sec_defconfig VARIANT_DEFCONFIG=msm8939_sec_a8_chnopen_defconfig SELINUX_DEFCONFIG=selinux_defconfig 
make -C $(pwd) O=output
cp output/arch/arm/boot/Image $(pwd)/arch/arm/boot/zImage
