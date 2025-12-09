#include "../include/application.h"
#include "../include/exceptions.h"

// ============================================
// CONSTRUCTOR
// ============================================

Application::Application() : currentUser(nullptr), running(true) {
  FileManager::ensureDataDirectory();
  loadData();
}

void Application::loadData() {
  try {
    products = FileManager::loadProducts();
    users = FileManager::loadUsers();
    orders = FileManager::loadOrders();
  } catch (const exception &e) {
    cout << Utils::colorText("Warning: " + string(e.what()), "yellow") << endl;
  }
}

// ============================================
// MAIN ENTRY POINT
// ============================================

void Application::run() {
  while (running) {
    Utils::clearScreen();
    Utils::showMainHeader("🛒 MerxQ Shop System 🛒");

    if (currentUser == nullptr) {
      showMainMenu();
    } else if (currentUser->getRole() == "admin") {
      showAdminMenu();
    } else {
      showCustomerMenu();
    }
  }

  cout << endl;
  cout << Utils::colorText("Thank you for using MerxQ! 👋", "yellow", "",
                           "bold")
       << endl;
  cout << Utils::colorText("Have a great day!", "green") << endl << endl;
}

// ============================================
// MAIN MENUS
// ============================================

void Application::showMainMenu() {
  cout << Utils::colorText("Welcome to MerxQ!", "green", "", "bold") << endl;
  cout << Utils::colorText("Your online shopping solution", "yellow") << endl
       << endl;

  cout << Utils::colorText("MAIN MENU", "yellow", "", "bold") << endl << endl;
  cout << Utils::colorText("1.", "yellow", "", "bold") << " Login" << endl;
  cout << Utils::colorText("2.", "yellow", "", "bold") << " Register" << endl;
  cout << Utils::colorText("3.", "yellow", "", "bold")
       << " Browse Products (Guest)" << endl;
  cout << Utils::colorText("0.", "red", "", "bold") << " Exit" << endl << endl;

  int choice = Utils::getIntInput("Choose option: ", 0, 3);

  switch (choice) {
  case 1:
    login();
    break;
  case 2:
    registerCustomer();
    break;
  case 3:
    browseProducts();
    break;
  case 0:
    running = false;
    break;
  }
}

void Application::showCustomerMenu() {
  cout << Utils::colorText("Logged in as: ", "white")
       << Utils::colorText(currentUser->getName(), "yellow", "", "bold") << endl
       << endl;

  cout << Utils::colorText("CUSTOMER MENU", "yellow", "", "bold") << endl
       << endl;
  cout << Utils::colorText("1.", "green", "", "bold") << " Browse Products"
       << endl;
  cout << Utils::colorText("2.", "green", "", "bold") << " Search Products"
       << endl;
  cout << Utils::colorText("3.", "green", "", "bold") << " Add to Cart" << endl;
  cout << Utils::colorText("4.", "green", "", "bold") << " View Cart "
       << Utils::colorText("(" + to_string(currentCart.getTotalQuantity()) +
                               " items)",
                           "yellow")
       << endl;
  cout << Utils::colorText("5.", "green", "", "bold") << " Checkout" << endl;
  cout << Utils::colorText("6.", "green", "", "bold") << " Order History"
       << endl;
  cout << Utils::colorText("7.", "green", "", "bold") << " My Profile" << endl;
  cout << Utils::colorText("0.", "red", "", "bold") << " Logout" << endl
       << endl;

  int choice = Utils::getIntInput("Choose option: ", 0, 7);

  switch (choice) {
  case 1:
    browseProducts();
    break;
  case 2:
    searchProducts();
    break;
  case 3:
    addToCart();
    break;
  case 4:
    viewCart();
    break;
  case 5:
    checkout();
    break;
  case 6:
    viewOrderHistory();
    break;
  case 7:
    viewProfile();
    break;
  case 0:
    logout();
    break;
  }
}

void Application::showAdminMenu() {
  cout << Utils::colorText("Admin: ", "white")
       << Utils::colorText(currentUser->getName(), "yellow", "", "bold") << endl
       << endl;

  cout << Utils::colorText("ADMIN PANEL", "yellow", "", "bold") << endl << endl;
  cout << Utils::colorText("1.", "yellow", "", "bold") << " View Inventory"
       << endl;
  cout << Utils::colorText("2.", "yellow", "", "bold") << " Add Product"
       << endl;
  cout << Utils::colorText("3.", "yellow", "", "bold") << " Update Product"
       << endl;
  cout << Utils::colorText("4.", "yellow", "", "bold") << " Delete Product"
       << endl;
  cout << Utils::colorText("5.", "yellow", "", "bold") << " View All Orders"
       << endl;
  cout << Utils::colorText("6.", "yellow", "", "bold") << " Update Order Status"
       << endl;
  cout << Utils::colorText("7.", "yellow", "", "bold") << " View All Users"
       << endl;
  cout << Utils::colorText("0.", "red", "", "bold") << " Logout" << endl
       << endl;

  int choice = Utils::getIntInput("Choose option: ", 0, 7);

  switch (choice) {
  case 1:
    viewInventory();
    break;
  case 2:
    addProduct();
    break;
  case 3:
    updateProduct();
    break;
  case 4:
    deleteProduct();
    break;
  case 5:
    viewAllOrders();
    break;
  case 6:
    updateOrderStatus();
    break;
  case 7:
    viewAllUsers();
    break;
  case 0:
    logout();
    break;
  }
}

