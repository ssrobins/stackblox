#!/usr/bin/env python3

import argparse
import os.path
import subprocess

def main():
    platform = [
        "androidarm",
        "androidarm64",
        "ios",
        "linux",
        "macos",
        "windows"
    ]

    parser = argparse.ArgumentParser()
    parser.add_argument("platform", choices=platform, help="Build platform")
    parser.add_argument("--config", help="Build config")
    parser.add_argument("--build", action="store_true", help="Run build in CMake")
    parser.add_argument("--noConanPkgBuild", action="store_true", help="Use pre-built Conan packages and fail if they don't exist")
    parser.add_argument("--test", action="store_true", help="Run tests in CTest")
    parser.add_argument("--package", action="store_true", help="Run packaging in CPack")
    command_args = parser.parse_args()

    script_path = os.path.dirname(os.path.realpath(__file__))

    if command_args.config:
        config = command_args.config
    else:
        config = "Debug"

    conan_build_option = str()
    if command_args.noConanPkgBuild:
        conan_build_option = "-DCONAN_BUILD_MISSING_PKGS=OFF"

    subprocess.run(f"cmake --preset={command_args.platform} {conan_build_option}",
        cwd=script_path, shell=True, check=True)

    if command_args.test:
        command_args.build = True

    if command_args.package:
        # iOS packaging does a clean build so skip the build if packaging is selected
        if command_args.platform == "ios":
            command_args.build = False
        else:
            command_args.build = True

    if command_args.build:
        subprocess.run(f"cmake --build build_{command_args.platform} --config {config} --verbose",
            cwd=script_path, shell=True, check=True)

    if command_args.test:
        subprocess.run(f"ctest -C {config} --output-on-failure", cwd=os.path.join(script_path,
            f"build_{command_args.platform}"), shell=True, check=True)

    if command_args.package:
        subprocess.run(f"cpack -C {config}",
            cwd=os.path.join(script_path, f"build_{command_args.platform}"), shell=True, check=True)


if __name__ == "__main__":
    main()
