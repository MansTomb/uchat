#include "server.h"

static SSL_CTX *create_context(void) {
    const SSL_METHOD *method;
    SSL_CTX *ctx;

    method = SSLv23_server_method();  // Set SSLv2 client hello, also announce SSLv3 and TLSv1.

    ctx = SSL_CTX_new(method);
    if (!ctx) {
        perror("Unable to create SSL context");
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    return ctx;
}

static void configure_context(SSL_CTX *ctx) {
    SSL_CTX_set_ecdh_auto(ctx, 1);
    // SSL_CTX_set_options(ctx, SSL_OP_SINGLE_DH_USE);

    /* Set the key and cert */
    if (SSL_CTX_use_certificate_file(ctx, "cert.pem", SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    if (SSL_CTX_use_PrivateKey_file(ctx, "key.pem", SSL_FILETYPE_PEM) <= 0 ) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
}

void mx_init_ssl(SSL_CTX *ctx) {
    OpenSSL_add_all_algorithms();  // These function calls initialize openssl for correct work.
    SSL_load_error_strings();

    // ERR_load_BIO_strings();
    // ERR_load_crypto_strings();
    // SSL_library_init();

    ctx = create_context();
    configure_context(ctx);
}


void mx_accept_ssl(t_sock *sock, int *new_sock) {
    const char reply[] = "test\n";

    sock->ssl = SSL_new(sock->ctx);  // Create new SSL connection state object.
    SSL_set_fd(sock->ssl, *new_sock);  // Attach the SSL session to the socket descriptor.

    if (SSL_accept(sock->ssl) <= 0) {
        ERR_print_errors_fp(stderr);
        // mx_shutdown_ssl(ssl);
    }
    else
        SSL_write(sock->ssl, reply, strlen(reply));
}

// SSL_read(SSL, (char *)charBuffer, nBytesToRead);
// SSL_write(cSSL, "Hi :3\n", 6);
