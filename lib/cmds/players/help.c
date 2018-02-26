/* Original code from http://startfromlil.wordpress.com
 * adapted and modified by Zed @ Lilypad Mudlib
 * Modified so it queries user search paths from the accounts.o file via HAL
 * 06212013
 * file: /cmds/players/help.c
*/
#include <command.h>
#include <globals.h>

string* add_action_commands () {
    return map(commands(), (: $1[0] :)  ) - ({ "" });
}
string* commands_in_filesystem () {
    return map(get_dir(COMMAND_PREFIX + "*.c" ), (: $1[0..sizeof($1)-3] :));
}

int main(string arg) {
    object cobj;
    string help;
    string* cmds;

    if(arg) {
        if (member_array(arg, commands_in_filesystem()) > -1) {
            cobj=load_object(COMMAND_PREFIX +arg+ ".c");
            help=cobj->help();
            if(!help)
                help="No help available on that command.";
            if(help[sizeof(help)-1..] != "\n")
                help += "\n";
            write(help);
        }
        else if(member_array(arg, add_action_commands()) > -1) {
            write("No help available on that command.\n");
        }
        else {
            write("There is no such command to get help on.\n");
        }
        return 1;
    }
    else {
        printf("\n%s Help\n\n", MUD_NAME);
        write("You have access to the following commands:\n");
        cmds=add_action_commands() + commands_in_filesystem();
        write(implode(sort_array(cmds, 1), ", ") + "\n");
        write("You can ask for help on any of the commands by "
             +"typing:\n"
             +"\"help <command>\".\n"
             +"If no help is available, you will be notified.\n");
        return 1;
    }
}

string help() {
    return @help
Lists the commands available to you, if you just type "help."
Gives help on individual commands, if you type "help <command>."
help;
}