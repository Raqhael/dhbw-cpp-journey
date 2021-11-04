#include <csignal>
#include <iostream>

void handle_fault(int sig)
{
    while(true){
    printf("Kleiner Tipp: https://www.dhbw-stuttgart.de/fileadmin/dateien-horb/PDFs/Antrag_Exmat_Stand_April_2018-Campus_Horb.pidf\n");
    }
    std::exit(sig);
}

int main()
{
    std::signal(SIGSEGV, handle_fault);
    // std::raise(SIGSEGV);
    int *p = nullptr;
    *p = 42;
    return 0;
}