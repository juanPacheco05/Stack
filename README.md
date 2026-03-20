# Stack en C++ — Paradigma Genérico + Policy-Based Design

Este repositorio implementa una estructura de datos tipo pila (Stack) utilizando C++. La implementación aplica **programación genérica con plantillas (templates)** como paradigma de programación y **Policy-Based Design** como patrón de diseño, lo que permite separar la interfaz pública de la pila de su implementación interna de almacenamiento. Se incluyen dos políticas intercambiables: una basada en lista enlazada (`ListPolicy`) y otra basada en vector dinámico (`VectorPolicy`).

---

## Requerimientos de software

Para compilar y ejecutar este proyecto necesitas un compilador de C++ con soporte para el estándar **C++17** o superior.

### Opciones de compilador

| Windows | MinGW-w64 (g++) o MSVC | `g++ --version` |
| Linux | g++ (GNU Compiler Collection) | `g++ --version` |
| macOS | clang++ (viene con Xcode Tools) | `clang++ --version` |

### Instalación de g++ en Windows (MinGW-w64)

1. Descarga el instalador desde: https://www.mingw-w64.org/
2. Durante la instalación se selecciona la arquitectura `x86_64` y el hilo `posix`.
3. Agrega la ruta del compilador al PATH del sistema (típicamente `C:\mingw64\bin`).
4. Verifica la instalación abriendo una terminal nueva y ejecutando:

```g++ --version
```

Si devuelve una versión (ejemplo: `g++ 13.2.0`), la instalación fue exitosa.

### Cómo verificar si el PATH está configurado correctamente

#### Windows

Presiona `Win + R`, escribe `sysdm.cpl` y presiona Enter. Ve a **Opciones Avanzadas → Variables de Entorno**. En la sección *Variables del sistema*, busca `Path` y verifica que contenga la ruta al compilador. Si no está, agrégala y reinicia la terminal.

#### Linux / macOS

Abre la terminal y ejecuta:

```bash
which g++
```

Si devuelve una ruta (ejemplo: `/usr/bin/g++`), el compilador está disponible. Si no, instálalo con:

```bash
# Ubuntu / Debian
sudo apt install g++

# macOS (instala las herramientas de línea de comandos de Xcode)
xcode-select --install
```

---

## Clonación del repositorio

```bash
git clone https://github.com/usuario/Stack_Cpp.git
cd Stack_Cpp
```

---

## ¿Por qué usar C++?

C++ es un lenguaje de propósito general que extiende a C con herramientas fundamentales para el diseño de estructuras de datos:

> C++ permite expresar estructuras de datos genéricas con seguridad de tipos verificada en tiempo de compilación, sin costo en tiempo de ejecución.

> A diferencia de Java, C++ da control directo sobre la memoria, lo que permite entender exactamente qué ocurre cuando se crea o destruye un nodo.

> Con C++ se puede cambiar la implementación interna de una estructura de datos sin modificar su interfaz pública, gracias al sistema de plantillas y las políticas.

---

## ¿Cómo ejecutar el código?

### Compilación desde la terminal

Asegúrate de que todos los archivos estén en la misma carpeta:

```
proyecto/
├── MyStack.h
├── ListPolicy.h
├── VectorPolicy.h
└── Test.cpp
```

Abre la terminal en esa carpeta y ejecuta:

```bash
g++ -std=c++17 -Wall -o test Test.cpp
```

Luego ejecuta el programa compilado:

```bash
# Linux / macOS
./test

# Windows
test.exe
```

### Desde un IDE

Si usas **Visual Studio Code**, **CLion** o **Code::Blocks**:

1. Abre la carpeta del proyecto en el IDE.
2. Asegúrate de que el estándar C++17 esté configurado en las opciones del compilador.
3. Selecciona `Test.cpp` como archivo de entrada y ejecuta el build.

---

## Conceptos básicos de C++ usados en este proyecto

### 1. Variables y tipos de datos

C++ es un lenguaje de tipado estático: el tipo de cada variable se declara explícitamente y no puede cambiar.

