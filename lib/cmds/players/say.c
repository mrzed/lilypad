// file: say.c
// added echo back to player
// zed @ Lilypad Mudlib
// 2013-05-10
// added string requirement - no null says, see?
// zed @ Lilypad Mudlib
// 2013-05-27
//capitalize say name - Zed @ Lilypad Mudlib : 28062013
#include <command.h>

#ifdef __NO_ENVIRONMENT__
#define say(x) shout(x)
#endif

int main(string arg) {
    string msg = arg;

    if(!arg) {
        write("USAGE: say <what you want to say>\n");
        return 1;
    }
    else {
        say((string)capitalize(previous_object()->query_name())+ " says: " + msg + "\n");
    printf("You say: " +arg+ "\n");
    return 1;
    }
}
