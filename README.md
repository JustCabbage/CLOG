# CLOG [![MIT license](https://img.shields.io/badge/License-MIT-blue.svg)](https://lbesson.mit-license.org/)

# What is CLOG?
CLOG is a relatively basic logging implementation for debugging in applications.

# Features
- RGB Based Theme
- Customizable Logging options
- Timestamp Logging
- Date Logging
- Thread Safe

# Options
- Default - Everything Enabled
- NoTimestamps - Disable Timestamp Prefix
- NoColor - No Displayed Color | Ignores any color provided
- NoDate - Disable Date Prefix

# Examples

## Note
Initialization of CLOG is Required. Without doing so, the library may not function as intended.

## Standard Logging
```c++
CLOG::Logger::Initialize(CLOG::Colors::Color(255,255,255));
CLOG::Logger::Info("Information");
```

## Warning
```c++
CLOG::Logger::Initialize(CLOG::Colors::Color(255,255,255));
CLOG::Logger::Info("Warning");
```

## Error
```c++
CLOG::Logger::Initialize(CLOG::Colors::Color(255,255,255));
CLOG::Logger::Error("Error");
```

## Single Option Initialization
```c++
CLOG::Logger::Initialize(CLOG::Colors::Color(255,255,255), CLOG::Settings::LoggerOptions_NoDate);
```

## Multiple Options Initialization
```c++
CLOG::Logger::Initialize(CLOG::Colors::Color(255,255,255), CLOG::Settings::LoggerOptions_NoDate | CLOG::Settings::LoggerOptions_NoTimestamps);
```

## Update Colors
```c++
CLOG::Logger::Initialize(CLOG::Colors::Color(255,255,255));

CLOG::Logger::Info("Information");

CLOG::Logger::UpdateColor(CLOG::Logger::LogType_INFO,CLOG::Colors::Color(255,0,0));

CLOG::Logger::Info("Red");
```

# To Do

- Add Log Levels
- Add More Log Types
- Add Ability To Update Logger Options
