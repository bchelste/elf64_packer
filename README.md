---
# woody_woodpacker (packer for elf_64 files)

<div align="center">
<img src="https://github.com/bchelste/elf64_packer/blob/main/subject/woody_image.png" align="center" width="500" ></h1>
</div>


---


**Linux project**
(written in **C**)


This project is about coding a simple packer.

📦

“Packers” - are tools which compress executable programs (.exe, .dll,
.ocx ...) and then encrypting them simultaneously. 
During execution, a program passing through a packer is loaded in memory, compressed and encrypted, then it will be decompressed (decrypted as well) and finally be executed.

The existence of such programs is related to the fact that antivirus programs generally
analyse programs when they are loaded in memory, before they are executed. Thus,
encryption and compression of a packer allow to bypass this behavior by obfuscating the
content of an executable until it execution.

---

The goal of this project is to code a program that will at first encrypt a program given
as parameter. Only 64 bits ELF files will be managed here.

---

# The struct of ELF file
<div align="center">
<img src="https://github.com/bchelste/elf64_packer/blob/main/subject/elf_struct.png"></h1>
</div>

---

# some useful commands for working with ELF files
- **file** <efl_file>
- **readelf** (-h -> to read header, -a -> to read all) <elf_file>



to compile elf64 => flag **-m64** is required,


there is also flag **-no-pie** for **EXEC** type
(and type = **DYN** without that flag)

---
# Usage
**make**  