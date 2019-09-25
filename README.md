![Toshino Kyouko embraces the Utopia, why aren't you!?](the_truth.png "Don't Own, Use Proxy")

# komuniSTL
A C++ (non-standard) template library where you do NOT OWN anything!

# Motivation

Having used Rust for a bit, I realize that the problem of ownership can be "solved" (I hope) in C++ by preventing programmers from owning at all. Hence, this library.

If you look at `komunis::vector` you will see that you cannot obtain a reference to an element in it all. If you do want to operate on it, you will have to use member functions.

At best, you will have to copy the value and give it back to the vector at some later time.

# What Have Been Implemented So Far

1. vector
2. monad

# Exceptions

I will list stuff that I did use here:

1. `std::size_t`
2. `std::iostream`
