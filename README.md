# 📚 Library Management System

A command-line **Library Management System** written in C++, built as a hands-on project to practice core OOP concepts (classes, encapsulation, `const` correctness), STL containers, string processing, and file I/O / data persistence with CSV.

The project has two versions in this repo, showing the progression from an in-memory system to a persistent one:

| File | Description |
|---|---|
| `library.cpp` | Base version — in-memory library system, data resets every run (pre-loaded with a starter catalogue). |
| `csvlibrary.cpp` | Extended version — adds **CSV-based file persistence** so the catalogue and borrow records survive between runs. |

---

## ✨ Features

- **Add Book** — add a new title/author/year to the catalogue, or increment the copy count if it already exists.
- **Search Book** — case-insensitive substring search by title.
- **Borrow Book** — search first, then borrow by Book ID; decrements available copy count and updates status (`Available` / `Not Available`).
- **Return Book** — validates the book was actually borrowed (via an in-memory `borrowList`) before restoring it; if it wasn't borrowed, offers to add it as a new entry instead.
- **Catalogue View** — lists every book with ID, title, author, year, status, and copy count.
- **Persistent Storage** *(csvlibrary.cpp only)* — on exit, the full catalogue and current borrow list are written to disk and reloaded automatically the next time the program starts.

---

## 🗂️ Data Model

Each book is represented by a `Books` class with:

- `bId` — unique integer ID
- `bTitle`, `bAuthor` — stored in uppercase for consistent, case-insensitive matching
- `bYear` — publication year
- `bStatus` — `"Available"` / `"Not Available"`
- `bCount` — number of copies currently in the library

Getters in `csvlibrary.cpp` are marked `const`, so they can safely be called on `const Books&` references (important once the objects are passed around during CSV read/write operations).

---

## 💾 Persistence Design (`csvlibrary.cpp`)

Two CSV files back the system:

**`bookdetails.csv`** — one row per book:
```
id,title,author,year,status,count
1,WINGS OF FIRE,Dr.A. P. J. ABDUL KALAM and ARUN TIWARI,1999,Available,1
2,GOD OF SMALL THINGS,ARUNDATHI ROY,1997,Available,1
```

**`borrowlist.csv`** — one borrowed Book ID per line, tracking what's currently checked out.

### How it works
- `loadBook()` / `loadBorrowList()` run at program start, parsing each CSV line with `stringstream` + `getline(ss, word, ',')`, splitting on commas and reconstructing `Books` objects (rows are only accepted if they split into exactly 6 fields, guarding against malformed rows).
- `saveBook()` / `saveBorrowList()` run when the user exits (`case 'y'`), writing the current in-memory state back to the same two files.
- Net effect: the library's state is **fully persistent across sessions** — no database required, just plain CSV.

---

## 🚀 Getting Started

### Build & Run
```bash
g++ csvlibrary.cpp -o a && ./a
```

Make sure `bookdetails.csv` sits in the same directory as the executable (a sample file with 5 starter books is included). If it's missing, the program starts with an empty catalogue.

### Menu
```
Add Book(a)
Search(s)
Borrow(b)
Return(r)
Catalogue(c)
Exit(y)
```

---

## 🧠 What This Project Practices

- Basic OOP: encapsulation, getters/setters, `const` member functions
- STL: `std::vector`, `std::find`, `std::transform`
- String manipulation: case normalization, substring search
- Robust input handling: `cin.fail()` checks and stream recovery for invalid numeric input
- File I/O: `ifstream` / `ofstream`, manual CSV parsing and writing with `stringstream`
- Simple state management across two related data files (catalogue + borrow records) kept in sync at load and save time

---
