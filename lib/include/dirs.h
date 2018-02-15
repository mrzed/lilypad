// dirs include file
// include for organizing dir paths
// zed@lilypad

#ifndef dirs_h
#define dirs_h

#define CONFIG_DIR    "/etc"
#define LOG_DIR       "/log"
#define SECURE_DIR    "/secure"
#define SINGLE_DIR    "/single" //Remove all instances after removing refs to SINGLE_DIR and daemons are moved to /daemon or /secure/daemon
#define DAEMON_DIR    "/daemon"
#define SDAEMON_DIR    SECURE_DIR    "/daemon"
#define USER_DIR      "/users"

#endif /* dirs_h */
