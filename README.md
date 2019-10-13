# MultiLife RGB

Renders the https://multilife.live game state to a LED RGB matrix panel connected to a Raspberry Pi

## Dependencies

* [rpi-rgb-led-matrix](https://github.com/hzeller/rpi-rgb-led-matrix)

## Building

```bash
# clone repos
cd ~
git clone https://github.com/jmercha/multilife-rgb
git clone https://github.com/hzeller/rpi-rgb-led-matrix

# build librgbmatrix
cd ~/rpi-rgb-led-matrix/lib
make
sudo cp librgbmatrix.so.1 /usr/lib

# build multilife-rgb
cd ~/multilife-rgb
make
```