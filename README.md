https://gnutoolchains.com/raspberry/

descargue raspberry-gcc10.2.1-r2.exe (408 MB)

https://gnutoolchains.com/raspberry/tutorial/

installe en rpi: gdbserver

# version de Cmake

cmake-3.27.1-windows-x86_64

# RPI 3 b

# version de Raspbian
```
cat /etc/os-release

PRETTY_NAME="Raspbian GNU/Linux 11 (bullseye)"
NAME="Raspbian GNU/Linux"
VERSION_ID="11"
VERSION="11 (bullseye)"
VERSION_CODENAME=bullseye
ID=raspbian
ID_LIKE=debian
HOME_URL="http://www.raspbian.org/"
SUPPORT_URL="http://www.raspbian.org/RaspbianForums"
BUG_REPORT_URL="http://www.raspbian.org/RaspbianBugs"
```

## urls de utilidad:
https://github.com/microsoft/vscode-cmake-tools/tree/main/docs
https://vector-of-bool.github.io/docs/vscode-cmake-tools/
https://vector-of-bool.github.io/docs/vscode-cmake-tools/settings.html
https://vector-of-bool.github.io/docs/vscode-cmake-tools/debugging.html
https://enes-ozturk.medium.com/remote-debugging-with-gdb-b4b0ca45b8c1


plugins:
CMake Tools

Pasos:

en la carpeta padre del proyecto (workspaceFolder) se encuentran las carpetas:

-cmake
-toolchain

# Estructura:

```
rpi-projects/
|
|--> cmake/
|--> toolchain/
|--> cross.cmake
|--> first-project/        <-- a vscode project
|--> any_project_you_can_create/
```

Crear un archivo boo.c

agregar en CMakeLists.txt:

add_executable_custom(boo.c)


para debugear, ir al archivo, y debugear con (gdb) Launch



para compilar y copiar todos los ejecutables en destino

ejecutar la tarea "CMake: build & copy all"

ctrl shift p, escribir -> Tasks: Run Task

y buscar dicha tarea
