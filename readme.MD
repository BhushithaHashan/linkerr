# linkerr

**linkerr** is a simple interactive CLI tool to create **soft (symbolic) and hard links** for files on Linux.  
It provides a clear, step-by-step workflow, safe directory checks, and proper handling of paths, including `.` and `..` normalization and home directory expansion (`~`).

---

## Features

- Create **soft (symbolic) links** or **hard links**.
- Validates **source and target directories**.
- Prevents **hard links to directories** to avoid filesystem corruption.
- Normalizes paths, resolving `.` and `..`.
- Expands `~` to the current user's home directory.
- Clear success messages with source and link paths.
- Minimal, professional code structure using **C** with separate modules (`link_ops.c`, `utils.c`, `main.c`).

---

## Requirements

- Linux environment
- GCC compiler
- Standard C library
- Make utility (optional)

---

## Installation

Clone or download the repository:

```bash
git clone https://github.com/yourusername/linkerr.git
cd linkerr
make
./linkerr
```
## Example
```bash
Welcome to linkerr - interactive link manager
Choose link type:
1) Soft link
2) Hard link
> 2
Enter source directory path:
> ~/tmp
Enter source file or directory name:
> myfile.txt
Enter target directory for the link:
> ~/tmp/links
Enter name for the new link:
> myfile_hardlink

Hard link created successfully!
Source: /home/user/tmp/myfile.txt
Link:   /home/user/tmp/links/myfile_hardlink

```

