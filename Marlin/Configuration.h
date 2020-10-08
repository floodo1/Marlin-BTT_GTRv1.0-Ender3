/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#define CONFIGURATION_H_VERSION 020007

/**
 * Ender3 stock firmware github: https://github.com/Creality3DPrinting/Ender-3/tree/master/Ender-3%20Firmware%20(Marlin)/Ender-3%20(includes%20power%20failure%20resume-%20English)/Marlin
 */


// @section info
#define STRING_CONFIG_H_AUTHOR "(Ender3 GTR Marlin bugfix)" // Who made the changes. printed to the host during boot and M115

#define SHOW_CUSTOM_BOOTSCREEN  // on startup
#define SHOW_BOOTSCREEN // marlin boot screen
#define CUSTOM_STATUS_SCREEN_IMAGE


// @section machine
#define CUSTOM_MACHINE_NAME "Ender3 GTR"  // Name displayed in the LCD "Ready" message and Info menu
#define MACHINE_UUID "2f38eea3-4d29-44f3-9fac-517f905974e6"

#ifndef MOTHERBOARD
  #define MOTHERBOARD BOARD_BTT_GTR_V1_0
#endif

#define SERIAL_PORT -1
#define SERIAL_PORT_2 3
#define BAUDRATE 250000 // 115200 known good on BTT GTR :[2400, 9600, 19200, 38400, 57600, 115200, 250000, 500000, 1000000]


// @section extruder
#define EXTRUDERS 1
#define DEFAULT_NOMINAL_FILAMENT_DIA 1.75 // (1.75, 2.85, 3.0, ...). Used for Volumetric, Filament Width Sensor, etc.

// @section machine


// @section temperature
#define TEMP_SENSOR_0 1
#define TEMP_SENSOR_1 0
#define TEMP_SENSOR_2 0
#define TEMP_SENSOR_3 0
#define TEMP_SENSOR_4 0
#define TEMP_SENSOR_5 0
#define TEMP_SENSOR_6 0
#define TEMP_SENSOR_7 0
#define TEMP_SENSOR_BED 1
#define TEMP_SENSOR_PROBE 0
#define TEMP_SENSOR_CHAMBER 0

// Dummy thermistor constant temperature readings, for use with 998 and 999
#define DUMMY_THERMISTOR_998_VALUE 25
#define DUMMY_THERMISTOR_999_VALUE 100

#define MAX_REDUNDANT_TEMP_SENSOR_DIFF 10

#define TEMP_RESIDENCY_TIME     10  // (seconds) Time to wait for hotend to "settle" in M109
#define TEMP_WINDOW              1  // (°C) Temperature proximity for the "temperature reached" timer
#define TEMP_HYSTERESIS          3  // (°C) Temperature proximity considered "close enough" to the target

#define TEMP_BED_RESIDENCY_TIME 10  // (seconds) Time to wait for bed to "settle" in M190
#define TEMP_BED_WINDOW          1  // (°C) Temperature proximity for the "temperature reached" timer
#define TEMP_BED_HYSTERESIS      3  // (°C) Temperature proximity considered "close enough" to the target

// Below this temperature the heater will be switched off because it probably indicates a broken thermistor wire.
#define HEATER_0_MINTEMP   5  // per ender3 stock firmware github. v2 uses 0
#define HEATER_1_MINTEMP   5
#define HEATER_2_MINTEMP   5
#define HEATER_3_MINTEMP   5
#define HEATER_4_MINTEMP   5
#define HEATER_5_MINTEMP   5
#define HEATER_6_MINTEMP   5
#define HEATER_7_MINTEMP   5
#define BED_MINTEMP        5

// Above this temperature the heater will be switched off.
// This can protect components from overheating, but NOT from shorts and failures.
// (Use MINTEMP for thermistor short/failure protection.)
#define HEATER_0_MAXTEMP 275
#define HEATER_1_MAXTEMP 275
#define HEATER_2_MAXTEMP 275
#define HEATER_3_MAXTEMP 275
#define HEATER_4_MAXTEMP 275
#define HEATER_5_MAXTEMP 275
#define HEATER_6_MAXTEMP 275
#define HEATER_7_MAXTEMP 275
#define BED_MAXTEMP      125  // per marlin config example for Ender3

//===========================================================================
//============================= PID Settings ================================
//===========================================================================
// PID Tuning Guide here: https://reprap.org/wiki/PID_Tuning
#define PIDTEMP          // Comment to disable PID and enable bang-bang.
#define BANG_MAX 255     // Limits current to nozzle while in bang-bang mode; 255=full current
#define PID_MAX BANG_MAX // Limits current to nozzle while PID is active (see PID_FUNCTIONAL_RANGE below); 255=full current
#define PID_K1 0.95      // Smoothing factor within any PID loop

#if ENABLED(PIDTEMP)
  // Add PID auto-tuning to the "Advanced Settings" menu. (~250 bytes of PROGMEM). Or use gcode like "M303 C10 E0 S200 U1"
  //#define PID_AUTOTUNE_MENU

  /** Source                            Kp      Ki      Kd
   *  -------------------------------   -----   ----    -----
   *  calibrated "M303 C10 E0 S220 U1"  32.69   3.82    69.96   // 20200917
   *  Stock ender3 firmware (M503)      23.81   1.93    73.64
   *  Stock ender3 firwmare github      20.84   1.96    55.47   // "Stock CR-10S Hotend fan 100%"
   *  Marlin ender3 config example      21.73   1.54    76.55
   *  Marlin ender3 v2 config example   28.72   2.62    78.81
   */
  // #define PID_PARAMS_PER_HOTEND  // or Set/get with gcode: "M301 E[extruder number, 0-2]"
  #if ENABLED(PID_PARAMS_PER_HOTEND)
    // Specify between 1 and HOTENDS values per array, i.e. "{ 32.69, 20.84 }"
    // If fewer than EXTRUDER values are provided, the last element will be repeated.
    #define DEFAULT_Kp_LIST {  32.69,  20.84 }
    #define DEFAULT_Ki_LIST {   3.82,   1.96 }
    #define DEFAULT_Kd_LIST {  69.96   55.47 }
  #else
    #define DEFAULT_Kp 32.69
    #define DEFAULT_Ki 3.82
    #define DEFAULT_Kd 69.96
  #endif



