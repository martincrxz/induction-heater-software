# Trabajo Profesional
## Horno de inducción magnética
### Integrantes
* Martín Cruz García
* Federico Manuel Gomez Peter
* Mariana Szischik

### Requisitos
Para el desarrollo se recomienda usar un de los siguientes 
entornos de desarrollo:

* CLion
* Sublime Text
* QTCreator

Para compilar se requiere tener instalado la herramienta 
`cmake`:
```commandline
sudo apt-get install cmake
```

Se requiere de forma obligatoria, además, tener instalado las
bibliotecas de `QT`:
```commandline
sudo apt-get install qt5-default qt-declarative5-dev
```

Para realizar merges se recomienda la herramienta `meld`:
```commandline
sudo apt-get install git meld
```
Para setear como default el meld:
```commandline
git config --global merge.tool meld
git config --global diff.tool meld
```

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
