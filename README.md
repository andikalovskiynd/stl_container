# STL Skip list container

## Description
This project implements container in STL style based on "Skip list" data structure.

## Data structure 
Skip list is multi-level data structure which allows execute search, insert and delete operations for approximately in O(log N) time. 

## Features
* Full iterator system (common and constant).
* Support of standard concepts.
* Error handling.
* Support of standard operators.
* Unit tests.
* CI.

## Build
``` Bash
make
```

## Run tests
``` Bash
./test_skip_list
```

## Docs
* To get .html:
```Bash
doxygen Doxyfile
```
Generated HTML documentation is located at `docs/html/`. Open `index.html` in your browser.

* To get .pdf document:
```Bash
doxygen Doxyfile && cd docs/latex/ && make 
```
Generated PDF document is `docs/latex/refman.pdf`.

## Author 
Andikalovskiy Nikita 24.B82-mm

## Contacts
st131335@student.spbu.ru