#endif // PIDTEMP

//===========================================================================
//====================== PID > Bed Temperature Control ======================
//===========================================================================

/**
 * PID Bed Heating
 *
 * If this option is enabled set PID constants below.
 * If this option is disabled, bang-bang will be used and BED_LIMIT_SWITCHING will enable hysteresis.
 *
 * The PID frequency will be the same as the extruder PWM.
 * If PID_dT is the default, and correct for the hardware/configuration, that means 7.689Hz,
 * which is fine for driving a square wave into a resistive load and does not significantly
 * impact FET heating. This also works fine on a Fotek SSR-10DA Solid State Relay into a 250W
 * heater. If your configuration is significantly different than this and you don't understand
 * the issues involved, don't use bed PID until someone else verifies that your hardware works.
 */
#define PIDTEMPBED


/**
 * Max Bed Power
 * Applies to all forms of bed control (PID, bang-bang, and bang-bang with hysteresis).
 * When set to any value below 255, enables a form of PWM to the bed that acts like a divider
 * so don't use it unless you are OK with PWM on your bed. (See the comment on enabling PIDTEMPBED)
 */
#define MAX_BED_POWER 255 // limits duty cycle to bed; 255=full current

#if ENABLED(PIDTEMPBED)
  #define MIN_BED_POWER 0
  //#define PID_BED_DEBUG // Sends debug data to the serial port.
  #define DEFAULT_bedKp 116.48
  #define DEFAULT_bedKi 17.33
  #define DEFAULT_bedKd 521.83
  /** Source                            Kp      Ki      Kd
   *  -------------------------------   ------  -----   ------
   *  calibrated "M303 C12 E-1 S80 U1"  116.48  17.33   521.83  // 20200917
   *  calibrated "M303 C10 E-1 S80 U1"  138.16  24.32   523.15   // 20200917
   *  Stock ender3 firmware (M503)      disabled
   *  Marlin ender3 v2 config example   462.10  85.47   624.59
   *  FIND YOUR OWN: "M303 E-1 C8 S90" to run autotune on the bed at 90 degreesC for 8 cycles.
   */
#endif // PIDTEMPBED

#if EITHER(PIDTEMP, PIDTEMPBED)
  //#define PID_DEBUG             // Sends debug data to the serial port. Use 'M303 D' to toggle activation.
  //#define PID_OPENLOOP          // Puts PID in open loop. M104/M140 sets the output power from 0 to PID_MAX
  //#define SLOW_PWM_HEATERS      // PWM with very low frequency (roughly 0.125Hz=8s) and minimum state time of approximately 1s useful for heaters driven by a relay
  #define PID_FUNCTIONAL_RANGE 10 // If the temperature difference between the target temperature and the actual temperature
                                  // is more than PID_FUNCTIONAL_RANGE then the PID will be shut off and the heater will be set to min/max.
#endif


// @section extruder
// IT IS HIGHLY RECOMMENDED TO LEAVE THIS OPTION ENABLED! ***
#define PREVENT_COLD_EXTRUSION
// Add M302 to set the minimum extrusion temperature and/or turn cold extrusion prevention on and off.
#define EXTRUDE_MINTEMP 170

#define PREVENT_LENGTHY_EXTRUDE
#define EXTRUDE_MAXLENGTH 200 /** NOTE: For Bowden Extruders make this large enough to allow load/unload. */

//===========================================================================
//======================== Thermal Runaway Protection =======================
//===========================================================================

#define THERMAL_PROTECTION_HOTENDS // Enable thermal protection for all extruders
#define THERMAL_PROTECTION_BED     // Enable thermal protection for the heated bed
#define THERMAL_PROTECTION_CHAMBER // Enable thermal protection for the heated chamber

//===========================================================================
//============================== Endstop Settings ===========================
//===========================================================================

// @section homing
#define USE_XMIN_PLUG
#define USE_YMIN_PLUG
//#define USE_ZMIN_PLUG   // physically disconnected this in favor of probing z for homing = One less offset (end stop to nozzle) to deal with.

#define ENDSTOPPULLUPS

// Mechanical endstop with COM to ground and NC to Signal uses "false" here (most common setup).
#define X_MIN_ENDSTOP_INVERTING false
#define Y_MIN_ENDSTOP_INVERTING false
#define Z_MIN_ENDSTOP_INVERTING false
#define X_MAX_ENDSTOP_INVERTING false
#define Y_MAX_ENDSTOP_INVERTING false
#define Z_MAX_ENDSTOP_INVERTING false
// myconfig: use false which is what "M43 S" reports and yields succesful test
#define Z_MIN_PROBE_ENDSTOP_INVERTING false // BLTouch config might be overriding this to false anyway.

#define X_DRIVER_TYPE  TMC2208
#define Y_DRIVER_TYPE  TMC2208
#define Z_DRIVER_TYPE  TMC2208
#define E0_DRIVER_TYPE TMC2208
//#define E1_DRIVER_TYPE TMC2208
//#define E2_DRIVER_TYPE TMC2208

//=============================================================================
//============================== Movement Settings ============================
//=============================================================================
// @section motion

// Default Axis Steps Per Unit (steps/mm). Override with M92
//                                      X, Y, Z, E0 [, E1[, E2...]]
// guide on calculating = https://www.youtube.com/watch?v=eBUYLZ2TODw
// myconfig: originally calibrated extruder at 102.7 steps/mm but maybe there was a jam or issue with stepper driver config ...
// myconfig: 20201008 had gone back to 93 esteps then used that to calibrate at 96.17
#define DEFAULT_AXIS_STEPS_PER_UNIT   { 80, 80, 400, 96.17 }  // ender3 _SHOULD_ be 80, 80, 400, 93, per examples and many people on github
#define DEFAULT_MAX_FEEDRATE          { 500, 500, 5, 25 } // Override with M203

//#define LIMITED_MAX_FR_EDITING        // Limit edit via M203 or LCD to DEFAULT_MAX_FEEDRATE * 2
#if ENABLED(LIMITED_MAX_FR_EDITING)
  #define MAX_FEEDRATE_EDIT_VALUES    { 600, 600, 10, 50 } // ...or, set your own edit limits
