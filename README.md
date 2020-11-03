# Getting started

This project makes use of my fork of [simple2d](https://github.com/AdlanSADOU/simple2d) repository as a submodule.
Follow these steps to be able to build it:

## On Windows

First of all, you should have the Visual C++ compiler installed that comes with the Visual Studio installation.
Also, I'm using Visual Studio Code for this project and it should `just work`.



```bash
git clone https://github.com/AdlanSADOU/Sample_simple2d.git --recursive
```
 `--recursive` meaning it should clone this repository with it's submodules, and even the submodules of the submodules.

Open a developer command prompt ie: `x64 Native Tools Command Prompt for VS 2019` (!important)
`cd` into the cloned repo then `code .` to open this repo as a workspace in Visual Studio Code.

`cd` into `deps/simple2d` and run `nmake /f NMakefile all install`
It should build the `simple2d` lib and dll and will be located at `/deps/simple2d/build`

---

If you are running this as a workspace in `Visual Studio Code` you can simply press `F5` to build and run.

If you dont, you're on your own.

---

Great things are in the works! If you're interested in an `SFML` like but simpler and lighter 2D library developed in `C` make sure to `Watch` this repo and my fork of [simple2d](https://github.com/AdlanSADOU/simple2d).
