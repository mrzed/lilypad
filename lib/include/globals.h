// file: globals.h

#ifdef __SENSIBLE_MODIFIERS__
#define staticf protected
#define staticv nosave
#else
#define staticf static
#define staticv static
#endif

#include "tests.h"
#include "daemons.h"

#define MUDLIB_VER	"0.1-pre_a"

//#define LIB_DAEMON "/lib/include/daemons"

#define LOGIN_OB	    "/clone/login"
#define USER_OB		    "/clone/user"
#define ROOM_OB		    "/clone/room"
#define VOID_OB		    "/single/void"
#define COLOR_OB	    "/secure/obj/colors"
#define ACCT_DATA    CONFIG_DIR    "/accounts.o"
#define HAL_DATA     CONFIG_DIR    "/hal.o"
#define MOTD    CONFIG_DIR  "/motd"
#define BANNER    CONFIG_DIR  "/banner"

#define ROOT_UID	"Root"
#define BACKBONE_UID	"Backbone"
#define INPUT_TO_NORMAL    0
#define INPUT_TO_NOECHO    1
#define INPUT_TO_NOBYPASS  2

#define BASE            "/inherit/base"

#define COMMAND_PREFIX	"/command/"
#define ADM_COM  "/cmds/admin/"
#define CRE_COM  "/cmds/creator/"
#define PLR_COM  "/cmds/players/"

//Some re-usable strings for string verification

#define AL_NUM	"[^a-zA-Z0-9]"
#define EMAIL_FMAT	"^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9._%+-]+\\.[a-zA-Z]+$"
// classes for message() efun.
#define M_STATUS	"status"
#define M_SAY		"say"

#define CLEAN_UP	"/inherit/clean_up"
