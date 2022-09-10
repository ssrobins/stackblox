#!/usr/bin/env python3

import argparse
import os.path
import shutil
import subprocess
import sys

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
    parser.add_argument("--iwyu", action="store_true", help="Enable 'Include What You Use' tool")
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
        conan_build_option = " -DCONAN_BUILD_MISSING_PKGS=OFF"

    build_dir = f"build_{command_args.platform}"

    iwyu_option = str()
    verbose = " --verbose"
    if command_args.iwyu:
        if not shutil.which("include-what-you-use"):
            print("include-what-you-use binary not found", flush=True)
            sys.exit(1)
        iwyu_option = f' -G "Ninja Multi-Config" -DCMAKE_CXX_INCLUDE_WHAT_YOU_USE="include-what-you-use;-Xiwyu;--mapping_file={script_path}/iwyu.imp"'
        if command_args.platform == "ios":
            iwyu_option += " -DCMAKE_OSX_ARCHITECTURES=arm64"
        build_dir += "_iwyu"
        verbose = ""

    cmake_cmd = f"cmake --preset={command_args.platform}{conan_build_option}{iwyu_option} -B {build_dir}"
    print(cmake_cmd, flush=True)
    subprocess.run(cmake_cmd, cwd=script_path, shell=True, check=True)

    if command_args.test:
        command_args.build = True

    if command_args.package:
        # iOS packaging does a clean build so skip the build if packaging is selected
        if command_args.platform == "ios":
            command_args.build = False
        else:
            command_args.build = True

    if command_args.build or command_args.iwyu:
        cmake_build_cmd = f"cmake --build {build_dir} --config {config}{verbose}"
        if command_args.iwyu:
            cmake_build_cmd += " --clean-first"
        print(cmake_build_cmd, flush=True)
        subprocess.run(cmake_build_cmd, cwd=script_path, shell=True, check=True)

    if command_args.test:
        ctest_cmd = f"ctest -C {config} --output-on-failure"
        print(ctest_cmd, flush=True)
        subprocess.run(ctest_cmd, cwd=os.path.join(script_path, build_dir), shell=True, check=True)

    if command_args.package:
        cpack_cmd = f"cpack -C {config}"
        print(cpack_cmd, flush=True)
        subprocess.run(cpack_cmd, cwd=os.path.join(script_path, build_dir), shell=True, check=True)


if __name__ == "__main__":
    main()
