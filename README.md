# MerxQ - Online Shop & Inventory System

A C++ CLI-based online shopping and inventory management system demonstrating Object-Oriented Programming principles.

## 🎯 Features

- **User Management**: Customer and Admin roles with authentication
- **Shopping System**: Browse products, manage cart, place orders
- **Inventory Management**: Admin tools to add/update/delete products
- **Data Persistence**: JSON-based file storage for all data
- **Robust Error Handling**: Custom exceptions for safe operations
- **Beautiful CLI**: Colorful ANSI terminal interface

## 🏗️ Project Structure

```
MerxQ/
├── main.cpp                          # Entry point
├── utils.h / utils.cpp               # Common utilities (colors, input validation)
├── exceptions.h / exceptions.cpp     # Custom exception classes
├── user.h / user.cpp                 # Base User class (polymorphism)
├── customer.h / customer.cpp         # Customer class (derived)
├── admin.h / admin.cpp               # Admin class (derived)
├── product.h / product.cpp           # Product class
├── cart.h / cart.cpp                 # Shopping cart
├── order.h / order.cpp               # Order management
├── filemanager.h / filemanager.cpp   # JSON file I/O
├── application.h / application.cpp   # Main application logic
├── lib/
│   └── json.hpp                      # JSON library (nlohmann/json)
└── data/
    ├── users.json                    # User data
    ├── products.json                 # Product catalog
    └── orders.json                   # Order history
```

## 🚀 Getting Started

### Prerequisites
- C++ compiler with C++17 support (g++, clang++)
- Make

### Build Instructions

```bash
# Clone the repository
git clone <repository-url>
cd MerxQ

# Build the project
make

# Run the application
./merxq
```

### Clean Build

```bash
make clean && make
```

## 📖 Usage

### Default Admin Account
- **Email**: admin@merxq.com
- **Password**: admin123

### Customer Features
1. Register a new account
2. Browse available products
3. Add items to cart
4. Place orders
5. View order history

### Admin Features
1. View inventory with stock levels
2. Add new products
3. Update product details (price, stock)
4. Delete products
5. View all customer orders
6. Update order status

## 🎓 OOP Concepts Demonstrated

- **Inheritance**: Customer and Admin classes inherit from User base class
- **Polymorphism**: Runtime polymorphism through virtual functions
- **Encapsulation**: Private data members with public interfaces
- **Exception Handling**: Custom exception classes for robust error handling
- **File I/O**: JSON-based data persistence

## 👥 Contributors

- Md Anwar Hosen (Azhar Anowar) - Developer
- Al-Rafi Azad - Developer
- Md Arafat Hossain - Developer
- Taohidul Islam - Developer
## 📝 License

This project is created for educational purposes.

---

**Built with ❤️ using C++**
