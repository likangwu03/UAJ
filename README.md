# Nightmare Dogs
### Rushtaurant Secrets

###### Gameplay del juego:
[![Gameplay](https://imgur.com/LPyujLi.png)](https://drive.google.com/file/d/10_YlJI0IKXg_S6E_47FBobYrS6awHKzf/view?usp=sharing)
### [¡Descarga el juego aquí!](https://ucm-fdi-disia.github.io/Nightmare-Dogs/ "Página web")
- [Release del juego](https://github.com/UCM-FDI-DISIA/Nightmare-Dogs/releases/latest "Release del juego")


------------
### Documentación:
- [Enlace al material de las presentaciones](https://drive.google.com/drive/folders/1a7Z0Bc-AFx-a9P5l2t9r2TmYJNg2jmCD?usp=share_linkhttps://drive.google.com/drive/folders/1a7Z0Bc-AFx-a9P5l2t9r2TmYJNg2jmCD?usp=share_link "Enlace al material de las presentaciones")
- (IMAGEN Y EXPLICACIÓN DEL UML)

------------


### GDD:
(Pasar GDD a md)

------------
### QA:
Con el fin de mejorar la jugabilidad, el equipo de desarrollo ha ideado y llevado a cabo un plan de pruebas con usuarios. Tras redactar los parámetros a comprobar, algunos miembros del equipo han seguido las pautas ingeniadas, examinando así a potenciales clientes. A lo largo de este proceso se han notificado multitud de detalles y problemas en los que los integrantes del grupo no habían reparado. Para arreglar esto, se redactaron los errores y contratiempos y se propusieron nuevas soluciones para mejorar el desarrollo del proyecto. Poco a poco, todo se ha ido ajustando. Se presenta a continuación la documentación pertinente.

En primer lugar, el plan de pruebas que se ha seguido para evaluar la jugabilidad con usuarios reales:
- Preguntas de control
    - Edad (Respuesta redactable)
    - ¿Cuánta experiencia tiene el usuario en los juegos de gestión y recursos? (Posibles respuestas: ninguna, normal, mucha)
- ¿Entiende bien las siguientes mecánicas? (Posibles respuestas en cada apartado: sí, no, no probado)
    - Añadir ingrediente a la cesta	
    - Quitar ingrediente de la cesta	
    - Pagar ingredientes	
    - Escoger ingredientes de la isla	
    - Devolver ingredientes a la isla	
    - Cocinar	
    - Asignar al cliente	
    - Atender a un cliente	
    - Servir plato al cliente	
    - Tirar plato	
    - Pedir otro plato	
    - Cobrar	
    - Limpiar mesa	
    - Pasar de restaurante a despensa	
    - Ahuyentar el ladrón	
    - Matar al ladrón
- Si ha habido confusión o dificultad en alguna de las mecánicas anteriores indica cuál y por qué razón (Respuesta redactable)
- Observaciones respecto al menú diario (Posibles respuestas en cada apartado: sí, no)
    - ¿Ha estado atento al menú del día mientras hacía compras? 	
    - ¿Ha comprado ingredientes que no estén en este?	
    - ¿Ha prestado atención al precio de la cesta respecto del dinero que tiene? (ha estado ajustando cantidad de ingredientes a comprar)	
    - ¿Ha estado atento al menú del día mientras cocinaba?	
    - ¿Ha intentado cocinar platos justo los que pedían los clientes?
- Rellenar: "Cantidad de grupos de clientes cobrados"/"Total de grupos de clientes que han llegado al restaurante" (Respuesta comparando dos valores)
- ¿Ha conseguido el usuario el objetivo del día en el primer día? (Posibles respuestas: sí, no)
- En el caso de no haber conseguido el objetivo del día, indicar la cantidad que le ha faltado por superar (Posibles respuestas: <20, 20-80, >80)
- ¿Cuántos días ha sobrevivido? (Respuesta numérica)
- ¿Por qué motivos perdió la partida? (Multirespuesta)
    - No alcanzó el objetivo del día
    - La reputación llegó a 0
    - Los ladrones llegaron a la fórmula secreta/nevera
    - Otro: (Respuesta redactable)
- ¿Se nota que al usuario cada día le cueste más gestionar el restaurante? (Posibles respuestas: sí, no)
- En el caso de que le haya costado más gestionar, preguntar al usuario qué parte es más difícil o molesta (Multirespuesta)
    - La frecuencia con que vienen los clientes
    - El tiempo de espera del cliente es demasiado corto
    - La frecuencia con que vienen los ladrones
    - Otro: (Respuesta redactable)
- ¿Al usuario le ha costado o le ha resultado confuso en algún momento reconocer el ingrediente por su tamaño? Indicar dónde (Multirespuesta)
    - Los carteles
    - Menú del día
    - Icono encima de la cocina
    - Plato que pide el cliente
    - Teclas que aparecen sobre los ladrones
    - Otro: (Respuesta redactable)
- ¿El usuario ha mostrado disgusto o estrés en algún momento? ¿Por qué motivo? (Respuesta redactable)
- Otros comentarios (Respuesta redactable)

A continuación se presenta una tabla con las conclusiones extraídas a partir de las pruebas, así como las soluciones propuestas para mejorar el juego.

| Tipo de conclusión | Conclusiones | Soluciones |
|--------------------|--------------|------------|
| Confusiones        | - No sabe con qué controles se elige el menú del día | Mostrar el input en el juego |
|                    | - Botones para matar/ahuyentar ladrones | Mostrar el dibujo junto con el input |
|                    | - No sabe con qué tecla se abre la cesta  | Mostrar el input en el juego |
|                    | - Resulta confusa la combinación de controles de enter y space | Mostrar en pantalla cuándo se necesita pulsar enter   |
|                    | - Vaciar el inventario de ingredientes en cocina es poco intuitivo | Mostrar en pantalla la capacidad de poder vaciar el inventario |
|                    | - La mecánica de pagar en el supermercado no es suficientemente intuitiva  | Mejorar la interfaz   |
|                    | - La mecánica de rachas resulta confusa  | Mejorar la claridad visual para indicar que se recibe más dinero |
|                    | - No se sabe que se puede consultar el menú diario  | Mostrar el input sobre el icono |
|                    | - Resulta confusa la mecánica de cocinar, el usuario cree que hay varias formas de hacerlo  | Añadir tutorial en página web |
|                    | - No sabe cuando usar espacio y cuando usar enter  | Mostrar en pantalla cuándo se necesita pulsar enter |
|                    | - Resulta confusa la interacción con el cliente para tomarle nota   | Aumetar un poco el tamaño del trigger para que sea más sencillo de interactuar |
|                    | - El usuario ha tenido problemas al interactuar con las mesas para tomar nota y servir platos  | Ajustar el trigger de las mesas |
|                    | - El usuario confunde cocinar con cambiar de plato  | Añadir tutorial en página web |
|Balance             | - Desequilibrio entre gestión de cocina y ladrones (llegada de ladrones y de clientes es demasiado frecuente   | Disminur la frecuencia de los ladrones y la probabilidad de que llegue un grupo grande de clientes |
|                    | - El tiempo del día pasa muy rápido  | Aumentar la duración del día  |
|   Bugs             | - Triggers desajustados en el supermercado | Ajustar triggers   |
|                    | - Trigger desajustados de las mesas  | Ajustar trigger de las mesas |
|                    | - No se pueden añadir ingredientes a la cesta  | Revisar y arreglar código |