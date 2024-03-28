On Windows, use:

```
cmake -S ..\src -B . -DBUILD_SHARED_LIBS=OFF -DUSE_STATIC_RUNTIME=ON -DCMAKE_TOOLCHAIN_FILE=C:/local/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows-static
```