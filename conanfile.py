from conans import ConanFile

class Conan(ConanFile):
    name = "StackBlox"
    version = ""
    settings = "os"
    generators = "cmake"

    def requirements(self):
        self.requires.add("gtest/1.8.1#87754ca5593a1001e629122ee514d931aa9e8bf7")
        self.requires.add("ssrobins_engine/0.1.0#518a3143d2536d48691a4c3c2520e34bbfca8aae")
