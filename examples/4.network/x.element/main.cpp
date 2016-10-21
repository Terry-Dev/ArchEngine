#include <iostream>
#include <network/html/element.hpp>

using namespace arch;

int main(void)
{
    network::html::element html("html");
    html << "head" << "title" = "'helloworld;'";
    html << "body" << "h1" = "Hello world.";
    html << "body" << "h2" = "Welcome to ArchEngine world!";
    std::cout << html.to_string();
    std::cin.get();
    return 0;
}
