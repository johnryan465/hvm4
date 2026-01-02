fn Term wnf_mov_lam(u32 lab, u32 loc, u8 side, Term lam) {
  if (lab == 0) {
    lab = __atomic_fetch_add(&PARSE_FRESH_LAB, 1, __ATOMIC_RELAXED);
  }
  return wnf_dup_lam(lab, loc, side, lam);
}

  
  