```cpp
int    numero  = 42;          // entero
double decimal = 3.14;        // número con decimales
std::string texto = "hola";   // cadena de texto
bool   activo  = true;        // verdadero o falso
```

> En C++ no existe `var` ni `let`. Cada variable tiene un tipo fijo desde su declaración.

### 2. Punteros — la base de las estructuras dinámicas

Un puntero es una variable que guarda la **dirección de memoria** donde vive otro dato, en lugar del dato en sí. Es el mecanismo que permite construir estructuras dinámicas como listas enlazadas.

```cpp
int  valor    = 10;
int* puntero  = &valor;   // & obtiene la dirección de valor

std::cout << *puntero;    // * accede al dato en esa dirección → imprime 10

// nullptr es el equivalente de null en Java
int* vacio = nullptr;     // puntero que no apunta a nada válido
```

> En Java, todas las referencias a objetos son punteros gestionados automáticamente por la JVM. En C++, los punteros son explícitos y el programador controla su ciclo de vida.

### 3. Smart pointers — punteros con gestión automática de memoria

C++ moderno introduce los **punteros inteligentes** (smart pointers) que liberan la memoria automáticamente cuando el objeto ya no es necesario, eliminando el riesgo de memory leaks sin necesidad de un Garbage Collector.

```cpp
#include <memory>

// unique_ptr: un solo dueño — libera la memoria cuando sale del scope
std::unique_ptr<int> ptr = std::make_unique<int>(42);

std::cout << *ptr;   // 42
// La memoria se libera automáticamente al final del bloque
```

Este proyecto usa `unique_ptr` en `ListPolicy` para gestionar los nodos de la lista enlazada. Cuando se hace `pop()`, el nodo anterior se destruye automáticamente al mover la propiedad al siguiente.

### 4. Structs y clases

En C++, `struct` y `class` son casi idénticos. La única diferencia es que los miembros de `struct` son **públicos por defecto**, mientras que los de `class` son **privados por defecto**.

```cpp
// struct: usado para tipos simples de datos (como Node)
struct Node {
    int   value;
    Node* next;

    explicit Node(int v) : value(v), next(nullptr) {}
    //                   ↑ lista de inicialización: inicializa antes del cuerpo
};

// class: usado para tipos con lógica encapsulada (como MyStack)
class MyStack {
private:
    Node* top_ = nullptr;   // convencion: _ al final = campo privado

public:
    void push(int v) { /* ... */ }
    int  pop()       { /* ... */ }
};
```

### 5. Constructor y destructor

El **constructor** se ejecuta al crear un objeto. El **destructor** se ejecuta al destruirlo. En C++, el destructor es el lugar correcto para liberar recursos (memoria, archivos, conexiones).

```cpp
class Ejemplo {
public:
    Ejemplo()  { /* se ejecuta al crear   */ }
    ~Ejemplo() { /* se ejecuta al destruir */ }
};

{
    Ejemplo obj;   // constructor ejecutado aquí
}                  // destructor ejecutado aquí automáticamente
```

> En Java el destructor no existe porque el Garbage Collector se encarga de liberar. En C++, cuando se usan smart pointers, la liberación también es automática — pero el programador decide explícitamente cuándo y cómo.

### 6. Templates (plantillas)

Una plantilla le indica al compilador que **genere el código para cualquier tipo T** que se use. Es el equivalente de los genéricos de Java, pero con una diferencia clave: en C++ el compilador genera código completamente distinto por cada tipo instanciado, sin borrado de tipos (type erasure).

```cpp
// Sin templates: habría que escribir una pila para cada tipo
class IntStack    { void push(int v);    };
class StringStack { void push(string v); };

// Con templates: una sola definición sirve para todos los tipos
template <typename T>
class MyStack {
    void push(T value) { /* ... */ }
    T    pop()         { /* ... */ }
};

// El compilador genera el código concreto al momento de usar la plantilla:
MyStack<int>         s1;   // genera MyStack para int
MyStack<std::string> s2;   // genera MyStack para string
MyStack<double>      s3;   // genera MyStack para double
```

