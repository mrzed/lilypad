/* file: /cmds/players/help.c
 * Zed @ Lilypad Mudlib
 * 06212013
*/
#include <command.h>
#include <globals.h>

string* add_action_commands () {
    return map(commands(), (: $1[0] :)  ) - ({ "" });
}
string* get_cmds() {
    string key = capitalize(this_player()->query_name());
    string *cmds = ({}), *paths = HAL_D->get_cmd_path(key);
    int i;
    string verb = lower_case(query_verb());

    for(i = 0; i < sizeof(paths); i ++) {
        if(file_exists(paths[i] + verb + ".c"))
            cmds += ({ paths[i] + verb});
        }
    return cmds;//, (: $1[0..sizeof($1)-3] :);
    //return map(get_dir(COMMAND_PREFIX + "*.c" ), (: $1[0..sizeof($1)-3] :));
}

int main(string arg) {
    object cobj;
    string help;
    string* cmds;

    if(arg) {
        if(member_array(arg, get_cmds()) > -1) {
            cobj=load_object(arg + ".c");
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
        cmds=add_action_commands() + get_cmds();
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