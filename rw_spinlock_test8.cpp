// Copyright 2023 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "rw_spinlock.hpp"
#include <boost/core/lightweight_test.hpp>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <cstdio>

static int count = 0;
static rw_spinlock sp;

void f( int k, int m, int n )
{
    std::printf( "Thread %d of %d started.\n", k, m );

    for( int i = 0; i < n; ++i )
    {
        int oldc;

        for( ;; )
        {
            {
                std::shared_lock<rw_spinlock> lock( sp );
                oldc = count;
            }

            if( oldc % m == k ) break;
        }

        {
            std::lock_guard<rw_spinlock> lock( sp );
            if( count == oldc ) ++count;
        }
    }

    std::printf( "Thread %d of %d finished.\n", k, m );
}

int main()
{
    int const N = 100000; // total iterations
    int const M = 8;      // threads

    std::thread th[ M ];

    for( int i = 0; i < M; ++i )
    {
        th[ i ] = std::thread( f, i, M, N );
    }

    for( int i = 0; i < M; ++i )
    {
        th[ i ].join();
    }

    BOOST_TEST_EQ( count, N * M );

    return boost::report_errors();
}
