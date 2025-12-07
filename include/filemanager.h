#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "admin.h"
#include "customer.h"
#include "order.h"
#include "product.h"
#include <memory>
#include <string>
#include <vector>

using namespace std;

// ============================================
// FILE MANAGER CLASS (Static)
// ============================================
// Handles JSON file I/O for data persistence

class FileManager {
private:
  // File paths
  static const string PRODUCTS_FILE;
  static const string USERS_FILE;
  static const string ORDERS_FILE;

public:
  // ============================================
  // PRODUCTS
  // ============================================
  static vector<Product> loadProducts();
  static void saveProducts(const vector<Product> &products);
  static Product findProduct(const string &productId);
  static void updateProduct(const Product &product);
  static void deleteProduct(const string &productId);
  static string generateProductId();

  // ============================================
  // USERS
  // ============================================
  static vector<shared_ptr<User>> loadUsers();
  static void saveUsers(const vector<shared_ptr<User>> &users);
  static shared_ptr<User> findUserByEmail(const string &email);
  static shared_ptr<User> findUserById(int userId);
  static void addUser(shared_ptr<User> user);
  static int generateUserId();

  // ============================================
  // ORDERS
  // ============================================
  static vector<Order> loadOrders();
  static void saveOrders(const vector<Order> &orders);
  static vector<Order> getCustomerOrders(int customerId);
  static void addOrder(const Order &order);
  static void updateOrderStatus(const string &orderId, OrderStatus status);
  static string generateOrderId();

  // ============================================
  // UTILITY
  // ============================================
  static bool fileExists(const string &filename);
  static void ensureDataDirectory();
};

#endif
