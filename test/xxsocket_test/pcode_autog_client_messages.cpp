/* This file is generated by pcode_autog-1.16.6
** Copyright(c) HALX99, ALL RIGHTS RESERVED.
**
** Purpose: contains all protocol message definiations and codec function
**          implementations
**
*/
#include "pcode_autog_client_messages.h"

#include "pcode_autog_client_constants.h"

#include <unordered_map>

#include <functional>

using namespace messages;

// pcode_autog_create_header implemented by user.
extern obinarystream pcode_autog_begin_encode(uint16_t command_id);

obinarystream MsgHeader::encode(void) const
{
    obinarystream obs;

    /// encode message fields.
    obs.write_i(this->length);
    obs.write_i(this->command_id);
    obs.write_i(this->version);
    obs.write_i(this->reserved);
    obs.write_i(this->reserved2);
    return std::move(obs);
}

int MsgHeader::decode(const char* data, int len)
{
    ibinarystream ibs;
    ibs.vassign(data, len);

    ibs.read_i(this->length);
    ibs.read_i(this->command_id);
    ibs.read_i(this->version);
    ibs.read_i(this->reserved);
    ibs.read_i(this->reserved2);
    return ibs.remain();
}

std::string MsgHeader::get_formated_string(void) const
{
    std::stringstream ss;
    ss << "MsgHeader:\n";
    ss << strfmt("length", this->length << '\n', '-');
    ss << strfmt("command_id", this->command_id << '\n', '-');
    ss << strfmt("version", this->version << '\n', '-');
    ss << strfmt("reserved", this->reserved << '\n', '-');
    ss << strfmt("reserved2", this->reserved2 << '\n', '-');
    return ss.str();
}

obinarystream MsgPeerEndpointReq::encode(void) const
{
    /// create message header stream.
    auto obs = pcode_autog_begin_encode(CID_MSG_PEER_ENDPOINT_REQ);

    /// encode message fields.
    obs.write_i(this->user_id);
    return std::move(obs);
}

int MsgPeerEndpointReq::decode(const char* data, int len)
{
    ibinarystream ibs;
    ibs.vassign(data, len);

    ibs.read_i(this->user_id);
    return ibs.remain();
}

std::string MsgPeerEndpointReq::get_formated_string(void) const
{
    std::stringstream ss;
    ss << "MsgPeerEndpointReq:\n";
    ss << strfmt("user_id", this->user_id << '\n', '-');
    return ss.str();
}

int MsgPeerEndpointResp::decode(const char* data, int len)
{
    ibinarystream ibs;
    ibs.vassign(data, len);

    ibs.read_i(this->user_id);
    ibs.read_v(this->addr);
    ibs.read_i(this->port);
    return ibs.remain();
}

std::string MsgPeerEndpointResp::get_formated_string(void) const
{
    std::stringstream ss;
    ss << "MsgPeerEndpointResp:\n";
    ss << strfmt("user_id", this->user_id << '\n', '-');
    ss << strfmt("addr", this->addr << '\n', '-');
    ss << strfmt("port", this->port << '\n', '-');
    return ss.str();
}

obinarystream MsgGetFriendListReq::encode(void) const
{
    /// create message header stream.
    auto obs = pcode_autog_begin_encode(CID_MSG_GET_FRIENDLIST_REQ);

    /// encode message fields.
    obs.write_i(this->user_id);
    return std::move(obs);
}

std::string MsgGetFriendListReq::get_formated_string(void) const
{
    std::stringstream ss;
    ss << "MsgGetFriendListReq:\n";
    ss << strfmt("user_id", this->user_id << '\n', '-');
    return ss.str();
}

int MsgGetFriendListResp::decode(const char* data, int len)
{
    ibinarystream ibs;
    ibs.vassign(data, len);

    ibs.read_i(this->result);
    ibs.read_i(this->user_id);
    uint16_t friends_size; 
    ibs.read_i(friends_size);
    this->friends.resize(friends_size);
    for(uint16_t friendsindex = 0; friendsindex < friends_size; ++friendsindex)
    {
        ibs.read_i(this->friends[friendsindex].user_id);
        ibs.read_v(this->friends[friendsindex].user_name);
        ibs.read_i(this->friends[friendsindex].equip_id);
        ibs.read_i(this->friends[friendsindex].hero_id);
        ibs.read_i(this->friends[friendsindex].hero_lv);
        ibs.read_i(this->friends[friendsindex].hero_hp);
        ibs.read_i(this->friends[friendsindex].hero_mp);
    }
    return ibs.remain();
}

std::string MsgGetFriendListResp::get_formated_string(void) const
{
    std::stringstream ss;
    ss << "MsgGetFriendListResp:\n";
    ss << strfmt("result", (int)this->result << '\n', '-');
    ss << strfmt("user_id", this->user_id << '\n', '-');
    return ss.str();
}

static char s_allocp[16384]; // static alloc memory.
static std::unordered_map<int, std::function<MsgBase*(void)>> s_table_message_ctor;
MsgBase* messages::temp_create_message(int command_id)
{
    auto target = s_table_message_ctor.find(command_id);
    if(target != s_table_message_ctor.end())
        return (target->second)();
    assert(false);
    return nullptr;
}

static int internal_message_ctor_table_preinit(void)
{
    s_table_message_ctor[CID_MSG_PEER_ENDPOINT_REQ]= []()->MsgBase*{ return new(s_allocp) MsgPeerEndpointReq(); };
    s_table_message_ctor[CID_MSG_PEER_ENDPOINT_RESP]= []()->MsgBase*{ return new(s_allocp) MsgPeerEndpointResp(); };
    s_table_message_ctor[CID_MSG_GET_FRIENDLIST_REQ]= []()->MsgBase*{ return new(s_allocp) MsgGetFriendListReq(); };
    s_table_message_ctor[CID_MSG_GET_FRIENDLIST_RESP]= []()->MsgBase*{ return new(s_allocp) MsgGetFriendListResp(); };
    return 0;
}

static const int __TABLE_INIT_PLACE_HOLDER = internal_message_ctor_table_preinit();

