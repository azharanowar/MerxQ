#ifndef ADMIN_H
#define ADMIN_H

#include "user.h"
#include <string>

using namespace std;

// ============================================
// ADMIN CLASS (Derived from User)
// ============================================
// Demonstrates: Inheritance, Method Overriding

class Admin : public User {
private:
  string department;
  bool superAdmin; // Can manage other admins

public:
  // Constructor
  Admin(int id, const string &name, const string &email, const string &password,
        const string &department = "General", bool superAdmin = false);

  // ============================================
  // OVERRIDE PURE VIRTUAL (Required)
  // ============================================
  void displayMenu() override;

  // ============================================
  // OVERRIDE VIRTUAL FUNCTIONS
  // ============================================
  void displayInfo() const override;

  // ============================================
  // ADMIN-SPECIFIC METHODS (Inventory Management)
  // ============================================
  void viewInventory();
  void addProduct();
  void updateProduct(int productId);
  void deleteProduct(int productId);

  // ============================================
  // ADMIN-SPECIFIC METHODS (Order Management)
  // ============================================
  void viewAllOrders();
  void updateOrderStatus(int orderId);

  // ============================================
  // ADMIN-SPECIFIC METHODS (User Management)
  // ============================================
  void viewAllUsers();

  // ============================================
  // GETTERS & SETTERS
  // ============================================
  string getDepartment() const { return department; }
  bool isSuperAdmin() const { return superAdmin; }

  void setDepartment(const string &newDepartment);
  void setSuperAdmin(bool status);
};

#endif
