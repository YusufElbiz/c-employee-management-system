# C Employee Management System

This is a simple employee and department management system written in C. The project handles employees and departments using text files (`calisanlar.txt` and `birimler.txt`). It supports adding, listing, and managing employee data.

## 💡 Features

- Add, update, and delete employee records
- Department management
- File-based persistence (`.txt`)
- Console-based interaction
- Modular structure with `Proje1.c` and `Proje1.h`
- Includes `Makefile` for easy compilation

## 📁 Project Structure

```
├── Proje1.c            # Logic functions
├── Proje1.h            # Header file
├── main.c              # Entry point
├── calisanlar.txt      # Employee data
├── birimler.txt        # Department data
├── Makefile            # Build script
├── bin/program.exe     # Compiled output
├── .vscode/            # VSCode configs
└── PROJE-1 Rapor.docx  # Project documentation
```

## 🛠️ How to Compile

Using the provided Makefile:

```bash
make
```

Or manually with `gcc`:

```bash
gcc main.c Proje1.c -o program.exe
```

## 📦 Output

Compiled binary will be available in `bin/program.exe`.

## 👤 Author

**Yusuf Elbiz**  


