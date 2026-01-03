// ( (%x=v; body) arg )
// -------------------- APP-MOV
// %x=v; (body arg)
fn Term wnf_app_mov(Term mov, Term arg) {
  // 1. Structural cleanup: commuting APP with MOV
  // // ITRS++;
  u32 loc = term_val(mov);
  u32 lab = term_ext(mov) >> 1;
  Term bod = heap_read(loc + 1);
  u64 new_loc = heap_alloc(2);
  heap_write(new_loc + 0, heap_read(loc + 0));
  heap_write(new_loc + 1, term_new_app(bod, arg)); // app(body, arg)
  return term_new(0, MOV, lab, new_loc);
}
