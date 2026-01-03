// ( GOT(v) arg )
// -------------- APP-GOT
// GOT(v arg)
fn Term wnf_app_got(Term got, Term arg) {
  u32 loc = term_val(got);
  u32 ext = term_ext(got);
  u32 lab = ext >> 1;
  u8 side = ext & 1;
  Term val = heap_read(loc);
  u64 new_loc = heap_alloc(2);
  heap_write(new_loc + 0, val);
  heap_write(new_loc + 1, arg);
  Term app = term_new(0, APP, 0, (u32)new_loc);
  u64 res_loc = heap_alloc(1);
  heap_write(res_loc, app);
  return term_new_got(side, lab, (u32)res_loc);
}
