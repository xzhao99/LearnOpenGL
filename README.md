# LearnOpenGL

Learning examples from [LearnOpenGL](www.learnopengl.com)

See the [github repo](https://github.com/JoeyDeVries/LearnOpenGL/tree/master)

## build instruction

Following the original instruction, we use a combination of ```GLAD``` as the OpenGL loading library and ```GLFW``` to create/manage windows and contexts. However, different from the author's process, we here use ```vcpkg``` as a package manager to import the related libraries. At the time of initiating this example, the OpenGL version is 4.6 on my Windows(info from OpenGL extension viewer)

```[]
mkdir build

# this will use Ninja as the default generator
cmake -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE:PATH=C:/DevTools/vcpkg/scripts/buildsystems/vcpkg.cmake

# explicitly specify to use VS as the generator
cmake -B build -G "Visual Studio 17 2022" -A x64 "" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE:PATH=C:/DevTools/vcpkg/scripts/buildsystems/vcpkg.cmake

cmake --build build/ --config Debug
```
