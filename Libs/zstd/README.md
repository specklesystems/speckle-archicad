# zstd (vendored single-file amalgamation)

- **Version:** 1.5.7
- **Source:** copied verbatim from `specklesystems/speckle-converters`
  (`native/third_party/zstd`, introduced by PR #15 "minipq"), which in turn
  generated it from the official zstd release with
  `python combine.py -r ../../lib -x legacy/zstd_legacy.h -o zstd.c zstd-in.c`.
- **License:** dual BSD / GPLv2 (see `LICENSE`); we use it under BSD.
- **Consumers:** `Libs/minipq` (parquet write on send, parquet read on receive).

To upgrade: regenerate the amalgamation from a newer zstd release (or re-copy
from speckle-converters) and replace `zstd.c` / `zstd.h` / `zstd_errors.h`.
