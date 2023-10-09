#ifndef GENERAL_HPP
#define GENERAL_HPP

#include <cstddef>
#include <tuple>
#include <memory>
#include <iostream>

namespace Container
{

    enum cont_status
    {
        CONT_OK =0,
        CONT_NOK,
    };

    template <class T>
    class container_ptr : public std::shared_ptr<T>
    {
        public:
            // T* operator -> ()
            // {
            //     // std::cout << "get" << std::endl;
            //     return this->get();
            // }

            // container_ptr<T>& operator = (const container_ptr<T>& a)
            // {
            //     std::cout << "const copy " << a << std::endl;
            //     return *this;
            // }

            // container_ptr<T>& operator = (container_ptr<T> a)
            // {
            //     std::cout << "copy " << a << std::endl;
            //     return *this;
            // }

            // container_ptr<T>& operator = (container_ptr<T>&& a)
            // {
            //     std::cout << "move" << std::endl;
            //     return *this;
            // }
    };

}; // Container

#endif // GENERAL_HPP
