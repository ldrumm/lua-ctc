# lua-ctc
constant time string comparisons for Lua.

Comparing sensitive strings in the naive (or optimized) way may give your attacker
information about the contents of the secret.

This module allows the timing safe comparison of strings.

```Lua
local constant_time_compare = require('ctc')
local passwd = 'mysecret111'
local guess = 'mysecret110'
print(("%q == %q?:"):format(passwd, guess), constant_time_compare(guess, passwd))
```

## When should I use this?

- Whenever you're verifying secret/potentially secret information for a potential
attacker. i.e. checking HMACs, password hashes, or verifying some information
where the attacker can learn how much of the string they have correct, based on
how long it takes you to check for them.

## When shouldn't I use this?

- When the above isn't true. All implementations of Lua I'm aware of do some heavy
optimizations when it comes to comparing/storing strings, so every use of this library
has a non-negligle performance hit.
- When your values aren't strings. This may sound obvious, but if your values aren't strings
they may be converted to strings at the point of call, which can do some weird stuff to generator functions.

## Caveats
1.  Interning of strings themselves at parse/read time may indeed cause the VM
    to branch the fast/slow path when strings are different which may exhibit
    timing issues before we're even at a position to test this ourselves.
2.  The Lua VM does not make any guarantees about the strings it passes to our
    C function, and due to (1), [may legally return the same pointer](http://www.lua.org/manual/5.2/manual.html#lua_tolstring).
    This could theoretically lead to the exhibition of extra subtle timing issues
    due to locality.
3.  I don't know what I'm doing.
