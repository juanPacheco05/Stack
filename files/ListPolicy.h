#pragma once
#include <memory>
#include <stdexcept>

// ============================================================
//  ListPolicy.h
//  Policy de almacenamiento basada en lista enlazada.
//
//  Según el documento (sección 1.3 y 2.5):
//    "El Node vive como struct privado dentro de la Policy.
//     Nadie externo lo ve."
//    "Stack no sabe nada de Node ni de punteros.
//     Cambiar la implementación = escribir una nueva Policy."
//
//  Esta policy encapsula TODO lo relacionado con la lista
//  enlazada: el nodo, los punteros, el push y el pop.
//  MyStack no ve nada de esto.
// ============================================================

struct ListPolicy {

    /**
     * Container<T> es la clase que MyStack instancia internamente.
     * MyStack le pide a ListPolicy su Container para el tipo T,
     * y delega en él todas las operaciones de almacenamiento.
     *
     * Equivale al patrón del documento (sección 2.5):
     *   typename Policy::template Container<T> storage_;
     */
    template <typename T>
    struct Container {
    private:

        // --------------------------------------------------------
        //  Node — struct privado dentro de la Policy
        //  Nadie fuera de ListPolicy puede ver ni instanciar Node.
        //  Esto cumple la tabla de la sección 1.3 del documento:
        //  "Struct privado dentro de la Policy. Nadie externo lo ve."
        // --------------------------------------------------------
        struct Node {
            T value;
            std::unique_ptr<Node> next;

            /**
             * Constructor con lista de inicialización.
             * Más eficiente que asignar en el cuerpo (sección 2.3).
             */
            explicit Node(T val, std::unique_ptr<Node> nxt = nullptr)
                : value(std::move(val)), next(std::move(nxt)) {}
        };

        // Puntero a la cima de la pila
        std::unique_ptr<Node> top_;
        std::size_t size_ = 0;

    public:

        /**
         * Inserta un elemento en la cima. O(1).
         * Crea un nuevo Node que apunta al top_ actual,
         * luego top_ pasa a ser ese nuevo nodo.
         */
        void push(T value) {
            auto newNode = std::make_unique<Node>(std::move(value), std::move(top_));
            top_ = std::move(newNode);
            ++size_;
        }

        /**
         * Elimina y retorna el elemento en la cima. O(1).
         * Lanza excepción si la pila está vacía (sección 2.7).
         */
        T pop() {
            if (isEmpty())
                throw std::underflow_error("pop() llamado en pila vacía.");
            T val = std::move(top_->value);
            top_ = std::move(top_->next); // el nodo viejo se destruye solo (unique_ptr)
            --size_;
            return val;
        }

        /** Retorna el valor en la cima sin eliminarlo. */
        const T& peek() const {
            if (isEmpty())
                throw std::underflow_error("peek() llamado en pila vacía.");
            return top_->value;
        }

        /** @return true si no hay elementos. */
        bool isEmpty() const { return top_ == nullptr; }

        /** @return Número de elementos. */
        std::size_t size() const { return size_; }
    };
};
