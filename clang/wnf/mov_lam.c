fn Term wnf_mov_lam(u32 lab, u32 loc, u8 side, Term lam) {
  if (lab == 0) {
    lab = __atomic_fetch_add(&PARSE_FRESH_LAB, 1, __ATOMIC_RELAXED);
  }
  // If the binder already contains a SUP, just take our side (FREE)
  Term cell = heap_read(loc);
  if (term_tag(cell) == SUP && term_ext(cell) == lab) {
    return heap_read(term_val(cell) + side);
  }

  // Otherwise, perform the interaction (COUNTED)
  ITRS++;
  u32  lam_loc = term_val(lam);
  u32  lam_ext = term_ext(lam);
  Term bod     = heap_read(lam_loc);
  u64 a = heap_alloc(5);
  heap_write(a + 4, bod);
  Copy B = term_clone_at(a + 4, lab);
  heap_write(a + 0, B.k0);
  heap_write(a + 1, B.k1);
  heap_write(a + 2, term_new(0, VAR, 0, a + 0));
  heap_write(a + 3, term_new(0, VAR, 0, a + 1));
  Term su = term_new(0, SUP, lab, a + 2);
  Term l0 = term_new(0, LAM, lam_ext, a + 0);
  Term l1 = term_new(0, LAM, lam_ext, a + 1);
  
  // Update lambda variable with the SUP
  heap_subst_var(lam_loc, su);
  
  // Update the MOV binder with a SUP of the two LAMs
  // This allows other GOT terms to find their respective LAM
  u64 s_loc = heap_alloc(2);
  heap_write(s_loc + 0, l0);
  heap_write(s_loc + 1, l1);
  Term res_su = term_new(0, SUP, lab, (u32)s_loc);
  heap_set(loc, res_su);

  return side == 0 ? l0 : l1;
}