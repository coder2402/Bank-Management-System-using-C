## 2023-10-27 - [Optimized File Scanning in `new_acc`]
**Learning:** `fscanf` is O(fields) and can be dangerous with malformed data. `fgets` + `sscanf` is O(1) for targeted field extraction and safer. Also, always `rewind` file pointers when retrying a scan in a loop.
**Action:** Use `fgets` + `sscanf` for existence checks or single-field lookups in large files. Ensure file pointers are reset on retry logic.

## 2023-10-27 - [Edit-In-Place Optimization for Large Files]
**Learning:** When modifying a specific record in a large file, parsing every line with `fscanf` and reformatting with `fprintf` is extremely wasteful (CPU + I/O overhead). `fgets` coupled with `fputs` for non-matching lines reduces this to a simple string copy, which is ~10x faster for large datasets.
**Action:** Replace full-record parsing loops with `fgets` loops that only parse the identifier. Use `fputs` to copy unmodified lines directly.
