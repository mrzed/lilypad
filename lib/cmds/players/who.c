/* File:  /commands/who.c
 * who command - show who's online
 * USAGE: who
 * Zed - Lilypad
 * 2013-05-26
*/

// this needs a lot of work, but it is getting better
// added position to who command - Zed @ Lilypad Mudlib

#include <command.h>
#include <daemons.h>
mapping accts = ([]);

int main(string arg) {
    object *list;
    int i;
    string title, key;

    if(file_exists(ACCT_DATA)) {
        restore_object(ACCT_DATA);
    }
    //save_object(ACCT_DATA);

    printf("%-25s idle\n", "Name  (*edit, +input)");
    printf("--------------------      -------\n");
    for (list = users(), i=0; i<sizeof(list); i++) {
        key = capitalize((string)list[i]->query_name());
        title = accts[key]["title"];
        printf("%-25s %4d\n", capitalize((string)list[i]->query_name()+" <"+title+">") +
        (in_edit(this_player()) ? "*" : "") +
        (in_input(this_player()) ? "+" : ""),
        query_idle(this_player()) / 60
        );
    }
    return 1;
}