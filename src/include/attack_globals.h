#pragma once

#include <memory>

#include "attack_tables.h"

namespace AttackGlobals {
    extern std::unique_ptr<AttackTables::AttackData> ad;
    // extern AttackTables::AttackData ad;
}