#include "server.h"

// static void if_changing_profile(t_info *info, t_peer *peer, int type, cJSON *get) {
//     if (type == make_change_password)
//         mx_db_get_self_response(info, peer, get, &mx_change_password);
//     else if (type == make_update_profile)
//         mx_db_get_self_response(info, peer, get, &mx_update_profile);
// }

// static void if_getting_info(t_info *info, t_peer *peer, int type, cJSON *get) {
//     if (type == get_client_contacts)
//         mx_db_get_self_response(info, peer, get, &mx_get_contact_list);
//     else if (type == get_client_chats)
//         mx_db_get_self_response(info, peer, get, &mx_get_clients_chats);
//     else if ()
// }

// static void if_contacts_chats(t_info *info, t_peer *peer, int type, cJSON *get) {
//     if (type == make_add_new_contact)
//         mx_db_get_self_response(info, peer, get, &mx_add_new_contact);
//     else if (type == make_del_contact)
//         mx_db_get_self_response(info, peer, get, &mx_del_contact);
//     else if (type == make_new_personal_chat)
//         mx_db_create_personal_chat(info, peer, type, get);
// }

void mx_response_db(t_info *info, t_peer *peer, cJSON *get) {
    // printf("%s\n", peer->recv_buff);
    int type = MX_TYPE(get);

    if (type == make_register)
        mx_db_registration(info, peer, get);  // + дописать его в канал general или нет ???
    else if (type == make_authorization)
        mx_db_authorization(info, peer, get);  // + подгрузка истории
    else if (type == make_delete_user)
        mx_db_delete(info, peer, get);

    else if (type == send_message)
        mx_db_send_message(info, peer, get);
    else if (type == edit_message || type == delete_message)
        mx_db_edit_message(info, peer, get);
    else if (type == logout) {
        mx_db_logout(info, peer, get);
    }

    else if (type == make_change_password)
        mx_db_get_self_response(info, peer, get, &mx_change_password);
    else if (type == make_update_profile)
        mx_db_get_self_response(info, peer, get, &mx_update_profile);


    else if (type == get_client_contacts)
        mx_db_get_self_response(info, peer, get, &mx_get_contact_list);
    else if (type == get_client_chats)
        mx_db_get_self_response(info, peer, get, &mx_get_clients_chats);
    else if (type == get_client_chat_messages)
        mx_db_get_self_response(info, peer, get, &mx_get_client_chat_messages);


    else if (type == make_add_new_contact)
        mx_db_get_self_response(info, peer, get, &mx_add_new_contact);
    else if (type == make_del_contact)
        mx_db_get_self_response(info, peer, get, &mx_del_contact);
    else if (type == make_new_personal_chat)
        mx_db_create_personal_chat(info, peer, get);

    else
        printf("unknown type of message\n");
}