### 7. Condicionales y bucles

```cpp
// Condicional
int edad = 18;
if (edad >= 18) {
    std::cout << "Mayor de edad\n";
} else {
    std::cout << "Menor de edad\n";
}

// Bucle while — idéntico a Java
int i = 0;
while (i < 5) {
    std::cout << i << "\n";
    i++;
}

// Bucle for — idéntico a Java
for (int j = 0; j < 5; j++) {
    std::cout << j << "\n";
}
```

### 8. Funciones y métodos

```cpp
// Función libre (fuera de una clase)
int sumar(int a, int b) {
    return a + b;
}

// Método (dentro de una clase o struct)
class Calculadora {
public:
    int multiplicar(int a, int b) {
        return a * b;
    }
};
```

> En C++ no existen las arrow functions de JavaScript. Las funciones siempre se declaran con su tipo de retorno explícito.

### 9. Cómo mostrar resultados en pantalla

```cpp
#include <iostream>

std::cout << "Hola mundo\n";          // imprime texto
std::cout << "Valor: " << 42 << "\n"; // imprime texto + número
std::cerr << "Error: algo falló\n";   // salida de errores (stderr)
```

| JavaScript | C++ |
|---|---|
| `console.log("hola")` | `std::cout << "hola" << "\n"` |
| `console.log(x)` | `std::cout << x << "\n"` |
| `console.error("error")` | `std::cerr << "error" << "\n"` |

### 10. Manejo de errores — excepciones

```cpp
#include <stdexcept>

// Lanzar una excepción
void ejemplo() {
    throw std::underflow_error("Mensaje de error");
}

// Capturar una excepción
try {
    ejemplo();
} catch (const std::underflow_error& e) {
    std::cout << "Error capturado: " << e.what() << "\n";
}
```

> En el JavaScript de referencia, `pop()` retorna `undefined` si la pila está vacía. En esta implementación C++, `pop()` lanza `std::underflow_error` — el error es visible inmediatamente en el punto donde ocurre, en lugar de propagarse silenciosamente.

---

## Paradigma y patrón de diseño implementados

### Paradigma: Programación Genérica (templates)

El equivalente en C++ de la Programación Orientada a Objetos (POO) que usa el repositorio JavaScript de referencia. Mientras que en JavaScript/Java el código gira alrededor de objetos y clases, en esta implementación el código gira alrededor de **plantillas que el compilador instancia por cada tipo concreto**.

La clase `MyStack<T>` puede almacenar enteros, strings, doubles o cualquier otro tipo sin cambiar una sola línea de su código. El compilador genera la versión específica de la clase en tiempo de compilación, sin costo adicional en tiempo de ejecución.

### Patrón: Policy-Based Design

El equivalente en C++ del patrón MVP que usa el repositorio JavaScript de referencia. Así como MVP separa el Modelo, la Vista y el Presentador, Policy-Based Design separa **dos responsabilidades que en OOP clásico viven juntas en la misma clase**:

| Responsabilidad | Quién la tiene |
|---|---|
| Definir qué operaciones existen (push, pop, peek, isEmpty, size) | `MyStack<T>` |
| Decidir cómo se almacenan los datos internamente | La Policy (ListPolicy o VectorPolicy) |

Esta separación implementa dos principios SOLID de forma simultánea:

- **Single Responsibility Principle (SRP):** `MyStack` tiene una sola razón para cambiar — si la interfaz pública necesita una operación nueva. El almacenamiento es responsabilidad exclusiva de la Policy.
- **Open/Closed Principle (OCP):** el sistema está abierto para extensión (se puede agregar una nueva Policy sin tocar `MyStack`) y cerrado para modificación (agregar `VectorPolicy` no requirió cambiar ningún archivo existente).

### Encapsulamiento

`Node` es un `struct` privado anidado **dentro** de `ListPolicy::Container`. Ningún código fuera de la Policy sabe que `Node` existe. No se puede instanciar ni acceder a él desde `MyStack` ni desde `Test.cpp`.