// ============================================
// AUTHENTICATION
// ============================================

void Application::login() {
  Utils::clearScreen();
  Utils::showSubHeader("Login");

  string email = Utils::getStringInput("Email: ");
  string password = Utils::getStringInput("Password: ");

  try {
    auto user = FileManager::findUserByEmail(email);
    if (user->authenticate(password)) {
      currentUser = user;
      cout << Utils::colorText("✓ Login successful!", "green", "", "bold")
           << endl;
      Utils::pauseScreen();
    } else {
      throw AuthenticationException("Incorrect password");
    }
  } catch (const UserNotFoundException &) {
    cout << Utils::colorText("✗ User not found!", "red") << endl;
    Utils::pauseScreen();
  } catch (const AuthenticationException &) {
    cout << Utils::colorText("✗ Incorrect password!", "red") << endl;
    Utils::pauseScreen();
  }
}

void Application::registerCustomer() {
  Utils::clearScreen();
  Utils::showSubHeader("Register New Account");

  string name = Utils::getStringInput("Full Name: ");
  string email = Utils::getStringInput("Email: ");
  string password = Utils::getStringInput("Password: ");
  string address = Utils::getStringInput("Address (optional): ");
  string phone = Utils::getStringInput("Phone (optional): ");

  try {
    // Check if email already exists
    try {
      FileManager::findUserByEmail(email);
      cout << Utils::colorText("✗ Email already registered!", "red") << endl;
      Utils::pauseScreen();
      return;
    } catch (const UserNotFoundException &) {
      // Email not found - good, we can register
    }

    int newId = FileManager::generateUserId();
    auto newCustomer =
        make_shared<Customer>(newId, name, email, password, address, phone);
    FileManager::addUser(newCustomer);
    users = FileManager::loadUsers();

    cout << Utils::colorText("✓ Registration successful!", "green", "", "bold")
         << endl;
    cout << Utils::colorText("You can now login with your credentials.",
                             "yellow")
         << endl;
    Utils::pauseScreen();
  } catch (const exception &e) {
    cout << Utils::colorText("✗ Error: " + string(e.what()), "red") << endl;
    Utils::pauseScreen();
  }
}

void Application::logout() {
  currentUser = nullptr;
  currentCart.clear();
  cout << Utils::colorText("✓ Logged out successfully!", "green") << endl;
  Utils::pauseScreen();
}





// ============================================
// CUSTOMER FEATURES
// ============================================

void Application::displayProductList() const {
  if (products.empty()) {
    cout << Utils::colorText("No products available.", "yellow") << endl;
    return;
  }

  cout << endl;
  cout << Utils::colorText("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
                           "━━━━━━━━━━━━━━",
                           "yellow")
       << endl;
  cout << Utils::colorText(
              " ID     │ Name                      │ Price      │ Stock",
              "white", "", "bold")
       << endl;
  cout << Utils::colorText("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
                           "━━━━━━━━━━━━━━",
                           "yellow")
       << endl;

  for (const Product &p : products) {
    p.displayShort();
  }
  cout << Utils::colorText("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
                           "━━━━━━━━━━━━━━",
                           "yellow")
       << endl;
}

void Application::browseProducts() {
  Utils::clearScreen();
  Utils::showSubHeader("📦 Product Catalog");

  products = FileManager::loadProducts(); // Refresh
  displayProductList();

  Utils::pauseScreen();
}

void Application::searchProducts() {
  Utils::clearScreen();
  Utils::showSubHeader("🔍 Search Products");

  string query = Utils::getStringInput("Search term: ");

  // Convert query to lowercase for case-insensitive search
  string queryLower = query;
  for (char &c : queryLower)
    c = tolower(c);

  cout << endl;
  cout << Utils::colorText("Search results for: ", "white")
       << Utils::colorText(query, "yellow", "", "bold") << endl;

  bool found = false;
  for (const Product &p : products) {
    // Convert product fields to lowercase for comparison
    string nameLower = p.getName();
    string catLower = p.getCategory();
    string descLower = p.getDescription();
    for (char &c : nameLower)
      c = tolower(c);
    for (char &c : catLower)
      c = tolower(c);
    for (char &c : descLower)
      c = tolower(c);

    if (nameLower.find(queryLower) != string::npos ||
        catLower.find(queryLower) != string::npos ||
        descLower.find(queryLower) != string::npos) {
      p.displayShort();
      found = true;
    }
  }

  if (!found) {
    cout << Utils::colorText("No products found matching your search.",
                             "yellow")
         << endl;
  }

  Utils::pauseScreen();
}

