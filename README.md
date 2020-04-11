# Trabajo Profesional
# Hola dani
## Horno de inducción magnética
### Integrantes
* Martín Cruz García
* Federico Manuel Gomez Peter
* Mariana Szischik

### Requisitos
Para el desarrollo del siguiente trabajo es indispensable contar con las
siguientes herramientas:

* Git
* Compilador (ver sección correspondiente)
* Cmake
* Qt (en versión 5.9 o superior)
En particular se requieren las bibliotecas:
* Qt5 core
* Qt5 charts
* Qt5 serial-port

Se recomienda además contar con un editor de texto o IDE para poder editar
el código. Los recomendados son (todos multiplataforma, disponible para todos
los sistemas operativos)

* CLion
* Sublime Text
* QTCreator

#### Linux
La instalación de todos estos componentes es trivial

```
sudo apt-get install cmake qtcreator qt5-default qtdeclarative5-dev
sudo apt-get install libqt5charts5-dev
```

##### meld (opcional)
Para realizar merges se recomienda la herramienta `meld`:
```commandline
sudo apt-get install git meld
```
Para setear como default el meld:
```commandline
git config --global merge.tool meld
git config --global diff.tool meld
```

Para compilar, ubicarse en el directorio donde se encuentra el código 
con una terminal y escribir los siguientes comandos.

```commandline
mkdir build # Crea una carpeta llamada build, si ya existe, saltearse esto
cd build
cmake ..
make
```
#### Windows
Recomiendo instalar primero `git`. Con ese programa clonen el proyecto
de este repositorio. Luego instalen `QTcreator`. Los elementos necesarios
para que funcione todo son:

- Qt 5.14.1/MinGW7.3.0 32-bit
- Qt 5.14.1/Qt Charts
- Developers and Designers Tools/MinGW7.3.0 32-bit
- Developers and Designers Tools/Qt Installer Framework 3.2

Opcionalmente se pueden instalar:
- Qt 5.14.1/MinGW7.3.0 64-bit
- Developers and Designers Tools/CMake 3.16.0 32 y/o 64-bit
- Developers and Designers Tools/MinGW7.3.0 64-bit
- Developers and Designers Tools/Qt Creator 4.11.1 CDB Debugger Support
- Developers and Designers Tools/Debugging  Tools for Windows

##### Importante!!

Si instala otras versiones de Qt o de alguno de sus componentes, revisar y modificar el script de 
compilación `deploy-installer.bat`

Ejecutar dicho script, este compilará y generará un instalador `horno-induccion-installer.exe`. Una vez generado, instalar el programa, y usarlo libremente.

### Links útiles
* [QT](https://www.qt.io/download)
* [QT tools API and Tools](https://www.qt.io/qt-features-libraries-apis-tools-and-ide/?utm_campaign=Navigation%202019&utm_source=megamenu=)
* [Sublime Text](https://www.sublimetext.com/3)
* [CLion](https://www.jetbrains.com/clion/)
