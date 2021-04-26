## Imaginary ASM to IA-32(x86 Intel Assembly)

This project is the second assignment of Basic Software discipline (2018/2) at University of Brasília.

### 1. Students
|Name (Git User)|ID|
|--|--|
|Hugo Nascimento Fonseca (@Hugo-NF)|16/0008166|
|José Luiz Gomes Nogueira (@01oseluiz)|16/0032458|
 
### 2. Tools and environment
- Language: C++ 17
- OS: Ubuntu 18.04 (g++ 7.3.0) 
- CMake: 3.10 ou higher
- Valgrind: 3.13.0

### 3. Compilation
```markdown
cmake CMakeLists.txt
make
```
* If Makefile is already present, you are able to skip the first command.
### 4. Usage and options available
```
./tradutor (optional flags) myfile1 myfile2 ... myfileN
```
* Available flags
    - -h	= help menu
    - -o	= translate and create executable file, aka: _nasm_ e _ld_
    - -c	= only translate **(default)**
    - -v	= show version
    - -d	= show developers

* The following file extensions are assumed
    * Imaginary ASM source code:        .asm
    * x86 Intel Assembly source code:   .s

* Some source code examples provided by discipline professor and project specification are available in /docs directory  

See at [GitHub repo](https://github.com/Hugo-NF/IA-32-Translator)