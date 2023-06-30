from conan import ConanFile

required_conan_version = ">=2.0.4"

class Conan(ConanFile):
    name = "StackBlox"
    version = ""
    settings = "os", "arch", "compiler", "build_type"
    generators = "CMakeDeps"
    default_options = {
        "sdl_image/*:bmp": False,
        "sdl_image/*:gif": False,
        "sdl_image/*:imageio": False,
        "sdl_image/*:lbm": False,
        "sdl_image/*:pcx": False,
        "sdl_image/*:pnm": False,
        "sdl_image/*:svg": False,
        "sdl_image/*:tga": False,
        "sdl_image/*:with_libjpeg": False,
        "sdl_image/*:with_libpng": True,
        "sdl_image/*:with_libtiff": False,
        "sdl_image/*:with_libwebp": False,
        "sdl_image/*:xcf": False,
        "sdl_image/*:xpm": False,
        "sdl_image/*:xv": False,
        "sdl_mixer/*:flac": False,
        "sdl_mixer/*:fluidsynth": False,
        "sdl_mixer/*:mad": False,
        "sdl_mixer/*:mikmod": False,
        "sdl_mixer/*:modplug": False,
        "sdl_mixer/*:mpg123": False,
        "sdl_mixer/*:nativemidi": False,
        "sdl_mixer/*:ogg": True,
        "sdl_mixer/*:opus": False,
        "sdl_mixer/*:tinymidi": False,
        "sdl_mixer/*:wav": False,
    }

    def build_requirements(self):
        self.test_requires("gtest/1.13.0")

    def requirements(self):
        self.requires("sdl/2.26.5")
        self.requires("sdl_image/2.0.5")
        self.requires("sdl_mixer/2.0.4")
        self.requires("sdl_ttf/2.20.1")
