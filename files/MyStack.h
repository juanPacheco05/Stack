#pragma once
#include "ListPolicy.h"

// ============================================================
//  MyStack.h
//  La clase principal de la pila.
//
//  Según el documento (sección 1.3 y 2.5):
//    "Stack solo define la interfaz.
//     El almacenamiento es de la Policy."
//    "Stack no sabe nada de Node ni de punteros."
//
//  MyStack recibe la Policy como parámetro template y
//  delega TODO el almacenamiento en Policy::Container<T>.
//  MyStack nunca menciona Node, next, unique_ptr ni punteros.
//
//  Esto implementa dos principios SOLID (sección 2.5):
//    - SRP: MyStack tiene una sola razón para cambiar — su interfaz.
//    - Open/Closed: se extiende con nuevas Policies sin tocar MyStack.
// ============================================================

/**
 * @brief Pila genérica con Policy-Based Design.
 *
 * @tparam T      Tipo del dato a almacenar.
 * @tparam Policy Política de almacenamiento (por defecto: ListPolicy).
 *
 * Uso:
 *   MyStack<int>                     → lista enlazada (por defecto)
 *   MyStack<int, VectorPolicy>       → almacenamiento con vector
 *
 * Equivalencias con MyStack.js:
 *   push()   → push()
 *   pop()    → pop()
 *   peek()   → peek()
 *   isEmpty()→ isEmpty()
 */
template <typename T, typename Policy = ListPolicy>
class MyStack {
private:
    // Le pide a la Policy su Container para el tipo T.
    // MyStack no sabe qué hay dentro de storage_:
    // puede ser una lista enlazada, un vector, o cualquier otra cosa.
    typename Policy::template Container<T> storage_;

public:

    /**
     * Inserta un elemento en la cima de la pila.
     * Delega completamente en la Policy.
     */
    void push(T value) {
        storage_.push(std::move(value));
    }

    /**
     * Elimina y retorna el elemento en la cima.
     * Delega completamente en la Policy.
     */
    T pop() {
        return storage_.pop();
    }

    /**
     * Retorna el elemento en la cima SIN eliminarlo.
     * Delega completamente en la Policy.
     */
    const T& peek() const {
        return storage_.peek();
    }

    /** @return true si la pila no tiene elementos. */
    bool isEmpty() const {
        return storage_.isEmpty();
    }

    /** @return Número de elementos en la pila. */
    std::size_t size() const {
        return storage_.size();
    }
};
