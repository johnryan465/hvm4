// % X = ^name
// ---------- MOV-NAM
// X ← ^name
fn Term wnf_mov_nam(u32 lab, u32 loc, u8 side, Term nam) {
  // ITRS++; // Commutation is free
  heap_subst_var(loc, nam);
  return nam;
}