#endif

#define DEFAULT_MAX_ACCELERATION      { 500, 500, 100, 1000 } // Override with M201
//#define LIMITED_MAX_ACCEL_EDITING     // Limit edit via M201 or LCD to DEFAULT_MAX_ACCELERATION * 2
#if ENABLED(LIMITED_MAX_ACCEL_EDITING)
  #define MAX_ACCEL_EDIT_VALUES       { 6000, 6000, 200, 20000 } // ...or, set your own edit limits
#endif

/**
 * Default Acceleration (change/s) change = mm/s
 * Override with M204
 *   M204 P    Acceleration
 *   M204 R    Retract Acceleration
 *   M204 T    Travel Acceleration
 */
// can go as high as 1250 per https://github.com/talldonkey/Marlin-2.0-Ender-3-SKR-1.3/blob/2.0.x-Ender-3-SKR-1.3/Marlin/Configuration.h
// per stock ender3 github firmware = 500, stock ender3 M503 = 250
#define DEFAULT_ACCELERATION          500    // X, Y, Z and E acceleration for printing moves, default 3000
#define DEFAULT_RETRACT_ACCELERATION  500    // E acceleration for retracts, default = 3000
#define DEFAULT_TRAVEL_ACCELERATION   500    // X, Y, Z acceleration for travel (non printing) moves, default = 3000

// marlin Ender3 example config = disabled, ender3 v2 = enable
// #define CLASSIC_JERK
#if ENABLED(CLASSIC_JERK)
  // stock ender3 firmware (M503): 5.0, 5.0, 0.4 (x,y,z)
  #define DEFAULT_XJERK 10.0  // default = 10
  #define DEFAULT_YJERK 10.0  // default = 5
  #define DEFAULT_ZJERK  0.3  // default = 0.4
  //#define TRAVEL_EXTRA_XYJERK 0.0     // Additional jerk allowance for all travel moves
  //#define LIMITED_JERK_EDITING        // Limit edit via M205 or LCD to DEFAULT_aJERK * 2
  #if ENABLED(LIMITED_JERK_EDITING)
    #define MAX_JERK_EDIT_VALUES { 20, 20, 0.6, 10 } // ...or, set your own edit limits
  #endif
#endif

// stcok ender3 firmware (M503) = 5.0, default = 5.0
#define DEFAULT_EJERK    5.0  // May be used by Linear Advance

#if DISABLED(CLASSIC_JERK)
  // marlin ender3 btt e3 mini 2.0 config example = 0.08
  #define JUNCTION_DEVIATION_MM 0.013 // (mm) Distance from real junction edge, default = 0.08
  #define JD_HANDLE_SMALL_SEGMENTS    // Use curvature estimation instead of just the junction angle
                                      // for small segments (< 1mm) with large junction angles (> 135°).
#endif

//#define S_CURVE_ACCELERATION

//===========================================================================
//============================= Z Probe Options =============================
//===========================================================================
// @section probes
// See https://marlinfw.org/docs/configuration/probes.html

// myconfig: temporarily disable bltouch
#define BLTOUCH

// Force the use of the probe for Z-axis homing
#define USE_PROBE_FOR_Z_HOMING

/**
 * Nozzle-to-Probe offsets { X, Y, Z }
 *
 * - Use a caliper or ruler to measure the distance from the tip of
 *   the Nozzle to the center-point of the Probe in the X and Y axes.
 * - For the Z offset use your best known value and adjust at runtime.
 * - Probe Offsets can be tuned at runtime with 'M851', LCD menus, babystepping, etc.
 *
 * Assuming the typical work area orientation:
 *  - Probe to RIGHT of the Nozzle has a Positive X offset
 *  - Probe to LEFT  of the Nozzle has a Negative X offset
 *  - Probe in BACK  of the Nozzle has a Positive Y offset
 *  - Probe in FRONT of the Nozzle has a Negative Y offset
 *
 * Some examples:
 *   #define NOZZLE_TO_PROBE_OFFSET { 10, 10, -1 }   // Example "1"
 *   #define NOZZLE_TO_PROBE_OFFSET {-10,  5, -1 }   // Example "2"
 *   #define NOZZLE_TO_PROBE_OFFSET {  5, -5, -1 }   // Example "3"
 *   #define NOZZLE_TO_PROBE_OFFSET {-15,-10, -1 }   // Example "4"
 *
 *     +-- BACK ---+
 *     |    [+]    |
 *   L |        1  | R <-- Example "1" (right+,  back+)
 *   E |  2        | I <-- Example "2" ( left-,  back+)
 *   F |[-]  N  [+]| G <-- Nozzle
 *   T |       3   | H <-- Example "3" (right+, front-)
 *     | 4         | T <-- Example "4" ( left-, front-)
 *     |    [-]    |
 *     O-- FRONT --+
 */
// for this BLTouch bracket https://www.thingiverse.com/thing:3733792 :
#define MYCONFIG_PROBE_OFFSET_X -40 // calibrated ... did this calibrate at -42???
#define MYCONFIG_PROBE_OFFSET_Y -12 // calibrated
#define MYCONFIG_PROBE_OFFSET_Z -1.82 // new value from new PROBE_OFFSET_WIZARD
#define NOZZLE_TO_PROBE_OFFSET { MYCONFIG_PROBE_OFFSET_X, MYCONFIG_PROBE_OFFSET_Y, MYCONFIG_PROBE_OFFSET_Z }

#define PROBING_MARGIN 2  // myconfig: will be adjusted for each edge of the build surface in configuration_adv

// XY Speed 10000 (166.6*60) and 1/2 speed for slow per TeachingTech https://www.youtube.com/watch?v=BV11-VOQjMc
#define XY_PROBE_SPEED (166*60) // X and Y axis travel speed (mm/min) between probes, default: 133*60=7980
#define Z_PROBE_SPEED_FAST HOMING_FEEDRATE_Z  // Feedrate (mm/min) for the first approach when double-probing (MULTIPLE_PROBING == 2)
// stick with our known working super slow speed (1/2 of fast when fast is 4*60)
#define Z_PROBE_SPEED_SLOW (2*60) // Feedrate (mm/min) for the "accurate" probe of each point, default = 1/2 fast speed

