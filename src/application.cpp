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
