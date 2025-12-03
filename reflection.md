# Reflexión de la mini App - LexBot

## ¿Qué aprendiste sobre el concepto de objetos?

Aprendí que los objetos son cosas que encapsulan datos (atributos) y comportamientos (métodos) de forma coherente. En este proyecto vi cómo:

**Cada clase tiene una responsabilidad única:** *Usuario* maneja autenticación, *Ejercicio* gestiona preguntas, *Progreso* registra estadísticas.
**Los objetos interactúan:** La clase *App* controla las interacciones entre Usuario, Ejercicio y Progreso.
**La reutilización:** En lugar de repetir el mismo código muchas veces, creé métodos que se pueden llamar múltiples veces desde diferentes contextos.
**El estado persiste:** Los objetos mantienen información en memoria y la pueden guardar en archivos para recuperarla después.

**Mantenimiento**: También aprendí que al usar clases es mucho más sencillo darle mantenimiento a la app, sea agregando nuevas cosas o haciendo cambios. Hace que todo se vea más limpio, sea más fácil de entender y leer.

## ¿Qué sugerencias o código te dio Copilot?

Puedo decir que copilot que me ayudo de las siguientes maneras a lo largo del proyecto: 

**Arquitectura y control de flujo:**

Creación de la *clase App* como controladora central que gestiona todos los menús y la navegación del programa con switch-case anidados. Porque en un inicio yo pensaba poner todos esos switch cases en el archivo principal y eso hubiera sido un desastre total a diferencia de cómo realmente quedó.

**Mantenimiento de datos (simulando base de datos):**

- Métodos estáticos en Usuario para *cargar/guardar credenciales en archivos .txt* usando ifstream y ofstream.
- Métodos en Progreso que registran ejercicios completados por usuario en archivos, permitiendo recuperar el historial en futuras sesiones.

**Explicación y mejora continua:**

- *Explicaciones* paso a paso de conceptos como *try-catch, size_t, y CSV vs TXT*.
- *Detección de bugs* (espacios en trim, falta de break; en switch) y correcciones iterativas.
- Validación de entrada con cin.fail() y cin.clear().

## ¿Qué harías diferente si tuvieras más tiempo?
Si hubiera tenido más tiempo para hacer está mini App me hubiera gustado agregar lo siguiente.
- Una base de datos como SQLite, que hace el trabajo mucho más eficiente que guardar la información en un archivo .txt.
- Agregaría una interfaz gráfica al proyecto para que no se viera solamente en la terminal porque tiene mucho más potencial que eso.
- Me gustaría agregar un sistema de reportes, para que el usuario lo pueda exportar en un archivo .pdf.
- Agregar ejercicios más dinámicos para los usuarios.