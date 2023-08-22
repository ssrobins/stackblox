import os
import subprocess

current_working_dir = os.getcwd()
conan_center_dir = f"{current_working_dir}/conan-center-index"
conan_center_repo = f"https://github.com/ssrobins/conan-center-index.git"
conan_center_branch = "package-fixes"

if not os.path.exists(conan_center_dir):
    subprocess.run(["git", "clone", "--depth=1", conan_center_repo, "-b", conan_center_branch],
        check=True, cwd=current_working_dir)

subprocess.run(["git", "checkout", conan_center_branch],
    check=True, cwd=conan_center_dir)
subprocess.run(["git", "fetch", "origin", conan_center_branch],
    check=True, cwd=conan_center_dir)
subprocess.run(["git", "reset", "--hard", f"origin/{conan_center_branch}"],
    check=True, cwd=conan_center_dir)

subprocess.run(["conan", "export", ".", "--version", "2.26.5"],
    check=True, cwd=f"{conan_center_dir}/recipes/sdl/all")
subprocess.run(["conan", "export", ".", "--version", "2.0.5"],
    check=True, cwd=f"{conan_center_dir}/recipes/sdl_image/all")
subprocess.run(["conan", "export", ".", "--version", "2.0.4"],
    check=True, cwd=f"{conan_center_dir}/recipes/sdl_mixer/all")
subprocess.run(["conan", "export", ".", "--version", "2.20.1"],
    check=True, cwd=f"{conan_center_dir}/recipes/sdl_ttf/all")
