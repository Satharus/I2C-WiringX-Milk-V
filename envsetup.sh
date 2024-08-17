#!/bin/bash


SDK=/opt/riscv-musl/
TOOLCHAIN_DIR=/opt/riscv-musl/ 

export TOOLCHAIN_PREFIX=${TOOLCHAIN_DIR}/bin/riscv64-linux-musl-
export SYSROOT=${SDK}/
export CC=${TOOLCHAIN_PREFIX}gcc

export CFLAGS=" -mcmodel=medany -mabi=lp64d"
# -Os
export LDFLAGS="-D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64"

echo "SDK environment is ready"

