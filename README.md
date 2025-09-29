# 📞 PhoneBook

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://github.com/TigGev/PhoneBook/blob/main/LICENSE)
[![Language: C](https://img.shields.io/badge/language-C-blue.svg)](https://github.com/TigGev/PhoneBook)
[![Project Status](https://img.shields.io/badge/status-active-brightgreen.svg)](https://github.com/TigGev/PhoneBook)
[![GitHub Stars](https://img.shields.io/github/stars/TigGev/PhoneBook.svg?style=social)](https://github.com/TigGev/PhoneBook/stargazers)
[![GitHub Forks](https://img.shields.io/github/forks/TigGev/PhoneBook.svg?style=social)](https://github.com/TigGev/PhoneBook/network)

A simple console-based Phone Book application written in C.

It allows you to add, list, search, and delete contacts.

Contacts are stored in a text file so they persist between program runs.

## 🚀 Features

* Add a contact (name + phone number)
* List all saved contacts
* Search contact by name
* Delete contact by name
* Save data to file (`data/contacts.txt`)

## 📂 Project Structure

```
PhoneBook/
│
├── include/
│   └── phonebook.h           # Header file (structs + function declarations)
│
├── src/
│   ├── main.c               # Program entry point (menu loop)
│   └── phonebook.c          # Core phonebook logic
│
├── data/
│   └── contacts.txt         # Contact storage (created automatically)
│
├── build/                   # Compiled binary (ignored in git)
├── tests/                   # Optional unit tests
│
├── Makefile                 # Build instructions
├── README.md                # Documentation
└── LICENSE                  # License file
```

## ⚙️ Build & Run

### Build
```bash
make
```

### Run
```bash
./build/PhoneBook
```

## 📖 Usage

1. Run the program
2. Select an option from the menu:
   - 1 → Add contact
   - 2 → List contacts
   - 3 → Search contact
   - 4 → Delete contact
   - 5 → Save & Exit
3. Contacts will be saved to `data/contacts.txt`.

## 🛠️ Future Improvements

- Edit/update existing contacts
- Support for longer names (with spaces)
- Case-insensitive search
- Dynamic memory instead of static array