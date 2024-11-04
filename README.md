# Monitor T&H (Temperatura y Humedad)
En esta práctica, ocupamos el sensor de temperatura y humedad DHT11 y una simulación de un programa con el que el usuario puede interactuar a través de 3 pulsadores y una pantalla LCD16x2

Existen 5 modos en el programa
> - Temperatura
> - Humedad
> - Índice de Calor
> - Humidificador
> - Ventilador

Los últimos 2 modos permiten activar o desactivar una carga correspondiente a la que se indica (Es necesario el uso de un relevador o un arreglo de transistores Darlington (ULN2003/ULN2803) para no sobrecargar el Arduino)
El humidificador y el ventilador se activan automáticamente dependiendo del nivel de humedad y temperatura respectivamente.

# Advertencia
Soy consciente de que en este código lleve a cabo malas prácticas y la repetición no necesaria. Esto debido a que programar en Arduino es algo jodido y lo que más me afectó a la hora de hacer esto es la dificultad de crear tareas asíncronas y multihilos en Arduino
El diagrama esquemático no está disponible por el momento porque no hay software accesible, mientras tanto revise la imagen del montaje físico.