/**
 * Multiple Probing
 *
 * You may get improved results by probing 2 or more times.
 * With EXTRA_PROBING the more atypical reading(s) will be disregarded.
 *
 * A total of 2 does fast/slow probes with a weighted average.
 * A total of 3 or more adds more slow probes, taking the average.
 */
// myconfig
//#define MULTIPLE_PROBING 2
//#define EXTRA_PROBING    1

/**
 * Z probes require clearance when deploying, stowing, and moving between
 * probe points to avoid hitting the bed and other hardware.
 * Servo-mounted probes require extra space for the arm to rotate.
 * Inductive probes need space to keep from triggering early.
 *
 * Use these settings to specify the distance (mm) to raise the probe (or
 * lower the bed). The values set here apply over and above any (negative)
 * probe Z Offset set with NOZZLE_TO_PROBE_OFFSET, M851, or the LCD.
 * Only integer values >= 1 are valid here.
 *
 * Example: `M851 Z-5` with a CLEARANCE of 4  =>  9mm from bed to nozzle.
 *     But: `M851 Z+1` with a CLEARANCE of 2  =>  2mm from bed to nozzle.
 */
// myconfig: DO NOT SET DEPLOY CLEARANCE <10 and BETWEEN/MULTI <5
// Deply=5 Between=4 per TeachingTech https://www.youtube.com/watch?v=BV11-VOQjMc
#define Z_CLEARANCE_DEPLOY_PROBE    6 // Z Clearance for Deploy/Stow, Antclabs recommends at least 10
#define Z_CLEARANCE_BETWEEN_PROBES  4 // Z Clearance between probe points, Antclabs recommends at least 5
#define Z_CLEARANCE_MULTI_PROBE     4 // Z Clearance between multiple probes
#define Z_AFTER_PROBING             8 // Z position after probing is done

// myconfig: use 1mm, default -2
#define Z_PROBE_LOW_POINT          -1 // Farthest distance below the trigger-point to go before stopping

// For M851 give a range for adjus2ting the Z probe offset
// per marlin config example for Ender3:  vs has -10 and 10
#define Z_PROBE_OFFSET_RANGE_MIN -2 // default -10
#define Z_PROBE_OFFSET_RANGE_MAX 1  // default 10

// Enable M48
#define Z_MIN_PROBE_REPEATABILITY_TEST

// Before deploy/stow pause for user confirmation
//#define PAUSE_BEFORE_DEPLOY_STOW
#if ENABLED(PAUSE_BEFORE_DEPLOY_STOW)
  //#define PAUSE_PROBE_DEPLOY_WHEN_TRIGGERED // For Manual Deploy Allenkey Probe
#endif

/**
 * Enable one or more of the following if probing seems unreliable.
 * Heaters and/or fans can be disabled during probing to minimize electrical
 * noise. A delay can also be added to allow noise and vibration to settle.
 * These options are most useful for the BLTouch probe, but may also improve
 * readings with inductive probes and piezo sensors.
 */
//#define PROBING_HEATERS_OFF       // Turn heaters off when probing
#if ENABLED(PROBING_HEATERS_OFF)
  //#define WAIT_FOR_BED_HEATER     // Wait for bed to heat back up between probes (to improve accuracy)
#endif
//#define PROBING_FANS_OFF          // Turn fans off when probing
//#define PROBING_STEPPERS_OFF      // Turn steppers off (unless needed to hold position) when probing
//#define DELAY_BEFORE_PROBING 200  // (ms) To prevent vibrations from triggering piezo sensors

// For Inverting Stepper Enable Pins (Active Low) use 0, Non Inverting (Active High) use 1
// :{ 0:'Low', 1:'High' }
#define X_ENABLE_ON 0
#define Y_ENABLE_ON 0
#define Z_ENABLE_ON 0
#define E_ENABLE_ON 0 // For all extruders

// Disable axis steppers immediately when they're not being stepped.
// WARNING: When motors turn off there is a chance of losing position accuracy!
#define DISABLE_X false
#define DISABLE_Y false
#define DISABLE_Z false
// Turn off the display blinking that warns about possible accuracy reduction
//#define DISABLE_REDUCED_ACCURACY_WARNING

// @section extruder
#define DISABLE_E false             // Disable the extruder when not stepping, For all extruders
#define DISABLE_INACTIVE_EXTRUDER   // Keep only the active extruder enabled

// @section machine
// Invert the stepper direction. Change (or reverse the motor connector) if an axis goes the wrong way.
#define INVERT_X_DIR true
#define INVERT_Y_DIR true
#define INVERT_Z_DIR false

// @section extruder
// For direct drive extruder v9 set to true, for geared extruder set to false.
#define INVERT_E0_DIR true
#define INVERT_E1_DIR false
#define INVERT_E2_DIR false
#define INVERT_E3_DIR false
#define INVERT_E4_DIR false
#define INVERT_E5_DIR false
#define INVERT_E6_DIR false
#define INVERT_E7_DIR false

// @section homing
//#define NO_MOTION_BEFORE_HOMING // Inhibit movement until all axes have been homed
//#define UNKNOWN_Z_NO_RAISE    // Don't raise Z (lower the bed) if Z is "unknown." For beds that fall when Z is powered off.
/** (mm) Minimal Z height before homing (G28) for Z clearance above the bed, clamps, ...
 *  NOTE: Be sure to have this much clearance over your Z_MAX_POS to prevent grinding. */
#define Z_HOMING_HEIGHT  6      // myconfig: confirmed this clears the clamps
#define Z_AFTER_HOMING  8       // (mm) Height to move to after homing Z

#define X_HOME_DIR -1 // 1=MAX, -1=MIN
#define Y_HOME_DIR -1
#define Z_HOME_DIR -1

// @section machine
// The size of the print bed
#define X_BED_SIZE 228  // approx 2mm from right edge of bed, with -2 x min pos
#define Y_BED_SIZE 208  // just inside clip buffer approx, with y min pos -21

