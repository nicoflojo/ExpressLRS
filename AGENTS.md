# ExpressLRS firmware

This is an upstream ExpressLRS checkout used by the OpenRX receiver family.
Work here only for an explicit firmware/build task. Each OpenRX board repository
under `../../hardware/OpenRX-*` owns its target definition in `firmware/`;
hardware truth remains in those repositories.

`src/hardware/` may be a separate, ignored ExpressLRS target-catalogue checkout;
it is not tracked by this repository. Inspect both Git states when that checkout
exists, follow upstream build and test instructions, and do not treat local
binaries or `user_defines.txt` as product requirements.
