# Nightmare Dogs
### Rushtaurant Secrets

###### Gameplay del juego:
[![Gameplay](https://imgur.com/LPyujLi.png)](https://drive.google.com/file/d/10_YlJI0IKXg_S6E_47FBobYrS6awHKzf/view?usp=sharing)
### [¡Descarga el juego aquí!](https://ucm-fdi-disia.github.io/Nightmare-Dogs/ "Página web")
- [Release del juego](https://github.com/UCM-FDI-DISIA/Nightmare-Dogs/releases/latest "Release del juego")


------------
### Documentación:
- [Enlace al material de las presentaciones](https://drive.google.com/drive/folders/1a7Z0Bc-AFx-a9P5l2t9r2TmYJNg2jmCD?usp=share_linkhttps://drive.google.com/drive/folders/1a7Z0Bc-AFx-a9P5l2t9r2TmYJNg2jmCD?usp=share_link "Enlace al material de las presentaciones")
- **UML**  
![UML](/documents/UML.png "Clicando se redireccion a una página donde hacer zoom")  
Hay muchos componentes que tienen conexiones con SDLUtils, InputHandler y Transform, por lo tanto, no se han indicado sus conexiones con los mismos.

------------


### GDD:

#### <ins>ÍNDICE</ins>
1. [**Ficha técnica**](#id1)
2. [**Descripción**](#id2)
3. [**Jugabilidad**](#id3)
    1. [Cámara](#id4)
    2. [Mecánicas del jugador](#id5)
    3. [Mecánicas del cliente](#id6)
    4. [Mecánicas del ladrón](#id7)
    5. [Mecáncias de escenario y objetos](#id8)
        1. [Restaurante](#id9)
        2. [Despensa](#id10)
        3. [Supermercado](#id10)
    6. [Ingredientes](#id11)
    7. [Recetas](#id12)
4. [**Diseño de las escenas**](#id13)
    1. [Restaurante](#id14)
    2. [Despensa](#id15)
    3. [Supermercado](#id16)
5. [**HUD**](#id17)
    1. [Mockup del HUD](#id18)
    3. [Explicación de los elementos del HUD y su funcionamiento](#id19)
6. [**Visual/Estética**](#id20)
7. [**Menús y flujo de juego**](#id21)
8. [**Contenido**](#id22)
    1. [Historia y personaje principal](#id23)
    2. [Resumen de cada día](#id24)
    3. [Finales](#id25)
9. [**Referencias**](#id26)
    1. [Videojuegos](#id27)
    2. [Assets](#id28)

#### 1. Ficha técnica <a name="id1"></a>
**Título:** RushTaurant Secrets  
**Género:** Gestión de tiempo y recursos, cocina  
**Target:** Jugador casual  
**Rating:** Pegi 12  
**Plataforma:** PC  
**Modos de juego:** Un jugador, multijugador en línea

#### 2. Descripción <a name="id2"></a>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;El juego es un simulador de cocina con gestión de tiempo y recursos en 2D. Se juega desde una perspectiva “falso top-down” y se controla a un personaje en tercera persona.  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;El objetivo del juego será gestionar un restaurante, intentando ganar la máxima cantidad de dinero posible para poder seguir comprando ingredientes. Para ello, será necesario atender a los clientes que van llegando al local, colocándolos en mesas libres, tomando nota de sus pedidos, sirviéndoles, y cobrándoles. Sin embargo, además de lidiar con los clientes, el jugador también tendrá que hacerse cargo de ladrones, que intentarán robarle y que irán poco a poco acabando con su paciencia.

3. #### Jugabilidad <a name="id3"></a>
    1. ##### Cámara <a name="id4"></a>
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;En todo momento, la cámara permite ver el escenario en una perspectiva top-down, mostrando el escenario en su totalidad. Está colocada en un punto fijo y no se moverá ni seguirá al jugador.
       
    2. ##### Mecánicas del jugador <a name="id5"></a>
       | Mecánica | Descripción | Input<br>(Teclado,<br>Xbox,<br>PlayStation) | Escena |
       |:---:|:---:|:---:|:---:|
       | ***Desplazamiento*** | Desde una posición de reposo, el personaje comienza se mueve por el escenario, cambiando su sprite según la dirección en la que se          esté moviendo. | WASD<br>Joystick izquierdo | Restaurante<br>Supermercado<br>Despensa |
       | ***Abrir/Cerrar menú de compras***   | Estando en la casilla contigua al ingrediente que se desea comprar, cuando se pulsa el botón oportuno, se abre o se          cierra el menú de compra. Al alejarse de dicha casilla, también se cierra automáticamente. | SPACE<br>Botón A<br>Equis | Supermercado |
       | ***Decidir cantidad a añadir a la cesta***   | Estando el menú de compras abierto, se puede disminuir o aumentar la cantidad a comprar. Si se decide la            cantidad a 0, se quita directamente de la cesta. | FLECHAS<br>LS/RS<br>L1/R1 | Supermercado |
       | ***Añadir a la cesta*** | Estando el menú de compras abierto,se puede añadir a la cesta con la cantidad decidida. | ENTER<br>Botón B<br>Círculo |                  Supermercado |
       | ***Abrir cesta*** | Se abre un menú que indica los ingredientes que hay en la cesta y su cantidad. | Z<br>Botón Y<br>Triángulo | Supermercado |
       | ***Pagar*** | Mismo menú de la cesta con la opción de pagar. Aparece al salir del supermercado. Tras esta acción se gasta el dinero y se reciben los                ingredientes. | SPACE<br>Botón B<br>Círculo | Supermercado |
       | ***Asignar mesa a un cliente*** | Se le asigna una mesa aleatoria de las mesas ocupables al grupo de clientes de la cola con el que se interactúa. Todas las        mesas son de cuatro personas. | SPACE<br>Botón B<br>Círculo | Restaurante |
       | ***Atender a un cliente*** | Cuando el grupo de clientes se haya sentado en la mesa, se podrá interactuar con cada cliente para tomar nota de su pedido.            Dicho pedido se mostrará en una nube encima de su cabeza. | SPACE<br>Botón B<br>Círculo | Restaurante |
       | ***Juntar ingredientes*** | Al interactuar con un ingrediente, aparecerá un indicador con los ingredientes que ha ido recogiendo. Si se intentan coger más          ingredientes de los que pueden llevar, la acción no tendrá efecto. | SPACE<br>Botón B<br>Círculo | Restaurante |
       | ***Devolver ingredientes*** | Si el jugador ha cogido algún ingrediente, los devuelve a su lugar uno a uno desde el último elegido hasta el primero, o todos        de golpe dependiendo del botón pulsado. Dichos ingredientes no se perderán. Al salir de la zona de cocina, se devolverán todos de golpe. | X<br>Botón                A<br>Equis | Restaurante |
       | ***Cocinar*** | Al interactuar con un horno, se consumen los ingredientes recogidos para crear un plato. El proceso tarda unos segundos, indicados por el          icono de un reloj. Si no hay ingredientes recogido o los ingredientes no coinciden con la receta (tanto en número como el tipo de ingredientes, sin importar          el orden), no tiene efecto. | SPACE<br>Botón B<br>Círculo | Restaurante |
       | ***Coger un plato*** | Al interactuar con un horno en el que se haya terminado de cocinar un plato, se añadirá dicho plato al inventario del jugador. El            inventario dispone de cuatro espacios. Si está lleno, la acción no tendrá efecto. | SPACE<br>Botón B<br>Círculo | Restaurante |
       | ***Seleccionar plato*** | Se elige en el inventario el plato a servir/desechar. | FLECHAS<br>LS/RS<br>L1/R1 | Restaurante |
       | ***Servir*** | Al interactuar con una mesa ocupada, se sirve el plato seleccionado y desaparece del inventario del jugador. Si se selecciona uno erróneo o          no se dispone de ninguno en el inventario, la acción no tendrá efecto. | SPACE<br>Botón B<br>Círculo | Restaurante |
       | ***Cobrar*** | Al interactuar con la caja, se cobra a todas las personas que hay en la cola esperando para pagar, aumentando la cantidad de dinero del              jugador. Si se cobra a varias personas a la vez, se hace una racha y se obtiene más dinero. Además, se obtiene una cantidad de reputación por cada cliente            dependiendo de los corazones que tenga. | SPACE<br>Botón B<br>Círculo | Restaurante |
       | ***Ahuyentar o matar a un ladrón*** | Cada cierto tiempo aparece un intruso en la despensa para robar la fórmula secreta (si el jugador se encuentra en la          cocina, se le notifica con una exclamación). El jugador tendrá que entrar en la despensa, acercarse al ladrón y decidir si matarlo y usar su carne, o                ahuyentarlo. Dependiendo de la opción que elija se desbloquearán determinados finales. Si elige matarlo, algunos ladrones tratarán de abrir la nevera y otros        de robar la fórmula secreta. | Q/E<br>Botón A / B<br>Equis /Círculo | Despensa |
       | ***Limpiar mesa*** | Después de que un grupo de clientes haya abandonado la mesa, esta se manchará. El jugador debe acercarse y limpiarla para que otro            grupo se pueda sentar en ella. | SPACE<br>Botón B<br>Círculo | Restaurante |
       | ***Indicar al cliente de que no se dispone del plato que ha pedido en carta*** | El jugador puede acercarse a un cliente e indicarle que el plato que ha            pedido ya no está disponible en la carta. La primera vez el cliente escogerá otro plato del menú del día y se perderá una pequeña cantidad de reputación. Si          se le vuelve a indicar que el plato que ha elegido tampoco está disponible, el cliente se marchará del restaurante y se perderá más reputación (no pedirá dos        veces seguidas el mismo plato). | C<br>Botón A<br>Equis | Restaurante |
       | ***Acceder a la despensa*** | El jugador, al acercarse a la puerta de la despensa, puede teclear el botón correspondiente y acceder a ella. | SPACE<br>Botón        B<br>Círculo | Restaurante |
       
    3. ##### Mecánicas del jugador <a name="id6"></a>
       | Nombre | Descripción |
       |:---:|:---:|
       | **Esperar en la cola** | Los clientes van llegando al restaurante en grupos de 1 a 4, siendo más probable que lleguen grupos de menos clientes. Al llegar,          esperarán en la cola hasta que se le acerque el jugador e interactúe con ell grupo. |
       | **Sentarse en una mesa** | Tras interactuar con el grupo de clientes, estos caminarán hasta la mesa siguiendo un camino predeterminado. |
       | **Pedir comida** | Después de haberse sentado en la mesa, a los clientes les aparecerá una interrogación encima de su cabeza para indicar que desean pedir          comida. |
       | **Pagar comida** | Cuando hayan terminado de comer todas las personas que hay sentadas en una mesa, se acercarán a la caja para pagar la cuenta. Siempre se        realiza un solo pago, independientemente de si se trata de una sola persona o de un grupo. |
       | **Sistema de felicidad** | Desde que un cliente llega al restaurante hasta que sale, el tiempo que pase sin ser atendido irá disminuyendo su felicidad. Si          pierde toda la felicidad, se irá del restaurante sin pagar. Además, si no se le ha servido, bajará la reputación del restaurante. En el caso de que fuera un          grupo, valdría con que solo uno se marchara del restaurante para que el resto también lo hiciera. El nivel de felicidad del cliente se muestra con un número          de corazones encima. |
       
    4. ##### Mecánicas del ladrón <a name="id7"></a>
       | Nombre | Descripción |
       |:---:|:---:|
       | **Acceder a la despensa** | Cada cierto tiempo a partir del s  egundo día aparecerá un ladrón en la despensa. Si el jugador decide matar al ladrón, al día            siguiente se dispondrá de un nuevo ingrediente, la carne especial, cuya cantidad dependerá del número de ladrones a los que haya matado el jugador. |
       | **Robar la fórmula** | El ladrón en la despensa intentará robar la fórmula secreta. Si lo consigue el jugador perderá y se mostrará el final “**BAD ENDING          4**”. |
       | **Localizar cadáver** | En caso de que se haya asesinado a un ladrón en un día anterior, algunos de los nuevos ladrones tratarán de acceder al congelador          para encontrar los cuerpos de sus compañeros y llamar a la policía. El congelador se encuentra más próximo a la puerta por donde se cuelan, por lo que es más        rápido llegar a él. Si alguno lo consigue se cargará el final “**BAD ENDING 3**”. Sin embargo, no es incompatible con que traten de buscar la fórmula secreta.        Unos irán hasta donde se encuentra la misma y otros hasta el congelador. |
    5. ##### Mecánicas de escenario y objetos <a name="id8"></a>
        1. ###### Restaurante <a name="id9"></a>
           | Nombre | Descripción | Imagen | Funcionamiento/Comportamiento en el escenario |
           |:---:|:---:|:---:|:---:|
           | **Menú del día** | Selección de platos que pueden pedir los clientes cada día | ![daily_menu](/RushTaurantSecrets/assets/Images/UI/dailymenu.png) | Al inicio del día, el jugador debe elegir un menú del día entre los dos disponibles. Cada uno está formado por cuatro recetas. En el caso de que el jugador mate a un ladrón y consiga carne "especial", en el día siguiente, uno de los platos de cada menú tendrá este ingrediente. |
           | **Limpiar mesa** | Acción realizada para volver a habilitar una mesa. | ![clean_table](/RushTaurantSecrets/assets/Images/UI/HUD/cleanTable_icon.png) | Una vez los clientes abandonan una mesa, esta se ensuciará y no será posible que otro grupo de clientes la ocupe hasta que el jugador interactúe con ella para limpiarla |
           | **Reputación** | Reputación que va teniendo el restaurante a lo largo de la partida | ![star](/RushTaurantSecrets/assets/Images/UI/HUD/star.png) ![empty_star](/RushTaurantSecrets/assets/Images/UI/HUD/empty_star.png) | Va de 0 a 100. Cada estrella equivale a 20 de reputación. Se transforma en la probabilidad de recibir propina. Cada 20 de reputación (una estrella) supone un 20% de propinas, es decir, un 20% extra sobre la suma total de los platos del grupo. Se conserva a lo largo del juego, y si queda por debajo de 0 al final del día, se acaba el juego. |
           | **Horno** | Elemento del escenario usado para preparar las recetas | ![oven](https://i.imgur.com/rIHx3gB.png) | Al interactuar con él con los ingredientes necesarios para elaborar un plato, se comienza a cocinar el dicho plato. Una vez cocinado, al interactuar con él, se añade el plato al inventario del jugador. Hay varios hornos en la cocina para poder cocinar varios platos a la vez. |
           | **Mesas** | Elemento donde se coloca a los clientes tras atenderlos | ![table](https://i.imgur.com/cdUpqQL.png) | Es asignada a un grupo de clientes cuando se les atiende. Tras su uso debe ser limpiada antes de poder volver a usarse. No puede ser asignada a otro cliente mientras está en uso. Todas las mesas son de máximo cuatro clientes. |
           | **Caja registradora** | Elemento del escenario donde los clientes van a pagar. | ![cash_register](https://i.imgur.com/cYChALF.png) | Los clientes se desplazan hasta ella una vez han terminado de comer. Al interactuar con ella se cobra a los clientes. En caso de que haya varios en la cola se obtiene más dinero por cobrarles en “racha”. |
           | **Papelera** | Elemento donde se puede tirar un plato del inventario | ![bin](https://i.imgur.com/utCSsLH.png) | Es necesario acercarse e interactuar con ella para poder desechar un plato. |
       2. ###### Despensa <a name="id9"></a>
          | Nombre | Imagen | Funcionamiento/Comportamiento en el escenario |
          |:---:|:---:|:---:|
          | **Congelador/Nevera** | ![freezer](/RushTaurantSecrets/assets/Images/Scenario/freezer1.png) | Sirve para almacenar la carne de los ladrones en caso de ser asesinados. Si un ladrón interactúa con ella y hay un cadáver dentro se pierde la partida, activando el final **BAD ENDING 3**. |
          | **Fórmula secreta** | ![secret_formula](https://i.imgur.com/rywKffL.png) | Si un ladrón interactúa con ella, se pierde la partida activando el final **BAD ENDING 4**. |
       3. ###### Supermercado <a name="id10"></a>
          | Nombre | Imagen | Funcionamiento/Comportamiento en el escenario |
          |:---:|:---:|:---:|
          | **Menú de compra** | ![shopping_menu](https://i.imgur.com/Y3AYO3o.png) | Se selecciona previamente el ingrediente a comprar y se abre el menú de compra, que muestra la cantidad que se desea comprar y el precio a pagar. |
          | **Caja registradora** | ![secret_formula](https://i.imgur.com/mrrODvl.png) | Al pasar sobre ella, aparecerá un botón de comprar en el menú de la cesta para pagar los ingredientes que se han cogido. |
          
    6. ##### Ingredientes <a name="id11"></a>
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Los ingredientes perecen en un solo día. Por lo tanto, los que no se gasten en el día actual no se conservarán para el siguiente.
       <table align="center">
       <tr>
        <td>
        <table border=1.5>
            <thead>
            <tr>
                <th align="center" valign="center">Nombre</th>
                <th align="center" valign="center">Imagen</th>
                <th align="center" valign="center">Precio</th>
            </tr>
            </thead>
            <tbody>
            <tr>
                <td align="center" valign="center">Harina</td>
                <td align="center" valign="center"><image src="/RushTaurantSecrets/assets/Images/Food/Ingredients/FLOUR.png" alt="flour"></td>
                <td align="center" valign="center">1</td>
            </tr>
            <tr>
                <td align="center" valign="center">Patatas</td>
                <td align="center" valign="center"><image src="/RushTaurantSecrets/assets/Images/Food/Ingredients/POTATO.png" alt="potato"></td>
                <td align="center" valign="center">1</td>
            </tr>
            <tr>
                <td align="center" valign="center">Lechuga</td>
                <td align="center" valign="center"><image src="/RushTaurantSecrets/assets/Images/Food/Ingredients/LETTUCE.png" alt="lettuce"></td>
                <td align="center" valign="center">2</td>
            </tr>
            <tr>
                <td align="center" valign="center">Fresa</td>
                <td align="center" valign="center"><image src="/RushTaurantSecrets/assets/Images/Food/Ingredients/STRAWBERRY.png" alt="lettuce"></td>
                <td align="center" valign="center">2</td>
            </tr>
            <tr>
                <td align="center" valign="center">Ajo</td>
                <td align="center" valign="center"><image src="/RushTaurantSecrets/assets/Images/Food/Ingredients/GARLIC.png" alt="garlic"></td>
                <td align="center" valign="center">2</td>
            </tr>
            <tr>
                <td align="center" valign="center">Arroz</td>
                <td align="center" valign="center"><image src="/RushTaurantSecrets/assets/Images/Food/Ingredients/RICE.png" alt="rice"></td>
                <td align="center" valign="center">2</td>
            </tr>
            <tr>
                <td align="center" valign="center">Manzanas</td>
                <td align="center" valign="center"><image src="/RushTaurantSecrets/assets/Images/Food/Ingredients/APPLE.png" alt="apple"></td>
                <td align="center" valign="center">2</td>
            </tr>
            <tr>
                <td align="center" valign="center">Frambuesa</td>
                <td align="center" valign="center"><image src="/RushTaurantSecrets/assets/Images/Food/Ingredients/JAM.png" alt="mermelada"></td>
                <td align="center" valign="center">3</td>
            </tr>
            <tr>
                <td align="center" valign="center">Fideos</td>
                <td align="center" valign="center"><image src="/RushTaurantSecrets/assets/Images/Food/Ingredients/PASTA.png" alt="pasta"></td>
                <td align="center" valign="center">3</td>
            </tr>
            <tr>
                <td align="center" valign="center">Queso</td>
                <td align="center" valign="center"><image src="/RushTaurantSecrets/assets/Images/Food/Ingredients/CHEESE.png" alt="cheese"></td>
                <td align="center" valign="center">4</td>
            </tr>
            <tr>
                <td align="center" valign="center">Pollo</td>
                <td align="center" valign="center"><image src="/RushTaurantSecrets/assets/Images/Food/Ingredients/CHICKEN.png" alt="chicken"></td>
                <td align="center" valign="center">6</td>
            </tr>
            <tr>
                <td align="center" valign="center">Salmón</td>
                <td align="center" valign="center"><image src="/RushTaurantSecrets/assets/Images/Food/Ingredients/RAW_SALMON.png" alt="salmon"></td>
                <td align="center" valign="center">8</td>
            </tr>
            </tbody>
        </table>
        </td>
        <td>
        <table border=1.5>
            <thead>
            <tr>
                <th align="center" valign="center">Nombre</th>
                <th align="center" valign="center">Imagen</th>
                <th align="center" valign="center">Precio</th>
            </tr>
            </thead>
            <tbody>
            <tr>
                <td align="center" valign="center">Huevos</td>
                <td align="center" valign="center"><image src="/RushTaurantSecrets/assets/Images/Food/Ingredients/EGG.png" alt="egg"></td>
                <td align="center" valign="center">1</td>
            </tr>
            <tr>
                <td align="center" valign="center">Chocolate</td>
                <td align="center" valign="center"><image src="/RushTaurantSecrets/assets/Images/Food/Ingredients/CHOCOLATE.png" alt="chocolate"></td>
                <td align="center" valign="center">2</td>
            </tr>
            <tr>
                <td align="center" valign="center">Maíz</td>
                <td align="center" valign="center"><image src="/RushTaurantSecrets/assets/Images/Food/Ingredients/CORN.png" alt="corn"></td>
                <td align="center" valign="center">2</td>
            </tr>
            <tr>
                <td align="center" valign="center">Zanahoria</td>
                <td align="center" valign="center"><image src="/RushTaurantSecrets/assets/Images/Food/Ingredients/CARROT.png" alt="carrot"></td>
                <td align="center" valign="center">2</td>
            </tr>
            <tr>
                <td align="center" valign="center">Leche</td>
                <td align="center" valign="center"><image src="/RushTaurantSecrets/assets/Images/Food/Ingredients/MILK.png" alt="milk"></td>
                <td align="center" valign="center">2</td>
            </tr>
            <tr>
                <td align="center" valign="center">Tomate</td>
                <td align="center" valign="center"><image src="/RushTaurantSecrets/assets/Images/Food/Ingredients/TOMATO.png" alt="tomato"></td>
                <td align="center" valign="center">3</td>
            </tr>
            <tr>
                <td align="center" valign="center">Mantequilla</td>
                <td align="center" valign="center"><image src="/RushTaurantSecrets/assets/Images/Food/Ingredients/BUTTER.png" alt="butter"></td>
                <td align="center" valign="center">3</td>
            </tr>
            <tr>
                <td align="center" valign="center">Mostaza</td>
                <td align="center" valign="center"><image src="/RushTaurantSecrets/assets/Images/Food/Ingredients/MUSTARD.png" alt="mustard"></td>
                <td align="center" valign="center">3</td>
            </tr>
            <tr>
                <td align="center" valign="center">Curry</td>
                <td align="center" valign="center"><image src="/RushTaurantSecrets/assets/Images/Food/Ingredients/CURRY.png" alt="curry"></td>
                <td align="center" valign="center">3</td>
            </tr>
            <tr>
                <td align="center" valign="center">Salchicha</td>
                <td align="center" valign="center"><image src="/RushTaurantSecrets/assets/Images/Food/Ingredients/SAUSAGE.png" alt="sausage"></td>
                <td align="center" valign="center">5</td>
            </tr>
            <tr>
                <td align="center" valign="center">Gambas</td>
                <td align="center" valign="center"><image src="/RushTaurantSecrets/assets/Images/Food/Ingredients/SHRIMP.png" alt="shrimp"></td>
                <td align="center" valign="center">7</td>
            </tr>
            <tr>
                <td align="center" valign="center">Carne humana</td>
                <td align="center" valign="center"><image src="/RushTaurantSecrets/assets/Images/Food/Ingredients/MEAT.png" alt="human_meat"></td>
                <td align="center" valign="center">Se obtiene tras matar a una persona</td>
            </tr>
            </tbody>
        </table>
        </td>
       </tr>
       </table>
       
   7. ##### Recetas <a name="id12"></a>
      | Nombre | Imagen | Ingredientes necesarios | Precio | Ganancia | Tiempo necesario | Dificultad |
      |:------:|:------:|:-----------------------:|:------:|:--------:|:----------------:|:----------:|
      |**Huevo frito**|![fried_egg](/RushTaurantSecrets/assets/Images/Food/Dishes/FRIED_EGG.png)|Huevos|4|3|0.5s|1|
      |**Pan**|![bread](/RushTaurantSecrets/assets/Images/Food/Dishes/BREAD.png)|Harina|4|3|0.7s|1|
      |**Mermelada**|![marmelade](/RushTaurantSecrets/assets/Images/Food/Dishes/MARMELADE_TOAST.png)|Frambuesa<br>Harina|8|4|1s|1|
      |**Pan con ajo**|![garlic_bread](/RushTaurantSecrets/assets/Images/Food/Dishes/GARLIC_BREAD.png)|Harina<br>Ajo|7|4|0.7s|1|
      |**French fries**|![french_fries](/RushTaurantSecrets/assets/Images/Food/Dishes/FRENCH_FRIES.png)|Patata<br>Tomate|8|4|1s|1|
      |**Pancake**|![pancake](/RushTaurantSecrets/assets/Images/Food/Dishes/PANCAKE.png)|Harina<br>Huevos<br>Leche|8|4|1.5s|1|
      |**Tarta de fresa**|![strawberry_cake](/RushTaurantSecrets/assets/Images/Food/Dishes/STRAWB_CAKE.png)|Harina<br>Huevos<br>Fresa|9|5|2.5s|2|
      |**Tarta de chocolate**|![chocolate_cake](/RushTaurantSecrets/assets/Images/Food/Dishes/CHOCO_CAKE.png)|Harina<br>Huevos<br>Fresa|9|5|2.5s|2|
      |**Tarta de frambuesa**|![rasp_cake](/RushTaurantSecrets/assets/Images/Food/Dishes/RASP_CAKE.png)|Harina<br>Huevos<br>Frambuesa>|10|5|2s|2|
      |**Galletas**|![cookies](/RushTaurantSecrets/assets/Images/Food/Dishes/COOKIES.png)|Mantequilla<br>Harina<br>Chocolate|11|5|1.7s|2|
      |**Omelette**|![omelette](/RushTaurantSecrets/assets/Images/Food/Dishes/OMELETTE.png)|Huevos<br>Mantequilla<br>Harina<br>Maíz|14|7|2s|2|
      |**Tarta de manzana**|![apple_pie](/RushTaurantSecrets/assets/Images/Food/Dishes/APPLE_PIE.png)|Huevos<br>Harina<br>Manzana|10|6|2.5s|2|
      |**Tarta de queso**|![cheesecake](/RushTaurantSecrets/assets/Images/Food/Dishes/CHEESECAKE.png)|Huevos<br>Harina<br>Queso|12|6|2.5s|2|
      |**Burrito vegetariano**|![burrito](/RushTaurantSecrets/assets/Images/Food/Dishes/BURRITO.png)|Lechuga<br>Harina<br>Arroz|11|6|3s|2|
      |**Puré de patatas**|![puree](/RushTaurantSecrets/assets/Images/Food/Dishes/PUREE.png)|Patatas<br>Zanahoria<br>Ajo|11|6|3.5s|2|
      |**Helado**|![ice_cream](/RushTaurantSecrets/assets/Images/Food/Dishes/ICE_CREAM.png)|Milk<br>Chocolate<br>Fresa<br>Frambuesa|17|8|2.5s|3|
      |**Nachos**|![nachos](/RushTaurantSecrets/assets/Images/Food/Dishes/NACHOS.png)|Maíz<br>Harina<br>Mostaza|16|10|3s|3|
      |**HotDog**|![hotdog](/RushTaurantSecrets/assets/Images/Food/Dishes/HOTDOG.png)|Harina<br>Mostaza<br>Salchichas|19|10|2.7s|3|
      |**Sandwich de salmón**|![salmon_sandwich](/RushTaurantSecrets/assets/Images/Food/Dishes/SANDWICH.png)|Harina<br>Lechuca<br>Salmón|20|10|1s|3|
      |**Sushi**|![sushi](/RushTaurantSecrets/assets/Images/Food/Dishes/SUSHI.png)|Salmón<br>Arroz|21|11|3.7s|3|
      |**Curry con arroz**|![curry_rice](/RushTaurantSecrets/assets/Images/Food/Dishes/CURRY_RICE.png)|Patata<br>Curry<br>Arroz<br>Ajo|22|14|3s|4|
      |**Pizza**|![pizza](/RushTaurantSecrets/assets/Images/Food/Dishes/PIZZA.png)|Harina<br>Salchichas<br>Queso|25|15|5s|4|
      |**Pollo asado**|![roasted_chicken](/RushTaurantSecrets/assets/Images/Food/Dishes/ROASTED_CHICKEN.png)|Pollo<br>Tomate<br>Zanahoria|28|17|6s|4|
      |**Filete especial**|![fillet](/RushTaurantSecrets/assets/Images/Food/Dishes/FISH_FILLET.png)|Carne humana<br>Zanahoria|15|13|4s|5|
      |**Albóndigas especial**|![meatballs](/RushTaurantSecrets/assets/Images/Food/Dishes/MEATBALLS.png)|Carne humana<br>Harina<br>Curry|18|14|5.5s|5|
      |**Espagueti especial**|![spaghetti](/RushTaurantSecrets/assets/Images/Food/Dishes/SPAGHETTI.png)|Carne humana<br>Fideos<br>Tomate|20|14|5s|5|
      |**Burguer especial**|![burguer](/RushTaurantSecrets/assets/Images/Food/Dishes/BURGER.png)|Carne humana<br>Harina<br>Lechuga<br>Tomate<br>Queso|30|20|6.5s|5|
      |**Ramen especial**|![ramen](/RushTaurantSecrets/assets/Images/Food/Dishes/RAMEN.png)|Fideos<br>Huevos<br>Gambas<br>Carne humana<br>Ajo|38|27|7s|5|
      
4. #### Diseño de las escenas <a name="id13"></a>
   1. #### Restaurante <a name="id14"></a>
      <p align="center">
        <image src="/RushTaurantSecrets/assets/Images/Cutscenes/Restaurant.png" alt="restaurant" width="50%" height="50%">
      </p>
      &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Escenario en el que se desarrolla la parte principal del juego, que se divide en la zona de cocina, la zona de mesas y la entrada. Los clientes irán llegando por la entrada y acumulándose unos detrás de otros en una fila. Cuando el jugador les asigne una mesa, caminarán hacia ella y la ocuparán, mostrándolos sentados en las sillas. En la zona de la cocina se lleva a cabo la elaboración de los platos y se realiza el cobro a los clientes. Se ve una pequeña previsualización de la despensa, pero no refleja lo que sucede en ella realmente.
   3. #### Despensa <a name="id15"></a>
      <p align="center">
        <image src="/RushTaurantSecrets/assets/Images/Cutscenes/Pantry.png" alt="pantry" width="50%" height="50%">
      </p>
      &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Escenario que ocurre a la vez que el restaurante. Cuando el jugador está en la despensa, se ralentizará el flujo del tiempo en el restaurante. A partir del segundo día aparecerán ladrones por el camino de la izquierda, e intentarán llegar a la fórmula secreta para apoderarse de ella. Si los ladrones consiguen llegar a la fórmula antes de que el jugador los pare, se pierde la partida. Cuando el jugador mata a un ladrón, se tendrá también que evitar que lleguen a la nevera, dificultando el juego. Si los ladrones llegan a la nevera, descubrirán el cadáver de su compañero y se terminará la partida.
   4. #### Supermercado <a name="id16"></a>
      <p align="center">
        <image src="https://i.imgur.com/sTDs8zb.png" alt="pantry" width="50%" height="50%">
      </p>
      &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Escenario al que tiene que ir el jugador antes de abrir el restaurante. Para comprar un ingrediente, primero tiene que acercarse a la zona donde se encuentra el alimento y añadirlo a la cesta. Entonces, se abre el menú de compra, donde elige la cantidad que desea comprar y se le muestra el precio total. Cuando haya decidido lo que comprar, se guardará en la cesta. A la cesta se puede acceder en cualquier momento para ver qué alimentos ha comprado, el precio total, y descartar alimentos. Para pagar, tendrá que pasar por caja y aparecerá en el menú de la cesta un botón de “pagar” para confirmar la compra. Si dispone de suficiente dinero, podrá realizarla.

5. #### HUD <a name="id17"></a>
   1. ##### Mockup del HUD <a name="id18"></a>
      |![HUD_restaurant](https://i.imgur.com/NSLmzEz.png)|![HUD_supermarket](https://i.imgur.com/PcDO2O4.png)| 
      |:---:|:---:|
      |HUD en el supermercado|HUD en el supermercado|
   2. ##### Explicación de los elementos del HUD y su funcionamiento <a name="id19"></a>
      | Elemento | Imagen | Explicación |
      | :---: | :---: | :---: |
      | **Reputación** | ![star](/RushTaurantSecrets/assets/Images/UI/HUD/star.png)![empty_star](/RushTaurantSecrets/assets/Images/UI/HUD/empty_star.png)![empty_star](/RushTaurantSecrets/assets/Images/UI/HUD/empty_star.png)![empty_star](/RushTaurantSecrets/assets/Images/UI/HUD/empty_star.png)![empty_star](/RushTaurantSecrets/assets/Images/UI/HUD/empty_star.png) | Reputación del juego. Va del 0 al 100. De cara al usuario se representa en estrellas (1 estrella = 20 reputación). La reputación se traduce en propinas. |
      | **Dinero** | ![money_icon](/RushTaurantSecrets/assets/Images/UI/HUD/money_icon.png) | Muestra el dinero que tiene el jugador actualmente. |
      | **Objetivo** | ![target_icon](/RushTaurantSecrets/assets/Images/UI/HUD/target_icon.png) | Muestra el dinero que hay que conseguir el día actual. |
      | **Reloj** | ![clock](/RushTaurantSecrets/assets/Images/UI/HUD/clock.png) | Indica el momento del día para saber cuando va a terminar la jornada. |
      | **Inventario** | ![inventory](/RushTaurantSecrets/assets/Images/UI/HUD/inventory.png) | Lugar donde guardar los platos hechos, máximo cuatro platos. |
      | **Menú del día** | ![daily_menu_icon](/RushTaurantSecrets/assets/Images/UI/HUD/daily_menu_button.png) | Carta del día, está apuntado las comidas que va a servir el día actual. |
      | **Cesta** | ![basket_yellow](/RushTaurantSecrets/assets/Images/UI/HUD/basket_yellow.png) | Contiene los ingredientes comprados de momento. |
      | **Día** | ![day](https://i.imgur.com/lI29VkR.png) | Día en el que se encuentra el jugador RushTaurant Secrets. |

6. #### Visual/estética <a name="id20"></a>
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;La estética es en estilo pixel art con vista top-down falsa (se ven los escenarios y los personajes como si la cámara estuviera ligeramente elevada, pero no como si estuviera colocada en el techo). Los escenarios están inspirados en interiores de edificios reales como cocinas o supermercados, pero con una disposición adecuada al flujo del juego y la jugabilidad del mismo.  
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;La ambientación empleada, en contraposición al ritmo rápido, las mecánicas del juego y el lore, transmite una sensación de relajación y familiaridad, de ahí su estilo “chibi” y paleta de colores pastel.
   <p align="center">
    <image src="https://i.imgur.com/00WpFof.png" alt="esthetic1" width="30%" height="30%"><br>
    <image src="https://i.imgur.com/XjEoi0j.png" alt="esthetic2" width="50%" height="50%"><br>
    <image src="https://i.imgur.com/RWaeAWz.png" alt="esthetic3" width="50%" height="50%">
   </p>

7. #### Menú y flujo de juego <a name="id21"></a>
   <p align="center">
        <image src="https://imgur.com/LPyujLi.png" alt="main_menu" width="60%" height="60%">
        <table>
            <thead>
                <tr>
                    <th align="center" valign="center"> 
                        <image src="https://i.imgur.com/p2vxSwO.png" alt="game_flow" width="90%" height="90%">
                    </th>
                </tr>
            </thead>
            <tbody>
                <tr>
                    <td align="center" valign="center">Diagrama de flujo del funcionamiento de la interfaz extradiegética (no se incluyen cinemáticas)</td>
                </tr>
            </tbody>
        </table>
   </p>

8. #### Contenido <a name="id22"></a>
   1. ##### Historia y personaje principal <a name="id23"></a>
      &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Hace muchos años los padres de la protagonista eran propietarios de un restaurante muy famoso. Se rumoreaba que su fórmula secreta era capaz de hacer que cualquier negocio llegara a tener gran fama. La popularidad del restaurante duró poco ya que, al extenderse el rumor de la fórmula, innumerables robos de un negocio vecino asolaron el local y la vida de los propietarios se convirtió en un infierno. Finalmente decidieron cerrar y llevar una vida más humilde, pero más feliz. Poco después, tuvieron un bebé. Influenciada por el pasado de sus padres, desarrolló un gusto por la cocina, con una especial afinidad por la charcutería, dedicando sus tiempos libres a matar animales, guardarlos en latas de conserva y cocinarlos. Cuando sus padres murieron por causas desconocidas, la protagonista se propuso seguir el camino que sus progenitores habían dejado. Valiéndose de la fórmula secreta que había heredado, reabrió el restaurante. Sin embargo, los antiguos enemigos de sus padres se enteraron y aliaron para terminar lo que años atrás habían empezado: robar la fórmula y hacer que su local triunfara de una vez. Lo que no sabían es que la protagonista era capaz de hacer cualquier cosa por crear el mejor restaurante de la ciudad.
   2. ##### Resumen de cada día <a name="id24"></a>
      | Días | Dinero a conseguir | Frecuencia con la que vienen los clientes | Frecuencia con la que vienen los ladrones | Frecuencia de bajada de felicidad |             Cantidad de reputación perdida |
      |:---:|:---:|:---:|:---:|:---:|:---:|
      | **Día 1** | 30 | 11s | 23,5 - 37s | 2,1s | 3 |
      | **Día 2** | 60 | 10,5s | 23 - 36s | 2s | 4,4 |
      | **Día 3** | 80 | 10s | 22,5 - 35s | 1,9s | 4,6 |
      | **Día 4** | 110 | 9,5 | 22 - 34s | 1,8s | 4,8 |
      | **Día 5** | 130 | 9s | 21,5 - 33s | 1,7s | 5 |
      | **Día 6** | 150 | 8,5s | 21 - 32s | 1,6s | 5,1 |
      | **Día 7** | 200 | 8s | 20,5 - 31s | 1,5s | 5,2 |
      | **Día 8** | 225 | 7,5s | 20 - 30s | 1,4s | 5,3 |
      | **Día 9** | 263 | 7s | 19,75 - 29,5s | 1,3s | 5,4 |
      | **Día 10** | 300 | 6,5s | 19,5 - 29s | 1,2s | 5,5 |

      &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Se ha realizado el análisis de dos juegos de inspiración similar para realizar esta tabla:
      - [*Fabolous Angela: Wedding Disaster*](https://docs.google.com/spreadsheets/d/1LAK7xEuwEh-cA7Zvm-_AhGIjfFltQOT0/edit?usp=share_link&ouid=108574916439104152988&rtpof=true&sd=true) de la saga spinoff *Fabolous Angela*, que pertenece a la saga principal *Delicious Emily*.
      - [*Penguin Diner*](https://docs.google.com/spreadsheets/d/1BrLpbWepVvRsidPz6GdemALuWLK7NfL0PQx5IvR8FCg/edit?usp=share_link) de la saga *Penguin Diner*.
   
   3. ##### Finales <a name="id25"></a>
      | TIPO | Contexto | Forma de conseguir |
      |:---:|:---:|:---:|
      | **BAD ENDING 1** | Los clientes no se han quedado satisfechos con el servicio, por lo que el restaurante ha perdido toda la fama y cierra definitivamente. |       La fama se queda negativa al final del día. |
      | **BAD ENDING 2** | Se quiebra el restaurante por no conseguir suficiente dinero. El jugador no puede soportar las deudas y tiene que vender su casa. | No ha       superado el dinero necesario para superar el día. |
      | **BAD ENDING 3** | La policía hace una redada en el restaurante tras descubrir que ha matado a personas. La protagonista es arrestada y revela que fue ella         quien mató a sus padres. | Un ladrón ha conseguido abrir el congelador. |
      | **BAD ENDING 4** | Los ladrones consiguen la fórmula secreta. Como su jefe tiene más dinero que el jugador, revive el local cochambroso que tenía. El               restaurante de la protagonista no puede rivalizar con el de su enemigo y termina cerrando. | Un ladrón ha conseguido acceder a la fórmula secreta. |
      | **NORMAL ENDING** | Seguirá protegiendo la fórmula secreta y el misterio de los cadáveres. | Ha matado al menos 1 persona y ha podido superar todos los días       |
      | **HAPPY ENDING** | Se ha ganado el dinero suficiente para renovar el restaurante y contratar más personas, por lo tanto, el protagonista ya no tendrá que           servir. Además, se han contratado a unos guardias de seguridad para proteger la fórmula y que nadie pueda robarla. | No ha matado a ninguna persona y ha podido       superar todos los días |
     
      &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Hay un [documento](/documents/game_design/art_design/cinemática_diálogos.pdf) con el diseño, arte y diálogos utilizados en cada una de las cinemáticas correspondientes a estos finales y al resto de cinemáticas que hay en el juego.

9. #### Contenido <a name="id26"></a>
    1. ##### Videojuegos <a name="id27"></a>
       - Saga Penguin Diner (Bigwig Media)
       - Saga Delicious Emily
    2. ##### Assets <a name="id28"></a>
       *Comida:*
       - <https://ghostpixxells.itch.io/pixelfood>
       - <https://ghostpixxells.itch.io/pixel-mart>  
       
       *Escenarios y personajes*
       - <https://gif-superretroworld.itch.io/exterior-pack>
       - <https://limezu.itch.io/moderninteriors>
       - <https://caniaeast.itch.io/simple-sky-pixel-backgrounds>  
       
       *UI:*
       - <https://crusenho.itch.io/complete-gui-essential-pack>
       - <https://dreammix.itch.io/keyboard-keys-for-ui
       - <https://cupnooble.itch.io/sprout-lands-asset-pack>
       - <https://pipoya.itch.io/free-popup-emotes-pack>  
       
       *Sonido:*
       - <https://leohpaz.itch.io/minifantasy-dungeon-sfx-pack>
       - <https://jdwasabi.itch.io/8-bit-16-bit-sound-effects-pack>
       - <https://kronbits.itch.io/freesfx>
       - <https://coloralpha.itch.io/50-menu-interface-sfx>
       - <https://olexmazur.itch.io/fantasy-card-game>
       - <https://darkworldaudio.itch.io/sound-effects-survival-i>
       - <https://simon13666.itch.io/sound-starter-pack>
       - <https://richarrest.itch.io/visual-novel-music-pack-tiny-pack>
       - <https://ellr.itch.io/universal-ui-soundpack>
       - <https://jdsherbert.itch.io/ultimate-ui-sfx-pack>
       - <https://www.youtube.com/watch?v=4kVTqUxJYBA>
       - <https://www.free-stock-music.com/sound-effects-library-cash-register-sound.html>
       - <https://pixabay.com/>
       - <https://pixabay.com/music/video-games-8-bit-dream-land-142093/>
       
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
