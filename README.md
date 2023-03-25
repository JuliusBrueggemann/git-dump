# Building git-dump
`git-dump` is built using CMake and [vcpkg](https://github.com/microsoft/vcpkg). If you don't have `vcpkg` installed already, follow the installation instructions
from the `vcpkg` repository. Installing `vcpkg` is very easy and only requires you to clone the `vcpkg` repository and run the `bootstrap_vcpkg` script.

Before building `git-dump`, it is recommended to set the `CMAKE_TOOLCHAIN_FILE` environment variable to `<path to vcpkg>/scripts/buildsystems/vcpkg.cmake`.
This tells CMake to use `vcpkg` without having to touch the CMake configuration.

Once the environment variable is set, you can simply open the project in an IDE like Visual Studio or CLion (as long as your IDE understands CMake).
Alternatively, you can build `git-dump` from the command line:

```
cmake -S . -B build --preset=x64-release-static --install-prefix=<your preferred installation path>
cmake --build build
cmake --install build
```

This will install `git-dump` to `<your preferred installation path>/bin`. For example, if you specify `C:\Program Files\git-dump\` as installation path, 
`git-dump` will be installed to `C:\Program Files\git-dump\bin`. You will need to manually add the installation path to the `PATH` environment variable if you 
want to be able to use `git-dump` from anywhere on the system.
