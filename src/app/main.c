#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sagui.h>

#include "my_lib.h"

/* NOTE: Error checking has been omitted to make it clear. */

static void req_cb(__SG_UNUSED void *cls, __SG_UNUSED struct sg_httpreq *req,
                   struct sg_httpres *res) {
  sg_httpres_send(res,
                  "<html><head><title>Hello world</title></head><body>Hello "
                  "world</body></html>",
                  "text/html; charset=utf-8", 200);
}

int main(int argc, const char *argv[]) {

  print_hello_world();

  struct sg_httpsrv *srv;
  uint16_t port;
  if (argc != 2) {
    printf("%s <PORT>\n", argv[0]);
    return EXIT_FAILURE;
  }
  port = strtol(argv[1], NULL, 10);
  srv = sg_httpsrv_new(req_cb, NULL);
  if (!sg_httpsrv_listen(srv, port, false)) {
    sg_httpsrv_free(srv);
    return EXIT_FAILURE;
  }
  fprintf(stdout, "Server running at http://localhost:%d\n",
          sg_httpsrv_port(srv));
  fflush(stdout);
  getchar();
  sg_httpsrv_free(srv);
  return EXIT_SUCCESS;
}


/*
//#include <iostream>

#include "my_lib.h"

int main() {

  //std::cout << "Hello World!!";
  print_hello_world();

  return 0;

}
*/