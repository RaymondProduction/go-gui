# GO GUI

### Project Overview

This project combines Go and C++ to create a graphical user interface (GUI) application using wxWidgets, a popular C++ library for building cross-platform GUIs. Below is an explanation of the project's functionality.

---

### Overview

1. **Core Idea**:
   - The project uses wxWidgets in C++ to handle the GUI and Go for the main program logic. It demonstrates how to bridge Go and C++ using `cgo`.

2. **Dynamic Library**:
   - A shared library (`libwxinterface.so`) written in C++ exposes functions to:
     - Create a window.
     - Add buttons to the window.
     - Handle callbacks triggered by button presses.
     - Run the wxWidgets event loop.

3. **Callback Mechanism**:
   - The project allows Go code to register functions (callbacks) that will be triggered when GUI buttons are pressed. These callbacks are managed via a global registry in Go and invoked from the wxWidgets C++ code.

---

### Functionality

1. **Window Creation**:
   - The Go code calls the `CreateWindow` function from the C++ library to create a wxWidgets window with specified dimensions and a title.

2. **Button Addition**:
   - The Go program registers a callback function, retrieves a unique callback ID, and passes it along with button properties (position, size, label) to the `AddButton` function in the C++ library.
   - The C++ side binds the button’s click event to the callback and invokes the Go callback when the button is pressed.

3. **Event Loop**:
   - The Go program invokes `RunEventLoop`, which starts the wxWidgets event loop to handle GUI interactions.

4. **Cleanup**:
   - After the event loop ends, the `Cleanup` function is called to release wxWidgets resources.

---

### Applications

- This project demonstrates how to build a custom Go API for creating and managing wxWidgets-based GUIs.
- It can be extended to create more complex GUIs with additional widgets and interactions.

### Command Explanations and linux setup

#### `sudo apt install libwxgtk3.2-dev`
Installs the development library for wxWidgets version 3.2, which includes headers and files required for compiling projects with wxWidgets.

#### `sudo apt install build-essential`
Installs essential tools for compilation, including `gcc`, `g++`, and `make`.

#### `sudo apt install wx-common`
Installs common configuration files for wxWidgets, necessary for the proper functioning of wx tools.

#### `sudo apt search wx`
Used to search for packages related to wxWidgets in the repositories.

#### `g++ -shared -fPIC -o libwxinterface.so wxlib.cpp `wx-config --cxxflags --libs``
Compiles `wxlib.cpp` into a shared library `libwxinterface.so`, using `wx-config` to obtain compiler flags and wxWidgets libraries.

#### `wx-config --cxxflags`
Displays the compiler flags required to include wxWidgets in your project.

#### `export LD_LIBRARY_PATH=$(pwd):$LD_LIBRARY_PATH`
Adds the current directory to the `LD_LIBRARY_PATH` environment variable so that dynamic libraries in it can be found during program execution.

#### `go run main.go`
Compiles and runs your Go code, which uses the created dynamic library `libwxinterface.so`.

---

### macOS Setup

#### Install Dependencies
1. Install wxWidgets:
   ```bash
   brew install wxwidgets
   ```

2. Install GCC (if not already installed):
   ```bash
   brew install gcc
   ```

#### Compile the Shared Library
Use the following command to compile the `wxlib.cpp` file into a shared library (`libwxinterface.dylib`):
```bash
g++ -shared -fPIC -std=c++11 -o libwxinterface.dylib wxlib.cpp $(wx-config --cxxflags --libs)
```

#### Configure the Dynamic Library Path
Add the current directory to the `DYLD_LIBRARY_PATH` so the dynamic library can be found:
```bash
export DYLD_LIBRARY_PATH=$(pwd):$DYLD_LIBRARY_PATH
```

#### Run the Go Code
Execute the Go file:
```bash
go run main.go
```

### Windows Setup with MSYS2 MinGW64

1. Install Dependencies

Update the package manager and install the required tools:

pacman -Syu
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-make

2. Build wxWidgets

Navigate to the wxWidgets build directory and compile the library:

cd wxWidgets-3.2.6/build/msw/
mingw32-make -f makefile.gcc SHARED=1 UNICODE=1 BUILD=release

3. Copy Required DLLs

Copy wxmsw32u_core_gcc_custom.dll from the compiled wxWidgets libraries to the project directory:

cp ./wxWidgets-3.2.6/lib/gcc_dll/wxmsw32u_core_gcc_custom.dll ./


#### Notes:

I have some problems with the SSH agent on Windows, so I need to run the command:
```bash
eval $(ssh-agent -s)
```

