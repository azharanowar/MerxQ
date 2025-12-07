# MerxQ - Online Shop & Inventory System

A C++ CLI-based online shopping and inventory management system demonstrating Object-Oriented Programming principles.

## 🎯 Features

- **User Management**: Customer and Admin roles with authentication
- **Shopping System**: Browse products, search, manage cart, place orders
- **Inventory Management**: Admin tools for complete product CRUD operations
- **Order Tracking**: Order history and status management
- **Data Persistence**: JSON-based file storage
- **Beautiful CLI**: Colorful ANSI terminal interface

## 🏗️ Project Structure

```
MerxQ/
├── include/
│   ├── utils.h              # Utilities (colors, input validation)
│   ├── exceptions.h         # Custom exception classes
│   ├── user.h               # Base User class
│   ├── customer.h           # Customer class (derived)
│   ├── admin.h              # Admin class (derived)
│   ├── product.h            # Product class
│   ├── cart.h               # Shopping cart
│   ├── order.h              # Order management
│   ├── filemanager.h        # JSON file I/O
│   └── application.h        # Main application
├── src/
│   ├── main.cpp             # Entry point
│   ├── utils.cpp
│   ├── user.cpp
│   ├── customer.cpp
│   ├── admin.cpp
│   ├── product.cpp
│   ├── cart.cpp
│   ├── order.cpp
│   ├── filemanager.cpp
│   └── application.cpp
├── lib/
│   └── json.hpp             # nlohmann/json library
├── data/
│   ├── users.json           # User accounts
│   ├── products.json        # Product catalog
│   └── orders.json          # Order history
└── Makefile
```

## 🚀 Getting Started

### Prerequisites
- C++ compiler with C++17 support (g++, clang++)
- Make

### Build & Run

```bash
# Build the project
make

# Run the application
./merxq

# Clean and rebuild
make clean && make
```

## 👤 Test Accounts

| Role | Email | Password |
|------|-------|----------|
| Admin | admin@gmail.com | 123 |
| Customer | customer@merxq.com | pass123 |

## 📋 User Roles & Features

### Customer Features
- Register new account
- Login/Logout
- Browse all products
- Search products (case-insensitive)
- Add items to cart
- View and modify cart
- Checkout and place orders
- View order history
- View profile

### Admin Features
- Login/Logout
- View complete inventory
- Add new products
- Update product details (name, price, stock, category, description)
- Delete products
- View all customer orders
- Update order status (Pending → Confirmed → Processing → Shipped → Delivered)
- View all registered users

## 🎨 Color Scheme

| Color | Usage |
|-------|-------|
| Red | Errors, warnings, exit options |
| Green | Success messages, prices |
| Yellow | Headers, highlights, IDs |
| White | Regular text |
| Blue BG | Main header |

## 🎓 OOP Concepts Demonstrated

- **Inheritance**: `Customer` and `Admin` inherit from `User` base class
- **Polymorphism**: Virtual functions for `displayInfo()` and authentication
- **Encapsulation**: Private members with getters/setters
- **Abstraction**: `FileManager` static class for data operations
- **Exception Handling**: Custom exceptions (`InvalidInputException`, `ProductNotFoundException`, etc.)

## 👥 Development Team

| Name | Role |
|------|------|
| Md Anwar Hosen (Azhar Anowar) | Developer |
| Al-Rafi Azad | Developer |
| Md Arafat Hossain | Developer |
| Taohidul Islam | Developer |

## 📝 License

This project is created for educational purposes.

---

**Built with ❤️ using C++17**
