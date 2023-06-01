#pragma once

#include <Arduino.h>
#include <stdint.h>

enum Setting_flags {
  UPPER_INC = 1 << 0,
  LOWER_INC = 1 << 1,
  STEPPED = 1 << 2,
  TOGGLE_ON = 1 << 3,
};
const uint8_t no_flags = 0;

class Command {
  static char lastCommand;

public:
  String name;
  char sign;
  Command(String s);
  String serialize();
};

enum Setting_type { SLIDER, TOGGLE, TEXT_FIELD, ACTION };
const String setting_name[] = {"slider", "toggle", "text_field", "action"};
enum Result { BAD_COMMAND, SUCCESS, FAILURE };

class Setting {
public:
  Command c;
  Setting_type type;
  uint8_t flags;
  Setting(String, uint8_t, Setting_type);
  virtual String serialize();
  virtual Result onCommand(char *) = 0;
};

class Toggle : public Setting {

public:
  bool value;
  Toggle(String n, bool v = false, uint8_t flags = no_flags);
  String serialize();
  Result onCommand(char *);
};

class Slider : public Setting {
  double upper;
  double lower;

public:
  double value;
  Slider(String n, double v = 0.0f, uint8_t flags = no_flags);
  String serialize();
  Result onCommand(char *);
};

class TextField : public Setting {
public:
  String value;
  TextField(String n, String s = "", uint8_t flags = no_flags);
  String serialize();
  Result onCommand(char *);
};
