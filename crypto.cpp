#include "crypto.h"
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/bio.h>
#include <iomanip>
#include <sstream>
#include <cstring>
#include <iostream>

std::string sha256(const std::string &s) {
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1(reinterpret_cast<const unsigned char*>(s.c_str()), s.size(), hash);

    std::stringstream ss;
    for (int i = 0; i < SHA_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    return ss.str();
}

// Function to Base64 decode
std::vector<unsigned char> base64_decode(const std::string& input) {
    BIO *bio, *b64;
    std::vector<unsigned char> buffer(input.size());
    memset(buffer.data(), 0, buffer.size());

    bio = BIO_new_mem_buf((void*)input.c_str(), input.size());
    b64 = BIO_new(BIO_f_base64());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    int length = BIO_read(bio, buffer.data(), buffer.size());
    BIO_free_all(bio);

    buffer.resize(length);
    return buffer;
}

// Function to decrypt Blowfish CBC
std::string blowfish_decode(const std::vector<unsigned char>& ciphertext, const std::string& key, const std::string& iv) {
    EVP_CIPHER_CTX *ctx;
    int len;
    int plaintext_len;
    unsigned char plaintext[1024] = {0};

    if (!(ctx = EVP_CIPHER_CTX_new())) {
        return "failed to create new cipher context";
    }

    if (1 != EVP_DecryptInit_ex(ctx, EVP_bf_cbc(), NULL, (const unsigned char*)key.c_str(), (const unsigned char*)iv.c_str())) {
        return "failed to initialize cipher context";
    }

    if (1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext.data(), ciphertext.size())) {
        return "failed to decrypt";
    }

    plaintext_len = len;

    if (1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) {
        return "failed to finalize decryption";
    }

    plaintext_len += len;
    EVP_CIPHER_CTX_free(ctx);

    return std::string((char*)plaintext, plaintext_len);
}