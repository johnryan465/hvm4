fn Term wnf_mov_lam(u32 loc, Term lam) {
  ITRS++;
  u32  lam_loc = term_val(lam);
  u32  lam_ext = term_ext(lam);
  Term bod     = heap_read(lam_loc);

  u32  lab     = 0;
  u64  a       = heap_alloc(5);
  heap_write(a + 4, bod);
  Copy B       = term_clone_at(a + 4, lab);
  heap_write(a + 0, B.k0);
  heap_write(a + 1, B.k1);
  heap_write(a + 2, term_new(0, VAR, 0, a + 0));
  heap_write(a + 3, term_new(0, VAR, 0, a + 1));
  Term su      = term_new(0, SUP, lab, a + 2);
  Term res     = term_new(0, LAM, lam_ext, a + 0);
  heap_subst_var(lam_loc, su);
  heap_subst_var(loc, res);
  return res;
}