
## Raspberry

- Testeado en Raspberry 3 B
Requisitos en raspberry:
    - SO raspbian
    - apt install gdbserver

### version de Raspbian
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
[1](https://github.com/microsoft/vscode-cmake-tools/tree/main/docs)
[2](https://vector-of-bool.github.io/docs/vscode-cmake-tools/)
[3](https://vector-of-bool.github.io/docs/vscode-cmake-tools/settings.html)
[4](https://vector-of-bool.github.io/docs/vscode-cmake-tools/debugging.html)
[5](https://enes-ozturk.medium.com/remote-debugging-with-gdb-b4b0ca45b8c1)
[6](https://gnutoolchains.com/raspberry/tutorial/)


## plugins:
[vscode-cmake-tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)
[vscode-cpptools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)

# Estructura de repositorio:


```txt
rpi-projects/
|
|── cmake/
|── toolchain/
|── cross.cmake
|── first-project/        <-- a vscode project
|── any_project_you_can_create/
```

## Cmake
Descargar zip (windows) de https://cmake.org/download/
descomprimir contenido como carpeta llamada `cmake`

### version de Cmake:
cmake-3.27.1-windows-x86_64

## Toolchain
https://gnutoolchains.com/raspberry/

descargue raspberry-gcc10.2.1-r2.exe (408 MB)

## debugear

TODO: agregar imagenes


# Compilar y copiar todos los ejecutables en destino

TODO: agregar imagenes

1. ejecutar la tarea "CMake: build & copy all"

2. ctrl shift p, escribir -> Tasks: Run Task

3. Buscar dicha tarea
