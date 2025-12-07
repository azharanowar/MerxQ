#ifndef CART_H
#define CART_H

#include "product.h"
#include <utility>
#include <vector>

using namespace std;

// ============================================
// CART ITEM STRUCT
// ============================================
struct CartItem {
  Product product;
  int quantity;

  CartItem(const Product &p, int qty) : product(p), quantity(qty) {}

  double getSubtotal() const { return product.getPrice() * quantity; }
};

// ============================================
// CART CLASS
// ============================================
// Shopping cart for customer purchases

class Cart {
private:
  vector<CartItem> items;

public:
  // ============================================
  // CONSTRUCTORS
  // ============================================
  Cart() = default;

  // ============================================
  // CART OPERATIONS
  // ============================================
  void addItem(const Product &product, int quantity = 1);
  void removeItem(const string &productId);
  void updateQuantity(const string &productId, int newQuantity);
  void clear();

  // ============================================
  // DISPLAY
  // ============================================
  void displayCart() const;

  // ============================================
  // GETTERS
  // ============================================
  double getTotal() const;
  int getItemCount() const;
  int getTotalQuantity() const;
  bool isEmpty() const { return items.empty(); }
  vector<CartItem> getItems() const { return items; }

  // ============================================
  // ITEM LOOKUP
  // ============================================
  bool hasProduct(const string &productId) const;
  CartItem *findItem(const string &productId);
  const CartItem *findItem(const string &productId) const;
};

#endif
