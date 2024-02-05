![logo](examples/moon.png)

# GRAFFITI

Graffiti is a dynamic, open-source project aimed at providing an easy-to-use platform for enthusiasts and designers to create logos and images from instructions. These creations can then be exported to PNG files. Graffiti uses the high-performance 2D vector graphics library [Blend2D](https://blend2d.com/) to render images. This allows for a unique blend of programming and design, opening up new possibilities for digital art.

## Features

Graffiti comes with a wide range of features:

- **Vector Graphics**: Graffiti projects use relative values, allowing the resulting images to be used in any size.
- **Scripting Capabilities**: Built on top of Lua, Graffiti inherits almost all features of the language. This allows for image creation with a level of automation that is impossible to reach with conventional tools.
- **Ease of Use**: Graffiti is designed to be easy to learn and apply.
- **Color Support**: Supports all HTML colors (see colors.lua).
- **Path Support**: Allows for the creation and manipulation of paths.
- **Gradient Support**: Allows for the creation of gradients.
- **Image Reusage**: Supports the reuse of images.
- **Layer and Crop Support**: Supports layers with cropping and customizable cropping.
- **Units**: Supports px, cm, and % units (% is the default).
- **Transformations**: Supports translate, resize, and rotate operations.

## Installation

Follow these steps to install Graffiti:

1. Clone the repository:

```
$ git clone https://github.com/renemuala/graffiti.git
```

2. Navigate to the cloned repository:

```
$ cd graffiti
```

3. Create a new directory for the build:

```
$ mkdir build cd build
```

4. Run CMake to generate the build files:

```
$ cmake ..
```

5. Build the project:

```
$ cmake --build .
```

You should now have the Graffiti executable in your build directory.

6. Install graffiti on your system (Optional)

```
$ make install 
```

### All in one

```
git clone https://github.com/renemuala/graffiti.git
cd graffiti 
mkdir build cd build
cmake ..
cmake --build .
# optional install
make install
```

> Make sure to use tabs instad of spaces when writting graffiti code

## Why Graffiti?

Graffiti provides a unique blend of design and programming, allowing users to create intricate and customizable images using scripts. This opens up a new realm of possibilities for digital art, making it accessible to both designers and programmers. With its extensive feature set, Graffiti offers a level of automation and precision that is hard to achieve with conventional design tools. Whether you're a designer looking to automate your workflows or a programmer interested in exploring the world of design, Graffiti is the tool for you.

## Acknowledgements

I would like to express my gratitude to the following individuals and projects that have made Graffiti possible:

- [Blend2D](https://blend2d.com/): For the high-performance 2D vector graphics library used in Graffiti.
- [Lua](https://www.lua.org/): For providing the powerful scripting language that Graffiti is built upon.
- [CMake](https://cmake.org/): For the robust build system used in Graffiti.