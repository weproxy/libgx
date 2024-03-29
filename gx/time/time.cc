//
// weproxy@foxmail.com 2022/10/03
//

#include "co/time.h"

#include "time.h"

namespace gx {
namespace time {

// // The unsigned zero year for internal calculations.
// // Must be 1 mod 400, and times before it will not compute correctly,
// // but otherwise can be changed at will.
// const int64 absoluteZeroYear = -292277022399;

// // The year of the zero Time.
// // Assumed by the unixToInternal computation below.
// const int64 internalYear = 1;

// // Offsets to convert between internal and absolute or Unix times.
// const int64 absoluteToInternal = (absoluteZeroYear - internalYear) * 365.2425 * secondsPerDay;
// const int64 internalToAbsolute = -absoluteToInternal;

// const int64 unixToInternal = (1969 * 365 + 1969 / 4 - 1969 / 100 + 1969 / 400) * secondsPerDay;
// const int64 internalToUnix = -unixToInternal;

// const int64 wallToInternal = (1884 * 365 + 1884 / 4 - 1884 / 100 + 1884 / 400) * secondsPerDay;

////////////////////////////////////////////////////////////////////////////////

// Equal ...
bool Time::Equal(const Time& t) const { return t_.tv_sec == t.t_.tv_sec && t_.tv_nsec == t.t_.tv_nsec; }

// Add ...
Time Time::Add(const Duration& d) const {
    Time t(*this);
    t.t_.tv_sec += d.Seconds();
    return t;
}

// Sub ...
Duration Time::Sub(const Time& t) const { return Duration(this->UnixNano() - t.UnixNano()); }

// String ...
string Time::String() const { return ""; }

// After reports whether the time instant t is after u.
bool Time::After(const Time& u) const {
    return t_.tv_sec > u.t_.tv_sec || (t_.tv_sec == u.t_.tv_sec && t_.tv_nsec > u.t_.tv_nsec);
}

// Before reports whether the time instant t is before u.
bool Time::Before(const Time& u) const {
    return t_.tv_sec < u.t_.tv_sec || (t_.tv_sec == u.t_.tv_sec && t_.tv_nsec < u.t_.tv_nsec);
}

////////////////////////////////////////////////////////////////////////////////
// Now ...
Time Now() {
    // struct timeval tv;
    // ::gettimeofday(&tv, 0);
    struct timespec t;
    #ifndef _WIN32
    clock_gettime(CLOCK_MONOTONIC, &t);
    #else
    int64 usec = now::us();
    t.tv_sec = usec / 1000000;
    t.tv_nsec = usec - t.tv_sec * 1000000;
    #endif
    return Time(t);
}

// AfterFunc ...
bool AfterFunc(const Time& t, const func<void()>& fn) { return false; }

// Sleep
void Sleep(const Duration& d) { sleep::ms(d.Milliseconds()); }

// Since ...
Duration Since(const Time& t) { return Now().Sub(t); }

}  // namespace time
}  // namespace gx