// Travel limits (mm) after homing, corresponding to endstop positions.
// for discussion about endstops off the bed see https://github.com/MarlinFirmware/Marlin/issues/17158
// can be negative, per https://github.com/talldonkey/Marlin-2.0-Ender-3-SKR-1.3/blob/2.0.x-Ender-3-SKR-1.3/Marlin/Configuration.h
#define X_MIN_POS -2   // x limit is at the edge of the bed, with small 1mm buffer
#define Y_MIN_POS -21  // y limit is 8mm off bed (-8) and clip buffer approx 20mm (-20)
#define Z_MIN_POS 0
#define X_MAX_POS X_BED_SIZE
#define Y_MAX_POS Y_BED_SIZE
#define Z_MAX_POS 210 // bowden tube is already sloped downwards, and at 220mm cables are hitting upper cross bar ... use 210 with room for Z_HOMING_HEIGHT

// Software Endstops - Prevent moves outside the set machine bounds.
// Use 'M211' to set software endstops on/off or report current state
#define MIN_SOFTWARE_ENDSTOPS
#if ENABLED(MIN_SOFTWARE_ENDSTOPS)
  #define MIN_SOFTWARE_ENDSTOP_X
  #define MIN_SOFTWARE_ENDSTOP_Y
  #define MIN_SOFTWARE_ENDSTOP_Z
#endif
#define MAX_SOFTWARE_ENDSTOPS
#if ENABLED(MAX_SOFTWARE_ENDSTOPS)
  #define MAX_SOFTWARE_ENDSTOP_X
  #define MAX_SOFTWARE_ENDSTOP_Y
  #define MAX_SOFTWARE_ENDSTOP_Z
#endif
#if EITHER(MIN_SOFTWARE_ENDSTOPS, MAX_SOFTWARE_ENDSTOPS)
  //#define SOFT_ENDSTOPS_MENU_ITEM  // Enable/Disable software endstops from the LCD
#endif

//===========================================================================
//=============================== Bed Leveling ==============================
//===========================================================================
// @section calibrate

/**
 * Choose one of the options below to enable G29 Bed Leveling. The parameters
 * and behavior of G29 will change depending on your selection.
 *
 *  If using a Probe for Z Homing, enable Z_SAFE_HOMING also!
 * - AUTO_BED_LEVELING_BILINEAR
 *   Probe several points in a grid.
 *   You specify the rectangle and the density of sample points.
 *   The result is a mesh, best for large or uneven beds.
 *
 * - AUTO_BED_LEVELING_UBL (Unified Bed Leveling)
 *   A comprehensive bed leveling system combining the features and benefits
 *   of other systems. UBL also includes integrated Mesh Generation, Mesh
 *   Validation and Mesh Editing systems.
 */
// https://marlinfw.org/docs/configuration/configuration.html#bed-leveling
#define AUTO_BED_LEVELING_BILINEAR
//#define AUTO_BED_LEVELING_UBL

// "G28 disables bed leveling. Follow with M420 S to turn leveling on,
// or use RESTORE_LEVELING_AFTER_G28 to automatically keep leveling on after G28."
// https://marlinfw.org/docs/gcode/G028.html
#define RESTORE_LEVELING_AFTER_G28

/**
 * Enable detailed logging of G28, G29, M48, etc.
 * NOTE: Requires a lot of PROGMEM!
 * Use with i.e. 'M111 S38' -- 32 (levelling) + 4 (errors) + 2 (info) then back off with 'M111 S0'
 */
#define DEBUG_LEVELING_FEATURE

#if ANY(MESH_BED_LEVELING, AUTO_BED_LEVELING_BILINEAR, AUTO_BED_LEVELING_UBL)
  // Gradually reduce leveling correction until a set height is reached,
  // at which point movement will be level to the machine's XY plane.
  // The height can be set with M420 Z<height>
  #define ENABLE_LEVELING_FADE_HEIGHT

  // For Cartesian machines, instead of dividing moves on mesh boundaries, split up moves into short segments like a Delta.
  // This follows the contours of the bed more closely than edge-to-edge straight moves.
  #define SEGMENT_LEVELED_MOVES
  #define LEVELED_SEGMENT_LENGTH 5.0 // (mm) Length of all segments (except the last one)

  // Enable the G26 Mesh Validation Pattern tool. Photo of good print: https://github.com/MarlinFirmware/Marlin/issues/7021#issuecomment-315636600
  #define G26_MESH_VALIDATION
  #if ENABLED(G26_MESH_VALIDATION)
    // SPLA config:
    #define MESH_TEST_NOZZLE_SIZE    0.4  // (mm) Diameter of primary nozzle.
    #define MESH_TEST_LAYER_HEIGHT   0.2  // (mm) Default layer height for the G26 Mesh Validation Tool.
    #define MESH_TEST_HOTEND_TEMP    215  // (°C) Default nozzle temperature for the G26 Mesh Validation Tool.
    #define MESH_TEST_BED_TEMP       80   // (°C) Default bed temperature for the G26 Mesh Validation Tool.
    #define G26_XY_FEEDRATE          20   // (mm/s) Feedrate for XY Moves for the G26 Mesh Validation Tool.
    #define G26_RETRACT_MULTIPLIER   6.0  // G26 Q (retraction) used by default between mesh test elements.
  #endif

#endif

#if EITHER(AUTO_BED_LEVELING_LINEAR, AUTO_BED_LEVELING_BILINEAR)
  // Set the number of grid points per dimension.
  #define GRID_MAX_POINTS_X 7
  #define GRID_MAX_POINTS_Y GRID_MAX_POINTS_X // default = GRID_MAX_POINTS_X

  // Probe along the Y axis, advancing X after each column
  //#define PROBE_Y_FIRST

  #if ENABLED(AUTO_BED_LEVELING_BILINEAR)
    // Beyond the probed grid, continue the implied tilt?
    // Default is to maintain the height of the nearest edge.
    //#define EXTRAPOLATE_BEYOND_GRID

    // Experimental Subdivision of the grid by Catmull-Rom method,
    // Synthesizes intermediate points to produce a more detailed mesh.
    #define ABL_BILINEAR_SUBDIVISION
    #if ENABLED(ABL_BILINEAR_SUBDIVISION)
      #define BILINEAR_SUBDIVISIONS 3 // Number of subdivisions between probe points, default = 3
    #endif

  #endif