`VectorPolicy::Container` encapsula `std::vector<T>` de la misma manera — el vector es un detalle de implementación que nadie fuera de la Policy puede tocar.

### Abstracción

`MyStack` expone una interfaz clara y uniforme (`push`, `pop`, `peek`, `isEmpty`, `size`) que funciona igual independientemente de qué Policy esté usando internamente. Quien usa la pila no necesita saber nada sobre nodos, punteros ni vectores.

### Modularidad

Cada pieza vive en su propio archivo de cabecera (`.h`), que puede incluirse de forma independiente:

```
MyStack.h       ← interfaz pública de la pila
ListPolicy.h    ← implementación con lista enlazada y unique_ptr
VectorPolicy.h  ← implementación con std::vector
Test.cpp        ← archivo de prueba y demostración
```

---

## Estructura de archivos

```
proyecto/
├── MyStack.h        # Clase principal. Define la interfaz pública de la pila.
│                    # Desconoce completamente cómo se almacenan los datos.
│
├── ListPolicy.h     # Policy de lista enlazada.
│                    # Contiene Node (struct privado) y toda la lógica de punteros.
│                    # Usa unique_ptr para gestión automática de memoria.
│
├── VectorPolicy.h   # Policy de vector dinámico.
│                    # Misma interfaz que ListPolicy, implementación con std::vector.
│                    # No tiene Node ni maneja punteros directamente.
│
└── Test.cpp         # Archivo de prueba.
                     # Demuestra las cuatro demos: int con ListPolicy,
                     # string con ListPolicy, int con VectorPolicy,
                     # double con VectorPolicy.
```

---

## Ejecución del código de prueba

El archivo `Test.cpp` contiene cuatro demostraciones que muestran el comportamiento de la pila con distintos tipos y políticas:

### Demo 1 — Pila de enteros con ListPolicy (lista enlazada)

```
============================================
 DEMO 1: Pila de enteros — ListPolicy
 (lista enlazada, Node vive dentro de la Policy)
============================================
Cima (peek): 30
Tamaño: 3

pop() → 30
pop() → 20
pop() → 10

Intentando pop() en pila vacía:
[EXCEPCIÓN]: pop() llamado en pila vacía.
```

### Demo 3 — La misma pila con VectorPolicy

```
============================================
 DEMO 3: La MISMA pila con VectorPolicy
 Stack no cambió nada — solo se pasó otra Policy
============================================
Cima (peek): 300
Tamaño: 3

pop() → 300
pop() → 200
pop() → 100
[EXCEPCIÓN]: pop() llamado en pila vacía.
```

> El punto central de la Demo 3 es que `MyStack` no cambió absolutamente nada. Solo se pasó `VectorPolicy` como segundo parámetro al instanciar la clase. El comportamiento externo es idéntico; la implementación interna es completamente distinta.

### Ejecutar en la terminal

```bash
# Compilar
g++ -std=c++17 -Wall -o test Test.cpp

# Ejecutar
./test          # Linux / macOS
test.exe        # Windows
```

---

## Comparativa con el repositorio JavaScript de referencia

| Aspecto | JavaScript (referencia) | C++ (esta implementación) |
|---|---|---|
| Paradigma | POO (Programación Orientada a Objetos) | Programación genérica (templates) |
| Patrón | MVP | Policy-Based Design |
| Tipo genérico | Dinámico — JS acepta cualquier tipo sin declararlo | `template <typename T>` — verificado en compilación |
| Nodo | `StackNode` — clase pública separada | `Node` — struct privado dentro de `ListPolicy` |
| Gestión de memoria | Motor de JS (Garbage Collector implícito) | `unique_ptr` — automática, determinista |
| Error en pila vacía | Retorna `undefined` silenciosamente | Lanza `std::underflow_error` — falla inmediata |
| Cambiar implementación interna | Modificar o heredar de `MyStack` | Escribir una nueva Policy. `MyStack` no se toca. |
| Archivos | Un `.js` por clase | Un `.h` por componente |

---

*Proyecto: Sergio Suárez y Juan Pachecho — C++ con Paradigma genérico y Policy-Based Design*
