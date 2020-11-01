#!/usr/bin/env python3

import platform
import subprocess
import tarfile
import urllib.request
import zipfile


cmake_version = "3.19.0-rc2"

if platform.system() == "Darwin":
    cmake_platform = "Darwin-x86_64"
    cmake_archive_ext = ".tar.gz"
elif platform.system() == "Linux":
    cmake_platform = "Linux-x86_64"
    cmake_archive_ext = ".tar.gz"
elif platform.system() == "Windows":
    cmake_platform = "win64-x64"
    cmake_archive_ext = ".zip"

cmake_dir = f"cmake-{cmake_version}-{cmake_platform}"
cmake_archive = f"{cmake_dir}{cmake_archive_ext}"
cmake_url = f"http://dnqpy.com/temp/{cmake_archive}"

print(f"Downloading {cmake_url}", flush=True)
urllib.request.urlretrieve(f"{cmake_url}", f"{cmake_archive}")

print(f"Extracting {cmake_archive}", flush=True)
if "tar" in cmake_archive:
    with tarfile.open(f"{cmake_archive}", "r:gz") as tar:
        tar.extractall()
elif "zip" in cmake_archive:
    with zipfile.ZipFile(f"{cmake_archive}", 'r') as zip:
        zip.extractall()
else:
    print("Unsupported archive: {cmake_archive}")
    exit(1)

subprocess.run("cmake --version", shell=True, check=True)