#elif ENABLED(AUTO_BED_LEVELING_UBL)
  //===========================================================================
  //========================= Unified Bed Leveling ============================
  //===========================================================================
  #define MESH_EDIT_GFX_OVERLAY   // Display a graphics overlay while editing the mesh

  // see this discussion about UBL mesh generation https://github.com/MarlinFirmware/Marlin/issues/15933
  // myconfig: set this to be clip size (10mm) + buffer (5mm) ... if larger than PROBING_MARGIN then G29 shouldn't require manual steps
  //#define MESH_INSET 26              // Set Mesh bounds as an inset region of the bed
  #define MESH_INSET 3             // Set Mesh bounds as an inset region of the bed
  // myconfig: start with 7, up to 10 once UBL is known good
  #define GRID_MAX_POINTS_X 5      // Don't use more than 15 points per axis, implementation limited.
  #define GRID_MAX_POINTS_Y GRID_MAX_POINTS_X

  #define UBL_MESH_EDIT_MOVES_Z     // Sophisticated users prefer no movement of nozzle
  #define UBL_SAVE_ACTIVE_ON_M500   // Save the currently active mesh in the current slot on M500

  //#define UBL_Z_RAISE_WHEN_OFF_MESH 2.5 // When the nozzle is off the mesh, this value is used
                                          // as the Z-Height correction value.
#endif // BED_LEVELING

/** Add a bed leveling sub-menu for ABL or MBL. Include a guided procedure if manual probing is enabled.
 *  NOTE: With this enabled all levelling functions are consolidated in "Motion"->"Bed Leveling" menu,
 *        otherwise functions will be clutter "Motion" menu.
 */
#define LCD_BED_LEVELING    // myconfig: necessary for PROBE_OFFSET_WIZARD in configuration_adv
#if ENABLED(LCD_BED_LEVELING)
  #define MESH_EDIT_Z_STEP  0.025 // (mm) Step size while manually probing Z axis.
  #define LCD_PROBE_Z_RANGE 4     // (mm) Z Range centered on Z_MIN_POS for LCD Z adjustment
  //#define MESH_EDIT_MENU        // Add a menu to edit mesh points
#endif

// Myconfig: define bed corners for use with manual leveling from menu and G35 assisted (probe) tramming
// (mm) Left, Front, Right, Back insets
#define MYCONFIG_CSCREW_L_INSET 28
#define MYCONFIG_CSCREW_F_INSET 19
#define MYCONFIG_CSCREW_R_INSET 30
#define MYCONFIG_CSCREW_B_INSET 19

// Add a menu item to move between bed corners for manual bed adjustment
// per https://blog.gruby.com/2020/01/05/installing-a-bltouch-on-an-ender-3-pro/
#define LEVEL_BED_CORNERS
#if ENABLED(LEVEL_BED_CORNERS)
  // (mm) Left, Front, Right, Back insets
  #define LEVEL_CORNERS_INSET_LFRB { \
    MYCONFIG_CSCREW_L_INSET, \
    MYCONFIG_CSCREW_F_INSET, \
    MYCONFIG_CSCREW_R_INSET, \
    MYCONFIG_CSCREW_B_INSET \
  }
  #define LEVEL_CORNERS_HEIGHT      0.0   // (mm) Z height of nozzle at leveling points, default 0.0
  #define LEVEL_CORNERS_Z_HOP       4.0   // (mm) Z height of nozzle between leveling points
  //#define LEVEL_CENTER_TOO              // Move to the center after the last corner
#endif

/**
 * Commands to execute at the end of G29 probing.
 * Useful to retract or move the Z probe out of the way.
 */
//#define Z_PROBE_END_SCRIPT "G1 Z10 F12000\nG1 X15 Y330\nG1 Z0.5\nG1 Z10"


// @section homing

// The center of the bed is at (X=0, Y=0)
//#define BED_CENTER_AT_0_0

// Manually set the home position. Leave these undefined for automatic settings. Values can be changed with M206
/** NOTE: compile error unless defined */
// Better to use X_MIN_POS and Y_MIN_POS per https://github.com/MarlinFirmware/Marlin/issues/17158
// stock ender3 firmware (M503) = -5.0, -15.0, 0 (x,y,z)
#define MANUAL_X_HOME_POS X_MIN_POS // default = 0
#define MANUAL_Y_HOME_POS Y_MIN_POS // default = 0
#define MANUAL_Z_HOME_POS 0

/* Use "Z Safe Homing" to avoid homing with a Z probe outside the bed area.
 *  - Allow Z homing only after X and Y homing AND stepper drivers still enabled.
 *  - If stepper drivers time out, it will need X and Y homing again before Z homing.
 *  - Move the Z probe (or nozzle) to a defined XY point before Z Homing.
 *  - Prevent Z homing when the Z probe is outside bed area.
 */
#define Z_SAFE_HOMING
#if ENABLED(Z_SAFE_HOMING)
  // home Z on X/Y min endstops:
  // #define Z_SAFE_HOMING_X_POINT X_MIN_POS
  // #define Z_SAFE_HOMING_Y_POINT Y_MIN_POS
  // home on bed center (marlin default):
  #define Z_SAFE_HOMING_X_POINT X_CENTER
  #define Z_SAFE_HOMING_Y_POINT Y_CENTER
#endif

// Homing speeds (mm/min)
#define HOMING_FEEDRATE_XY (50*60)  // mm/min 50*60=3000
// could go as high as 1000! per https://forum.duet3d.com/topic/13351/faster-z-homing-with-dual-endstop-switch-probe?_=1602015491157
// 12*60=720 per https://jgaurorawiki.com/a5/modifications/bltouch
// 20*60=1200 per TeachingTech https://www.youtube.com/watch?v=BV11-VOQjMc
#define HOMING_FEEDRATE_Z  (10*60)   // mm/min  confirmed slow probing = 4*60=240  ... not crucial as second probe speed is what matters

#define VALIDATE_HOMING_ENDSTOPS

// @section calibrate

