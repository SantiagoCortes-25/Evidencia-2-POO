# Reflexión de Oscar André Galicia Anduaga (A01724046)

## ¿Cómo utilicé la IA en el proyecto?
Mi uso de AI fue siempre  controlado y la mayoría del tiempo primero intentaba resolver todo por mi cuenta y solo cuando me atoraba con conceptos técnicos o matemáticos más complicados, la usaba para aclarar ideas o validar lo que ya había hecho. Me ayudó mucho para entender el algoritmo que usamos para detectar las áreas de oportunidad, el sistema de recomendación adaptativa, el uso eficiente de string_view para leer CSV y la implementación correcta de enum class para clasificar los ejercicios y los niveles de dificultad, pero siempre como apoyo para comprender.

## ¿Qué componentes desarrollé sin ayuda de IA?
El motor de ejercicios (Ejercicio.cpp) lo desarrollé por mi cuenta, tanto la lógica de selección aleatoria cómo validar respuestas e integrar los distintos tipos de ejercicios, usando principalmente  mis conocimientos previos. También fui quien creó el sistema de migración de archivos .txt a CSV, cosa que hizo que tuviera que repensar toda la parte de persistencia de datos, y además aporté alrededor de 80 ejercicios para la base de datos.

## ¿Cómo aseguré la calidad del código?
Para asegurar la calidad del código lo que hacía era que cada vez que la IA me explicaba un algoritmo, construía mis propios casos de prueba con datos que podía calcular a mano para confirmar que los resultados del programa fueran correctos. Un ejemplo de esto fue con la regresión lineal, donde comparé los valores generados con cálculos hechos por mí. Además compilaba constantemente para poder detectar errores rápido, y probé escenarios como usuarios sin sesiones o con una sola, lo que ayudó a encontrar y corregir bugs antes de que afectaran al sistema.

## ¿Qué conocimientos adquirí?
Aprendí muchísimo sobre algoritmos de análisis de datos y su aplicación práctica, pasando de no saber nada de la regresión lineal a poder implementarla y explicarla. Con este proyecto también profundicé varias características de C++20 que antes solo entendía superficialmente. Algo importante que descubrí fue que la IA nos ayuda a acelerar el aprendizaje cuando la usas para entender y no para copiar, porque al pedir explicaciones en lugar de código entendía mucho mejor, ya que era como un tutor personal.

## ¿Qué desafíos y riesgos observé?
El mayor reto fue no usar la IA luego luego cuando me frustraba, porque aunque hubiera sido más fácil copiar código, sabía que eso no me ayudaba a aprender. También me di cuenta que la IA no siempre considera las limitaciones reales del entorno, como cuando sugirió usar caracteres Unicode que causaban problemas en la terminal de Windows y tuvimos que reemplazar por ASCII, o algoritmos que eran correctos pero poco eficientes para lo que necesitábamos, lo que me enseñó a no confiar ciegamente en sus sugerencias.