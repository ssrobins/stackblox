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
        "sdl/*:alsa": True,
        "sdl/*:arts": False,
        "sdl/*:directfb": False,
        "sdl/*:directx": False,
        "sdl/*:esd": False,
        "sdl/*:iconv": False,
        "sdl/*:jack": False,
        "sdl/*:libunwind": False,
        "sdl/*:nas": False,
        "sdl/*:opengl": False,
        "sdl/*:opengles": False,
        "sdl/*:pulse": False,
        "sdl/*:sndio": False,
        "sdl/*:video_rpi": False,
        "sdl/*:vulkan": False,
        "sdl/*:wayland": False,
        "sdl/*:x11": False,
        "sdl/*:xcursor": False,
        "sdl/*:xinerama": False,
        "sdl/*:xinput": False,
        "sdl/*:xrandr": False,
        "sdl/*:xscrnsaver": False,
        "sdl/*:xshape": False,
        "sdl/*:xvm": False,
    }

    def config_options(self):
        self.options["sdl/*"].iconv = self.settings.os == "iOS"
        self.options["sdl/*"].opengl = self.settings.os != "Android"
        self.options["sdl/*"].opengles = self.settings.os == "Android"
        self.options["sdl/*"].x11 = self.settings.os == "Linux"
        self.options["sdl/*"].xinput = self.settings.os == "Linux"

    def build_requirements(self):
        self.test_requires("gtest/1.14.0")

    def requirements(self):
        self.requires("sdl/2.28.3")
        self.requires("sdl_image/2.0.5")
        self.requires("sdl_mixer/2.0.4")
        self.requires("sdl_ttf/2.20.2")
