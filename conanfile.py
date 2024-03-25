from conan import ConanFile
from conan.tools.cmake import cmake_layout

class Pkg(ConanFile):
    settings = "os", "compiler", "arch", "build_type"
    generators = "CMakeDeps", "CMakeToolchain"

    default_options = {
        "boost*:header_only": True,
        "libsodium*:shared": False,
        "sr25519*:shared": False,

        # Lacks ENABLE_WEBSOCKETS options.
        # "libcurl*:shared": False
    }

    def requirements(self):
        self.requires("boost/1.84.0")
        self.requires("nlohmann_json/3.11.3")
        self.requires("libsodium/1.0.19")
        self.requires("gtest/1.14.0")
        self.requires("sr25519/1.0.0")
        # Lacks ENABLE_WEBSOCKETS options.
        # self.requires("libcurl/8.6.0")

    def layout(self):
        self.folders.build_folder_vars = ["settings.os", "settings.compiler", "settings.compiler.version", "settings.arch", "settings.build_type"]
        cmake_layout(self)
