#include <iostream>
#include "../include/printHello.hpp"
#include "../include/CSimpleSharedPtr.hpp"

#include <memory>

void real_shared_ptr()
{
    std::shared_ptr<CPrintHello> p_ptr = std::make_shared<CPrintHello>();

    std::cout << " ptr count = " << p_ptr.use_count() << std::endl;

    std::shared_ptr<CPrintHello> p_ptr1 = p_ptr;
    std::cout << " ptr count = " << p_ptr.use_count() << std::endl;
    std::cout << " ptr1 count = " << p_ptr1.use_count() << std::endl;
}
int main()
{
    CSimpleShared_prt<CPrintHello> p_Print(new CPrintHello);

    // auto p_Print2 = p_Print;
    CSimpleShared_prt<CPrintHello> p_Print2 ;
    p_Print2 = p_Print;
    std::cout << " p_Print count = " << p_Print.use_count() << std::endl;
    std::cout << " p_Print2 count = " << p_Print2.use_count() << std::endl;
    return 0;
}