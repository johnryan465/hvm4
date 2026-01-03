fn Term parse_term(PState *s, u32 depth);

fn Term parse_term_mov(PState *s, u32 depth) {
  parse_skip(s);
  u32 cloned = parse_match(s, "&");
  u32 nam = parse_name(s);
  parse_skip(s);
  // Inline label support: %x&L or %x&(L) or %x&
  u32 lab = 0;
  if (parse_match(s, "&")) {
    if (parse_peek(s) == '(') {
      parse_consume(s, "(");
      // Dynamic label currently not supported for MOV in this parser version
      // but matching the syntax anyway
      parse_term(s, depth);
      parse_consume(s, ")");
    } else {
      lab = parse_name(s);
    }
  }
  parse_skip(s);
  parse_consume(s, "=");
  Term val = parse_term(s, depth);
  parse_skip(s);
  parse_match(s, ";");
  parse_skip(s);
  parse_bind_push(nam, depth, lab, PBIND_MOV, cloned);
  Term body = parse_term(s, depth + 1);
  parse_bind_pop();
  u64 loc = heap_alloc(2);
  HEAP[loc + 0] = val;
  HEAP[loc + 1] = body;
  return term_new(0, MOV, lab, loc);
}
