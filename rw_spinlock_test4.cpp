// Copyright 2023 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "rw_spinlock.hpp"
#include <mutex>
#include <shared_mutex>

static rw_spinlock sp;
static rw_spinlock sp2;

int main()
{
    sp.lock();
    sp2.lock_shared();
    sp2.lock_shared();

    sp.unlock();
    sp2.unlock_shared();
    sp2.unlock_shared();

    {
        std::lock_guard<rw_spinlock> lock( sp );
        std::shared_lock<rw_spinlock> lock2( sp2 );
        std::shared_lock<rw_spinlock> lock3( sp2 );
    }
}
