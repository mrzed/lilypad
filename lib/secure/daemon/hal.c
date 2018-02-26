/* File:  /secure/daemon/hal.c
 * HAL Daemon - HAL is the daemon than verifies permissions for
 * command execution, file access levels, and promotions\demotions
 * Zed - Lilypad
 * 2018-02-22
*/
#include <globals.h> //globals.h also inherits dirs.h and daemoms.h

inherit "/inherit/error_out";
mapping accts = ([]);

void create() {
    if(file_exists(ACCT_DATA)) {
        restore_object(ACCT_DATA);
    }
    save_object(ACCT_DATA);
}

void promote_user(string sender, string user, string ntitle, int i) {
    string temp = capitalize(user);
    string *paths;
    //if(file_exists(ACCT_DATA)) {
        //restore_object(ACCT_DATA);
    //}
    if(sizeof(accts) > 0) {
        //write("Good data. accts mapping is not empty, continuing...\n"); //debuggin - Zed
        switch(i) {
            case 1: paths = ({ ADM_COM, CRE_COM, PLR_COM });break;
            case 2: paths = ({ CRE_COM, PLR_COM });break;
            default: paths = ({ PLR_COM });break;
        }
        accts[temp]["position"] = i;
        accts[temp]["title"] = capitalize(ntitle);
        accts[temp]["cmd_path"] = paths;
        save_object(ACCT_DATA);
        tell_object(find_living(user), "You have been promoted to "+capitalize(ntitle)+" by "+capitalize(sender)+".\n");
        write("You successfully promoted "+capitalize(user)+" to "+capitalize(ntitle)+".\n");
    }
        else {
        write("ERROR! Empty mapping!\nYou should probably let someone know about this...\n");
        return;
        }
}

int get_position(string user) {
    int pos = 0;
    string key = capitalize(user);

    //if(file_exists(ACCT_DATA)) {
        //restore_object(ACCT_DATA);
    //}
    if(sizeof(accts) > 0) {
        pos = accts[key]["position"];
        return pos;
    }
    else {
    write("ERROR! Mapping is empty.\n");
    return 0;
    }
}

void demote_user() {
//add demotion code here
}

string *get_cmd_path(string user) {
    string *paths;
    string key = capitalize(user);
    paths = ({});

    if(file_exists(ACCT_DATA)) {
        restore_object(ACCT_DATA);
    }
    if(sizeof(accts) > 0) {
        paths = accts[key]["cmd_path"];
        return paths;
    }
    else {
        write("No paths, sir....\n");
        return 0;
    }
}

//daemon testing function
string test() {
    string str = "HAL says: Here is your output, Dave...\n";
    return str;
}