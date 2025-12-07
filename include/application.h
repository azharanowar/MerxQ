#ifndef APPLICATION_H
#define APPLICATION_H

#include "admin.h"
#include "cart.h"
#include "customer.h"
#include "filemanager.h"
#include "order.h"
#include "product.h"
#include <memory>
#include <vector>

using namespace std;

// ============================================
// APPLICATION CLASS
// ============================================
// Main application orchestrator - ties all systems together

class Application {
private:
  vector<Product> products;
  vector<shared_ptr<User>> users;
  vector<Order> orders;
  shared_ptr<User> currentUser;
  Cart currentCart;
  bool running;

  // ============================================
  // MAIN MENUS
  // ============================================
  void showMainMenu();
  void showCustomerMenu();
  void showAdminMenu();

  // ============================================
  // AUTHENTICATION
  // ============================================
  void login();
  void registerCustomer();
  void logout();

  // ============================================
  // CUSTOMER FEATURES
  // ============================================
  void browseProducts();
  void searchProducts();
  void addToCart();
  void viewCart();
  void checkout();
  void viewOrderHistory();
  void viewProfile();

  // ============================================
  // ADMIN FEATURES
  // ============================================
  void viewInventory();
  void addProduct();
  void updateProduct();
  void deleteProduct();
  void viewAllOrders();
  void updateOrderStatus();
  void viewAllUsers();

  // ============================================
  // HELPERS
  // ============================================
  void loadData();
  void displayProductList() const;
  Product *findProductById(const string &productId);

public:
  Application();

  // ============================================
  // MAIN ENTRY POINT
  // ============================================
  void run();
};

#endif
