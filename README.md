# proyecto_poo_2021
Proyecto final para la catedra de Programación Orientada a Objetos cursada en 2021.

Para este proyecto se uso C++ y Qt como libreria grafica.

El proyecto consto de 3 instancias a lo largo del año, requisitos de cada instancia: 
El codigo representa la version de la tercera instancia, cabe recalcar que los requistos son acumulativos.

Requisitos instancia #1: https://github.com/jpsq/proyecto_poo_2021/blob/master/Requisitos%20instancias/requisitos_instancia_1.pdf

Requisitos instancia #2: https://github.com/jpsq/proyecto_poo_2021/blob/master/Requisitos%20instancias/requisitos_instancia_2.pdf

Requisitos instancia #3: https://github.com/jpsq/proyecto_poo_2021/blob/master/Requisitos%20instancias/requisitos_instancia_3.txt

Diagrama UML de la version final: https://github.com/jpsq/proyecto_poo_2021/blob/master/Diagramas/uml_class_diagram.png

En lineas generales:

El software debe presentar un mapa de 30 por 30 (dato que puede ser configurable) el cual 
contenga montaña (área donde no puede avanzar el ciervo) y meseta (área donde puede 
avanzar el ciervo) y pastizal (area donde puede avanzar el ciervo y alimentarse).
El mapa no tiene areas cerradas por montañas.
La población de ciervos se mueve de forma aleatoria por el mapa y mueve un casillero por 
día, a la vez puede encontrar pastizales, los cuales se encuentran de forma aleatoria en el 
mapa. Si los ciervos no encuentran pastizales por 3 días, la población muere. Los pastizales
duran 10 días y se secan o son comidos, y vuelven a crecer después de 5 días. 
Cada día debe ser 10 segundos en la simulación (esto también debe ser configurable) 
Si una población de ciervos se encuentra con otra población pueden suceder 3 cosas: 
1. Se encuentran y no hay conflictos y cada población sigue su camino. 
2. Se encuentran y se unen formando una sola población. 
3. Se cruzan y generan una nueva población, es decir, el resultado del encuentro son 3
poblaciones. 
Estas acciones se realizan dependiendo del tipo de población: 
● tipo A : si se encuentra con otra población de tipo A realiza la acción 3. 
            si se encuentra con otra población de tipo B realiza la acción 1. 
● tipo B: si se encuentra con población B realiza la acción 2.   
 
Dicho software debe permitir ingresar cuantas poblaciones de ciervos de tipo A y B van a 
estar en la simulación y cuantos pastizales habrá. Luego, se debe poder correr dicha 
simulación.

Debe incluirse uso de archivos para guardar simulaciones en proceso y configuraciones.



