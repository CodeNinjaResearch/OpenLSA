# OpenLSA
Open Large Scale Attraction Emulator (OpenLSA) is an emulator for the ride boards in Let's Go Jungle Special, The House Of The Dead 4 Special, and possibly Jurassic Park Special. The project aims to document the protocol so that large attraction games using these boards, can be played at home.

## Game Information

### Let's Go Jungle Special

Let's go jungle special sends its serial commands to `/dev/ttyS0`. If this isn't populated on your Lindbergh you may need to symlink it using this command:

```
ln -s /dev/tts/0 /dev/ttyS0
```

## Protocol Information

- Baud Rate: 115200
- Recive: 7 bytes a go
  - 1st byte is always 0xC0
  - 2nd byte is checksum which is the exclusive bitwise or (^) operation over the next 5 payload bytes
  - 3rd to 7th byte is payload
- Send: 22 bytes a go
  - 1st byte is always 0xC0
  - 2nd to 21st byte is payload
  - 22nd byte is checksum which is the exclusive bitwise or (^) operation over the previous 20 bytes.

The question remains, why is the checksum at the start on the way out, and at the end on the way in? Possibly I'm confusing myself here, and the checksum should come at the start but looking at the code it doesn't seem to.

## Dumps

When the machine is starting up this is repeated:

```
C0 01 00 00 01 00 00
```

When the machine is erroring this is repeated indefinately: 

```
C0 16 00 00 04 00 12
```

When the machine is in test mode this is repeated indefinately:

```
C0 13 00 00 00 00 13
```

## Emulator Information

The emulation is written in _python 2.7_ which you must have installed.

To run the emulator, open the openlsa.py file and change the file path to the RS232 device you are using. You can then type `python openlsa.py` and will start to see output from the Lindbergh device.
