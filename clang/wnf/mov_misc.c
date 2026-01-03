// MOV-MOV
fn Term wnf_mov_mov(u32 b_loc, Term a_var, u32 lab, u8 side) {
  // ITRS++;
  u32 a_loc = term_val(a_var);
  Term val = heap_take(a_loc);
  heap_subst_var(a_loc, term_new_got(side, lab, b_loc));
  heap_set(b_loc, val);
  return val;
}

// MOV-NAM
fn Term wnf_mov_nam(u32 lab, u32 loc, u8 side, Term nam) {
  // ITRS++;
  heap_subst_var(loc, nam);
  return nam;
}

// MOV-DRY
fn Term wnf_mov_dry(u32 lab, u32 loc, u8 side, Term dry) {
  // ITRS++;
  u32 d_loc = term_val(dry);
  u64 base = heap_alloc(4);
  u32 at = (u32)base;
  heap_write(at + 0, heap_read(d_loc + 0));
  heap_write(at + 1, heap_read(d_loc + 1));
  Term f = term_new_got(side, lab, at + 0);
  Term a = term_new_got(side, lab, at + 1);
  Term res = term_new(0, DRY, 0, at + 2);
  heap_write(at + 2, f);
  heap_write(at + 3, a);
  heap_subst_var(loc, res);
  return res;
}

// MOV-RED
fn Term wnf_mov_red(u32 lab, u32 loc, u8 side, Term red) {
  // ITRS++;
  u32 r_loc = term_val(red);
  u64 base = heap_alloc(4);
  u32 at = (u32)base;
  heap_write(at + 0, heap_read(r_loc + 0));
  heap_write(at + 1, heap_read(r_loc + 1));
  Term f = term_new_got(side, lab, at + 0);
  Term g = term_new_got(side, lab, at + 1);
  Term res = term_new(0, RED, 0, at + 2);
  heap_write(at + 2, f);
  heap_write(at + 3, g);
  heap_subst_var(loc, res);
  return res;
}
