/* File:  /secure/daemon/checkin.c
 * Checkin Daemon - Checks players in and created needed objs
 * and checks passwords in the accounts.o file.
 * Zed - Lilypad
 * 2018-02-15
*/

#include <globals.h> //globals.h also inherits dirs.h and daemoms.h

mapping accts = ([]);

//verify accts.o file exists, and if not create it
void create() {
    if(file_exists(ACCT_DATA)) {
        restore_object(ACCT_DATA);
    }
    save_object(ACCT_DATA);
}

int acct_count() {
    return sizeof(keys(accts));
}

int acct_exists(string acct) {
    if(member_array(acct, keys(accts)) != -1) {
        return 1;
    }
    return 0;
}

int valid_acct_name(string name) {
    if(!name)
        return 0;
    if(strlen(name) < 3)
        return 0;
    if(strlen(name) > 16)
        return 0;
    if(regexp(name, AL_NUM))
        return 0;
    return 1;
}

string normalize_acct_name(string name) {
    return capitalize(lower_case(name));
}

int valid_password(string password) {
    if(!password)
        return 0;

    if(strlen(password) < 6)
        return 0;

    return 1;
}

int password_match(string name, string password) {
    if(acct_exists(name)) {
        if(crypt(password, name) == accts[name]["password"]) {
            return 1;
        }
    }
    return 0;
}

int valid_email(string email) {
    if(!email)
        return 0;

    if(strlen(email) < 8)
        return 0;

    if(regexp(email, EMAIL_FMAT))
        return 1;

    return 0;
}

void create_acct(string name, string password, string email) {
    int firstPlayer = 0;
    string title;
    string *srch_paths;

    if(acct_count() < 1) {
        firstPlayer = 1;
        title = "Admin";
        srch_paths = ({ ADM_COM, CRE_COM, PLR_COM });
    }

    else {
        title = "Player";
        srch_paths = ({ PLR_COM });
    }

    if(!acct_exists(name)) {
        accts[name] = ([]);
    }
    accts[name]["password"] = crypt(password, name);
    accts[name]["email"] = email;
    accts[name]["position"] = firstPlayer;
    accts[name]["title"] = title;
    accts[name]["cmd_path"] = srch_paths;
    accts[name]["date created"] = time();
    accts[name]["last login"] = accts[name]["date created"];
    accts[name]["last logout"] = 0;
    accts[name]["time played"] = 0;
    save_object(ACCT_DATA);

    if(firstPlayer)
        write("\n\nWhoa, all right! " +name+ " is the first to login, so has been made an admin!\n");
    if(!firstPlayer)
        write("\n\nWelcome to "+MUD_NAME+", "+name+"!\n");
}

void set_login(string name) {
    if(!acct_exists(name))
        return;

    accts[name]["last login"] = time();
    save_object(ACCT_DATA);
}

void set_logout(string name) {
    if(!acct_exists(name))
        return;

    accts[name]["last logout"] = time();
    accts[name]["total played"] += ( accts[name]["last logout"] - accts[name]["last login"] );
    save_object(ACCT_DATA);
}

void set_wizard(string name, int enabled) {
    if(!acct_exists(name))
        return;

    accts[name]["position"] = enabled;
    save_object(ACCT_DATA);
}

void set_password(string name, string password) {
    if(!acct_exists(name))
        return;

    accts[name]["password"] = crypt(password, name);
    save_object(ACCT_DATA);
}

void set_email(string name, string email) {
    if(!acct_exists(name))
        return;

    accts[name]["email"] = email;
    save_object(ACCT_DATA);
}

void set_offline(string name) {
    if(!acct_exists(name))
        return;

    accts[name]["online"] = 0;
    accts[name]["last logout"] = time();
    accts[name]["total played"] += ( accts[name]["last logout"] - accts[name]["last login"] );
    save_object(ACCT_DATA);
}

void set_online(string name) {
    if(!acct_exists(name))
        return;

    accts[name]["online"] = 1;
    accts[name]["last login"] = time();
    save_object(ACCT_DATA);
}

//daemon testing function
string test() {
    string str = "daemon return test";
    return str;
}