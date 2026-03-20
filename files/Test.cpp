

#include <iostream>
#include <string>
#include <stdexcept>
#include "MyStack.h"        
#include "VectorPolicy.h"   

int main() {

    std::cout << "============================================\n";
    std::cout << " DEMO 1: Pila de enteros — ListPolicy\n";
    std::cout << " (lista enlazada, Node vive dentro de la Policy)\n";
    std::cout << "============================================\n";

    MyStack<int> intStack;

    intStack.push(10);
    intStack.push(20);
    intStack.push(30);

    std::cout << "Cima (peek): " << intStack.peek() << "\n";
    std::cout << "Tamaño: "      << intStack.size() << "\n\n";

    while (!intStack.isEmpty()) {
        std::cout << "pop() → " << intStack.pop() << "\n";
    }

    std::cout << "\nIntentando pop() en pila vacía:\n";
    try {
        intStack.pop();
    } catch (const std::underflow_error& e) {
        std::cerr << "[EXCEPCIÓN]: " << e.what() << "\n";
    }

    std::cout << "\n============================================\n";
    std::cout << " DEMO 2: Pila de strings — ListPolicy\n";
    std::cout << "============================================\n";

    MyStack<std::string> strStack;
    strStack.push("Hola");
    strStack.push("Mundo");
    strStack.push("C++");

    while (!strStack.isEmpty()) {
        std::cout << "pop() → " << strStack.pop() << "\n";
    }

    std::cout << "\n============================================\n";
    std::cout << " DEMO 3: La MISMA pila con VectorPolicy\n";
    std::cout << " Stack no cambió nada — solo se pasó otra Policy\n";
    std::cout << "============================================\n";

    MyStack<int, VectorPolicy> vecStack;

    vecStack.push(100);
    vecStack.push(200);
    vecStack.push(300);

    std::cout << "Cima (peek): " << vecStack.peek() << "\n";
    std::cout << "Tamaño: "      << vecStack.size() << "\n\n";

    while (!vecStack.isEmpty()) {
        std::cout << "pop() → " << vecStack.pop() << "\n";
    }

    try {
        vecStack.pop();
    } catch (const std::underflow_error& e) {
        std::cerr << "[EXCEPCIÓN]: " << e.what() << "\n";
    }


    std::cout << "\n============================================\n";
    std::cout << " DEMO 4: Pila de doubles — VectorPolicy\n";
    std::cout << " Equivalente a los push() de tipos en Test.js\n";
    std::cout << "============================================\n";

    MyStack<double, VectorPolicy> doubleStack;
    doubleStack.push(3.14);
    doubleStack.push(2.71);
    doubleStack.push(1.41);

    while (!doubleStack.isEmpty()) {
        std::cout << "pop() → " << doubleStack.pop() << "\n";
    }

    std::cout << "\n============================================\n";
    std::cout << " Proyecto: Wilson Soledad, Sergio Suárez\n";
    std::cout << " C++ — Paradigma genérico + Policy-Based Design\n";
    std::cout << "============================================\n";

    return 0;
}
