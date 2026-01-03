fn Term term_new_mov_at(u64 loc, u32 lab, Term val, Term bod) {
  heap_write(loc + 0, val);
  heap_write(loc + 1, bod);
  return term_new(0, MOV, lab, (u32)loc);
}

fn Term term_new_mov(u32 lab, Term val, Term bod) {
  return term_new_mov_at(heap_alloc(2), lab, val, bod);
}
