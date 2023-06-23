[![✗](https://img.shields.io/badge/Release-v0.2.0-ffb600.svg?style=for-the-badge)](https://github.com/agustin-golmar/Flex-Bison-Compiler/releases)

# Compilador Flex/Bison

Un compilador vacío de ejemplo construido con Flex y Bison.

## Requerimientos

Para construir el compilador, se requieren las siguientes dependencias:

* [Bison v3.8.2](https://www.gnu.org/software/bison/)
* [CMake v3.24.1](https://cmake.org/)
* [Flex v2.6.4](https://github.com/westes/flex)
* [GCC v11.1.0](https://gcc.gnu.org/)
* [Make v4.3](https://www.gnu.org/software/make/)

Si en lugar de trabajar con un entorno _Linux_, se está construyendo el proyecto sobre un entorno _Microsoft Windows_, se debe instalar _Microsoft Visual Studio 2022_ con las extensiones para desarrollar aplicaciones en _C/C++_, así como también las herramientas requeridas, con excepción del compilador _GCC_ y la herramienta _Make_.

## Construcción

Para construir el proyecto por completo, ejecute en la raíz del repositorio los siguientes comandos (en _Linux_):

```bash
user@machine:path/ $ chmod u+x --recursive script
user@machine:path/ $ script/build.sh
```

En un entorno _Microsoft Windows_, en cambio, se debe ejecutar:

```bash
user@machine:path/ $ script\build.bat
```

Luego se deberá abrir la solución generada `bin\Compiler.sln` con el IDE _Microsoft Visual Studio 2022_. Los ejecutables que este sistema construye se depositan dentro del directorio `bin\Debug` y `bin\Release`, según corresponda.

## Ejecución

Para compilar un programa, primero cree un archivo vacío denominado `program` (o el nombre que desee), con el siguiente contenido:

```
123123 + 123 - 2 * (454 + 890 / 89)
```

Luego, ejecute el compilador desde el directorio raíz del proyecto, o desde cualquier otro lugar indicando el path hacia el script `start.sh` y pasando por parámetro el path hacia el programa a compilar:

```bash
user@machine:path/ $ script/start.sh program
```

En Windows:

```bash
user@machine:path/ $ script\start.bat program
```

Debería obtener el resultado correcto de evaluar el programa anterior: `122318`.

## Testing

En Linux:

```bash
user@machine:path/ $ script/test.sh
```

En Windows:

```bash
user@machine:path/ $ script\test.bat
```

Si desea agregar nuevos casos de uso, deberá crear un archivo por cada uno, que contenga el programa a testear dentro de las carpetas `test/accept` o `test/reject` según corresponda (es decir, si el mismo debe ser aceptado o rechazado por el compilador).




# Informe final TP TLA

# Integrantes del equipo

- Santino Ranucci, 62092
- Agustin Zakalik, 62068

# Repositorio

[https://github.com/sranucci/Compiler-Flex-Bison-TLA](https://github.com/sranucci/Compiler-Flex-Bison-TLA)



# Introduccion

El objetivo principal del proyecto es desarrollar un lenguaje que permita crear gráficos. Estos gráficos se pueden mostrar en cualquier visualizador de HTML, tales como [https://html.onlineviewer.net/](https://html.onlineviewer.net/). O incluso levantando un servidor web local (como goLive de vscode, etc…) y usan la librería Graph.js de javascript.

Nuestro lenguaje permite crear cuatro tipos de gráficos: nube de puntos, gráfico circular, gráfico de barras y gráfico de lineas, los cuales son ampliamente utilizados por el publico general.

El problema que estamos solucionando es que usuarios con escasos conocimientos en programación puedan crear gráficos fácilmente.

# Consideraciones

Como se menciono anteriormente, nuestro compilador genera gráficos utilizando la herramienta Graph.js. Para generar el código HTML+javascript de los gráficos, no se necesitan programas ni requerimientos adicionales. Ni tampoco tener bajada la librería previamente pues la descarga el navegador via CDN al utilizar la pagina. Sin embargo, para hacer uso de algún visualizador de HTML online y poder bajar la librería vía CDN, se necesita conexión a internet.

# Desarrollo del proyecto

## Frontend

La primera entrega consistió en la creación de la gramática y el uso de las herramientas Flex y Bison para que un texto de entrada pueda ser tokenizado y se pueda saber si pertenece o no al lenguaje generado por nuestra gramática.

De esta manera, cualquier entrada que no pertenezca al lenguaje que genere nuestra gramática, no sera parseada por el backend. A su vez, se agregaron veinte casos de testeos: diez de aceptación y diez de error. Los casos de error consisten en cadenas de entrada que no cumplen con la gramática propuesta, por lo que nuestro compilador las rechaza.

La cadena de pasos seguida por el Frontend es la siguiente

1. El analizador léxico (Flex) tokeniza la cadena de entrada
2. El analizador sintáctico (Bison) se fija que la cadena de entrada tokenizada pertenezca al lenguaje
3. Si Flex y Bison no devuelven error, se delega la creación del código HTML y Javascript al backend

## Backend: Arquitectura y decisiones de diseño

Para lo que concierne al backend, se decidió utilizar el patrón de diseño singleton para tener centralizado el acceso a estructuras de datos que se utilizan para generar código. y para liberar memoria.

Los Singletons en la aplicación ubicados en /backend/support

### ChartType1Singleton:

```c
typedef struct chartType1Node {
    double x;
    double y;
    struct chartType1Node * next;
} chartType1Node;

typedef struct chartType1Singleton {
    char graphName[SIZE];
    char xAxisLabel[SIZE];
    char yAxisLabel[SIZE];
    char color[SIZE];
    chartType1Node * first;
    ChartType1State state;
} chartType1Singleton;
```

Este singleton consiste en una lista encadenada de coordenadas x e y, y a su vez en el nodo maestro almacena información importante del gráfico, como el nombre, nombre de eje x, nombre del eje y, etc… En el archivo chartType1Singleton.c, se encuentran funciones que se utilizan para acceder y modificar los datos de este singleton. Ademas, este singleton devuelve los datos en el formato necesario que pide chart js. Osea forma un string que directamente se puede imprimir al archivo de salida.

Expone estos métodos para interactuar con este singleton

```c
void addToList(double x, double y);
void setCT1Name(char * buff);

void setSelectedColor(SelectedColor color);

void addCoordinate(double x, double y);

void getXandYAxisData(char * xbuff,char * ybuff );

void setXAxisName(char * name);
void setYAxisName(char * name);

ChartType1State getChartType1State();
void setChartType1State(ChartType1State state);

void getDataAsScatter(char * buffer);

void getChartType1GraphName(char * buffer);
int getChartType1XAxisLabel(char * label);
int getChartType1YAxisLabel(char * label);
int getChartType1Color(char * color);

void freeCT1Mem();
```

Todos los “getters”, dan los datos en forma de string ya preparados para ser enviados al archivo de salida en el formato que los pide chart js.

Es importante notar que se tiene un campo ChartType1State y una función para interactuar con este. En nuestro TP tenemos 4 tipos de gráficos, pie, bar, scatter, y line. Como pide chart js el formato de los datos line y scatter es similar entre si. Mientras que como pide los datos chart js para pie y bar también es similar entre si. ChartType1Singleton esta hecho para almacenar los datos para los gráficos line y scatter, Y es por eso que necesita tener un estado que indica los datos de que gráfico esta almacenando. ChartType2Singleton maneja un concepto similar, y almacena los datos de forma cómoda para crear los gráficos pie y bar.

### ChartType2Singleton

```c
typedef enum {
    PIECHARTTYPE,
    BARCHARTTYPE,
} CT2TYPE;

typedef struct ChartType2Node {
    double number;
    char color[SIZE];
    char name[SIZE];
    struct ChartType2Node * next;
} ChartType2Node;

typedef struct {
    CT2TYPE type;
    char graphName[SIZE];
    ChartType2Node * first;
} ChartType2MasterNode;
```

El concepto de este singleton es muy similar al anterior. Una lista encadenada, pero a diferencia del otro, al ser un gráfico de barras o un pie chart, cada elemento puede tener color y nombre propio junto a un valor. Al igual que en el primer singleton, se uso un nodo maestro para guardar el nombre del gráfico.

Las funciones para interactuar que expone son:

```c
void addToCT2Data(double number, SelectedColor color, const char* name);
void setCT2PieChart();
void setCT2Name(char * name);
void setCT2BarChart();
void printCT2List();

void outputLabels(char * labels);
void outputBarNumbers(char * numbers);
void outputColors(char * colors);
void getGraphName(char * graphName);
void getChartType(char * buffer);
void freeCT2Data();
```

las funciones getters y output, sirven nuevamente para obtener los datos en el formato solicitado por chart js

Una vez que esta construido el AST,Habiendo llegado al nodo program, según el tipo de gráfico elegido por el usuario, se popula chartType1Singleton o chartType2Singleton pero no ambas. Al ser un singleton, la estructura populada a medida que se construye el AST es facilmente accedida desde generator.c, que hace uso de fopen, fprintf, los metodos de apoyo de los singletons mencionados previamente y  fclose para generar un archivo index.html que contiene el grafico solicitado por el usuario.

Finalmente, hay un tercer singleton:

### GarbageCollector:

```c

typedef struct memoryNode {
    void * memDir;
    struct memoryNode * next;
} memoryNode;

typedef struct {
    memoryNode * first;
} masterMemoryNode;

```

Este básicamente actúa como un controlador de accesos a memoria, es una lista encadenada de punteros a direcciones allocadas con la familia de funciones alloc, y al terminar el programa se encarga de liberar estas direcciones. Ofrece las siguientes funcionalidades

```c

void addToGarbageCollector(void *memDir);
void freeAll();
void * getMemory(int bytes);
```

En cualquier lugar del código (salvo en los otros 2 singletons) que se solicite una dirección de memoria, se hace con getMemory o bien, tras solicitarla se agrega al garbage collector. Para luego ser liberada al final.

## Porque tantos singletons?

Consideramos que dado que no es un proyecto trivial (tiene varios archivos.c, varios directorios, separacion front y back, etc…). Era una buena decision de arquitectura y diseño tener centralizado el acceso de datos y el manejo de memoria. Mediante los singletons, logramos un bajo acoplamiento entre distintos módulos con respecto al manejo de memoria (un modulo la pide pero luego otro la debe liberar) y también un bajo acoplamiento en cuanto al acceso de datos (se pueden acceder fácilmente desde cualquier parte del código con un único llamado a función).

## Porque dos singletons distintos para los gráficos?

El motivo principal radica en que chart js pedía muy distinto el formato para los gráficos de tipo pie y bar respecto a los gráficos de tipo line y scatter, como se mostró previamente, la forma de almacenar los datos es distinta, y para que no seguir el antipatron “THE GOD CLASS/OBJECT”. que es una falla de diseño en la cual un objeto se encarga de hacer todo. Decidimos separar en dos singletons distintos, somos conscientes que en un lenguaje orientado a objetos se podría haber reutilizado el comportamiento con herencia, pero no es el caso en C.

### Uso del programa

1- abrir la terminal

2- correr el script start ubicado en  el directorio script

```c
Ejemplo:
./script/start.sh [archivo a procesar]
```

3-Ubicar el archivo index.html generado en el directorio actual

4-Abrir con un visualizador html o levantando un webserver propio (como con la extension goLive de vscode)

# Dificultades encontradas

En un primer lugar, surgieron dificultades a la hora de elegir una gramática para el trabajo practico. Originalmente, se quiso crear un lenguaje similar a Markdown que facilite tomar notas. Esta idea fue descartada rápidamente, ya que la consigna pedía que existieran casos de falla, y Markdown esta hecho para no fallar.

Tras superar la dificultad anterior, optamos por generar una gramatica para generar graficos, que es ahora la gramática final del proyecto. Decidimos cambiar totalmente la idea, ya que el problema a solucionar era mas claro para la nueva idea.

Otra de las dificultades encontradas fue que no estaba funcionando del todo bien la liberacion de la memoria alocada, por lo que se decidió crear un “Garbage Collector”, que se encarga de juntar todo puntero a memoria alocada y liberarla al final del programa.

La dificultad mas grande de todas surgió a la hora de intentar generar código para crear un gráfico a partir de una función dada. Esto logro ser una complicación importante, y tras intentar por varias horas finalmente optamos por sacar la funcionalidad.

# Futuras extensiones

La extensión mas importante que haríamos es recuperar la funcionalidad de que se pueda generar un gráfico a partir de una función matemática dada por el usuario.

Por otro lado, seria una buena idea añadir muchos mas tipos de gráficos y colores, y potencialmente poder soportar todos los gráficos soportados por Graph.js y todos los colores soportados por CSS. Sin embargo, se necesitaría un equipo mas grande para poder añadir la función de soportar una gran cantidad de gráficos en un tiempo razonable.

# Conclusión

A lo largo del trabajo, se aprendió a utilizar las herramientas Flex y Bison para poder reconocer, parsear y generar código a partir de una cadena dada.

Sin embargo, lo que consideramos mas importante es que tuvimos la experiencia de entender como funciona un parser ascendente simple en su totalidad y como es su proceso de desarrollo.

Finalmente, el trabajo también ayudo a entender mas en profundidad algunos conceptos de la materia, como los conflictos Shift-Reduce o Reduce-Reduce de los parsers ascendentes, y del funcionamiento de las gramáticas.


