# Cubo de Rubik en OpenGL y Resolucion Mediante el Método Fridrich (CFOP)

## Introducción
Proyecto universitario de Computación Gráfica con OpenGL. El objetivo de este proyecto es crear y resolver un cubo de Rubik mediante el modelado, rendering y animación mediante la utilización del IDE Visual Studio 2019 y la API OpenGL, dando lugar a la utilización de nuestra placa gráfica de nuestra máquina personal. Este proyecto también se concentra en resolver el cubo de Rubik mediante el método Fridrich (CFOP) disponible en GitHub. Daremos a conocer puntos claves de nuestro proyecto como: Estructura, Transformaciones y Método de Fridrich.

![screenshot](https://github.com/RenzoAlessandro/Cubo-Rubik-OpenGL/blob/main/CubeRubik.gif)

- Video - https://youtu.be/1f8bpXxjI98

## Instalación
1. Clonar este repositorio e importarlo al proyecto base - **Visual Studio 2019**
2. Modificar los PATH de los archivos **main.cpp** y **Rubik.h**.

## Creditos 
Este proyecto es programado por:
* [Renzo Alessandro Sucari Velasquez](https://github.com/RenzoAlessandro)
* [Karen Alejandra Fernandez Fernandez Davila](https://github.com/RenzoAlessandro)

Docente: 
* [Manuel Eduardo Loaiza Fernández]

## Contribución
1. Modelado, renderizado y animacion del Cubo de Rubik.
2. Creación del window, shaders, texturas, etc.
3. Programacion del Grafo de Escena (Face, Cube, Rubik).
3. Incorporación del solver Método Fridrich (CFOP).
4. Uso de **glfwGetKey** para diferentes animaciones.

## Uso
### Keyboard
#### Menú
* 'I' - Desordenar el Cubo de Rubik.
* 'O' - Ordenar el Cubo de Rubik.
* 'G' - Visualización 306 del Cubo.
* 'Esc' - Quit.
#### Camara WALK AROUND
* 'W' - Adelante
* 'A' - Izquierda
* 'D' - Derecha
* 'S' - Atras
#### Movimientos del Cubo
* '1' - FRONT 
* '2' - RIGTH
* '3' - UP  
* '4' - LEFT 
* '5' - BACK 
* '6' - DOWN 
#### Propuesta de Animiación
* 'B' - Separacion o Unión del Cubo.
* 'N' - Modos de visualización (27 cubos, centros, vertices, aristas).
* 'M' - Modos de rasterización de poligono.
