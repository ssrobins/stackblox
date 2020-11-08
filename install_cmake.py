#!/usr/bin/env python3

import argparse
import os
import platform
import subprocess
import tarfile
import urllib.request
import zipfile

class CMakeInstall:
    def __init__(self, version):
        self.version = version

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

        cmake_dir = f"cmake-{self.version}-{cmake_platform}"
        self.archive = f"{cmake_dir}{cmake_archive_ext}"
        self.url = f"http://dnqpy.com/temp/{self.archive}"
        script_path = os.path.dirname(os.path.realpath(__file__))
        cmake_binary_path = os.path.join(script_path, cmake_dir, cmake_binary_dir)

    def download(self):
        print(f"Downloading {self.url}", flush=True)
        urllib.request.urlretrieve(f"{self.url}", f"{self.archive}")

    def extract(self):
        print(f"Extracting {self.archive}", flush=True)
        if "tar" in self.archive:
            with tarfile.open(f"{self.archive}", "r:gz") as tar:
                tar.extractall()
        elif "zip" in self.archive:
            with zipfile.ZipFile(f"{self.archive}", 'r') as zip:
                zip.extractall()
        else:
            print("Unsupported archive: {self.archive}", flush=True)
            exit(1)

    def set_path(self):
        if "GITHUB_PATH" in os.environ:
            print(f"Write CMake path, {cmake_binary_path}, to {os.environ['GITHUB_PATH']}", flush=True)
            with open(os.environ["GITHUB_PATH"], "a") as envfile:
                envfile.write(cmake_binary_path)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--version",
        help="CMake version in the form 3.18.4 or 3.19.0-rc2 for RCs.", required=True
    )
    cmake_args = parser.parse_args()

    cmake_install = CMakeInstall(cmake_args.version)

    cmake_install.download()
    cmake_install.extract()
    cmake_install.set_path()

if __name__ == "__main__":
    main()
