#!/usr/bin/env bash

exit_code=0
diff tests/hello-before.txt <(./hello) >&2 || exit_code=1
diff tests/elf-changer.txt <(./elf_changer hello) >&2 || exit_code=1
./elf_changer -c hello g1 g2 g3 >/dev/null
diff tests/hello-after.txt <(./hello) >&2 || exit_code=1

[ "$exit_code" == 0 ] && echo "All tests passed"
exit "$exit_code"
