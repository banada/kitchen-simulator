# Kitchen Simulator

A place to break a few eggs.

## Dependencies

On Ubuntu:
```
sudo apt-get install build-essential libsystemd-dev
```

## Build

```
cd kitchen-simulator
make
./bin/omelette
```

## libkitchensink

libkitchensink can be used to write programs where you simulate making food.

```
libkitchensink
├── stove
├── pan
└── fridge
```

## Daemons

kitchen-simulator daemons use the [sd-bus D-Bus API](https://0pointer.net/blog/the-new-sd-bus-api-of-systemd.html) for IPC.

| daemon | description|
| ------- | --------- |
| stoved | |
| fridged | |

