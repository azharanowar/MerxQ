#include "../include/customer.h"
#include <algorithm>
#include <iostream>

using namespace std;

// ============================================
// CONSTRUCTOR
// ============================================

Customer::Customer(int id, const string &name, const string &email,
                   const string &password, const string &address,
                   const string &phone)
    : User(id, name, email, password, "customer"), address(address),
      phone(phone) {}

// ============================================
// OVERRIDE: DISPLAY MENU
// ============================================

void Customer::displayMenu() {
  Utils::showSubHeader("Customer Menu");

  cout << Utils::colorText("  1. ", "yellow") << "Browse Products" << endl;
  cout << Utils::colorText("  2. ", "yellow") << "View Cart"
       << Utils::colorText(" [" + to_string(cartProductIds.size()) + " items]",
                           "yellow")
       << endl;
  cout << Utils::colorText("  3. ", "yellow") << "Place Order" << endl;
  cout << Utils::colorText("  4. ", "yellow") << "Order History" << endl;
  cout << Utils::colorText("  5. ", "yellow") << "My Profile" << endl;
  cout << Utils::colorText("  0. ", "red") << "Logout" << endl;
  cout << endl;
}

// ============================================
// OVERRIDE: DISPLAY INFO
// ============================================

void Customer::displayInfo() const {
  // Call base class method first
  User::displayInfo();

  // Add customer-specific info
  cout << Utils::colorText("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━", "green") << endl;
  cout << Utils::colorText("  Customer Details", "green", "", "bold") << endl;
  cout << Utils::colorText("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━", "green") << endl;
  cout << "  Address: "
       << Utils::colorText(address.empty() ? "Not set" : address, "white")
       << endl;
  cout << "  Phone:   "
       << Utils::colorText(phone.empty() ? "Not set" : phone, "white") << endl;
  cout << "  Cart:    "
       << Utils::colorText(to_string(cartProductIds.size()) + " items",
                           "yellow")
       << endl;
  cout << Utils::colorText("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━", "green") << endl;
}

// ============================================
// CART OPERATIONS
// ============================================

void Customer::browseProducts() {
  // TODO: Will be implemented with Product class
  cout << Utils::colorText("📦 Browsing products...", "yellow") << endl;
  cout << Utils::colorText("   (Product catalog coming soon!)", "yellow")
       << endl;
}

void Customer::addToCart(int productId) {
  cartProductIds.push_back(productId);
  cout << Utils::colorText("✓ Product added to cart!", "green") << endl;
}

void Customer::removeFromCart(int productId) {
  auto it = find(cartProductIds.begin(), cartProductIds.end(), productId);
  if (it != cartProductIds.end()) {
    cartProductIds.erase(it);
    cout << Utils::colorText("✓ Product removed from cart!", "green") << endl;
  } else {
    cout << Utils::colorText("✗ Product not found in cart!", "red") << endl;
  }
}

void Customer::viewCart() const {
  Utils::showSubHeader("Your Shopping Cart");

  if (cartProductIds.empty()) {
    cout << Utils::colorText("   Your cart is empty 🛒", "yellow") << endl;
  } else {
    cout << "   Items in cart: "
         << Utils::colorText(to_string(cartProductIds.size()), "green", "",
                             "bold")
         << endl;
    // TODO: Display actual product details when Product class is ready
    for (size_t i = 0; i < cartProductIds.size(); i++) {
      cout << "   " << (i + 1) << ". Product ID: " << cartProductIds[i] << endl;
    }
  }
  cout << endl;
}

void Customer::clearCart() {
  cartProductIds.clear();
  cout << Utils::colorText("✓ Cart cleared!", "green") << endl;
}

void Customer::placeOrder() {
  if (cartProductIds.empty()) {
    cout << Utils::colorText("✗ Cannot place order - cart is empty!", "red")
         << endl;
    return;
  }

  // TODO: Will create actual Order when Order class is ready
  cout << Utils::colorText("🎉 Order placed successfully!", "green", "", "bold")
       << endl;
  cout << Utils::colorText("   Thank you for shopping with MerxQ!", "yellow")
       << endl;
  clearCart();
}

void Customer::viewOrderHistory() const {
  Utils::showSubHeader("Order History");

  if (orderIds.empty()) {
    cout << Utils::colorText("   No orders yet. Start shopping! 🛍️", "yellow")
         << endl;
  } else {
    // TODO: Display actual order details when Order class is ready
    cout << "   Total orders: " << orderIds.size() << endl;
  }
  cout << endl;
}

// ============================================
// SETTERS
// ============================================

void Customer::setAddress(const string &newAddress) {
  if (!newAddress.empty()) {
    address = newAddress;
  }
}

void Customer::setPhone(const string &newPhone) {
  // Basic phone validation - at least 10 digits
  if (newPhone.length() >= 10) {
    phone = newPhone;
  }
}
