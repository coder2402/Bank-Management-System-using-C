## $(date +%Y-%m-%d) - [Fast-Forward Copy Strategy]
**Learning:** Optimizations to file operations (like `edit`, `transact`, `erase`) using copy-forward loops (`fgets` + `fputs`) can be further sped up. Once the target record is found and successfully modified/skipped, breaking out of the parsing loop and using a subsequent, simple `while (fgets...) fputs(...)` loop skips the overhead of `strtol` and conditional checks for the remaining records in the file.
**Action:** Always implement early breaks and secondary "fast-forward" copy loops when processing text files sequentially where only a single target record is expected to be modified or deleted.

## $(date +%Y-%m-%d) - [Early Exit in Linear Search]
**Learning:** Functions that perform linear searches through text files (like `see`) often lack an early exit condition once the target is found, leading to unnecessary parsing of the entire remainder of the file.
**Action:** Always add a `break` statement immediately after successfully processing a found target in a linear search loop to halt further I/O and parsing overhead.

## $(date +%Y-%m-%d) - [Pointer Arithmetic > strtok for Parsing]
**Learning:** For high-performance C text parsing where only specific fields are needed, manual pointer arithmetic (using `strchr` and advancing pointers) outperforms `strtok` by ~1.7x and `sscanf` by ~8x. `strtok` introduces overhead by modifying the source buffer inline (adding null terminators) and managing internal state across calls, whereas pointer arithmetic is purely read-oriented and avoids state overhead.
**Action:** When micro-optimizing critical file parsing loops in C, prefer `strtol`/`strtod` combined with pointer arithmetic (`strchr`) to skip over unused fields instead of using `strtok` or `sscanf`.