/**
 * Bed Skew Compensation
 *
 * This feature corrects for misalignment in the XYZ axes.
 *
 * Take the following steps to get the bed skew in the XY plane:
 *  1. Print a test square (e.g., https://www.thingiverse.com/thing:2563185)
 *  2. For XY_DIAG_AC measure the diagonal A to C
 *  3. For XY_DIAG_BD measure the diagonal B to D
 *  4. For XY_SIDE_AD measure the edge A to D
 *
 * Marlin automatically computes skew factors from these measurements.
 * Skew factors may also be computed and set manually:
 *
 *  - Compute AB     : SQRT(2*AC*AC+2*BD*BD-4*AD*AD)/2
 *  - XY_SKEW_FACTOR : TAN(PI/2-ACOS((AC*AC-AB*AB-AD*AD)/(2*AB*AD)))
 *
 * If desired, follow the same procedure for XZ and YZ.
 * Use these diagrams for reference:
 *
 *    Y                     Z                     Z
 *    ^     B-------C       ^     B-------C       ^     B-------C
 *    |    /       /        |    /       /        |    /       /
 *    |   /       /         |   /       /         |   /       /
 *    |  A-------D          |  A-------D          |  A-------D
 *    +-------------->X     +-------------->X     +-------------->Y
 *     XY_SKEW_FACTOR        XZ_SKEW_FACTOR        YZ_SKEW_FACTOR
 */
//#define SKEW_CORRECTION
#if ENABLED(SKEW_CORRECTION)
  // Input all length measurements here:
  #define XY_DIAG_AC 282.8427124746
  #define XY_DIAG_BD 282.8427124746
  #define XY_SIDE_AD 200

  // Or, set the default skew factors directly here
  // to override the above measurements:
  #define XY_SKEW_FACTOR 0.0

  //#define SKEW_CORRECTION_FOR_Z
  #if ENABLED(SKEW_CORRECTION_FOR_Z)
    #define XZ_DIAG_AC 282.8427124746
    #define XZ_DIAG_BD 282.8427124746
    #define YZ_DIAG_AC 282.8427124746
    #define YZ_DIAG_BD 282.8427124746
    #define YZ_SIDE_AD 200
    #define XZ_SKEW_FACTOR 0.0
    #define YZ_SKEW_FACTOR 0.0
  #endif

  // Enable this option for M852 to set skew at runtime
  //#define SKEW_CORRECTION_GCODE
#endif

//=============================================================================
//============================= Additional Features ===========================
//=============================================================================

// @section extras

/** EEPROM
 *   M500 - Store settings to EEPROM.
 *   M501 - Read settings from EEPROM. (i.e., Throw away unsaved changes)
 *   M502 - Revert settings to "factory" defaults. (Follow with M500 to init the EEPROM.)
 */
#define EEPROM_SETTINGS       // Persistent storage with M500 and M501
#define EEPROM_CHITCHAT       // Give feedback on EEPROM commands. Disable to save PROGMEM.
#define EEPROM_BOOT_SILENT    // Keep M503 quiet and only give errors during first load
#if ENABLED(EEPROM_SETTINGS)
  //#define EEPROM_AUTO_INIT  // Init EEPROM automatically on any errors.
#endif

// Host Keepalive
// When enabled Marlin will send a busy status message to the host
// every couple of seconds when it can't accept commands.
#define HOST_KEEPALIVE_FEATURE        // Disable this if your host doesn't like keepalive messages
#define DEFAULT_KEEPALIVE_INTERVAL 2  // Number of seconds between "busy" messages. Set with M113.
#define BUSY_WHILE_HEATING            // Some hosts require "busy" messages even during heating


// @section temperature
// Preheat Constants
#define PREHEAT_1_LABEL        "PLA"
#define PREHEAT_1_TEMP_HOTEND  180
#define PREHEAT_1_TEMP_BED      60
#define PREHEAT_1_FAN_SPEED    128 // Value from 0 to 255

#define PREHEAT_2_LABEL        "SPLA"
#define PREHEAT_2_TEMP_HOTEND  200
#define PREHEAT_2_TEMP_BED      80
#define PREHEAT_2_FAN_SPEED    128 // Value from 0 to 255

/** Nozzle Park - Park the nozzle at the given XYZ position on idle or G27.
 * The "P" parameter controls the action applied to the Z axis:
 *    P0  (Default) If Z is below park Z raise the nozzle.
 *    P1  Raise the nozzle always to Z-park height.
 *    P2  Raise the nozzle by Z-park amount, limited to Z_MAX_POS.
 */
#define NOZZLE_PARK_FEATURE
#if ENABLED(NOZZLE_PARK_FEATURE)
  // Specify a park position as { X, Y, Z_raise }
  // default here is "back left" per https://github.com/talldonkey/Marlin-2.0-Ender-3-SKR-1.3/blob/2.0.x-Ender-3-SKR-1.3/Marlin/Configuration.h
  #define NOZZLE_PARK_POINT { (X_MIN_POS + 10), (Y_MAX_POS - 10), 20 }
  //#define NOZZLE_PARK_X_ONLY          // X move only is required to park
  //#define NOZZLE_PARK_Y_ONLY          // Y move only is required to park
  #define NOZZLE_PARK_Z_RAISE_MIN   2   // (mm) Always raise Z by at least this distance
  #define NOZZLE_PARK_XY_FEEDRATE 100   // (mm/s) X and Y axes feedrate (also used for delta Z axis)
  #define NOZZLE_PARK_Z_FEEDRATE    5   // (mm/s) Z axis feedrate (not used for delta printers)
#endif


/** Print Job Timer - Automatically start and stop the print job timer on M104/M109/M190.
 *   M104 (hotend, no wait) - high temp = none,        low temp = stop timer
 *   M109 (hotend, wait)    - high temp = start timer, low temp = stop timer
 *   M190 (bed, wait)       - high temp = start timer, low temp = none
 * The timer can also be controlled with the following commands:
 *   M75 - Start the print job timer
 *   M76 - Pause the print job timer
 *   M77 - Stop the print job timer
 */
#define PRINTJOB_TIMER_AUTOSTART

/** Print Counter - Track statistical data such as:
 *  - Total print jobs
 *  - Total successful print jobs
 *  - Total failed print jobs
 *  - Total time printing
 * View the current statistics with M78.
 */
#define PRINTCOUNTER


