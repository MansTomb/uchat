#include "server.h"

void mx_initialize_ssl(){
    SSL_load_error_strings();
    SSL_library_init();
    OpenSSL_add_all_algorithms();
}

void mx_destroy_ssl() {
    // SSL_CTX_free(info->sock->ctx);
    ERR_free_strings();
    EVP_cleanup();
}

void mx_shutdown_ssl() {
    SSL_shutdown(ssl);
    SSL_free(ssl);
}

// SSL_CTX *sslctx;
// SSL *cSSL;

// InitializeSSL();
// sockfd = socket(AF_INET, SOCK_STREAM, 0);
// newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

// ctx = SSL_CTX_new( SSLv23_server_method());
// SSL_CTX_set_options(sslctx, SSL_OP_SINGLE_DH_USE);
// int use_cert = SSL_CTX_use_certificate_file(sslctx, "/serverCertificate.pem" , SSL_FILETYPE_PEM);

// int use_prv = SSL_CTX_use_PrivateKey_file(sslctx, "/serverCertificate.pem", SSL_FILETYPE_PEM);

// cSSL = SSL_new(sslctx);
// SSL_set_fd(cSSL, newsockfd );
//Here is the SSL Accept portion.  Now all reads and writes must use SSL
// ssl_err = SSL_accept(cSSL);
// if(ssl_err <= 0)
// {
//     //Error occurred, log and close down ssl
//     ShutdownSSL();
// }

// SSL_read(SSL, (char *)charBuffer, nBytesToRead);
// SSL_write(cSSL, "Hi :3\n", 6);
