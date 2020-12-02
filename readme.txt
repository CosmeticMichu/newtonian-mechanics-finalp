Bueno pirobos, primero que todo, no uso tildes porque en linux tengo la distribucion del teclado en gringo asi que no lo chupen.

Segundo, esto parece ser la primera parte del programa ya funcional, seria chimba si pueden
pillarlo a ver si hay algun error con las formulas o quiza como tal en la
implementacion, porque como pongo en el mensaje del commit, parece que calcula el
radio con la incertidumbre, hay que ver que efectivamente lo haga bien, que
creeria que sisa, en principio.

Falta organizarlo, pa no tener un solo archivo con 200 y pico de lineas que va a
tener este coso cuando ya este listo (calculando gravedad y la masa de la tierra) sino varios archivos y una funcion main
chikita para que el profesor la vea en el paper y si quiere ver las
implementaciones, entre a este repositorio, cuyo link estaria como en un
apendice o algo asi en el documento (recuerdenme borrar este readme) y
ahi vea bien las implementaciones.

En el script agrego algunos comentarios que creo que les pueden ayudar a
entender lo que va hacienddo el codigo en cada paso, alguna cosa pues me
preguntan.

input.txt va a ser el archivo en el que vamos a ingresar los datos que medimos,
en principio lo que trato de hacer es que tomemos un numero N de datos (es
importante que todos midamos con la misma incertidumbre porque el programa
trabaja con solo una incertidumbre y si le metemos mas de una es q cule verguero, toncs
toca que todos nos consigamos una cinta metrica para tomar las medidas y medir
con la misma inceritdumbre) y los organizamos por columnas, las iniciales que estan en la primera fila de
input.txt siguen esta convencion y es solo para que sea mas facil de leer para
nosotros lo que este en input.txt:

si(X), hi(X)

donde i es un numero que asigne a cada quien para ordenar cada conjunto de
datos, y X es la/las iniciales de la ciudad
donde cada quien va a tomar las medidas (A: Ayapel, Az:Aguazul, B:
Barrancabermeja, C: Cucuta), el resto de datos que aparecen ahorita, los puse
solo para probar que si me funcionara, que me botara los vectores con los datos
como debia y eso.

Tenemos que cuadrar cuantos datos vamos a tomar cada uno (yo diria que 5 para
altura (h) y 5 para la sombra (s), para que no pase mucho tiempo y nos cambie
demasiado la posicion del sol y la sobra.

Poco mas que decir, cualquier cosa pregunten por el grupo.

PD: Para el compa de Cucuta (que no me acuerdo del nombre, srry xd), quiza este bastante perdido, asi que no tenga pena
en preguntar todo lo que no entienda y tenga en mente. La motivacion de hacer
este codigo es basicamente que calcular todas esas incertidumbres es
bastante engorroso, toncs mjr implementamos un codigo que haga eso por nosotros,
y encima de que nos ahorra este trabajo de hacerlo a mano, nos permite organizar
mejor el pdf porque vamos a poner solo unos cuantos datos y un poco de la teoria
que se usa para implementar el programa, y no un poco de tablas ahi. Por otro lado, seria bueno que, si no
tiene linux o macOs, se descargue un compilador de C++ para windows o instale linux en una maquina virtual para que pruebe,
cacharree el codigo y se familiarice un poco, aunque en principio ustedes solo tienen que
rotar los datos que tomaron, ya sea en un .txt -con el nombre que quieran-, o solo ordenados en un
mensaje por wha, y yo ejecuto el codigo y ponemos los datos en el .pdf
