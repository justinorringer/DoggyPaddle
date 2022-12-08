# DoggyPaddle
Side-scrolling Gameboy Shooter

## How to play
1. Install a gb emulator
    + We used BGB: https://bgb.bircd.org/#downloads and run it with wine on fedora: https://wiki.winehq.org/Download
2. Download a release: [releases](https://github.com/justinorringer/DoggyPaddle/releases)
3. Load the `DoggyPaddle.gb` file into your emulator and play 🤠
    + if using wine + bgb, cli command looks like this: `wine bgb.exe DoggyPaddle.gb`

## Building yourself
If you want to make changes and test yourself:
1. Install gbdk: https://github.com/gbdk-2020/gbdk-2020/releases
2. In your shell environment, set the env variable `GBDK_HOME` to where you installed gbdk
    + ex, if you installed gbdk to `/usr/local/bin`: `export GBDK_HOME=/usr/local/bin/gbdk`
4. After cloning repo and making your changes, run `make` from the root of the repo
    + as an alternative to step 2, you can pass a variable to the call to `make` like so: `make GBDK_HOME=/usr/local/bin/gbdk`
6. Follow instructions above to run the resulting `.gb` file


Developed by [Justin](https://github.com/justinorringer) and [Daniel](https://github.com/dagbay-rh)
