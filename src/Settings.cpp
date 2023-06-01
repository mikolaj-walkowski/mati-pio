#include "Settings.h"
#include "http_parser.h"
#include <cstdlib>
#include <exception>
#include <stdint.h>

#define CHECK_COMMAND                                                          \
  if (str[0] != c.sign)                                                        \
    return BAD_COMMAND;

char Command::lastCommand = 'A';

Command::Command(String s) : name(s) { sign = lastCommand++; }

String Command::serialize() { return String(sign) + ":" + name; }

Setting::Setting(String s, uint8_t f, Setting_type t)
    : flags(f), type(t), c(s) {}

String Setting::serialize() { return c.serialize() + ":" + setting_name[type]; }

Toggle::Toggle(String s, bool v, uint8_t flag)
    : Setting(s, flag, TOGGLE), value(v) {}

Result Toggle::onCommand(char *str) {
  CHECK_COMMAND;
  if (str[1] == '1' || str[0] == '0') {
    value = (str[1] == '1');
    return SUCCESS;
  }
  return FAILURE;
}

String Toggle::serialize() {
  return Setting::serialize() + ":" + String(value);
}

Slider::Slider(String s, double v, uint8_t flag)
    : Setting(s, flag, SLIDER), value(v) {}

Result Slider::onCommand(char *str) {
  CHECK_COMMAND;
  double e;

  e = std::strtod(str, NULL);
  if ((e > upper) || (e == upper && !(UPPER_INC & flags)) || (e < lower) ||
      (e == lower && !(LOWER_INC & flags)) || (e == 0.0 && strcmp(str, "0.0")))
    return FAILURE;
  value = e;
  return SUCCESS;
}
String Slider::serialize() {
  return Setting::serialize() + ":" + String(value) + ":" + String(lower) +
         ":" + String(upper);
}

TextField::TextField(String s, String v, uint8_t flag)
    : Setting(s, flag, TEXT_FIELD), value(v) {}

Result TextField::onCommand(char *str) {
  CHECK_COMMAND;
  char *s = str;
  while (*s != '\0') {
    if (*s > 127) {
      return FAILURE;
    }
    ++s;
  }
  value = String(str);
  return SUCCESS;
}

String TextField::serialize() { return Setting::serialize() + ":" + value; }
