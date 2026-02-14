## 2023-10-27 - [Optimized File Scanning in `new_acc`]
**Learning:** `fscanf` is O(fields) and can be dangerous with malformed data. `fgets` + `sscanf` is O(1) for targeted field extraction and safer. Also, always `rewind` file pointers when retrying a scan in a loop.
**Action:** Use `fgets` + `sscanf` for existence checks or single-field lookups in large files. Ensure file pointers are reset on retry logic.
