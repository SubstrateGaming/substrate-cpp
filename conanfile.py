from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps

class libSubstratePackage(ConanFile):

    # Metadata
    name = "substrate"
    version = "1.0.0"
    license = "GPL 3"
    author = "svnscha"
    description = "C++ client interface to Polkadot (Substrate)"
    topics = ("crypto", "polkadot", "substrate", "sr25519")

    # Binary configuration
    settings = "os", "compiler", "arch", "build_type"
    generators = "CMakeDeps"

    options = {
        "shared": [True, False],
        "fPIC": [True, False],
        "with_tests": [True, False]
    }

    default_options = {
        "shared": False,
        "fPIC": True,
        "with_tests": True,
        "libsodium*:shared": False,
        "libcurl*:shared": False,
        "libcurl*:with_websockets": True,
        "libcurl*:with_http": True,
        "libcurl*:with_ssl": "openssl",
        "libcurl*:with_file": False,
        "libcurl*:with_ftp": False,
        "libcurl*:with_gopher": False,
        "libcurl*:with_imap": False,
        "libcurl*:with_ldap": False,
        "libcurl*:with_mqtt": False,
        "libcurl*:with_pop3": False,
        "libcurl*:with_rtsp": False,
        "libcurl*:with_smb": False,
        "libcurl*:with_smtp": False,
        "libcurl*:with_telnet": False,
        "libcurl*:with_tftp": False,
        "libcurl*:with_ntlm": False,
        "libcurl*:with_ntlm_wb": False,
        "libscale*:shared": False,
        "sr25519*:shared": False
    }

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "libSubstrate/*", "tests/*"

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def configure(self):
        if self.settings.os == "Windows":
            self.options["libcurl"].with_ssl = "schannel"
        if self.options.shared:
            self.options.rm_safe("fPIC")

    def requirements(self):
        self.requires("nlohmann_json/3.11.3", transitive_headers=True)
        self.requires("wide-integer/cci.20231015", transitive_headers=True)
        self.requires("libsodium/1.0.19")
        self.requires("sr25519/1.0.0@svnscha/dev")
        self.requires("libcurl/8.6.0@svnscha/dev")
        self.requires("libscale/1.1.1@svnscha/dev")
        if self.options.with_tests:
            self.requires("gtest/1.14.0")

    def layout(self):
        self.folders.build_folder_vars = ["settings.os", "settings.compiler", "settings.compiler.version", "settings.arch", "settings.build_type"]
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        if self.options.shared:
            tc.variables["BUILD_SHARED_LIBS"] = "ON"
        else:
            tc.variables["BUILD_SHARED_LIBS"] = "OFF"

        if self.options.with_tests:
            tc.variables["BUILD_TESTS"] = "ON"
        else:
            tc.variables["BUILD_TESTS"] = "OFF"

        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["substrate"]
