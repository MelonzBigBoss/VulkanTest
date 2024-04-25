#include <iostream>

#include "Renderer.h"

int main(int argc, char* argv[]) {
  std::cout<< "Program Started" << std::endl;
  std::cout<<argv[0]<<std::endl; 
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
