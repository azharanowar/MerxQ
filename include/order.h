#ifndef ORDER_H
#define ORDER_H

#include "cart.h"
#include <ctime>
#include <string>
#include <vector>

using namespace std;

// ============================================
// ORDER STATUS ENUM
// ============================================
enum class OrderStatus {
  PENDING,
  CONFIRMED,
  PROCESSING,
  SHIPPED,
  DELIVERED,
  CANCELLED
};

// ============================================
// ORDER ITEM STRUCT
// ============================================
struct OrderItem {
  string productId;
  string productName;
  double price;
  int quantity;

  double getSubtotal() const { return price * quantity; }
};

// ============================================
// ORDER CLASS
// ============================================
class Order {
private:
  string id;      // Order ID (e.g., "ORD001")
  int customerId; // Customer who placed the order
  vector<OrderItem> items;
  double totalAmount;
  OrderStatus status;
  string createdAt; // Timestamp
  string updatedAt; // Last update timestamp

public:
  // ============================================
  // CONSTRUCTORS
  // ============================================
  Order();
  Order(const string &id, int customerId, const vector<OrderItem> &items,
        double total);

  // ============================================
  // FACTORY METHOD
  // ============================================
  static Order createFromCart(const string &orderId, int customerId,
                              const Cart &cart);

  // ============================================
  // DISPLAY
  // ============================================
  void displayOrder() const;
  void displayShort() const; // One-line summary

  // ============================================
  // STATUS MANAGEMENT
  // ============================================
  void updateStatus(OrderStatus newStatus);
  static string statusToString(OrderStatus status);
  static OrderStatus stringToStatus(const string &statusStr);

  // ============================================
  // GETTERS
  // ============================================
  string getId() const { return id; }
  int getCustomerId() const { return customerId; }
  vector<OrderItem> getItems() const { return items; }
  double getTotalAmount() const { return totalAmount; }
  OrderStatus getStatus() const { return status; }
  string getStatusString() const { return statusToString(status); }
  string getCreatedAt() const { return createdAt; }
  string getUpdatedAt() const { return updatedAt; }
  int getItemCount() const { return items.size(); }

  // ============================================
  // UTILITY
  // ============================================
  static string getCurrentTimestamp();
};

#endif
