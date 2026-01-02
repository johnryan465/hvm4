// ( (%x=v; body) arg )
// -------------------- APP-MOV
// %x=v; (body arg)
fn Term wnf_app_mov(Term mov, Term arg) {
  ITRS++;
  u32 loc = term_val(mov);
  u32 lab = term_ext(mov);
  Term bod = heap_read(loc + 1);
  u64 new_loc = heap_alloc(2);
  heap_write(new_loc + 0, heap_read(loc + 0));
  heap_write(new_loc + 1, term_new_app(bod, arg));
  return term_new_mov_at((u32)new_loc, lab, heap_read(new_loc + 0), heap_read(new_loc + 1));
}
