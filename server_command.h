#pragma once

enum class ServerCommand {
    count = 0,
    append,
    remove,
    update,
    compare_two_records,
    records,
    record,
    record_in_text_format,
    save,
    load,
    clear,
    is_modified,
    end_connection
};

enum class ClientCommand {
    append = 0,
    remove,
    update,
    clear,
    end_connection
};

using clientID_t = unsigned;
