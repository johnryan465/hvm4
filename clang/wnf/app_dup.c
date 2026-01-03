// ( (!x = v; body) arg )
// -------------------- APP-DUP
// !x = v; (body arg)
fn Term wnf_app_dup(Term dup, Term arg) {
  ITRS++;
  u32 d_loc = term_val(dup);
  u32 d_ext = term_ext(dup);
  u8 side = (term_tag(dup) == DP0) ? 0 : 1;
  Term bod = heap_read(d_loc + (1 - side));
  u64 new_loc = heap_alloc(2);
  heap_write(new_loc + (1 - side), term_new_app(bod, arg)); // app(body, arg)
  heap_write(new_loc + side, heap_read(d_loc + side));      // val
  return term_new(0, side == 0 ? DP0 : DP1, d_ext, (u32)new_loc);
}
