// RUN: %sea bpf -m64 -O0 --bmc=mono --horn-bv2=true --inline --bound=8 --keep-shadows=true --horn-stats "%s" 2>&1 | OutputCheck %s
// RUN: %sea bpf -m64 -O3 --bmc=mono --horn-bv2=true --inline --bound=8 --keep-shadows=true --horn-stats "%s" 2>&1 | OutputCheck %s

// RUN: %sea bpf -m64 -O0 --bmc=mono --inline --bound=8 --keep-shadows=true --horn-stats "%s" 2>&1 | OutputCheck %s
// RUN: %sea bpf -m64 -O3 --bmc=mono --inline --bound=8 --keep-shadows=true --horn-stats "%s" 2>&1 | OutputCheck %s

// CHECK-L: unsat
// XFAIL: *

// Based on https://github.com/MCFuzzer/MCFuzz/issues/42.
// This works with the old bv-opsem and -O3, but not -O0.

extern void __VERIFIER_error(void) __attribute__((noreturn));

int main() {
  char *s = ":a";
  char *lim = s + 2;
  char *ptr = s;
  int sword = 1;
  while (ptr < lim && sword--) {
    while (*ptr != ':')
      ++ptr;
    ptr++;
  }
  if (ptr != s + 1)
    __VERIFIER_error();
  return 0;
}
