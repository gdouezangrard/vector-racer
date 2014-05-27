# Vector Racer Project

Vector Racer game written in C/SDL.

[Report](doc/main.pdf)

![Vector Racer](./doc/Capture_du_2014-05-27_22-22-04.png?raw=true "Vector Racer")

## Get started

### How to build

Run `cmake ../..` in the `src/build` directory. Then run `make` to build the
whole application, and `make doc` to use *Doxygen* auto-generated
documentation.

- `build/bin` contains binaries compiled from 'src/application',
- `build/doc` contains the doc.

### How to organize the project

- The sources files under 'src/src' uses headers in `src/include` and
  represents a library (e.g. *vectorMap*).
- The `src/examples` directory contains static assets (e.g. maps' files).
- The `src/application` directory contains source files of the application
  (i.e. files with a `main` function), and uses libraries built from `src/src`.
- The `src/doc` directory is used for *Doxygen* configuration.

All is configured with CMakeLists.txt. If you add a `library/application/file`,
you'll need to edit them !

## Libraries summary

* vectorMap
* vectorStep
* vectorDll
* vectorSdl
* vectorGraph
