# Samsung Galaxy Tab A8 10.5" Wi-Fi (SM-X200 / gta8wifi)

```
#
# SPDX-FileCopyrightText: The LineageOS Project
# SPDX-License-Identifier: Apache-2.0
#
```

The **Samsung Galaxy Tab A8 10.5" Wi-Fi** (codenamed `gta8wifi` / model `SM-X200`) is an entry-to-midrange tablet manufactured by Samsung and released in December 2021.

## Hardware Specifications

| Component | Hardware Profile |
| :--- | :--- |
| **SoC** | Unisoc Tiger T618 (`ums512` / `sharkl5Pro`) |
| **CPU** | Octa-core (2x ARM Cortex-A75 @ 2.0 GHz + 6x ARM Cortex-A55 @ 2.0 GHz) |
| **GPU** | ARM Mali-G52 3EE 2-core (Bifrost Gondul architecture) |
| **Memory** | 3GB / 4GB LPDDR4x RAM |
| **Storage** | 32GB / 64GB / 128GB eMMC 5.1 |
| **Display** | 10.5" WUXGA (1920x1200) TFT LCD, 240 DPI, 60 Hz |
| **Battery** | 7040 mAh Li-Po, 15W fast charging |
| **Audio** | Quad stereo speakers (Dolby Atmos), Unisoc SC2730 codec, AW882XX smart amplifiers |
| **Rear Camera** | 8.0 MP (GalaxyCore GC8034 / Hynix Hi-846) |
| **Front Camera** | 5.0 MP (GalaxyCore GC5035 / Hynix Hi-556) |
| **Connectivity** | Wi-Fi 802.11 a/b/g/n/ac dual-band, Bluetooth 5.0, GPS/GLONASS/Galileo |

---

## Setting Up Build Environment

### 1. Initialize LineageOS 21 Source
Initialize a LineageOS 21.0 (Android 14 / API 34) source tree:
```bash
repo init -u https://github.com/LineageOS/android.git -b lineage-21.0 --git-lfs --depth=1
```

### 2. Configure Local Manifest
Fetch the local manifest for Samsung Galaxy Tab A8 directly via `curl`:
```bash
mkdir -p .repo/local_manifests
curl -o .repo/local_manifests/gta8wifi.xml -L https://raw.githubusercontent.com/SM-200-205-207/android_device_samsung_gta8wifi/main/gta8wifi.xml
```

### 3. Sync Repositories
Sync the ROM tree and all required device repositories:
```bash
repo sync -c -j$(nproc --all) --force-sync --no-clone-bundle --no-tags
```

---

## Building LineageOS 21

```bash
# 1. Initialize build environment
source build/envsetup.sh

# 2. Select target
lunch lineage_gta8wifi-userdebug

# 3. Compile full ROM package
mka bacon -j$(nproc --all)
```

---

## Credits & Acknowledgements

Special thanks to the following developers and upstream projects whose work made this bringup possible:

* **[İsmail Demirbaş (@ismail-demirbas)](https://github.com/ismail-demirbas)** 
* **[SebaUbuntu & contributors / aospdtgen](https://github.com/sebaubuntu/aospdtgen)** — For the automated AOSP device tree generator from OEM dumps.
* **[The LineageOS Project](https://github.com/LineageOS)** & **Galaxy Tab A7 (`gta4xlwifi` / `gta4wifi`) Maintainers** —  platform references, partition layouts, and init blueprints.
* **[sprd-oss-devs](https://github.com/sprd-oss-devs)** — Unisoc Tiger T618 (`ums512`) Android 14 HAL and platform support.

