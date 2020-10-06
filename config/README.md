# Configurations
These pre-tested Configurations were most likely taken from https://github.com/MarlinFirmware/Configurations/archive/release-2.0.6.zip

## Upstream
Marlin configurations for specific machines are now maintained in their own repository at:
- https://github.com/MarlinFirmware/Configurations

Or the latest configs can be downloaded from:
- https://github.com/MarlinFirmware/Configurations/archive/bugfix-2.0.x.zip

# Marlin Firmware is configured using two files:

- `Configuration.h` contains core configuration options like machine geometry.
- `Configuration_adv.h` contains optional settings for advanced and low level features.

For Graphical LCD these files may also be included:

- `_Bootscreen.h` provides the bitmap for a custom Boot Screen.
- `_Statusscreen.h` provides bitmaps to customize the Status Screen.

See the [Configuration page](https://marlinfw.org/docs/configuration/configuration.html) for more information about configuration and individual configuration options.
