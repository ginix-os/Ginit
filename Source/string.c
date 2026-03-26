int
strlen(
  char *buf
) {
  char *bufstamp = buf;
  while(*(buf++));

  return buf-bufstamp;
}
