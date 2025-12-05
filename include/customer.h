#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "user.h"
#include <string>
#include <vector>

using namespace std;

// ============================================
// CUSTOMER CLASS (Derived from User)
// ============================================
// Demonstrates: Inheritance, Method Overriding

class Customer : public User {
private:
  string address;
  string phone;
  vector<int> cartProductIds; // Cart stores product IDs
  vector<int> orderIds;       // Past order IDs

public:
  // Constructor
  Customer(int id, const string &name, const string &email,
           const string &password, const string &address = "",
           const string &phone = "");

  // ============================================
  // OVERRIDE PURE VIRTUAL (Required)
  // ============================================
  void displayMenu() override;

  // ============================================
  // OVERRIDE VIRTUAL FUNCTIONS
  // ============================================
  void displayInfo() const override;

  // ============================================
  // CUSTOMER-SPECIFIC METHODS
  // ============================================
  void browseProducts();
  void addToCart(int productId);
  void removeFromCart(int productId);
  void viewCart() const;
  void clearCart();
  void placeOrder();
  void viewOrderHistory() const;

  // ============================================
  // GETTERS & SETTERS
  // ============================================
  string getAddress() const { return address; }
  string getPhone() const { return phone; }
  vector<int> getCart() const { return cartProductIds; }
  int getCartSize() const { return cartProductIds.size(); }

  void setAddress(const string &newAddress);
  void setPhone(const string &newPhone);
};

#endif
