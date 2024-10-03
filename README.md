[![Linux](https://github.com/samangh/cpp-template/actions/workflows/linux.yml/badge.svg)](https://github.com/samangh/cpp-template/actions/workflows/linux.yml)
[![macOS](https://github.com/samangh/cpp-template/actions/workflows/macos.yml/badge.svg)](https://github.com/samangh/cpp-template/actions/workflows/macos.yml)
[![Windows](https://github.com/samangh/cpp-template/actions/workflows/windows.yml/badge.svg)](https://github.com/samangh/cpp-template/actions/workflows/windows.yml)
[![Linux](https://github.com/samangh/cpp-template/actions/workflows/linux.yml/badge.svg)](https://github.com/samangh/cpp-template/actions/workflows/linux.yml)

## To compile

Clone the repository *recursively* and run through CMake as usual. See
the section below for dependencies.

```
git clone --recursive git@github.com:samangh/cpp-template.git 
mkdir cpp-template-build
cmake cpp-template -B cpp-template-build
cmake --build cpp-template-build
```

## Dependencies
### Linux

Use your favourite package manager (`apt`, `yum`, etc)

```
sudo apt update
sudo apt install coreutils libboost-dev libsdl2-dev libuv1-dev libfmt-dev libzstd-dev
```

## macOS

Easiest using Homebrew:

```
brew install zstd uv boost fmt sdl2
```

## MSYS2

Use `pacboy`:

```shell
pacman -S pactoys
pacboy -S toolchain:p cmake:p boost:p SDL2:p fmt:p libuv:p zstd:p
```

If using clang, you have to pass the `-fexperimental-library` compiler flag, so do the
following before calling CMake:

```shell
export CXXFLAGS=-fexperimental-library
```

This is not needed for non-clang compilers.

### Windows (dynamic)

Easiest to use vcpkg. Terminal to the VCPKG install location, then:

```shell
vcpkg update
vcpkg --triplet x64-windows install boost-crc sdl2 fmt libuv zstd
vpkg integrate install
```

Then, when using CMake pass the VCPKG flags.

```shell
cmake cpp-template -B cpp-template-build -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows -DCMAKE_BUILD_TYPE=Release
```

You need to specify the con fig when compiling, this must match the
value of `CMAKE_BUILD_TYPE` passed earlier during the CMake config.

```shell
cmake --build . --config Release
```





