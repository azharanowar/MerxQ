#include "../include/cart.h"
#include "../include/exceptions.h"
#include <iomanip>
#include <sstream>

// ============================================
// CART OPERATIONS
// ============================================

void Cart::addItem(const Product &product, int quantity) {
  if (quantity <= 0) {
    throw InvalidInputException("Quantity must be positive");
  }

  // Check if product already in cart
  CartItem *existing = findItem(product.getId());
  if (existing != nullptr) {
    existing->quantity += quantity;
  } else {
    items.push_back(CartItem(product, quantity));
  }
}

void Cart::removeItem(const string &productId) {
  for (auto it = items.begin(); it != items.end(); ++it) {
    if (it->product.getId() == productId) {
      items.erase(it);
      return;
    }
  }
  throw ProductNotFoundException("Product not found in cart: " + productId);
}

void Cart::updateQuantity(const string &productId, int newQuantity) {
  if (newQuantity < 0) {
    throw InvalidInputException("Quantity cannot be negative");
  }

  if (newQuantity == 0) {
    removeItem(productId);
    return;
  }

  CartItem *item = findItem(productId);
  if (item == nullptr) {
    throw ProductNotFoundException("Product not found in cart: " + productId);
  }
  item->quantity = newQuantity;
}

void Cart::clear() { items.clear(); }

// ============================================
// DISPLAY
// ============================================

void Cart::displayCart() const {
  if (items.empty()) {
    cout << endl;
    cout << Utils::colorText("┌─────────────────────────────────────────┐",
                             "yellow")
         << endl;
    cout << Utils::colorText("│", "yellow")
         << "       🛒 Your cart is empty!           "
         << Utils::colorText("│", "yellow") << endl;
    cout << Utils::colorText("└─────────────────────────────────────────┘",
                             "yellow")
         << endl;
    return;
  }

  cout << endl;
  cout << Utils::colorText("╔══════════════════════════════════════════════════"
                           "═════════════╗",
                           "cyan")
       << endl;
  cout << Utils::colorText("║", "cyan") << "                    🛒 "
       << Utils::colorText("SHOPPING CART", "white", "", "bold")
       << "                           " << Utils::colorText("║", "cyan")
       << endl;
  cout << Utils::colorText("╠══════════════════════════════════════════════════"
                           "═════════════╣",
                           "cyan")
       << endl;

  for (const CartItem &item : items) {
    stringstream priceStr, subtotalStr;
    priceStr << fixed << setprecision(2) << item.product.getPrice();
    subtotalStr << fixed << setprecision(2) << item.getSubtotal();

    cout << Utils::colorText("║", "cyan") << " "
         << Utils::colorText(item.product.getId(), "yellow") << " | "
         << Utils::colorText(item.product.getName(), "white", "", "bold");

    // Padding for alignment
    int nameLen = item.product.getName().length();
    for (int i = nameLen; i < 25; i++)
      cout << " ";

    cout << " x" << item.quantity << " @ $" << priceStr.str();
    cout << " = "
         << Utils::colorText("$" + subtotalStr.str(), "green", "", "bold");

    // Right padding
    int totalLen = subtotalStr.str().length();
    for (int i = totalLen; i < 10; i++)
      cout << " ";

    cout << Utils::colorText("║", "cyan") << endl;
  }

  cout << Utils::colorText("╠══════════════════════════════════════════════════"
                           "═════════════╣",
                           "cyan")
       << endl;

  stringstream totalStr;
  totalStr << fixed << setprecision(2) << getTotal();

  cout << Utils::colorText("║", "cyan")
       << "                                    "
       << Utils::colorText("TOTAL: $" + totalStr.str(), "green", "", "bold");

  int totalLen = totalStr.str().length();
  for (int i = totalLen; i < 15; i++)
    cout << " ";

  cout << Utils::colorText("║", "cyan") << endl;
  cout << Utils::colorText("╚══════════════════════════════════════════════════"
                           "═════════════╝",
                           "cyan")
       << endl;
}

// ============================================
// GETTERS
// ============================================

double Cart::getTotal() const {
  double total = 0.0;
  for (const CartItem &item : items) {
    total += item.getSubtotal();
  }
  return total;
}

int Cart::getItemCount() const { return items.size(); }

int Cart::getTotalQuantity() const {
  int total = 0;
  for (const CartItem &item : items) {
    total += item.quantity;
  }
  return total;
}

// ============================================
// ITEM LOOKUP
// ============================================

bool Cart::hasProduct(const string &productId) const {
  return findItem(productId) != nullptr;
}

CartItem *Cart::findItem(const string &productId) {
  for (auto &item : items) {
    if (item.product.getId() == productId) {
      return &item;
    }
  }
  return nullptr;
}

const CartItem *Cart::findItem(const string &productId) const {
  for (const auto &item : items) {
    if (item.product.getId() == productId) {
      return &item;
    }
  }
  return nullptr;
}
