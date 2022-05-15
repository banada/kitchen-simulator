#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <systemd/sd-bus.h>
#include "stove.h"

#define STOVE_DBUS_SERVICE_NAME "com.kitchensink.stoved"

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

/**
 *  D-Bus method callbacks
 *  (sd_bus_message_handler_t)
 *  TODO char *name[], int mass
 */
static int stove_input_food(sd_bus_message *m, void *userdata, sd_bus_error *ret_error) {

    int ret;
    int mass;

    /* Parse message */
    ret = sd_bus_message_read(m, "x", &mass);
    if (ret < 0) {
        printf("Failed to parse params from message to stove_input_food.\n");
        return -1;
    }

    /* Send response */
    ret = sd_bus_reply_method_return(m, "s", "stoved InputFood success!!");
    if (ret < 0) {
        printf("Failed to send response from stove_input_food.\n");
        return -1;
    }

    printf("stoved InputFood: mass %d\n", mass);

    printf("Sending a message to fridged\n");
    // Get bus that the messsage came from
    sd_bus *bus = sd_bus_message_get_bus(m);
    // Send message to fridged
    ret = sd_bus_call_method(bus,
                            "com.kitchensink.fridged",
                            "/com/kitchensink/fridged",
                            "com.kitchensink.fridged",
                            "InputFood",
                            NULL, NULL, "x", mass);
    if (ret < 0) {
        printf("Failed to send message from stoved to fridged.\n");
        return -1;
    }

    return 0;
}

static int stove_output_food(sd_bus_message *m, void *userdata, sd_bus_error *ret_error) {

    int ret;
    int mass;

    /* Parse message */
    ret = sd_bus_message_read(m, "x", &mass);
    if (ret < 0) {
        printf("Failed to parse params from message to stove_output_food.\n");
    }

    /* Send response */
    ret = sd_bus_reply_method_return(m, "s", "stoved OutputFood success!!");
    if (ret < 0) {
        printf("Failed to send response from stove_output_food.\n");
        return -1;
    }

    printf("stoved OutputFood: mass %d\n", mass);

    return 0;
}

/* Stove D-Bus Interface */
static const sd_bus_vtable stove_vtable[] = {
    SD_BUS_VTABLE_START(0),
    /**
     *  The "InputFood" method:
     *  - Takes an int (x)
     *  - Calls stove_input_food()
     *  - Returns a string (s)
     */
    SD_BUS_METHOD("InputFood", "x", "s", stove_input_food, SD_BUS_VTABLE_UNPRIVILEGED),
    SD_BUS_METHOD("OutputFood", "x", "s", stove_output_food, SD_BUS_VTABLE_UNPRIVILEGED),
    SD_BUS_VTABLE_END
};

static void cleanup_dbus(sd_bus **bus, sd_bus_slot **slot) {
    sd_bus_slot_unref(*slot);
    sd_bus_unref(*bus);
}

/**
 *  Connect to other daemons over D-Bus
 *  TODO generalize for all daemons?
 */
static int setup_dbus(sd_bus **bus, sd_bus_slot **slot) {
    int ret;

    printf("Setting up D-Bus..\n");

    ret = sd_bus_open_user(bus);
    if (ret < 0) {
        printf("setup_dbus: Failed to open user bus.\n");
        exit(1);
    }

    /* Register vtable, creating object */
    ret = sd_bus_add_object_vtable(*bus,
                                   slot,
                                   "/com/kitchensink/stoved",
                                   STOVE_DBUS_SERVICE_NAME,
                                   stove_vtable,
                                   NULL); /* User data ptr */
    if (ret < 0) {
        printf("setup_dbus: Failed to install object vtable.\n");
        cleanup_dbus(bus, slot);
        exit(1);
    }

    /* Get a well-known service name */
    ret = sd_bus_request_name(*bus, STOVE_DBUS_SERVICE_NAME, 0);
    if (ret < 0) {
        printf("setup_dbus: Failed to request service name \"%s\".\n",
               STOVE_DBUS_SERVICE_NAME);
        cleanup_dbus(bus, slot);
        exit(1);
    }

    return ret;
}

int main(void) {
    sd_bus *bus = NULL;
    sd_bus_slot *slot = NULL;
    int ret;

    printf("Starting stoved..\n");

    // stoved starts with no stoves, you need to configure
    // your own kitchen. A kitchen can have many stoves.

    // TODO register stoves with stoved

    // Set up signal handlers
    ret = setup_signal_handlers();
    if (ret < 0) {
        printf("Failed to set up signal handlers.\n");
        exit(1);
    }

    // Set up IPC
    printf("Setting up IPC\n");
    ret = setup_dbus(&bus, &slot);
    if (ret < 0) {
        printf("Failed to set up D-Bus.\n");
        exit(1);
    }

    while(1) {
        /* Process bus requests */
        ret = sd_bus_process(bus,
                             NULL); /* Message ptr TODO */
        if (ret < 0) {
            printf("Failed to process bus request: %d\n", ret);
            cleanup_dbus(&bus, &slot);
            exit(1);
        }
        /* Made progress, process next*/
        if (ret > 0) {
            printf("stoved: Next D-Bus request..\n");
            continue;
        }
        /* No progress was made, wait */
        printf("Waiting for next request..\n");
        ret = sd_bus_wait(bus,
                         (uint64_t) -1); /* Timeout UINT64_MAX */
        if (ret < 0) {
            printf("Failed to wait for bus: %d\n", ret);
            cleanup_dbus(&bus, &slot);
            exit(1);
        }
    }
}

