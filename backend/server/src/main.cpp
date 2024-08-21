#include "core/routs/routs.h"
#include "core/model/cloude/cloude.h"
#include "core/model/repository/repository.h"
// #include "components/libpqxx/include/pqxx/pqxx"
#include <iostream>
int main(void){
    try
    {
        Model::cloude::Init();
        Model::repository::Init();
        Rout::Init();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    getchar();
    return 0;
}