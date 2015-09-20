#include <iostream>
int main() {
  int a = 0;
  while ( true ) {
    std::cin >> a ;
    if (a == 42)
      break;
    std::cout << a << std::endl;
  }
}
