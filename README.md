# Proyectos Raspberry con C, C++, CMake, vscode plugins, etc

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
- [vscode-cmake-tools/docs](https://github.com/microsoft/vscode-cmake-tools/tree/main/docs)
- [vscode-cmake-tools](https://vector-of-bool.github.io/docs/vscode-cmake-tools/)
- [vscode-cmake-tools/settings](https://vector-of-bool.github.io/docs/vscode-cmake-tools/settings.html)
- [vscode-cmake-tools/debugging](https://vector-of-bool.github.io/docs/vscode-cmake-tools/debugging.html)
- [remote-debugging-with-gdb](https://enes-ozturk.medium.com/remote-debugging-with-gdb-b4b0ca45b8c1)
- [gnutoolchains.com/raspberry/tutorial](https://gnutoolchains.com/raspberry/tutorial/)


## plugins:
[vscode-cmake-tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)
[vscode-cpptools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)

# Estructura de repositorio:

```txt
rpi-projects/
|
|── curl/
|── cmake/
|── toolchain/
|── cross.cmake
|── first-project/
│   ├── .vscode/
│   │   ├── launch.json
│   |   ├── settings.json
│   |   ├── tasks.json
│   ├── CMakeLists.txt
│   ├── src
│       ├── *.c 
|── any_project_you_can_create/
```

La carpeta `first-project` corresponde a un proyecto de `vscode`

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


## Utilizar libreria libcurl

Las siguientes instrucciones para instalar curl en la carpeta toolchain.
Podes optar por la instalacion desde RPI, o directa utilizando la carpeta
`curl` de este repositorio.

### Instalacion desde RPI

1. Para eso es necesario acceder a la raspberry y ejecutar:

`sudo apt install libcurl4-openssl-dev`

Los componentes relevantes son:

- Archivos de encabezado: `/usr/include/arm-linux-gnueabihf/curl`
- Biblioteca estática: `/usr/lib/arm-linux-gnueabihf/libcurl.a`
- Biblioteca compartida (dinámica): `/usr/lib/arm-linux-gnueabihf/libcurl.so`

Podes guiarte del siguiente comando para obtener las rutas en caso de ser distintas:

`dpkg-query -L libcurl4-openssl-dev`

2. Copiado desde origen (RPI) a destino (carpeta toolchain local):

- `/usr/include/arm-linux-gnueabihf/curl` en `toolchain\arm-linux-gnueabihf\sysroot\usr\include\curl`
- `/usr/lib/arm-linux-gnueabihf/{libcurl.a, libcurl.so}` en `toolchain\arm-linux-gnueabihf\sysroot\lib`


### Instalacion "rápida"

Como no pesan muchos los archivos, puse dentro de la carpeta `curl` los archivos necesarios
para usar `curl`:

- `.\curl\curl` en `toolchain\arm-linux-gnueabihf\sysroot\usr\include\curl`
- `.\curl\{libcurl.a, libcurl.so}` en `toolchain\arm-linux-gnueabihf\sysroot\lib`

### `CMakeLists.txt`

Notar que en `CMakeLists.txt` se encuentra la instruccion que se encarga de importar `CURL`:

`find_package(CURL REQUIRED)`