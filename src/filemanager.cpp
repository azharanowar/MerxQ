#include "../include/filemanager.h"
#include "../include/exceptions.h"
#include "../lib/json.hpp"
#include <fstream>
#include <iomanip>
#include <sstream>

using json = nlohmann::ordered_json;

// ============================================
// FILE PATHS
// ============================================

const string FileManager::PRODUCTS_FILE = "data/products.json";
const string FileManager::USERS_FILE = "data/users.json";
const string FileManager::ORDERS_FILE = "data/orders.json";

// ============================================
// UTILITY
// ============================================

bool FileManager::fileExists(const string &filename) {
  ifstream file(filename);
  return file.good();
}

void FileManager::ensureDataDirectory() {
  // Data directory should exist, but we'll check files exist
  if (!fileExists(PRODUCTS_FILE)) {
    ofstream file(PRODUCTS_FILE);
    file << "[]";
    file.close();
  }
  if (!fileExists(USERS_FILE)) {
    ofstream file(USERS_FILE);
    file << "[]";
    file.close();
  }
  if (!fileExists(ORDERS_FILE)) {
    ofstream file(ORDERS_FILE);
    file << "[]";
    file.close();
  }
}

// ============================================
// PRODUCTS
// ============================================

vector<Product> FileManager::loadProducts() {
  vector<Product> products;

  try {
    ifstream file(PRODUCTS_FILE);
    if (!file.is_open()) {
      return products; // Return empty if file doesn't exist
    }

    json j;
    file >> j;
    file.close();

    for (const auto &item : j) {
      Product p(item.value("id", ""), item.value("name", ""),
                item.value("category", ""), item.value("description", ""),
                item.value("price", 0.0), item.value("quantity", 0));
      products.push_back(p);
    }
  } catch (const exception &e) {
    throw FileException("Error loading products: " + string(e.what()));
  }

  return products;
}

void FileManager::saveProducts(const vector<Product> &products) {
  try {
    json j = json::array();
    for (const Product &p : products) {
      j.push_back({{"id", p.getId()},
                   {"name", p.getName()},
                   {"category", p.getCategory()},
                   {"description", p.getDescription()},
                   {"price", p.getPrice()},
                   {"quantity", p.getQuantity()}});
    }

    ofstream file(PRODUCTS_FILE);
    if (!file.is_open()) {
      throw FileException("Cannot open products file for writing");
    }
    file << setw(4) << j << endl;
    file.close();
  } catch (const FileException &) {
    throw;
  } catch (const exception &e) {
    throw FileException("Error saving products: " + string(e.what()));
  }
}

Product FileManager::findProduct(const string &productId) {
  vector<Product> products = loadProducts();
  for (const Product &p : products) {
    if (p.getId() == productId) {
      return p;
    }
  }
  throw ProductNotFoundException("Product not found: " + productId);
}

void FileManager::updateProduct(const Product &product) {
  vector<Product> products = loadProducts();
  bool found = false;

  for (auto &p : products) {
    if (p.getId() == product.getId()) {
      p = product;
      found = true;
      break;
    }
  }

  if (!found) {
    products.push_back(product);
  }

  saveProducts(products);
}

void FileManager::deleteProduct(const string &productId) {
  vector<Product> products = loadProducts();
  bool found = false;

  for (auto it = products.begin(); it != products.end(); ++it) {
    if (it->getId() == productId) {
      products.erase(it);
      found = true;
      break;
    }
  }

  if (!found) {
    throw ProductNotFoundException("Product not found: " + productId);
  }

  saveProducts(products);
}

string FileManager::generateProductId() {
  vector<Product> products = loadProducts();
  int maxId = 0;

  for (const Product &p : products) {
    if (p.getId().length() > 1 && p.getId()[0] == 'P') {
      try {
        int id = stoi(p.getId().substr(1));
        if (id > maxId)
          maxId = id;
      } catch (...) {
      }
    }
  }

  stringstream ss;
  ss << "P" << setfill('0') << setw(3) << (maxId + 1);
  return ss.str();
}

// ============================================
// USERS
// ============================================

vector<shared_ptr<User>> FileManager::loadUsers() {
  vector<shared_ptr<User>> users;

  try {
    ifstream file(USERS_FILE);
    if (!file.is_open()) {
      return users;
    }

    json j;
    file >> j;
    file.close();

    for (const auto &item : j) {
      string role = item.value("role", "customer");

      if (role == "admin") {
        auto admin = make_shared<Admin>(
            item.value("id", 0), item.value("name", ""),
            item.value("email", ""), item.value("password", ""),
            item.value("department", ""), item.value("superAdmin", false));
        users.push_back(admin);
      } else {
        auto customer = make_shared<Customer>(
            item.value("id", 0), item.value("name", ""),
            item.value("email", ""), item.value("password", ""),
            item.value("address", ""), item.value("phone", ""));
        users.push_back(customer);
      }
    }
  } catch (const exception &e) {
    throw FileException("Error loading users: " + string(e.what()));
  }

  return users;
}

