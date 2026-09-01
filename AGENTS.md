# ExpressLRS firmware

This is an upstream ExpressLRS checkout used by OpenRX. Work here only for an
explicit firmware/build task. OpenDrone receiver target definitions are owned
by `../../hardware/OpenRX/shared/elrs-targets/`; hardware truth remains in that
repository.

`src/hardware/` may be a separate, ignored ExpressLRS target-catalogue checkout;
it is not tracked by this repository. Inspect both Git states when that checkout
exists, follow upstream build and test instructions, and do not treat local
binaries or `user_defines.txt` as product requirements.
