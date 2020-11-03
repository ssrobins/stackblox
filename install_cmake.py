#!/usr/bin/env python3

import argparse
import os
import platform
import subprocess
import tarfile
import urllib.request
import zipfile

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--version",
        help="CMake version in the form 3.18.4 or 3.19.0-rc2 for RCs.", required=True
    )
    cmake_args = parser.parse_args()

    if platform.system() == "Darwin":
        cmake_platform = "Darwin-x86_64"
        cmake_archive_ext = ".tar.gz"
        cmake_binary_dir = "CMake.app/Contents/bin"
    elif platform.system() == "Linux":
        cmake_platform = "Linux-x86_64"
        cmake_archive_ext = ".tar.gz"
        cmake_binary_dir = "bin"
    elif platform.system() == "Windows":
        cmake_platform = "win64-x64"
        cmake_archive_ext = ".zip"
        cmake_binary_dir = "bin"

    cmake_dir = f"cmake-{cmake_args.version}-{cmake_platform}"
    cmake_archive = f"{cmake_dir}{cmake_archive_ext}"
    cmake_url = f"http://dnqpy.com/temp/{cmake_archive}"
    script_path = os.path.dirname(os.path.realpath(__file__))
    cmake_binary_path = os.path.join(script_path, cmake_dir, cmake_binary_dir)

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
        print("Unsupported archive: {cmake_archive}", flush=True)
        exit(1)

    if "GITHUB_PATH" in os.environ:
        print(f"Write CMake path, {cmake_binary_path}, to {os.environ['GITHUB_PATH']}", flush=True)
        with open(os.environ["GITHUB_PATH"], "a") as envfile:
            envfile.write(cmake_binary_path)

if __name__ == "__main__":
    main()
