# Linux File Access Permissions and Types of Users

In Linux, file access control centers on **who** is trying to access a file and **what** actions they are permitted to perform.

---

## 1. Types of Users in Linux

Every file and directory in Linux is associated with three primary ownership categories:

1. **User / Owner (`u`):**
   * The specific user account that owns the file (typically the creator of the file, unless ownership is reassigned using `chown`).
2. **Group (`g`):**
   * A named group of users that share collaborative access to the file. Any member of this group receives the group-level permissions (unless they are the file's primary owner, in which case owner permissions apply).
3. **Others / World (`o`):**
   * All remaining user accounts on the system that are neither the file owner nor members of the file's assigned group.

> **Special Shorthands & Superuser:**
> * **All (`a`):** Used in `chmod` commands to apply changes simultaneously to `u`, `g`, and `o`.
> * **Root (`UID 0`):** The administrative superuser account capable of bypassing standard read/write restrictions across the filesystem.

---

## 2. Basic File Access Permissions

Each of the three user classes (`u`, `g`, `o`) can be granted or denied three fundamental permissions:

| Permission | Symbol | Octal Value | Effect on a **Regular File** | Effect on a **Directory** |
| :--- | :---: | :---: | :--- | :--- |
| **Read** | `r` | `4` | Allows viewing, opening, or copying the file's contents. | Allows listing the names of files and subdirectories inside (`ls`). |
| **Write** | `w` | `2` | Allows modifying, appending, or overwriting the file's contents. *(Deleting/renaming requires `w` on the parent directory).* | Allows creating, renaming, or deleting entries within the directory. |
| **Execute** | `x` | `1` | Allows running the file as a compiled program or shell script. | Allows traversing/entering the directory (`cd`) and accessing file metadata. |

---

## 3. Reading Permission Strings (`ls -l`)

Running `ls -l` displays a 10-character permission mode string at the beginning of each line, such as `-rwxr-xr--`:

```text
  -     rwx     r-x     r--
[type] [user]  [group] [others]
```

* **Character 1 (File Type):**
  * `-` : Regular file
  * `d` : Directory
  * `l` : Symbolic link
* **Characters 2–4 (`rwx` — User/Owner):** Read (`4`) + Write (`2`) + Execute (`1`) = **`7`**
* **Characters 5–7 (`r-x` — Group):** Read (`4`) + No Write (`0`) + Execute (`1`) = **`5`**
* **Characters 8–10 (`r--` — Others):** Read (`4`) + No Write (`0`) + No Execute (`0`) = **`4`**

---

## 4. Modifying Permissions and Ownership

### Symbolic Mode (`chmod`)
Uses user targets (`u`, `g`, `o`, `a`), operators (`+` add, `-` remove, `=` set exact), and permission letters (`r`, `w`, `x`):
```bash
chmod g+w notes.txt       # Grant write permission to the group
chmod o-rwx secret.txt    # Remove all permissions from others
chmod u=rwx,go=rx app.sh  # Set rwxr-xr-x explicitly
```

### Numeric / Octal Mode (`chmod`)
Adds the octal values (`4`, `2`, `1`) for each class:
```bash
chmod 754 script.sh       # Sets -rwxr-xr-- (Owner: 7, Group: 5, Others: 4)
chmod 600 private.key     # Sets -rw------- (Owner: 6, Group: 0, Others: 0)
```

### Changing Ownership (`chown` and `chgrp`)
```bash
chown alice report.pdf          # Change file owner to 'alice'
chown alice:developers app.py   # Change owner to 'alice' and group to 'developers'
chgrp staff shared_folder       # Change group ownership to 'staff'
```

---

## 5. Special Permission Bits

In addition to standard `rwx` bits, Linux supports three special permission flags:

| Special Bit | Symbol & Position | Octal Prefix | Behavior |
| :--- | :---: | :---: | :--- |
| **SUID** (Set User ID) | `s` in owner execute (`rws------`) | `4000` | Executes a binary with the privileges of the **file owner** rather than the user launching it. |
| **SGID** (Set Group ID) | `s` in group execute (`---rws---`) | `2000` | On executables: runs with the **file group's** privileges. On directories: new files inherit the **directory's group**. |
| **Sticky Bit** | `t` in others execute (`------rwt`) | `1000` | On shared directories (e.g., `/tmp`): prevents users from deleting or renaming files unless they own the file or directory. |