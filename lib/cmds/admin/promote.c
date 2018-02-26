/* File:  /cmds/admin/promote.c
 * promote command - promote player to creator or admin
 * USAGE: promote <player> <position>
 *    Current positions accounted for are:
 *        Admin (int of 1)
 *        Creator (int of 2)
 *        Player (int of 0)
 * Example:  promote zedtest creator
 * Zed - Lilypad
 * 2013-05-27
*/
#include <command.h>
#include <globals.h>

inherit "/inherit/error_out";

int test_code(object uzer) {
    string posi;
    string temp = uzer->query_name();
    write("test_code temp: "+temp+"\n");
    posi = HAL_D->get_position(uzer);
    write("posi from hal: "+posi+"\n");
}

int main(string who) {
    object player, user, prom;
    string pstr, target, sender, position;
    string *cmd;
    string def = " is not a valid option.\nYour options are:\n   Creator\n   Admin\n";
    prom = this_player();
    sender = prom->query_name();

    if(!who || !sscanf(who, "%s %s", target, position)) {
        write("USAGE: promote <player name> <position>\n"+
              "Type: 'help promote' for more details\n");
        return 1;
    }
    else {
        foreach (user in users()) {
            if (user->query_name() == target) {
            player = user;
            pstr = lower_case(player->query_name());
            cmd = explode(who, " ");
            target = cmd[0];
            position = cmd[1];
            }
        }

    }
    if (!player) {
        return error_out(sprintf("%s is not logged in.", target));
    }
    if (player == this_player()) {
        write("You cannot promote yourself, "+capitalize(this_player()->query_name())+".\n");
    }
    else {
        //write("===================================================\n");
        //write("Call promo code - this is only a debugging message.\n");
        //write("===================================================\n");
        write("=+=  Attempting Promotion of: "+target+" =+=\n");
        switch(cmd[1]) {
            case "creator": HAL_D->promote_user(sender, target, position, 2);break;
            case "admin": HAL_D->promote_user(sender, target, position, 1);break;
            default : write(cmd[1]+def);break;
        }
    }
    return 1;
}

string help() {
    string txt = "\n\nPromote\n";
    txt += "---------------------------------------------------------\n";
    txt += "Used to promote a player from player status to creator or \n";
    txt += "admin. A creator CANNOT promote a player above their own \n";
    txt += "position. Only an admin can promote to admin, and only a \n";
    txt += "creator can promote to creator.\n";
    txt += "---------------------------------------------------------\n";
    txt += "USAGE: promote <player name> <position>\n";
    return txt;
}