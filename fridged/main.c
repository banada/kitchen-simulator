#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <systemd/sd-bus.h>
#include "fridge.h"

#define FRIDGE_DBUS_SERVICE_NAME "com.kitchensink.fridged"

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
static int fridge_input_food(sd_bus_message *m, void *userdata, sd_bus_error *ret_error) {

    int ret;
    int mass;

    /* Parse message */
    ret = sd_bus_message_read(m, "x", &mass);
    if (ret < 0) {
        printf("Failed to parse params from message to fridge_input_food.\n");
        return -1;
    }

    /* Send response */
    ret = sd_bus_reply_method_return(m, "s", "fridged InputFood success!!");
    if (ret < 0) {
        printf("Failed to send response from fridge_input_food.\n");
        return -1;
    }

    printf("fridged InputFood: mass %d\n", mass);

    return 0;
}

static int fridge_output_food(sd_bus_message *m, void *userdata, sd_bus_error *ret_error) {

    int ret;
    int mass;

    /* Parse message */
    ret = sd_bus_message_read(m, "x", &mass);
    if (ret < 0) {
        printf("Failed to parse params from message to fridge_output_food.\n");
    }

    /* Send response */
    ret = sd_bus_reply_method_return(m, "s", "fridged OutputFood success!!");
    if (ret < 0) {
        printf("Failed to send response from fridge_output_food.\n");
        return -1;
    }

    printf("fridged OutputFood: mass %d\n", mass);

    return 0;
}

/* Stove D-Bus Interface */
static const sd_bus_vtable fridge_vtable[] = {
    SD_BUS_VTABLE_START(0),
    /**
     *  The "InputFood" method:
     *  - Takes an int (x)
     *  - Calls fridge_input_food()
     *  - Returns a string (s)
     */
    SD_BUS_METHOD("InputFood", "x", "s", fridge_input_food, SD_BUS_VTABLE_UNPRIVILEGED),
    SD_BUS_METHOD("OutputFood", "x", "s", fridge_output_food, SD_BUS_VTABLE_UNPRIVILEGED),
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
                                   "/com/kitchensink/fridged",
                                   FRIDGE_DBUS_SERVICE_NAME,
                                   fridge_vtable,
                                   NULL); /* User data ptr */
    if (ret < 0) {
        printf("setup_dbus: Failed to install object vtable.\n");
        cleanup_dbus(bus, slot);
        exit(1);
    }

    /* Get a well-known service name */
    ret = sd_bus_request_name(*bus, FRIDGE_DBUS_SERVICE_NAME, 0);
    if (ret < 0) {
        printf("setup_dbus: Failed to request service name \"%s\".\n",
               FRIDGE_DBUS_SERVICE_NAME);
        cleanup_dbus(bus, slot);
        exit(1);
    }

    return ret;
}

int main(void) {
    sd_bus *bus = NULL;
    sd_bus_slot *slot = NULL;
    int ret;

    printf("Starting fridged..\n");
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
            printf("fridged: Next D-Bus request..\n");
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

