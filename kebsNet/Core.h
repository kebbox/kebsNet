#pragma once
#include "net_common.h"
#include "EndToEnd.h"

std::string helpMap();


uint16_t custom_converter(std::string input);

void usr_make_connection(EndToEnd& istance, std::string ip, uint16_t port);

struct stopping_flags {
	bool acceptor;

};

void usr_send_message(const std::string& message, EndToEnd& istance);

void usr_break_connection(EndToEnd& istance);

void usr_listen_connection(EndToEnd& istance, stopping_flags &flg, uint16_t port);

void stop_listening(EndToEnd& istance);

std::vector<std::string> input_tokenizer(std::string word);

void reset_flags(stopping_flags& flg);

void user_input();
