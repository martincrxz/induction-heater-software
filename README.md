# Trabajo Profesional
## Horno de inducción magnética
### Integrantes
* Martín Cruz García
* Federico Manuel Gomez Peter
* Mariana Szischik

### Requisitos Linux
Para el desarrollo se recomienda usar un de los siguientes 
entornos de desarrollo:

* CLion
* Sublime Text
* QTCreator

#### Cmake
Para compilar se requiere tener instalado la herramienta 
`cmake`:
```commandline
sudo apt-get install cmake
```
#### QT
Se requiere de forma obligatoria, además, tener instalado las
bibliotecas de `QT`:
```commandline
sudo apt-get install qtcreator qt5-default qtdeclarative5-dev
```
#### meld
Para realizar merges se recomienda la herramienta `meld`:
```commandline
sudo apt-get install git meld
```
Para setear como default el meld:
```commandline
git config --global merge.tool meld
git config --global diff.tool meld
```
### Requisitos Windows
Recomiendo instalar primero `git`. Con ese programa clonen el proyecto
de este repositorio. Luego instalen `QTcreator`, que les instala tanto 
compilador como otras herramientas útiles para codear y compilar. 
Cuando lo abran, abran el proyecto de esta carpeta (eligiendo el
archivo `horno.pro`), y antes de compilar, vayan a la sección `project`,
y cambien el path de la carpeta en donde se va a buildear el programa.
Seteen la carpeta de build como `build`.

### Compilación
Se debe crear una carpeta `build` (obligatorio para que no
haya commits espúreos con compilaciones de alguno):

```commandline
mkdir build
cd build
cmake ..
make
```
### Links útiles
* [QT](https://www.qt.io/download)
* [QT tools API and Tools](https://www.qt.io/qt-features-libraries-apis-tools-and-ide/?utm_campaign=Navigation%202019&utm_source=megamenu=)
* [Sublime Text](https://www.sublimetext.com/3)
* [CLion](https://www.jetbrains.com/clion/)