void FileManager::saveUsers(const vector<shared_ptr<User>> &users) {
  try {
    json j = json::array();

    for (const auto &user : users) {
      json userJson;

      // Common fields first in logical order
      userJson["id"] = user->getId();
      userJson["name"] = user->getName();
      userJson["email"] = user->getEmail();

      // Add role-specific fields
      if (user->getRole() == "admin") {
        Admin *admin = dynamic_cast<Admin *>(user.get());
        if (admin) {
          userJson["password"] = user->getPassword();
          userJson["role"] = "admin";
          userJson["department"] = admin->getDepartment();
          userJson["superAdmin"] = admin->isSuperAdmin();
        }
      } else {
        Customer *customer = dynamic_cast<Customer *>(user.get());
        if (customer) {
          userJson["password"] = user->getPassword();
          userJson["role"] = "customer";
          userJson["phone"] = customer->getPhone();
          userJson["address"] = customer->getAddress();
        }
      }

      j.push_back(userJson);
    }

    ofstream file(USERS_FILE);
    if (!file.is_open()) {
      throw FileException("Cannot open users file for writing");
    }
    file << setw(4) << j << endl;
    file.close();
  } catch (const FileException &) {
    throw;
  } catch (const exception &e) {
    throw FileException("Error saving users: " + string(e.what()));
  }
}

shared_ptr<User> FileManager::findUserByEmail(const string &email) {
  vector<shared_ptr<User>> users = loadUsers();
  for (const auto &user : users) {
    if (user->getEmail() == email) {
      return user;
    }
  }
  throw UserNotFoundException("User not found: " + email);
}

shared_ptr<User> FileManager::findUserById(int userId) {
  vector<shared_ptr<User>> users = loadUsers();
  for (const auto &user : users) {
    if (user->getId() == userId) {
      return user;
    }
  }
  throw UserNotFoundException("User not found with ID: " + to_string(userId));
}

void FileManager::addUser(shared_ptr<User> user) {
  vector<shared_ptr<User>> users = loadUsers();
  users.push_back(user);
  saveUsers(users);
}

int FileManager::generateUserId() {
  vector<shared_ptr<User>> users = loadUsers();
  int maxId = 0;

  for (const auto &user : users) {
    if (user->getId() > maxId) {
      maxId = user->getId();
    }
  }

  return maxId + 1;
}

// ============================================
// ORDERS
// ============================================

vector<Order> FileManager::loadOrders() {
  vector<Order> orders;

  try {
    ifstream file(ORDERS_FILE);
    if (!file.is_open()) {
      return orders;
    }

    json j;
    file >> j;
    file.close();

    for (const auto &item : j) {
      vector<OrderItem> orderItems;
      if (item.contains("items")) {
        for (const auto &orderItem : item["items"]) {
          OrderItem oi;
          oi.productId = orderItem.value("productId", "");
          oi.productName = orderItem.value("productName", "");
          oi.price = orderItem.value("price", 0.0);
          oi.quantity = orderItem.value("quantity", 0);
          orderItems.push_back(oi);
        }
      }

      Order order(item.value("id", ""), item.value("customerId", 0), orderItems,
                  item.value("totalAmount", 0.0));

      string statusStr = item.value("status", "Pending");
      order.updateStatus(Order::stringToStatus(statusStr));

      orders.push_back(order);
    }
  } catch (const exception &e) {
    throw FileException("Error loading orders: " + string(e.what()));
  }

  return orders;
}

void FileManager::saveOrders(const vector<Order> &orders) {
  try {
    json j = json::array();

    for (const Order &order : orders) {
      json itemsJson = json::array();
      for (const OrderItem &item : order.getItems()) {
        itemsJson.push_back({{"productId", item.productId},
                             {"productName", item.productName},
                             {"price", item.price},
                             {"quantity", item.quantity}});
      }

      j.push_back({{"id", order.getId()},
                   {"customerId", order.getCustomerId()},
                   {"items", itemsJson},
                   {"totalAmount", order.getTotalAmount()},
                   {"status", order.getStatusString()},
                   {"createdAt", order.getCreatedAt()},
                   {"updatedAt", order.getUpdatedAt()}});
    }

    ofstream file(ORDERS_FILE);
    if (!file.is_open()) {
      throw FileException("Cannot open orders file for writing");
    }
    file << setw(4) << j << endl;
    file.close();
  } catch (const FileException &) {
    throw;
  } catch (const exception &e) {
    throw FileException("Error saving orders: " + string(e.what()));
  }
}

vector<Order> FileManager::getCustomerOrders(int customerId) {
  vector<Order> allOrders = loadOrders();
  vector<Order> customerOrders;

  for (const Order &order : allOrders) {
    if (order.getCustomerId() == customerId) {
      customerOrders.push_back(order);
    }
  }

  return customerOrders;
}

void FileManager::addOrder(const Order &order) {
  vector<Order> orders = loadOrders();
  orders.push_back(order);
  saveOrders(orders);
}

void FileManager::updateOrderStatus(const string &orderId, OrderStatus status) {
  vector<Order> orders = loadOrders();
  bool found = false;

  for (auto &order : orders) {
    if (order.getId() == orderId) {
      order.updateStatus(status);
      found = true;
      break;
    }
  }

  if (!found) {
    throw MerxQException("Order not found: " + orderId);
  }

  saveOrders(orders);
}

string FileManager::generateOrderId() {
  vector<Order> orders = loadOrders();
  int maxId = 0;

  for (const Order &order : orders) {
    if (order.getId().length() > 3 && order.getId().substr(0, 3) == "ORD") {
      try {
        int id = stoi(order.getId().substr(3));
        if (id > maxId)
          maxId = id;
      } catch (...) {
      }
    }
  }

  stringstream ss;
  ss << "ORD" << setfill('0') << setw(4) << (maxId + 1);
  return ss.str();
}
