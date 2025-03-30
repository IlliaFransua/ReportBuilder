#ifndef UUID_H
#define UUID_H

#include <sodium.h>

void generate_uuid_v4(char *uuid) {
  static int initialized = 0;

  if (initialized == 0) {
      if (sodium_init() < 0) {
          perror("libsodium initialization failed");
          return;
      }
      initialized = 1;
  }

  unsigned char random_bytes[16];

  randombytes_buf(random_bytes, sizeof(random_bytes));

  random_bytes[6] = (random_bytes[6] & 0x0f) | 0x40;
  random_bytes[8] = (random_bytes[8] & 0x3f) | 0x80;

  snprintf(
      uuid, 37, "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x",
      random_bytes[0], random_bytes[1], random_bytes[2], random_bytes[3],
      random_bytes[4], random_bytes[5], random_bytes[6], random_bytes[7],
      random_bytes[8], random_bytes[9], random_bytes[10], random_bytes[11],
      random_bytes[12], random_bytes[13], random_bytes[14], random_bytes[15]);
}

#endif UUID_H