# Trabajo Profesional
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
para que funcione todo se muestran en la siguiente imagen.

![alt text](https://gitlab.com/fedemgp/trabajoprofesional/raw/master/common/windows-installation-1.png "Instalación QT")

Como puede verse se necesita:
* Developers and Designers Tools (la instalación base)
* Sources y QtCharts
* Qt Data Visualization
* MSVC 2017 32/64 bits (trae todas las configuraciones de para cmake)

Luego se requiere bajar Visual Studio (2017 o posterior), para
que instale el entorno de desarrollo para C++. 

Finalmente, instalar Cmake y abrir la gui de este.

![alt text](https://gitlab.com/fedemgp/trabajoprofesional/raw/master/common/windows-2.png "Cmake")

Setear las rutas a donde se encuentra el código y a donde se va a buildear el 
ejecutable (dentro de la carpeta del codigo crear una carpeta `build`). Una 
vez seteado esto, darle click a `Configure`, `Generate`y finalmente a 
`Open project`. Cmake abrirá el visual studio, donde podrán ver el projecto.
Hagan click derecho en el nuestra `application` y denle a 
"Establecer como proyecto de inicio". Luego compilen y finalmente denle play.

### Links útiles
* [QT](https://www.qt.io/download)
* [QT tools API and Tools](https://www.qt.io/qt-features-libraries-apis-tools-and-ide/?utm_campaign=Navigation%202019&utm_source=megamenu=)
* [Sublime Text](https://www.sublimetext.com/3)
* [CLion](https://www.jetbrains.com/clion/)
