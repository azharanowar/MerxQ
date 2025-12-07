#include "../include/order.h"
#include "../include/exceptions.h"
#include <iomanip>
#include <sstream>

// ============================================
// CONSTRUCTORS
// ============================================

Order::Order()
    : id(""), customerId(0), totalAmount(0.0), status(OrderStatus::PENDING),
      createdAt(getCurrentTimestamp()), updatedAt(createdAt) {}

Order::Order(const string &id, int customerId, const vector<OrderItem> &items,
             double total)
    : id(id), customerId(customerId), items(items), totalAmount(total),
      status(OrderStatus::PENDING), createdAt(getCurrentTimestamp()),
      updatedAt(createdAt) {}

// ============================================
// FACTORY METHOD
// ============================================

Order Order::createFromCart(const string &orderId, int customerId,
                            const Cart &cart) {
  if (cart.isEmpty()) {
    throw InvalidInputException("Cannot create order from empty cart");
  }

  vector<OrderItem> orderItems;
  for (const CartItem &cartItem : cart.getItems()) {
    OrderItem item;
    item.productId = cartItem.product.getId();
    item.productName = cartItem.product.getName();
    item.price = cartItem.product.getPrice();
    item.quantity = cartItem.quantity;
    orderItems.push_back(item);
  }

  return Order(orderId, customerId, orderItems, cart.getTotal());
}

// ============================================
// DISPLAY
// ============================================

void Order::displayOrder() const {
  cout << endl;
  cout << Utils::colorText("╔══════════════════════════════════════════════════"
                           "═════════════╗",
                           "cyan")
       << endl;
  cout << Utils::colorText("║", "cyan") << "                    📦 "
       << Utils::colorText("ORDER DETAILS", "white", "", "bold")
       << "                          " << Utils::colorText("║", "cyan") << endl;
  cout << Utils::colorText("╠══════════════════════════════════════════════════"
                           "═════════════╣",
                           "cyan")
       << endl;

  // Order info
  cout << Utils::colorText("║", "cyan")
       << " Order ID:    " << Utils::colorText(id, "yellow", "", "bold")
       << endl;
  cout << Utils::colorText("║", "cyan")
       << " Customer ID: " << Utils::colorText(to_string(customerId), "white")
       << endl;
  cout << Utils::colorText("║", "cyan") << " Status:      "
       << Utils::colorText(statusToString(status),
                           status == OrderStatus::DELIVERED   ? "green"
                           : status == OrderStatus::CANCELLED ? "red"
                                                              : "yellow",
                           "", "bold")
       << endl;
  cout << Utils::colorText("║", "cyan")
       << " Created:     " << Utils::colorText(createdAt, "white") << endl;

  cout << Utils::colorText("╠══════════════════════════════════════════════════"
                           "═════════════╣",
                           "cyan")
       << endl;
  cout << Utils::colorText("║", "cyan")
       << Utils::colorText(" Items:", "white", "", "bold") << endl;

  for (const OrderItem &item : items) {
    stringstream priceStr, subtotalStr;
    priceStr << fixed << setprecision(2) << item.price;
    subtotalStr << fixed << setprecision(2) << item.getSubtotal();

    cout << Utils::colorText("║", "cyan") << "   • "
         << Utils::colorText(item.productName, "white");

    int nameLen = item.productName.length();
    for (int i = nameLen; i < 25; i++)
      cout << " ";

    cout << " x" << item.quantity << " @ $" << priceStr.str() << " = "
         << Utils::colorText("$" + subtotalStr.str(), "green") << endl;
  }

  cout << Utils::colorText("╠══════════════════════════════════════════════════"
                           "═════════════╣",
                           "cyan")
       << endl;

  stringstream totalStr;
  totalStr << fixed << setprecision(2) << totalAmount;

  cout << Utils::colorText("║", "cyan")
       << "                                    "
       << Utils::colorText("TOTAL: $" + totalStr.str(), "green", "", "bold")
       << endl;
  cout << Utils::colorText("╚══════════════════════════════════════════════════"
                           "═════════════╝",
                           "cyan")
       << endl;
}

void Order::displayShort() const {
  stringstream totalStr;
  totalStr << fixed << setprecision(2) << totalAmount;

  string statusColor = status == OrderStatus::DELIVERED   ? "green"
                       : status == OrderStatus::CANCELLED ? "red"
                                                          : "yellow";

  cout << Utils::colorText(id, "yellow") << " | "
       << Utils::colorText(to_string(items.size()) + " items", "white") << " | "
       << Utils::colorText("$" + totalStr.str(), "green") << " | "
       << Utils::colorText("[" + statusToString(status) + "]", statusColor)
       << " | " << createdAt << endl;
}

// ============================================
// STATUS MANAGEMENT
// ============================================

void Order::updateStatus(OrderStatus newStatus) {
  status = newStatus;
  updatedAt = getCurrentTimestamp();
}

string Order::statusToString(OrderStatus status) {
  switch (status) {
  case OrderStatus::PENDING:
    return "Pending";
  case OrderStatus::CONFIRMED:
    return "Confirmed";
  case OrderStatus::PROCESSING:
    return "Processing";
  case OrderStatus::SHIPPED:
    return "Shipped";
  case OrderStatus::DELIVERED:
    return "Delivered";
  case OrderStatus::CANCELLED:
    return "Cancelled";
  default:
    return "Unknown";
  }
}

OrderStatus Order::stringToStatus(const string &statusStr) {
  if (statusStr == "Pending")
    return OrderStatus::PENDING;
  if (statusStr == "Confirmed")
    return OrderStatus::CONFIRMED;
  if (statusStr == "Processing")
    return OrderStatus::PROCESSING;
  if (statusStr == "Shipped")
    return OrderStatus::SHIPPED;
  if (statusStr == "Delivered")
    return OrderStatus::DELIVERED;
  if (statusStr == "Cancelled")
    return OrderStatus::CANCELLED;
  return OrderStatus::PENDING;
}

// ============================================
// UTILITY
// ============================================

string Order::getCurrentTimestamp() {
  time_t now = time(nullptr);
  tm *ltm = localtime(&now);

  stringstream ss;
  ss << (1900 + ltm->tm_year) << "-" << setfill('0') << setw(2)
     << (1 + ltm->tm_mon) << "-" << setfill('0') << setw(2) << ltm->tm_mday
     << " " << setfill('0') << setw(2) << ltm->tm_hour << ":" << setfill('0')
     << setw(2) << ltm->tm_min << ":" << setfill('0') << setw(2) << ltm->tm_sec;

  return ss.str();
}

