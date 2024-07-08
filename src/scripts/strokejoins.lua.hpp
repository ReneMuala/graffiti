#pragma once

namespace scripts {
    constexpr auto strokejoins = R"LUASCRIPT(
join = {
    miterclip = 0,
    miterbevel = 1,
    miterround = 2,
    bevel = 3,
    round = 4,
}
    )LUASCRIPT";
}