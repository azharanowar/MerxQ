#include "../include/admin.h"
#include "../include/customer.h"
#include "../include/utils.h"
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

/**
 * MerxQ - Online Shop & Inventory System
 * Phase 2: User Class Hierarchy Demo
 * Demonstrates: Inheritance, Polymorphism, Encapsulation
 */

void demonstratePolymorphism(User *user) {
  // This function takes a base class pointer
  // but calls the derived class methods - POLYMORPHISM!
  cout << Utils::colorText("Calling displayMenu() through User pointer:",
                           "yellow")
       << endl;
  user->displayMenu();
}

int main() {
  Utils::clearScreen();

  Utils::showMainHeader("🛒 MerxQ Shop System 🛒");

  cout << Utils::colorText("Welcome to MerxQ!", "green", "", "bold") << endl;
  cout << Utils::colorText("Your online shopping solution", "cyan") << endl
       << endl;

  // ============================================
  // PHASE 2: USER HIERARCHY DEMONSTRATION
  // ============================================

  Utils::showSubHeader("Phase 2: User Hierarchy Complete! ✓");

  cout << Utils::colorText("✓", "green", "", "bold")
       << " Exception classes implemented" << endl;
  cout << Utils::colorText("✓", "green", "", "bold")
       << " User base class created" << endl;
  cout << Utils::colorText("✓", "green", "", "bold")
       << " Customer class (derived)" << endl;
  cout << Utils::colorText("✓", "green", "", "bold") << " Admin class (derived)"
       << endl
       << endl;

  Utils::showLoading("Initializing polymorphism demo", 1);

  // ============================================
  // CREATE SAMPLE USERS
  // ============================================

  Utils::showSubHeader("Creating User Objects");

  // Create a Customer
  Customer customer1(1, "Anwar Hosen", "anwar@email.com", "pass123",
                     "123 Main Street, Dhaka", "01700000001");

  // Create an Admin
  Admin admin1(100, "Super Admin", "admin@merxq.com", "admin123", "Management",
               true);

  cout << Utils::colorText("✓", "green")
       << " Created Customer: " << Utils::colorText(customer1.getName(), "cyan")
       << endl;
  cout << Utils::colorText("✓", "green")
       << " Created Admin: " << Utils::colorText(admin1.getName(), "magenta")
       << endl
       << endl;

  // ============================================
  // DISPLAY USER INFO (Virtual Function Demo)
  // ============================================

  Utils::showSubHeader("User Information (Virtual Override Demo)");

  customer1.displayInfo();
  cout << endl;
  admin1.displayInfo();
  cout << endl;

  // ============================================
  // POLYMORPHISM DEMONSTRATION
  // ============================================

  Utils::showSubHeader("Polymorphism Demo (Base Pointer → Derived Method)");

  // Store different user types in base class pointers
  vector<User *> users = {&customer1, &admin1};

  for (User *user : users) {
    cout << Utils::colorText("━━━ " + user->getName() + " (" + user->getRole() +
                                 ") ━━━",
                             "white", "", "bold")
         << endl;
    demonstratePolymorphism(user);
  }

  // ============================================
  // CART DEMONSTRATION
  // ============================================

  Utils::showSubHeader("Cart Operations Demo");

  customer1.viewCart();
  customer1.addToCart(101);
  customer1.addToCart(102);
  customer1.addToCart(103);
  customer1.viewCart();

  // ============================================
  // NEXT STEPS
  // ============================================

  cout << endl;
  cout << Utils::colorText("📝 Next Phase:", "yellow", "", "bold") << endl;
  cout << "  1. Create Product class" << endl;
  cout << "  2. Implement Cart with real products" << endl;
  cout << "  3. Add Order management" << endl;
  cout << "  4. File persistence (JSON)" << endl << endl;

  cout << Utils::colorText("Phase 2 Complete! 🎉", "green", "", "bold") << endl
       << endl;

  Utils::pauseScreen();

  return 0;
}
