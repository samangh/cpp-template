[![Linux](https://github.com/samangh/cpp-template/actions/workflows/linux.yml/badge.svg)](https://github.com/samangh/cpp-template/actions/workflows/linux.yml)
[![macOS](https://github.com/samangh/cpp-template/actions/workflows/macos.yml/badge.svg)](https://github.com/samangh/cpp-template/actions/workflows/macos.yml)
[![Windows](https://github.com/samangh/cpp-template/actions/workflows/windows.yml/badge.svg)](https://github.com/samangh/cpp-template/actions/workflows/windows.yml)
[![Linux](https://github.com/samangh/cpp-template/actions/workflows/linux.yml/badge.svg)](https://github.com/samangh/cpp-template/actions/workflows/linux.yml)

On Windows, use:

```
cmake -S ..\src -B . -DBUILD_SHARED_LIBS=OFF -DUSE_STATIC_RUNTIME=ON -DCMAKE_TOOLCHAIN_FILE=C:/local/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows-static
```