void Application::addToCart() {
  Utils::clearScreen();
  Utils::showSubHeader("🛒 Add to Cart");

  products = FileManager::loadProducts();
  displayProductList();

  string productId = Utils::getStringInput("Enter Product ID (or 'back'): ");
  if (productId == "back")
    return;

  try {
    Product product = FileManager::findProduct(productId);

    if (!product.isInStock()) {
      cout << Utils::colorText("✗ Product is out of stock!", "red") << endl;
      Utils::pauseScreen();
      return;
    }

    int quantity = Utils::getIntInput("Quantity: ", 1, product.getQuantity());

    currentCart.addItem(product, quantity);
    cout << Utils::colorText("✓ Added to cart!", "green", "", "bold") << endl;
    Utils::pauseScreen();
  } catch (const ProductNotFoundException &e) {
    cout << Utils::colorText("✗ " + string(e.what()), "red") << endl;
    Utils::pauseScreen();
  }
}

void Application::viewCart() {
  Utils::clearScreen();
  Utils::showSubHeader("🛒 Your Cart");

  currentCart.displayCart();
  Utils::pauseScreen();
}

void Application::checkout() {
  Utils::clearScreen();
  Utils::showSubHeader("💳 Checkout");

  if (currentCart.isEmpty()) {
    cout << Utils::colorText("Your cart is empty!", "yellow") << endl;
    Utils::pauseScreen();
    return;
  }

  currentCart.displayCart();

  cout << endl;
  string confirm = Utils::getStringInput("Confirm order? (yes/no): ");

  if (confirm != "yes" && confirm != "y") {
    cout << Utils::colorText("Order cancelled.", "yellow") << endl;
    Utils::pauseScreen();
    return;
  }

  try {
    // Create order
    string orderId = FileManager::generateOrderId();
    Order order =
        Order::createFromCart(orderId, currentUser->getId(), currentCart);

    // Save order
    FileManager::addOrder(order);

    // Update product stock
    for (const CartItem &item : currentCart.getItems()) {
      Product p = FileManager::findProduct(item.product.getId());
      p.reduceStock(item.quantity);
      FileManager::updateProduct(p);
    }

    // Clear cart
    currentCart.clear();
    products = FileManager::loadProducts();
    orders = FileManager::loadOrders();

    cout << endl;
    cout << Utils::colorText("╔═══════════════════════════════════════════╗",
                             "green")
         << endl;
    cout << Utils::colorText("║", "green") << "     "
         << Utils::colorText("ORDER PLACED SUCCESSFULLY!", "white", "", "bold")
         << "         " << Utils::colorText("║", "green") << endl;
    cout << Utils::colorText("╠═══════════════════════════════════════════╣",
                             "green")
         << endl;
    cout << Utils::colorText("║", "green")
         << " Order ID: " << Utils::colorText(orderId, "yellow", "", "bold")
         << "                       " << Utils::colorText("║", "green") << endl;
    cout << Utils::colorText("╚═══════════════════════════════════════════╝",
                             "green")
         << endl;

    Utils::pauseScreen();
  } catch (const exception &e) {
    cout << Utils::colorText("✗ Error: " + string(e.what()), "red") << endl;
    Utils::pauseScreen();
  }
}

void Application::viewOrderHistory() {
  Utils::clearScreen();
  Utils::showSubHeader("📋 Order History");

  vector<Order> customerOrders =
      FileManager::getCustomerOrders(currentUser->getId());

  if (customerOrders.empty()) {
    cout << Utils::colorText("You haven't placed any orders yet.", "yellow")
         << endl;
    Utils::pauseScreen();
    return;
  }

  cout << endl;
  for (const Order &order : customerOrders) {
    order.displayShort();
  }

  string viewDetails = Utils::getStringInput(
      "\nView order details? Enter Order ID (or 'back'): ");
  if (viewDetails != "back") {
    for (const Order &order : customerOrders) {
      if (order.getId() == viewDetails) {
        order.displayOrder();
        break;
      }
    }
  }

  Utils::pauseScreen();
}

void Application::viewProfile() {
  Utils::clearScreen();
  Utils::showSubHeader("👤 My Profile");

  currentUser->displayInfo();
  Utils::pauseScreen();
}


