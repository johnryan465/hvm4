fn Term parse_term(PState *s, u32 depth);

fn Term parse_term_mov(PState *s, u32 depth) {
  parse_skip(s);
  u32 cloned = parse_match(s, "&");
  u32 nam = parse_name(s);
  parse_skip(s);
  parse_consume(s, "=");
  Term val = parse_term(s, depth);
  parse_skip(s);
  parse_match(s, ";");
  parse_skip(s);
  u32 lab = PARSE_FRESH_LAB++;
  parse_bind_push(nam, depth, lab, PBIND_MOV, cloned);
  Term body = parse_term(s, depth + 1);
  u32 uses = parse_bind_get_uses();
  if (!cloned && uses > 1) {
    parse_error_affine(nam, uses, 0, "% &");
  }
  if (cloned) {
    body = parse_auto_dup(body, depth + 1, depth + 1, BJM, lab);
  }
  parse_bind_pop();
  return term_new_mov(lab, val, body);
}
