DEVICE_PATH := device/motorola/ali
BOARD_VENDOR := motorola

# Security patch level
VENDOR_SECURITY_PATCH := 2019-10-01

# HIDL
DEVICE_MANIFEST_FILE := $(DEVICE_PATH)/manifest.xml
DEVICE_MATRIX_FILE := $(DEVICE_PATH)/compatibility_matrix.xml

-include vendor/motorola/ali/BoardConfigVendor.mk
