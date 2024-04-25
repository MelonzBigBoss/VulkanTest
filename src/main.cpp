#include <iostream>

#include "Renderer.h"

int main() {
  std::cout<< "Program Started" << std::endl;

  Renderer* mainApp = new Renderer();

  try {
    mainApp->start();
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;

    int n;
    std::cin >> n;
  }

  delete mainApp;
  
  return 0;
}
