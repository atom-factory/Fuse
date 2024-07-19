# Quickstart Guide

This guide should help you get up and running with writing VST3
plug-ins with Fuse.

## Table of Contents

1. [Prerequisites](#prerequisites)
2. [Acquire Fuse](#acquire-fuse)
    1. [Building from source](#building-from-source)
3. [Creating a project](#creating-a-project)
    1. [With the VST3 SDK](#with-vst3-sdk)
    2. [Without the VST3 SDK](#without-vst3-sdk)
4. ["Hello World" Example](#hello-world-example)
5. [Troubleshooting](#troubleshooting)

## Prerequisites

Let's go over some prerequisites first:

1. **VST3 SDK** from Steinberg ([Download](https://steinberg.net/vst3sdk))
   > See our VST3 SDK Quickstart guide for setting this up [here](https://github.com/atom-factory/vst3-sdk-quickstart).
   The SDK isn't *required* to compile Fuse and run the examples, but Fuse is intended to be
   used in a VST3 project by design.

2. **A C/C++ compiler**. Recommendations below:
    - Windows: MSVC
    - Linux: Clang or GCC
    - macOS: Clang or GCC

## Acquire Fuse

You can get Fuse either by cloning the `master` branch source and building yourself
or by downloading one of the pre-compiled binaries over
at [releases](https://github.com/atom-factory/Fuse/releases/latest).

Fuse in required to be statically linked when used in a VST3 SDK project. This requirement doesn't exist
if being used outside of this context.

### Building from source

If building Fuse from source, we recommend simply cloning the repo to the root of your project
directory and adding it as a subdirectory to your `CMakeLists.txt`:

```cmake
add_subdirectory(Fuse)
```

This will build Fuse along with your project and updates can be acquired by simply pulling the repo.
Doing this allows you to simply link Fuse like so:

```cmake
target_link_libraries(MyVSTPlugin PRIVATE Fuse)
```

## Creating a project

TODO

### With VST3 SDK

TODO

### Without VST3 SDK

TODO

## "Hello World" Example

TODO

## Troubleshooting

TODO