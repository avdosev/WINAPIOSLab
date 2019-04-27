#pragma once

enum class ServerCommand {
    count = 0,
    append,
    remove,
    update,
    compare_two_records,
    records,
    record,
    save,
    load,
    clear,
    is_modified,
    end_connection
};
