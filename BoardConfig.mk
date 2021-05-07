#
# Copyright 2019 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

DEVICE_PATH := device/essential/mata

# Architecture
TARGET_ARCH := arm64
TARGET_ARCH_VARIANT := armv8-a
TARGET_CPU_ABI := arm64-v8a
TARGET_CPU_ABI2 :=
TARGET_CPU_VARIANT := cortex-a73

TARGET_2ND_ARCH := arm
TARGET_2ND_ARCH_VARIANT := armv8-a
TARGET_2ND_CPU_ABI := armeabi-v7a
TARGET_2ND_CPU_ABI2 := armeabi
TARGET_2ND_CPU_VARIANT := cortex-a73

# Bootloader
TARGET_BOOTLOADER_BOARD_NAME := msm8998
TARGET_NO_BOOTLOADER := true

# Platform
TARGET_BOARD_PLATFORM := msm8998
TARGET_SUPPORTS_64_BIT_APPS := true

# Kernel
BOARD_KERNEL_CMDLINE := androidboot.hardware=mata user_debug=31 ehci-hcd.park=3
BOARD_KERNEL_CMDLINE += lpm_levels.sleep_disabled=1 service_locator.enable=1
BOARD_KERNEL_CMDLINE += swiotlb=2048 androidboot.configfs=true
BOARD_KERNEL_CMDLINE += androidboot.usbcontroller=a800000.dwc3 cma=32M@0-0xffffffff
BOARD_KERNEL_CMDLINE += androidboot.selinux=permissive
BOARD_KERNEL_BASE := 0x00000000
BOARD_KERNEL_PAGESIZE := 4096
BOARD_KERNEL_TAGS_OFFSET := 0x02000000
BOARD_RAMDISK_OFFSET := 0x02200000
BOARD_KERNEL_IMAGE_NAME := Image.gz-dtb
#TARGET_PREBUILT_KERNEL := $(DEVICE_PATH)/prebuilt/Image.gz-dtb
TARGET_KERNEL_SOURCE := kernel/essential/msm8998
TARGET_KERNEL_CONFIG := mata_defconfig

# Partitions
BOARD_FLASH_BLOCK_SIZE := 131072
BOARD_BOOTIMAGE_PARTITION_SIZE := 536870912        #    32768 * 1024 mmcblk0p41-42
BOARD_RECOVERYIMAGE_PARTITION_SIZE := 536870912 
BOARD_DTBOIMG_PARTITION_SIZE := 8388608           #     8192 * 1024 mmcblk0p43-44
BOARD_SYSTEMIMAGE_PARTITION_SIZE := 2885681152    #  2818048 * 1024 mmcblk0p62-63
#BOARD_USERDATAIMAGE_PARTITION_SIZE := 23165123584 # 22622191 * 1024 mmcblk0p64
BOARD_BUILD_SYSTEM_ROOT_IMAGE := true
BOARD_USES_RECOVERY_AS_BOOT := true
TARGET_USERIMAGES_USE_EXT4 := true
TARGET_USERIMAGES_USE_F2FS := true

# Debug flags
TWRP_INCLUDE_LOGCAT := true
TARGET_USES_LOGD := true

# Encryption
PLATFORM_VERSION := 16.1.0
PLATFORM_SECURITY_PATCH := 2099-12-31
VENDOR_SECURITY_PATCH :=  2099-12-31

# TWRP specific build flags
TARGET_SYSTEM_PROP += $(DEVICE_PATH)/system.prop
RECOVERY_SDCARD_ON_DATA := true
TARGET_RECOVERY_QCOM_RTC_FIX := true
TW_NEW_ION_HEAP := true
TW_SCREEN_BLANK_ON_BOOT := true
TW_THEME := portrait_hdpi
BOARD_SUPPRESS_SECURE_ERASE := true
TW_X_OFFSET := 42
TARGET_RECOVERY_DEVICE_MODULES += android.hardware.boot@1.0
TW_INPUT_BLACKLIST := "hbtp_vm"
TW_EXCLUDE_TWRPAPP := true
TW_Y_OFFSET := 138
TW_H_OFFSET := -138

# Extras
USE_RECOVERY_INSTALLER := true
RECOVERY_INSTALLER_PATH := bootable/recovery/installer
TW_INCLUDE_REPACKTOOLS := true

# Workaround for error copying vendor files to recovery ramdisk
BOARD_VENDORIMAGE_FILE_SYSTEM_TYPE := ext4
TARGET_COPY_OUT_VENDOR := vendor
