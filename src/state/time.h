#pragma once

namespace kfs {

/// The total number of ticks since the system booted.
extern u32 tickCountSinceBoot;

/// Sleeps for the given number of microseconds.
///
/// Note that this function *will* sleep slightly
/// more time than requested. But it is guaranteed to
/// sleep at least the requested time.
void sleep(u32 microseconds);

}
