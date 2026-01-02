// % K = &L{x,y}
// ------------- MOV-SUP
// % A = x
// % B = y
// K ← &L{A,B}
fn Term wnf_mov_sup(u32 lab, u32 loc, u8 side, Term sup) {
  // If the binder already contains a SUP, just take our side (FREE)
  Term cell = heap_read(loc);
  if (term_tag(cell) == SUP && term_ext(cell) == lab) {
    return heap_read(term_val(cell) + side);
  }

  u32 s_lab = term_ext(sup);
  if (lab == s_lab) {
    ITRS++;
    u32  s_loc = term_val(sup);
    Term tm0   = heap_read(s_loc + 0);
    Term tm1   = heap_read(s_loc + 1);

    // Update the MOV binder with a SUP so other GOT terms can find their branch
    u64 res_loc = heap_alloc(2);
    heap_write(res_loc + 0, tm0);
    heap_write(res_loc + 1, tm1);
    heap_set(loc, term_new(0, SUP, lab, (u32)res_loc));

    return side == 0 ? tm0 : tm1;
  } else {
    // ITRS++; // Commutation is free
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