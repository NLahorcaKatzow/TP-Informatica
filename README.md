
# TP Cinta transportadora


Este trabajo práctico, correspondiente a la asignatura Informática 2, consiste en el desarrollo de un sistema de control para una cinta transportadora utilizando un microcontrolador Atmega128 programado en lenguaje C. El objetivo principal del proyecto es implementar un sistema de clasificación automática de productos según su color.


![Diagrama1](https://github.com/NLahorcaKatzow/TP-Informatica/blob/main/assets/Diagrama05.jpeg)



### Funcionalidad del Sistema
El sistema utiliza sensores TCS3200 que identifican el color de los productos a medida que avanzan por la cinta transportadora. Según el color detectado, el microcontrolador activará mecanismos que desvían los productos hacia contenedores designados para cada color. En caso de ser un color no permitido, este sistema detectara un error, encendiendo un led rojo y designará ese producto en el contenedor de "otros colores".

### Características del Proyecto
#### Detección de Colores: 
Los sensores de color integrados en la cinta transportadora permiten identificar los colores, rojo, verde, amarillo, azul, blanco y negro.
#### Control del Movimiento: 
El microcontrolador gestiona el movimiento de la cinta transportadora, asegurando que los productos avancen de manera controlada y sean clasificados correctamente.
#### Desvío Automático: 
Una vez detectado el color, el sistema activa las entradas de los filtros de productos para redirigirlos a los contenedores designados.


## Authors

- [@NLahorcaKatzow](https://www.github.com/NLahorcaKatzow)


## Features

- Deteccion de 6 colores
- Deteccion de colores no registrados
- Personalización de salidas de contenedores




## Related

Relacionados:

[Datasheet ATmega128](https://www.alldatasheet.com/datasheet-pdf/pdf/56260/ATMEL/ATMEGA128.html),
[Datasheet TCS3200](https://www.alldatasheet.com/datasheet-pdf/pdf/560507/AMSCO/TCS3200.html)