//=============================================================================
//============================= LCD and SD support ============================
//=============================================================================

// @section lcd

#define LCD_LANGUAGE en
#define DISPLAY_CHARSET_HD44780 WESTERN // default = JAPANESE
#define LCD_INFO_SCREEN_STYLE 0

#define SDSUPPORT

/** Encoder Direction Options - Test your encoder's behavior first with both options disabled.
 *  Reversed Value Edit and Menu Nav? Enable REVERSE_ENCODER_DIRECTION.
 *  Reversed Menu Navigation only?    Enable REVERSE_MENU_DIRECTION.
 *  Reversed Value Editing only?      Enable BOTH options.
 */
// This option reverses the encoder direction everywhere.
//  Set this option if CLOCKWISE causes values to DECREASE
//#define REVERSE_ENCODER_DIRECTION

// This option reverses the encoder direction for navigating LCD menus.
//  If CLOCKWISE normally moves DOWN this makes it go UP.
//  If CLOCKWISE normally moves UP this makes it go DOWN.
//#define REVERSE_MENU_DIRECTION

// This option reverses the encoder direction for Select Screen.
//  If CLOCKWISE normally moves LEFT this makes it go RIGHT.
//  If CLOCKWISE normally moves RIGHT this makes it go LEFT.
//#define REVERSE_SELECT_DIRECTION

#define INDIVIDUAL_AXIS_HOMING_MENU

//=============================================================================
//=======================   LCD / Controller Selection  =======================
//=========================      (Graphical LCDs)      ========================
//=============================================================================

// Factory display for Creality CR-10
// https://www.aliexpress.com/item/32833148327.html
// This is RAMPS-compatible using a single 10-pin connector.
// (For CR-10 owners who want to replace the Melzi Creality board but retain the display)
#define CR10_STOCKDISPLAY

//=============================================================================
//=============================== Extra Features ==============================
//=============================================================================

// @section extras

// Set number of user-controlled fans. Disable to use all board-defined fans.
// :[1,2,3,4,5,6,7,8]
#define NUM_M106_FANS 1   // Part cooling fan (FAN2)

// Increase the FAN PWM frequency. Removes the PWM noise but increases heating in the FET/Arduino
//#define FAST_PWM_FAN

// Use software PWM to drive the fan, as for the heaters. This uses a very low frequency
// which is not as annoying as with the hardware PWM. On the other hand, if this frequency
// is too low, you should also increment SOFT_PWM_SCALE.
//#define FAN_SOFT_PWM

// Incrementing this by 1 will double the software PWM frequency,
// affecting heaters, and the fan if FAN_SOFT_PWM is enabled.
// However, control resolution will be halved for each increment;
// at zero value, there are 128 effective control positions.
// :[0,1,2,3,4,5,6,7]
#define SOFT_PWM_SCALE 0

// If SOFT_PWM_SCALE is set to a value higher than 0, dithering can
// be used to mitigate the associated resolution loss. If enabled,
// some of the PWM cycles are stretched so on average the desired
// duty cycle is attained.
//#define SOFT_PWM_DITHER

// Temperature status LEDs that display the hotend and bed temperature.
// If all hotends, bed temperature, and target temperature are under 54C
// then the BLUE led is on. Otherwise the RED led is on. (1C hysteresis)
//#define TEMP_STAT_LEDS

// Support for BlinkM/CyzRgb
//#define BLINKM

// Support for PCA9632 PWM LED driver
//#define PCA9632

// Support for PCA9533 PWM LED driver
//#define PCA9533

/** RGB LED / LED Strip Control - Adds the M150 command to set the LED (or LED strip) color.
 *  If pins are PWM capable (e.g., 4, 5, 6, 11) then a range of luminance values can be set from 0 to 255.
 *  For NeoPixel LED an overall brightness parameter is also available.
 */
#define NEOPIXEL_LED
#if ENABLED(NEOPIXEL_LED)
  #define NEOPIXEL_TYPE   NEO_GRB     // NEO_GRBW / NEO_GRB - four/three channel driver type (defined in Adafruit_NeoPixel.h)
  #define NEOPIXEL_PIN    MYCONFIG_NEOPIXEL_PIN // LED driving pin
  //#define NEOPIXEL2_TYPE  NEOPIXEL_TYPE
  //#define NEOPIXEL2_PIN    5
  #define NEOPIXEL_PIXELS               8  // Number of LEDs in the strip. (Longest strip when NEOPIXEL2_SEPARATE is disabled.)

  #define NEOPIXEL_IS_SEQUENTIAL           // Sequential display for temperature change - LED by LED. Disable to change all LEDs at once.
  #define NEOPIXEL_BRIGHTNESS          20  // Initial brightness (0-255)
  #define NEOPIXEL_STARTUP_TEST            // Cycle through colors at startup

  // Support for second Adafruit NeoPixel LED driver controlled with M150 S1 ...
  //#define NEOPIXEL2_SEPARATE
  #if ENABLED(NEOPIXEL2_SEPARATE)
    #define NEOPIXEL2_PIXELS           15  // Number of LEDs in the second strip
    #define NEOPIXEL2_BRIGHTNESS      127  // Initial brightness (0-255)
    #define NEOPIXEL2_STARTUP_TEST         // Cycle through colors at startup
  #else
    //#define NEOPIXEL2_INSERIES             // Default behavior is NeoPixel 2 in parallel
  #endif

  // Use a single NeoPixel LED for static (background) lighting
  //#define NEOPIXEL_BKGD_LED_INDEX  0               // Index of the LED to use
  //#define NEOPIXEL_BKGD_COLOR { 255, 255, 255, 0 } // R, G, B, W
#endif

/**
 * Printer Event LEDs
 *
 * During printing, the LEDs will reflect the printer status:
 *
 *  - Gradually change from blue to violet as the heated bed gets to target temp
 *  - Gradually change from violet to red as the hotend gets to temperature
 *  - Change to white to illuminate work surface
 *  - Change to green once print has finished
 *  - Turn off after the print has finished and the user has pushed a button
 */
#if ANY(BLINKM, RGB_LED, RGBW_LED, PCA9632, PCA9533, NEOPIXEL_LED)
  #define PRINTER_EVENT_LEDS
#endif
