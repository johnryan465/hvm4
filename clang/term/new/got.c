fn Term term_new_got(u32 side, u32 lab, u32 loc) {
  u32 ext = (lab << 1) | (side & 1);
  return term_new(0, GOT, ext, loc);
}
