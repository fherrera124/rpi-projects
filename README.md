# Proyectos Raspberry with toolchains

## Motivo
La idea surgió de querer poder realizar proyectos tanto en C como en C++ en mi Raspberry
para aprender más sobre librerias POSIX de Linux, aprender C++, de Cmake, etc.
Como actualmente utilizo VsCode en windows, me puse a investigar como sería
posible realizar `crosscompiling`. Pero sin dejar de lado la posibilidad de debugear de manera
sencilla y casi instantánea cualquier porgrama que realizace. Me encontré que vscode
tiene buen coporte para ello mediante el uso de configuraciones en archivos json y plugins
que se pueden instalar. Me llevó un par de días lograr lo que específicamente yo buscaba.

## Lo que yo buscaba
1. Lo primero: quería poder realizar un programa, y que mediante un "click" se compilase el archivo
actual, suba mediante ssh/scp, levantar `gdbserver` en la raspberry, y que localmente
en vscode, poder debugear el programa tranquilamente.
2. Lo segundo: también quería, en caso de no especificar ningun programa en particular,
que todos los programas se compilaran y se subieran todos a mi raspberry y nada más.

## Sobre mi Raspberry

### Version de mi Raspberry
- version 3 B.

### Version de Raspbian:
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

### Dependencias:

- `gdbserver (sudo apt install gdbserver)`

## SO
- Windows 11 (luego intentare desde una pc con linux)

## Cmake
- La version que descargué es la `cmake-3.27.1-windows-x86_64`. Descargué el [zip](https://github.com/Kitware/CMake/releases/download/v3.27.1/cmake-3.27.1-windows-x86_64.zip) de https://cmake.org/download/ y
descomprimir contenido como carpeta llamada `cmake`
- Me quedó asi:
```txt
cmake
|── bin
|── doc
|── main
|── share

```

## Toolchain
https://gnutoolchains.com/raspberry/

descargue raspberry-gcc10.2.1-r2.exe (408 MB). Te deja seleccionar la carpeta destino de instalacion.
- Me quedó asi:
```txt
toolchain
|── arm-linux-gnueabihf/
|── bin/
|── include/
|── lib/
|── libexec/
|── share/
|── x86_64-w64-mingw32/
|── ... otros archivos
```

## Vscode:
- Es esencial instalar [Visual Studio Code](https://code.visualstudio.com/download)
Plugins necesarios:
- [vscode-cmake-tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)
- [vscode-cpptools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)

## Estructura de este repositorio:

```txt
rpi-projects/
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

## urls de utilidad:
- [vscode-cmake-tools/docs](https://github.com/microsoft/vscode-cmake-tools/tree/main/docs)
- [vscode-cmake-tools](https://vector-of-bool.github.io/docs/vscode-cmake-tools/)
- [vscode-cmake-tools/settings](https://vector-of-bool.github.io/docs/vscode-cmake-tools/settings.html)
- [vscode-cmake-tools/debugging](https://vector-of-bool.github.io/docs/vscode-cmake-tools/debugging.html)
- [remote-debugging-with-gdb](https://enes-ozturk.medium.com/remote-debugging-with-gdb-b4b0ca45b8c1)
- [gnutoolchains.com/raspberry/tutorial](https://gnutoolchains.com/raspberry/tutorial/)