#include "../include/admin.h"
#include <iostream>

using namespace std;

// ============================================
// CONSTRUCTOR
// ============================================

Admin::Admin(int id, const string &name, const string &email,
             const string &password, const string &department, bool superAdmin)
    : User(id, name, email, password, "admin"), department(department),
      superAdmin(superAdmin) {}

// ============================================
// OVERRIDE: DISPLAY MENU
// ============================================

void Admin::displayMenu() {
  Utils::showSubHeader("Admin Control Panel");

  cout << Utils::colorText("  📦 Inventory Management", "yellow", "", "bold")
       << endl;
  cout << Utils::colorText("  1. ", "yellow") << "View Inventory" << endl;
  cout << Utils::colorText("  2. ", "yellow") << "Add New Product" << endl;
  cout << Utils::colorText("  3. ", "yellow") << "Update Product" << endl;
  cout << Utils::colorText("  4. ", "yellow") << "Delete Product" << endl;
  cout << endl;

  cout << Utils::colorText("  📋 Order Management", "yellow", "", "bold")
       << endl;
  cout << Utils::colorText("  5. ", "yellow") << "View All Orders" << endl;
  cout << Utils::colorText("  6. ", "yellow") << "Update Order Status" << endl;
  cout << endl;

  if (superAdmin) {
    cout << Utils::colorText("  👥 User Management", "yellow", "", "bold")
         << endl;
    cout << Utils::colorText("  7. ", "yellow") << "View All Users" << endl;
    cout << endl;
  }

  cout << Utils::colorText("  0. ", "red") << "Logout" << endl;
  cout << endl;
}

// ============================================
// OVERRIDE: DISPLAY INFO
// ============================================

void Admin::displayInfo() const {
  // Call base class method first
  User::displayInfo();

  // Add admin-specific info
  cout << Utils::colorText("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━", "yellow") << endl;
  cout << Utils::colorText("  Admin Details", "yellow", "", "bold") << endl;
  cout << Utils::colorText("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━", "yellow") << endl;
  cout << "  Department:  " << Utils::colorText(department, "white", "", "bold")
       << endl;
  cout << "  Super Admin: "
       << Utils::colorText(superAdmin ? "Yes ⭐" : "No",
                           superAdmin ? "green" : "yellow")
       << endl;
  cout << Utils::colorText("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━", "yellow") << endl;
}

// ============================================
// INVENTORY MANAGEMENT
// ============================================

void Admin::viewInventory() {
  Utils::showSubHeader("Inventory Overview");
  // TODO: Will be implemented with Product class
  cout << Utils::colorText("   📦 Loading inventory...", "yellow") << endl;
  cout << Utils::colorText("   (Product catalog coming soon!)", "yellow")
       << endl;
}

void Admin::addProduct() {
  Utils::showSubHeader("Add New Product");
  // TODO: Will be implemented with Product class
  cout << Utils::colorText("   ➕ Add product form...", "yellow") << endl;
  cout << Utils::colorText("   (Product management coming soon!)", "yellow")
       << endl;
}

void Admin::updateProduct(int productId) {
  Utils::showSubHeader("Update Product #" + to_string(productId));
  // TODO: Will be implemented with Product class
  cout << Utils::colorText("   ✏️ Edit product form...", "yellow") << endl;
  cout << Utils::colorText("   (Product management coming soon!)", "yellow")
       << endl;
}

void Admin::deleteProduct(int productId) {
  // TODO: Will be implemented with Product class
  cout << Utils::colorText(
              "   🗑️ Deleting product #" + to_string(productId) + "...", "red")
       << endl;
  cout << Utils::colorText("   (Product management coming soon!)", "yellow")
       << endl;
}

// ============================================
// ORDER MANAGEMENT
// ============================================

void Admin::viewAllOrders() {
  Utils::showSubHeader("All Customer Orders");
  // TODO: Will be implemented with Order class
  cout << Utils::colorText("   📋 Loading orders...", "yellow") << endl;
  cout << Utils::colorText("   (Order management coming soon!)", "yellow")
       << endl;
}

void Admin::updateOrderStatus(int orderId) {
  // TODO: Will be implemented with Order class
  cout << Utils::colorText(
              "   📝 Updating order #" + to_string(orderId) + "...", "yellow")
       << endl;
  cout << Utils::colorText("   (Order management coming soon!)", "yellow")
       << endl;
}

// ============================================
// USER MANAGEMENT (Super Admin only)
// ============================================

void Admin::viewAllUsers() {
  if (!superAdmin) {
    cout << Utils::colorText("   ✗ Access denied! Super Admin only.", "red")
         << endl;
    return;
  }

  Utils::showSubHeader("All Users");
  // TODO: Will be implemented with FileManager
  cout << Utils::colorText("   👥 Loading users...", "yellow") << endl;
  cout << Utils::colorText("   (User management coming soon!)", "yellow")
       << endl;
}

// ============================================
// SETTERS
// ============================================

void Admin::setDepartment(const string &newDepartment) {
  if (!newDepartment.empty()) {
    department = newDepartment;
  }
}

void Admin::setSuperAdmin(bool status) { superAdmin = status; }
