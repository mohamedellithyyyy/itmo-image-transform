# ITMO Image Transform

A command-line utility written in C for reading,
processing, and writing 24-bit BMP images.

## Features

- BMP image reading and writing
- 90-degree clockwise rotation
- 90-degree counterclockwise rotation
- Horizontal flip
- Vertical flip
- Original image preservation

## Architecture

- Image representation
- BMP serialization and deserialization
- Image transformations
- Command-line interface

## Technologies

- C
- CMake
- GCC / Clang
- Git

## Usage

./image-transform input.bmp output.bmp cw90

## Supported transformations

- none
- cw90
- ccw90
- fliph
- flipv

## Disclaimer

Academic project developed as part of the
ITMO University Programming Languages course.