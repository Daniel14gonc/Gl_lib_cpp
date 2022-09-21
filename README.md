# Librería gl
***
## Introducción
Librería creada desde 0 para renderizar gráficas por computadora,
utilizando C++.

## Construye el proyecto localmente
1. Clona el repositorio usando. `https://github.com/Daniel14gonc/Gl_lib_cpp`.
2. Dentro de la carpeta del proyecto, para poder correr los scripts para correr el proyecto usa `chmod a+x *.sh`.
3. Ejecuta el script de bash `./run.sh`.
3. Entra en la carpeta `build` y ahí estará el archivo .bmp donde verás el resultado de
las gráficas creadas.

## Como ver la tarea de la casa hecha con líneas
1. Después de clonar el repositorio tienes que cambiarte a la branch de house con `git checkout house`.
2. Ahora que estás en la branch house, solo corre `./run.sh` y dentro la carpeta `build` encontrarás la imagen.

## Como ver la tarea de los polígonos
1. Después de clonar el repositorio tienes que cambiarte a la branch de polygons con `git checkout polygons`.
2. Ahora que estás en la branch polygons, solo corre `./run.sh` y dentro la carpeta `build` encontrarás la imagen.

## Como ver la tarea de la carga de .obj
1. Después de clonar el repositorio tienes que cambiarte a la branch de objects con `git checkout objects`.
2. Ahora que estás en la branch polygons, solo corre `./run.sh` y dentro la carpeta `build` encontrarás la imagen.

## Como ver la tarea de la carga de SR4
1. Después de clonar el repositorio tienes que cambiarte a la branch de fill_obj con `git checkout fill_obj`.
2. Ahora que estás en la branch polygons, solo corre `./run.sh`.
2. Dentro la carpeta `build` encontrarás `image.bmp` y `zBuffer.bmp`. La primera imagen es el .obj renderizado y la otra es el zBuffer renderizado.

## Como ver la tarea SR5
1. Después de clonar el repositorio tienes que cambiarte a la branch de textures con `git checkout textures`.
2. Ahora que estás en la branch polygons, solo corre `./run.sh`.
2. Dentro la carpeta `build` encontrarás `image.bmp` y `map.bmp`. La primera imagen es el .obj renderizado y la otra es la textura con polígonos sobre ella.

## Como ver la tarea SR6
1. Después de clonar el repositorio tienes que cambiarte a la branch de matrix con `git checkout matrix`.
2. Ahora que estás en la branch polygons, solo corre `./run.sh`.
2. Dentro la carpeta `build` encontrarás `image.bmp`.
3. Si quieres cambiar la vista de la imagen, ve a `./src/textures.cpp`. Puedes cambiar el argumento de la función load camera para que muestre "medium", "dutch", "low" o "high".

## Como ver el Lab 2.
1. Después de clonar el repositorio tienes que cambiarte a la branch de matrix con `git checkout shader`.
2. Ahora que estás en la branch polygons, solo corre `./run.sh`.
3. Dentro la carpeta `build` encontrarás `image.bmp`.
4. Si quieres ver el .bmp ya renderizado y la imagen de modelo ve a la carpeta `imagenes/`.