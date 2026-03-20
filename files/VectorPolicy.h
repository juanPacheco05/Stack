#pragma once
#include <vector>
#include <stdexcept>

// ============================================================
//  VectorPolicy.h
//  Policy de almacenamiento basada en std::vector.
//
//  Mencionada en el documento (sección 3, paso 6):
//    "VectorPolicy: escribir la segunda policy con std::vector.
//     Confirmar que Stack funciona igual."
//
//  Demuestra el Open/Closed Principle (sección 2.5):
//    - Abierto para extensión: nueva Policy sin tocar Stack.
//    - Cerrado para modificación: MyStack no cambia nada.
//
//  Misma interfaz que ListPolicy::Container<T>,
//  implementación completamente diferente por dentro.
// ============================================================

struct VectorPolicy {

    template <typename T>
    struct Container {
    private:
        // Aquí no hay Node ni punteros.
        // El almacenamiento interno es un std::vector.
        // MyStack no sabe ni le importa.
        std::vector<T> data_;

    public:

        /** Inserta en la cima (final del vector). O(1) amortizado. */
        void push(T value) {
            data_.push_back(std::move(value));
        }

        /** Elimina y retorna el último elemento. O(1). */
        T pop() {
            if (isEmpty())
                throw std::underflow_error("pop() llamado en pila vacía.");
            T val = std::move(data_.back());
            data_.pop_back();
            return val;
        }

        /** Retorna el último elemento sin eliminarlo. */
        const T& peek() const {
            if (isEmpty())
                throw std::underflow_error("peek() llamado en pila vacía.");
            return data_.back();
        }

        /** @return true si no hay elementos. */
        bool isEmpty() const { return data_.empty(); }

        /** @return Número de elementos. */
        std::size_t size() const { return data_.size(); }
    };
};
