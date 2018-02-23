
struct msg_header;
struct msg_body_presence 
struct msg_body_temperature

struct message
{
    enum type 
    {
        MT_UNKNOW = 0,
        MT_ALERT,
        MT_TEMPERATURE,
    }

    msg_header h;

    union 
    {
        msg_body_presence body_presence;
        msg_body_temperature body_temperature;
    };
};


struct msg_header
{
    message::type type;
    char[32] info;
};

struct msg_body_presence 
{
    bool presence; 
};

struct msg_body_temperature
{
    uint8_t temperature;
};


