#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>

void print_hex(const char *label, const unsigned char *data, size_t len) {
    printf("%s: ", label);
    for (size_t i = 0; i < len; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

void encrypt_decrypt(const char *plaintext, const char *key, const char *iv, int mode) {
    AES_KEY aes_key;
    unsigned char ciphertext[32];
    unsigned char decryptedtext[32];

    AES_set_encrypt_key((const unsigned char *)key, 128, &aes_key);

    // Encrypt
    AES_encrypt((const unsigned char *)plaintext, ciphertext, &aes_key);

    print_hex("Ciphertext", ciphertext, AES_BLOCK_SIZE);

    // Decrypt
    AES_set_decrypt_key((const unsigned char *)key, 128, &aes_key);

    AES_decrypt(ciphertext, decryptedtext, &aes_key);

    print_hex("Decryptedtext", decryptedtext, AES_BLOCK_SIZE);
}

int main() {
    const char *plaintext = "HelloPadding";
    const char *key = "0123456789abcdef";
    const char *iv = "1234567890abcdef";

    printf("Plaintext: %s\n", plaintext);

    printf("\nECB Mode:\n");
    encrypt_decrypt(plaintext, key, iv, AES_ENCRYPT);

    printf("\nCBC Mode:\n");
    encrypt_decrypt(plaintext, key, iv, AES_ENCRYPT | AES_CBC_FLAG);

    printf("\nCFB Mode:\n");
    encrypt_decrypt(plaintext, key, iv, AES_ENCRYPT | AES_CFB_FLAG);

    return 0;
}