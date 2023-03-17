// Copyright 2023 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "rw_spinlock.hpp"
#include <mutex>

// Sanity check only

static rw_spinlock sp;
static rw_spinlock sp2;

int main()
{
    sp.lock();
    sp2.lock();
    sp.unlock();
    sp2.unlock();

    {
        std::lock_guard<rw_spinlock> lock( sp );
        std::lock_guard<rw_spinlock> lock2( sp2 );
    }
}
