#include <iostream>

int main(int argc, char *argv[]) 
{
    Concurrent::run(InputGen:gen_input(400),6,5);
    return 0;
}