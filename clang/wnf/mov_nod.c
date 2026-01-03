fn Term wnf_mov_nod(u32 lab, u32 loc, u8 side, Term term) {
  u32 t_loc = term_val(term);
  u32 t_ext = term_ext(term);
  u8 t_tag = term_tag(term);

  if (t_tag == ERA) {
    heap_subst_var(loc, term);
    return term;
  }

  u32 ari = term_arity(term);
  u64 base = heap_alloc(2 * (u64)ari);
  u32 got_loc = (u32)base;
  u32 nod_loc = got_loc + ari;
  for (u32 i = 0; i < ari; i++) {
    heap_write(got_loc + i, heap_read(t_loc + i));
    heap_write(nod_loc + i, term_new_got(side, lab, got_loc + i));
  }

  Term res = term_new(0, t_tag, t_ext, nod_loc);
  heap_subst_var(loc, res);
  return res;
}
