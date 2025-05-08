
# 💳 Bank Management System (C++ File-Based)

A console-based bank management system developed in C++ that uses plain text files for persistent storage. It features account creation, login, balance management, and administrative controls.

---

## 📁 Features

- Admin and Regular user roles
- Account creation with default balance
- Login system (username + password)
- Deposit and withdrawal with validation
- Activity logging (Deposits & Withdrawals)
- Update user name or password
- Admin capabilities:
  - View user profiles
  - Update account statuses (Normal, Blocked, Suspended, Closed)
  - Delete user accounts
  - Search any user
- File-based storage (no database required)

---

## 🧠 Technologies Used

- **Language:** C++
- **Storage:** File I/O (`Accounts.txt`, `Deposits.txt`, `Withdrawals.txt`)
- **Structure:** OOP with class `Account` and modular functions

---

## 📂 Folder Structure

```plaintext
Bank-Management-System/
├── BankMS.cpp
├── Data/
│   ├── Accounts.txt
│   ├── Deposits.txt
│   └── Withdrawals.txt
```

---

## ⚙️ How to Run

1. Clone the repository:

   ```bash
   git clone https://github.com/FardinUbaid/Bank-Management-System
   cd Bank-Management-System
   ```

2. Compile using any C++ compiler (e.g., g++):

   ```bash
   g++ BankMS.cpp -o BankMS
   ```

3. Run the executable:

   ```bash
   ./BankMS
   ```

   Make sure the `Data/` folder exists or is created by the program.

---

## 📝 Notes

- Initial balance for new accounts is `500.00`.
- Deposits are allowed between `50` and `500,000`.
- Withdrawals are allowed if above `10` and within available balance.
- Admins can manage user statuses and delete accounts.
- Passwords are stored as plaintext (⚠️ not secure for production).

---

## 📌 Future Improvements

- Password encryption (e.g., hash with salt)
- GUI interface (Qt or wxWidgets)
- Database integration (MySQL/SQLite)
- Unit testing & modular header files

---

## 📄 License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for more info.

---

## 🙋‍♂️ Author

**Fardin Ubaid**  
GitHub: [@FardinUbaid](https://github.com/FardinUbaid)
