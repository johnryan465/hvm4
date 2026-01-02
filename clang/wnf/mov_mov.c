// % A = v
// % B = A
// ------- MOV-MOV
// A ← B
// % B = v
fn Term wnf_mov_mov(u32 b_loc, Term a_var, u32 lab, u8 side) {
  ITRS++;
  u32  a_loc = term_val(a_var);
  Term val   = heap_take(a_loc);
  heap_subst_var(a_loc, term_new_got(side, lab, b_loc));
  heap_set(b_loc, val);
  return val;
}
