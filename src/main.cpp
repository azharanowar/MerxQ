#include "utils.h"
#include <iostream>

using namespace std;

/**
 * MerxQ - Online Shop & Inventory System
 *
 * This is a temporary main file for testing the initial setup.
 * Full application logic will be implemented later.
 */

int main() {
  // Test the Utils class
  Utils::clearScreen();

  Utils::showMainHeader("🛒 MerxQ Shop System 🛒");

  cout << Utils::colorText("Welcome to MerxQ!", "green", "", "bold") << endl;
  cout << Utils::colorText("Your online shopping solution", "cyan") << endl
       << endl;

  Utils::showSubHeader("Initial Setup Complete");

  cout << Utils::colorText("✓", "green", "", "bold")
       << " Project structure created" << endl;
  cout << Utils::colorText("✓", "green", "", "bold")
       << " Utility functions working" << endl;
  cout << Utils::colorText("✓", "green", "", "bold")
       << " Color system operational" << endl
       << endl;

  Utils::showLoading("Loading system", 2);

  cout << endl;
  cout << Utils::colorText("📝 Next Steps:", "yellow", "", "bold") << endl;
  cout << "  1. Implement exception classes" << endl;
  cout << "  2. Create User base class" << endl;
  cout << "  3. Build Customer and Admin classes" << endl;
  cout << "  4. Add product management" << endl << endl;

  cout << Utils::colorText("System ready for development! 🚀", "magenta", "",
                           "bold")
       << endl
       << endl;

  Utils::pauseScreen();

  return 0;
}
