fn Term term_new_got(u32 side, u32 lab, u32 loc) {
  return term_new(0, GOT, (lab << 1) | (side & 1), loc);
}
