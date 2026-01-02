// % K = &L{x,y}
// ------------- MOV-SUP
// % A = x
// % B = y
// K ← &L{A,B}
fn Term wnf_mov_sup(u32 lab, u32 loc, u8 side, Term sup) {
  u32 s_lab = term_ext(sup);
  if (lab == s_lab) {
    ITRS++;
    u32  s_loc = term_val(sup);
    Term tm0   = heap_read(s_loc + 0);
    Term tm1   = heap_read(s_loc + 1);
    return heap_subst_cop(side, loc, tm0, tm1);
  } else {
    ITRS++;
    u32  s_loc = term_val(sup);
    u64  base  = heap_alloc(4);
    u32  at    = (u32)base;
    heap_write(at + 0, heap_read(s_loc + 0));
    heap_write(at + 1, heap_read(s_loc + 1));
    Term a     = term_new_got(side, lab, at + 0);
    Term b     = term_new_got(side, lab, at + 1);
    Term res   = term_new_sup_at(at + 2, s_lab, a, b);
    heap_subst_var(loc, res);
    return res;
  }
}