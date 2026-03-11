## $(date +%Y-%m-%d) - [Fast-Forward Copy Strategy]
**Learning:** Optimizations to file operations (like `edit`, `transact`, `erase`) using copy-forward loops (`fgets` + `fputs`) can be further sped up. Once the target record is found and successfully modified/skipped, breaking out of the parsing loop and using a subsequent, simple `while (fgets...) fputs(...)` loop skips the overhead of `strtol` and conditional checks for the remaining records in the file.
**Action:** Always implement early breaks and secondary "fast-forward" copy loops when processing text files sequentially where only a single target record is expected to be modified or deleted.

## $(date +%Y-%m-%d) - [Early Exit in Linear Search]
**Learning:** Functions that perform linear searches through text files (like `see`) often lack an early exit condition once the target is found, leading to unnecessary parsing of the entire remainder of the file.
**Action:** Always add a `break` statement immediately after successfully processing a found target in a linear search loop to halt further I/O and parsing overhead.

## $(date +%Y-%m-%d) - [Pointer Arithmetic Parsing Strategy]
**Learning:** For high-performance parsing of specific fields in delimited text files where not all fields are used, manually parsing string fields using pointer arithmetic is significantly faster than `strtok` (e.g., ~1.7x faster) and avoids stateful function overhead and inline buffer modifications.
**Action:** Always prefer manual pointer arithmetic over `strtok` or `sscanf` when optimizing line-by-line file parsing loops in hot paths, while ensuring bounds checking and safe handling of delimiter whitespace.
