#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "stove.h"

static void handle_sigterm(int signal) {
    printf("\nReceived SIGTERM, terminating.\n");
    exit(0);
}

static void handle_sigint(int signal) {
    printf("\nReceived SIGINT, exiting.\n");
    exit(0);
}

/**
 *  System signal handlers
 */
static int setup_signal_handlers(void) {
    int ret;
    struct sigaction sigterm, sigint;

    // SIGTERM
    sigterm.sa_flags = 0;
    // Signals to be blocked during handler exec
    sigemptyset(&sigterm.sa_mask);
    // Register handler
    sigterm.sa_handler = handle_sigterm;
    ret = sigaction(SIGTERM, &sigterm, NULL);
    if (ret < 0) {
        return ret;
    }

    // SIGINT
    sigint.sa_flags = 0;
    sigemptyset(&sigint.sa_mask);
    sigint.sa_handler = handle_sigint;
    ret = sigaction(SIGINT, &sigint, NULL);

    return ret;
}

int main(void) {
    stove_init(STOVE_GAS, 5);
    // stoved starts with no stoves, you need to configure
    // your own kitchen. A kitchen can have many stoves.
    // TODO register stoves with stoved
    int sig = setup_signal_handlers();
    if (sig < 0) {
        printf("Failed to set up signal handlers.\n");
        exit(1);
    }

    while(1) {

    }
}

