#pragma once

namespace bravo { namespace chain {

class database;

void update_witness_schedule( database& db );
void reset_virtual_schedule_time( database& db );

} }
