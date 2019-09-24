from conans import ConanFile

class Conan(ConanFile):
    name = "StackBlox"
    version = ""
    settings = "os"
    generators = "cmake"

    def requirements(self):
        self.requires.add("gtest/1.8.1#87754ca5593a1001e629122ee514d931aa9e8bf7")
        self.requires.add("ssrobins_engine/0.1.0#b89fc804e84394548b432a2912fd2d567f4ac2e8")
