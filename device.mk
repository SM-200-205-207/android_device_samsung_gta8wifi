#
# SPDX-FileCopyrightText: The LineageOS Project
# SPDX-License-Identifier: Apache-2.0
#

LOCAL_PATH := $(call my-dir)

# Enable updating of APEXes
$(call inherit-product, $(SRC_TARGET_DIR)/product/updatable_apex.mk)

# API levels
PRODUCT_SHIPPING_API_LEVEL := 30

# VNDK compatibility layer for Android 11 vendor blobs
PRODUCT_EXTRA_VNDK_VERSIONS := 30

# fastbootd
PRODUCT_PACKAGES += \
    android.hardware.fastboot-service.example_recovery \
    fastbootd

# Health (AIDL)
PRODUCT_PACKAGES += \
    android.hardware.health-service.example \
    android.hardware.health-service.example_recovery

# Memtrack (AIDL)
PRODUCT_PACKAGES += \
    android.hardware.memtrack-service.example

# Lights (AIDL)
PRODUCT_PACKAGES += \
    android.hardware.light-service.sprd

# Power (AIDL)
PRODUCT_PACKAGES += \
    android.hardware.power-service.example

# USB (AIDL)
PRODUCT_PACKAGES += \
    android.hardware.usb-service.example

# Shims
PRODUCT_PACKAGES += \
    libshim_camera \
    libui_shim \
    libgui_shim

# 32-Bit Legacy Audio & Camera Packages
PRODUCT_PACKAGES += \
    android.hardware.audio@6.0-impl:32 \
    android.hardware.audio.effect@6.0-impl:32 \
    libcamera2ndk_vendor

# Kernel
PRODUCT_ENABLE_UFFD_GC := false

# Overlays
DEVICE_PACKAGE_OVERLAYS += $(LOCAL_PATH)/overlay
PRODUCT_ENFORCE_RRO_TARGETS := *

# Partitions
PRODUCT_USE_DYNAMIC_PARTITIONS := true

# Product characteristics
PRODUCT_CHARACTERISTICS := tablet

# Rootdir
PRODUCT_PACKAGES += \
    log_to_csv.sh \
    loading.sh \
    para.sh \
    total.sh \
    install-recovery.sh \

PRODUCT_PACKAGES += \
    fstab.ums512 \
    fstab.ums512_25c10 \
    fstab.charge_mode \
    init.cali.rc \
    init.factorytest.rc \
    init.gta8wifi.rc \
    init.storage.rc \
    init.ums512_25c10.rc \
    init.ums512_25c10.usb.rc \

PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/rootdir/etc/fstab.ums512:$(TARGET_COPY_OUT_RAMDISK)/fstab.ums512 \
    $(LOCAL_PATH)/rootdir/etc/fstab.ums512:$(TARGET_COPY_OUT_RAMDISK)/fstab.ums512_25c10 \
    $(LOCAL_PATH)/rootdir/etc/fstab.ums512:$(TARGET_COPY_OUT_RAMDISK)/fstab.default \
    $(LOCAL_PATH)/rootdir/etc/fstab.charge_mode:$(TARGET_COPY_OUT_RAMDISK)/fstab.charge_mode \
    $(LOCAL_PATH)/rootdir/etc/init.recovery.ums512.rc:$(TARGET_COPY_OUT_RECOVERY)/root/init.recovery.ums512.rc \
    $(LOCAL_PATH)/rootdir/etc/init.recovery.ums512.rc:$(TARGET_COPY_OUT_RECOVERY)/root/init.recovery.ums512_25c10.rc \
    $(LOCAL_PATH)/task_profiles.json:$(TARGET_COPY_OUT_VENDOR)/etc/task_profiles.json \
    $(LOCAL_PATH)/cgroups.json:$(TARGET_COPY_OUT_VENDOR)/etc/cgroups.json

# Soong namespaces
PRODUCT_SOONG_NAMESPACES += \
    $(LOCAL_PATH)

# Inherit the proprietary files
$(call inherit-product, vendor/samsung/gta8wifi/gta8wifi-vendor.mk)
