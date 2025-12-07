#include "../include/application.h"
#include <iostream>

using namespace std;

/**
 * MerxQ - Online Shop & Inventory System
 * A CLI-based online shopping and inventory management system
 * demonstrating Object-Oriented Programming principles.
 *
 * Contributors:
 * - Md Anwar Hosen (Azhar Anowar)
 * - Al-Rafi Azad
 * - Md Arafat Hossain
 * - Taohidul Islam
 */

int main() {
  try {
    Application app;
    app.run();
  } catch (const exception &e) {
    cerr << "Fatal error: " << e.what() << endl;
    return 1;
  }

  return 0;
}
