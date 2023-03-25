# Building git-dump
`git-dump` is built using CMake and [vcpkg](https://github.com/microsoft/vcpkg). If you don't have `vcpkg` installed already, follow the installation instructions
from the `vcpkg` repository. Installing `vcpkg` is very easy and only requires you to clone the `vcpkg` repository and run the `bootstrap_vcpkg` script.

Before building `git-dump`, it is recommended to set the `CMAKE_TOOLCHAIN_FILE` environment variable to `<path to vcpkg>/scripts/buildsystems/vcpkg.cmake`.
This tells CMake to use `vcpkg` without having to touch the CMake configuration.

Once the environment variable is set, you can simply open the project in an IDE like Visual Studio or CLion (as long as your IDE understands CMake).
Alternatively, you can build `git-dump` from the command line:

```
cmake -S . -B build --preset=<preset>
cmake --build build
```
