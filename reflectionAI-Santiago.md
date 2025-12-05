# Reflexión de Santiago Cortés Martínez (A00843691)

## ¿Cómo integré la AI en mi flujo de trabajo?
A lo largo del desarrollo de LexBot fui usando Copilot y Claude como herramientas que me acompañaban, pero nunca como algo que hiciera el trabajo por mí. Desde el principio tuve claro que la AI era para entender mejor, no para que me resolviera las cosas. Mi proceso siempre fue el mismo: primero investigaba, luego probaba mi propia solución y, ya después, preguntaba a la AI para confirmar si iba por buen camino o si había algo que podía mejorar.
Gracias a eso entendí muchísimo mejor cómo implementar el sistema de progreso, el cálculo de rachas y varias cosas más que se pusieron bien complicadas, como trabajar con archivos CSV y manejar bien estructuras como std::vector o std::map. También me ayudó a resolver errores rarísimos de compilación que C++ te arroja sin avisar.

## ¿Qué desarrollé de forma autónoma?
La parte del sistema de control de flujo (App.cpp) fue completamente mía. Yo definí cómo se iban a mover los menús, cómo iba a navegar el usuario y cómo iba a conectar cada parte del sistema. Esa arquitectura la pensé yo desde cero. También programé el módulo de información (Info.cpp) y toda la parte de gestión de la cuenta del usuario. Me puse a investigar organizaciones reales en Monterrey que apoyan a personas con dislexia para construir la base de datos y escribí como 60 ejercicios, la mayoría de comprensión, porque era donde más quería aportar.

## ¿Qué métodos usé para validar el código?
Primero, revisión de código: cada línea que la AI sugería la revisaba y, si no la entendía, la reescribía yo mismo. No dejaba nada pasar “porque sí”. Después de cada cambio grande, corría todo y probaba no solo lo normal, sino también casos raros. ¿Qué pasa si alguien mete texto en lugar de números? ¿Qué pasa si intenta ver estadísticas sin hacer ejercicios? Cosas de ese estilo. Finalmente, cuando trabajé en analytics, revisé todo a mano con datos pequeñitos. Justo por eso descubrí lo del 8000%… porque hice los cálculos yo mismo y vi que algo no cuadraba.

## ¿Qué aprendizajes obtuve?
La enseñanza más importante fue darme cuenta de que la clave está en entender el “por qué” del código, no solo el “cómo”. Cada vez que preguntaba “¿por qué estamos usando esta estructura?” o “¿por qué este método es mejor?”, mi comprensión subía muchísimo más que cuando solo quería resolver algo rápido.
También mejoré un montón en C++, especialmente en C++20. Y aprendí algo que antes no tenía tan claro: diseñar software no es solo técnico, también es creativo. Hacer que todo encaje, que sea mantenible y que el usuario final lo entienda… toma mucho más pensamiento del que imaginaba.

## ¿Qué precauciones y limitaciones identifiqué?
Me puse una regla que me salvó de varios problemas: si Copilot me sugiere algo que no entiendo al 100%, lo borro y lo vuelvo a escribir yo. Eso evitó muchos bugs que hubieran pasado desapercibidos si solo hubiera copiado todo sin pensar. También aprendí que la AI puede dar soluciones que funcionan, pero que no encajan con el contexto. Hubo menús que técnicamente estaban bien, pero que no eran nada intuitivos para usuarios con dislexia, así que tuvimos que simplificarlos muchísimo.
Y algo que noté es que la AI casi nunca piensa en la experiencia del usuario. Nosotros tuvimos que meter pausas, mensajes de confirmación, y detalles que hacen el programa más humano. Eso no te lo sugiere la AI, es algo que lo tienes que ver tú.